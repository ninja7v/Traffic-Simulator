// Libraries
#include <GLFW/glfw3.h> // To display
#include <ctime>        // To use clock() and clock_t
#include <numeric>      // To use accumulate
//#include <tuple>
//#include <cmath>
// Headers
#include "../headers/Constants.h"
#include "../headers/Global.h"
#include "../headers/Intersection.h"
#include "../headers/Road.h"

#include "../headers/QLearningOperator.h"
#include "../headers/DeepRLOperator.h"

Intersection::Intersection(const int n, const std::vector<double> pos, const std::string& agentType)
   : idIntersection(n),
     position(pos),
     coordinates{ position[0] * constants::ratioX + constants::margin,
                  position[1] * constants::ratioY + constants::margin },
     currentGreenRoadIndex(0),
     lastAction(0),
     lastSwitchTime(clock()) {
     
     if (agentType == "DeepRL") {
         op = new DeepRLOperator();
     } else {
         op = new QLearningOperator();
     }
}

//Intersection::~Intersection(){}

const bool Intersection::isRed(const int id) const {
   return input.at(currentGreenRoadIndex) != id;
}

void Intersection::displayIntersection() const {
   glPointSize(constants::diameterIntersection);
   glColor3f(0.0f, 0.0f, 0.0f); // Black
   glEnable(GL_POINT_SMOOTH);
   glBegin(GL_POINTS);
   glVertex2f(static_cast<float>(coordinates[0]), static_cast<float>(coordinates[1]));
   glEnd();
   glDisable(GL_POINT_SMOOTH);
}

void Intersection::addInputRoad(Road* r) {
   if (r) {
       input.push_back(r->getID());
       inputRoads.push_back(r);
   }
}

const int Intersection::getID() const {
   return idIntersection;
}

const std::vector<double> Intersection::getPosition() const {
   return position;
}

bool Intersection::operator==(const Intersection i) {
   return idIntersection == i.idIntersection;
}

void Intersection::update() {
    if (inputRoads.empty()) return;

    // 1. Construct State
    // State: [currentGreenIndex, road0_occ, road0_speed, road0_usage, ..., roadN_occ, roadN_speed, roadN_usage]
    std::vector<int> state;
    state.push_back(currentGreenRoadIndex);

    int totalNumberOfArrivingVehicle = std::accumulate(
        inputRoads.begin(), inputRoads.end(), 0,
        [](int sum, const Road* r) { return sum + r->getTotalNumberOfArringVehicles(); }
    );
    const double averageNewVehicles = (double)totalNumberOfArrivingVehicle / (double)inputRoads.size();
    for (const Road* r : inputRoads) {
        auto stats = r->getVehicleStats(averageNewVehicles);
        state.push_back(std::get<0>(stats)); // Occupancy
        state.push_back(std::get<1>(stats)); // Speed
        state.push_back(std::get<2>(stats)); // Usage
    }

    // 2. Calculate Reward (from previous action)
    // Reward = -sum((actual_time - ideal_time)^penalty)
    double reward = 0.0;
    constexpr double penaltyCoeff = 2.0; // Configurable
    for (const Road* r : inputRoads) {
        for (const auto& v : r->getVehicles()) {
            const double timeOnRoad = (double)(clock() - v->getEnterRoadTime()) / CLOCKS_PER_SEC;
            const double dist = v->distance(r->getStart());
            const double ideal = dist / v->getSpeedMax();
            double diff = timeOnRoad - ideal;
            if (diff < 0) diff = 0; // Should not happen

            reward -= pow(diff, penaltyCoeff);
        }
    }

    // 3. Learn
    // Available actions: 0 to inputRoads.size()-1
    std::vector<int> availableActions;
    for (size_t i = 0; i < inputRoads.size(); ++i) {
        availableActions.push_back(static_cast<int>(i));
    }

    if (!lastState.empty()) {
        op->learn(lastState, lastAction, reward, state, availableActions);
    }

    // 4. Decide
    const clock_t now = clock();
    const double timeSinceSwitch = (double)(now - lastSwitchTime) / CLOCKS_PER_SEC;
    if (timeSinceSwitch > 0.5) { // Minimum 0.5 seconds green
        const int action = op->decide(state, availableActions);
        
        if (action != -1) {
            currentGreenRoadIndex = action;
            lastAction = action;
            lastState = state;
            lastSwitchTime = now;
        }
    } else {
        // TODO: learning continuity?
    }
}
