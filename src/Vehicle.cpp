// Libraries
#include <list>      // To use lists
#include <cstdlib>   // To use rand()
#include <iostream>  // To use input/output
#include <GL/glut.h> // To display
#include <time.h>    // To use clock()
#include <array>     // To use arrays
// Header files
#include "../headers/Constants.h"
#include "../headers/Vehicle.h"

Vehicle::Vehicle(Intersection* i1, Intersection* i2, int id, Intersection* target, std::list<Road*> track)
   : idVehicle(id), destination(target), itinerary(track) {
   position = i1->getPosition();
   updateDirection(i2);
   speed = 0.0f; // Unit is pixel per seconds
}

float Vehicle::phi(bool red) {
   return (red) ? 0 : 1.0f;
}

float Vehicle::speedFunction(float dist) {
   // Constant
   //return constants::speedMax;
   // Simple
   //return constants::speedMax - (constants::coefficient / dist);
   // Greenshield
   return getSpeedMax() * (1 - (float)pow(constants::distanceSecurity / dist, 2.0));
   // Underwood
   //return constants::speedMax * (1 - exp(-pow(dist - constants::distanceSecurity, 2.0)));
}

void Vehicle::moveToVehicle(Vehicle* v) {
   // Distance with the car ahead
   float d = distance(v);
   // Updating speed
   if (d < constants::distanceSecurity) {
      speed = 0; // Pound!
   }
   else {
      speed = (speed < speedFunction(d)) ? speed + getAcceleration() : speedFunction(d);
   }
   // Moving
   float coef = speed * (clock() - tc) / 1;
   position[0] += direction[0] * coef;
   position[1] += direction[1] * coef;
   tc = clock();
}

void Vehicle::moveToIntersection(Intersection* i, int idRoad) {
   // Taking traffic light information
   bool isRed = i->isRed(idRoad) ? true : false;
   // Distance with the intersection ahead
   float d = distance(i);
   // Updating speed
   if (isRed) {
      if (d < constants::distanceSecurity) {
         speed = (speed < speedFunction(d)) ? speed + getAcceleration() : getSpeedMax();
      }
      else {
         speed = (speed < speedFunction(d)) ? speed + getAcceleration() : speedFunction(d);
      }
   }
   else {
      speed = (speed < getSpeedMax()) ? speed + getAcceleration() : getSpeedMax();
   }
   // Moving
   float coef = speed * (clock() - tc) / 1;
   position[0] += direction[0] * coef;
   position[1] += direction[1] * coef;
   tc = clock();
}

Road* Vehicle::nextRoad() {
   return (itinerary.empty()) ? nullptr : itinerary.front();
}

void Vehicle::updateDirection(Intersection* i) {
   float d = distance(i);
   direction = { (i->getPosition()[0] - position[0]) / d,
                 (i->getPosition()[1] - position[1]) / d };
}

void Vehicle::updateItinerary() {
   if (!itinerary.empty()) {
      itinerary.pop_front();
   }
}

void Vehicle::displayVehicle() {
   float size = 15;
   float frame[4][2] = { {direction[1] * constants::width / 2 + (-direction[0] - direction[1] / 2) * size + position[0] * constants::ratioX + constants::margin,
                         -direction[0] * constants::width / 2 + (+direction[0] / 2 - direction[1]) * size + position[1] * constants::ratioY + constants::margin},
                         {direction[1] * constants::width / 2 + (-direction[0] + direction[1] / 2) * size + position[0] * constants::ratioX + constants::margin,
                         -direction[0] * constants::width / 2 + (-direction[0] / 2 - direction[1]) * size + position[1] * constants::ratioY + constants::margin},
                         {direction[1] * constants::width / 2 + (+direction[0] + direction[1] / 2) * size + position[0] * constants::ratioX + constants::margin,
                         -direction[0] * constants::width / 2 + (-direction[0] / 2 + direction[1]) * size + position[1] * constants::ratioY + constants::margin},
                         {direction[1] * constants::width / 2 + (+direction[0] - direction[1] / 2) * size + position[0] * constants::ratioX + constants::margin,
                         -direction[0] * constants::width / 2 + (+direction[0] / 2 + direction[1]) * size + position[1] * constants::ratioY + constants::margin}, };
   const float* color = getColor();
   glColor3f(color[0], color[1], color[2]);
   glBegin(GL_QUADS);
   glEnableClientState(GL_VERTEX_ARRAY);
   glVertex2f(frame[0][0], frame[0][1]);
   glVertex2f(frame[1][0], frame[1][1]);
   glVertex2f(frame[2][0], frame[2][1]);
   glVertex2f(frame[3][0], frame[3][1]);
   glEnd();
   glFlush();
   glDrawArrays(GL_QUADS, 0, 1);
   glEnableClientState(GL_VERTEX_ARRAY);
   /*GLfloat point[] = { posX * constants::ratioX, posY * constants::ratioY };
   glPointSize(15);
   glColor3f(0.0f, 0.0f, 0.5f);
   glVertexPointer(2, GL_FLOAT, 0, point);
   glDrawArrays(GL_POINTS, 0, 1);*/
}

float Vehicle::distance(Vehicle* v) {
   return pow(pow(position[0] - v->position[0], 2) + pow(position[1] - v->position[1], 2), 0.5);
}

float Vehicle::distance(Intersection* i) {
   return pow(pow(position[0] - i->getPosition()[0], 2) + pow(position[1] - i->getPosition()[1], 2), 0.5);
}

int Vehicle::getID() {
   return idVehicle;
}

bool Vehicle::getStatus() {
   return isArrived;
}

float Vehicle::getSpeed() {
   return speed;
}

Intersection* Vehicle::getDestination() {
   return destination;
}

std::list<Road*> Vehicle::getItinerary() {
   return itinerary;
}

std::array<float, 2> Vehicle::getPosition() {
   return position;
}

void Vehicle::setStatus(bool arrived) {
   isArrived = arrived;
}

void Vehicle::setPosition(std::array<float, 2> pos) {
   position = pos;
}
