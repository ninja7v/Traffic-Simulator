// Libraries
#include <string>       // To use to_string()
#include <GL/glut.h>    // To display (glutBitmapCharacter())
#include <GLFW/glfw3.h> // To display
#include <time.h>       // To use clock()
// Header files
#include "../headers/Constants.h"
#include "../headers/Global.h"
#include "../headers/Intersection.h"

Intersection::Intersection(int n = 0, std::vector<float> pos = { 0, 0 })
   :idIntersection(n), position(pos),
    coordinates{ position[0] * constants::ratioX + constants::margin,
                 position[1] * constants::ratioY + constants::margin } {
}

//Intersection::~Intersection(){}

const bool Intersection::isRed(int id) {
   const int currentPeriod = ((clock() - global::t0) / constants::period);
   return (input[currentPeriod % input.size()] == id) ? false : true;
}

void Intersection::displayIntersection() {
   glPointSize(constants::diameterIntersection);
   glColor3f(0.0f, 0.0f, 0.0f); // Black
   glEnable(GL_POINT_SMOOTH);
   glBegin(GL_POINTS);
   glVertex2f(coordinates[0], coordinates[1]);
   glEnd();
   glDisable(GL_POINT_SMOOTH);
}

void Intersection::addInputRoad(const int id) {
   input.push_back(id);
}

const int Intersection::getID() {
   return idIntersection;
}

const std::vector<float> Intersection::getPosition() {
   return position;
}

bool Intersection::operator==(const Intersection i) {
   return idIntersection == i.idIntersection ? true : false;
}
