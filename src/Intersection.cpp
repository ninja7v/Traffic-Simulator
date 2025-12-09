// Libraries
#include <GLFW/glfw3.h> // To display
#include <ctime>        // To use clock() and clock_t
#include <numeric>      // To use accumulate
#include <memory>       // To use smart pointers
// Headers
#include "../headers/Constants.h"
#include "../headers/Global.h"
#include "../headers/Intersection.h"
#include "../headers/Road.h"
#include "../headers/QLearningOperator.h"
#include "../headers/DeepRLOperator.h"

Intersection::Intersection(const int n,
                           const std::vector<double> pos,
                           std::shared_ptr<IntersectionOperator> op)
   : idIntersection(n),
     position(pos),
     coordinates{ position[0] * constants::ratioX + constants::margin,
                  position[1] * constants::ratioY + constants::margin },
     op(op),
     currentGreenRoadIndex(0),
     lastAction(0),
     lastSwitchTime(clock()) {
}

const bool Intersection::isRed(const int id) const {
   return input.at(currentGreenRoadIndex) != id;
}

void Intersection::displayIntersection() const {
   glPointSize(constants::diameterIntersection);
   glColor3d(0.0, 0.0, 0.0); // Black
   glEnable(GL_POINT_SMOOTH);
   glBegin(GL_POINTS);
   glVertex2d(coordinates[0], coordinates[1]);
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

const int Intersection::getNumberInputRoads() const {
   return static_cast<int>(inputRoads.size());
}

bool Intersection::operator==(const Intersection i) {
   return idIntersection == i.idIntersection;
}

void Intersection::update() {
    if (inputRoads.empty()) return;

    // 1. Construct State
    // State: [currentGreenIndex, road0_occ, road0_speed, road0_usage, ..., roadN_occ, roadN_speed, roadN_usage]
    // Standardized to stateSize
    std::vector<int> state(constants::stateSize, 0); // Initialize with 0 (padding)
    state.push_back(currentGreenRoadIndex);

    const int totalNumberOfArrivingVehicle = std::accumulate(
        inputRoads.begin(), inputRoads.end(), 0,
        [](int sum, const Road* r) { return sum + r->getTotalNumberOfArringVehicles(); }
    );
    const double averageNewVehicles = static_cast<double>(totalNumberOfArrivingVehicle) / static_cast<double>(inputRoads.size());
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
            const double timeOnRoad = static_cast<double>(clock() - v->getEnterRoadTime()) / static_cast<double>(CLOCKS_PER_SEC); // in seconds
            const double dist = v->distance(r->getStart());
            const double ideal = dist / v->getSpeedMax();
            const double diff = std::max(timeOnRoad - ideal, 0.0); // safety
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
    const double timeSinceSwitch = static_cast<double>(now - lastSwitchTime) / static_cast<double>(CLOCKS_PER_SEC); // in seconds
    if (timeSinceSwitch > constants::trafficLightPeriod) {
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
