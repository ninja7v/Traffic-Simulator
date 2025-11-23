// Libraries
#include <GLFW/glfw3.h> // To display
#include <time.h>       // To use clock()
// Header files
#include "../headers/Constants.h"
#include "../headers/Global.h"
#include "../headers/Intersection.h"

Intersection::Intersection(const int n = 0, const std::vector<double> pos = { 0.0, 0.0 })
   : idIntersection(n), position(pos),
     coordinates{ position[0] * constants::ratioX + constants::margin,
                  position[1] * constants::ratioY + constants::margin } {
}

//Intersection::~Intersection(){}

const bool Intersection::isRed(const int id) const {
   const int currentPeriod = ((clock() - global::t0) / constants::period);
   return input[currentPeriod % input.size()] != id;
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

void Intersection::addInputRoad(const int id) {
   input.push_back(id);
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
