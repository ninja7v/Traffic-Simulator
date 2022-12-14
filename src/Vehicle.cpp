// Libraries
//#include <array>     // To use arrays // already included in vehicle.h
//#include <list>      // To use lists // already included in vehicle.h
#include <GL/glut.h> // To display
#include <time.h>    // To use clock()
#include <iostream>  // To debug
//#include <algorithm>  // To use max // already included in Constants.h
// Header files
#include "../headers/Constants.h"
#include "../headers/Vehicle.h"

Vehicle::Vehicle(Intersection* i1, Intersection* i2, int id, Intersection* target, std::list<Road*> track)
   : idVehicle(id), destination(target), itinerary(track) {
   position = i1->getPosition();
   setDirection(i2);
   speed = 0.0f; // Unit is pixel per seconds
}

float Vehicle::breakingSpeed(float d) {
   // Choose breaking speed function
   // - Constant (order 1 -> not smoth)
   //return constants::speedMax;
   // - Sigmoid (warning: f(0) != 0)
   //return this->getSpeedMax() / (1 + exp(-d + 2*constants::distanceSecurity));
   // - Underwood
   //return constants::speedMax * (1 - exp(-pow(d - constants::distanceSecurity, 2.0)));
   // - Squared
   return getSpeedMax() * pow(d, 2) / (pow(d, 2) + 5 * constants::distanceSecurity);
}

void Vehicle::moveToVehicle(Vehicle* v) {
   // Distance with the intersection ahead
   const float d = distance(v);
   // Update speed
   if (d < constants::distanceSecurity)
      speed = 0; // Pound!
   else
      speed = (speed < breakingSpeed(d)) ? speed + getAcceleration() : (speed + breakingSpeed(d)) / 2;
   // Move
   const float s = speed * 17; // 17 = average time frame in ms (clock() - tc);
   position[0] += direction[0] * s;
   position[1] += direction[1] * s;
   //tc = clock();
}

void Vehicle::moveToIntersection(Intersection* i, int idRoad) {
   // Distance with the intersection ahead
   const float d = distance(i);
   // Update speed
   if (i->isRed(idRoad))
      if (d < constants::distanceSecurity)
         speed = 0; // Pound!
      else
         speed = (speed < breakingSpeed(d)) ? speed + getAcceleration() : (speed + breakingSpeed(d)) / 2;
   else
      speed = (speed < getSpeedMax()) ? speed + getAcceleration() : getSpeedMax();
   // To add: case where next road is full
   // Move
   const float s = speed * 17; // 17 = average time frame in ms (clock() - tc);
   try {
      position[0] += direction[0] * s;
      position[1] += direction[1] * s;
      if (distance(i) > d)
         throw position;
   }
   catch (std::array<float, 2> pos) {
#if DEBUG
      std::cout << "The vehicle is escaping!" << std::endl;
#endif
      exit(-1);
   }
   //tc = clock();
}

void Vehicle::updateItinerary() {
   if (!itinerary.empty()) {
      itinerary.pop_front();
   }
}

void Vehicle::displayVehicle() {
   const float W = getWidth();
   const float H = getHeight();
   float center[2] = { direction[1] * constants::widthRoad / 2 + position[0] * constants::ratioX + constants::margin,
                      -direction[0] * constants::widthRoad / 2 + position[1] * constants::ratioY + constants::margin };
   float frame[4][2] = { {center[0] - direction[0] * H - direction[1] * W,
                          center[1] + direction[0] * W - direction[1] * H},
                         {center[0] - direction[0] * H + direction[1] * W,
                          center[1] - direction[0] * W - direction[1] * H},
                         {center[0] + direction[0] * H + direction[1] * W,
                          center[1] - direction[0] * W + direction[1] * H},
                         {center[0] + direction[0] * H - direction[1] * W,
                          center[1] + direction[0] * W + direction[1] * H}, };
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
}

Road* Vehicle::nextRoad() {
   return (itinerary.empty()) ? nullptr : itinerary.front();
}

float Vehicle::distance(Vehicle* v) {
   return std::max(pow(pow(position[0] - v->position[0], 2) + pow(position[1] - v->position[1], 2), 0.5) - (this->getHeight() + v->getHeight()) / 15, 0.0);
}

float Vehicle::distance(Intersection* i) {
   // this->getHeight() gives an abort, so we don't take it into the computation
   return std::max(pow(pow(position[0] - i->getPosition()[0], 2) + pow(position[1] - i->getPosition()[1], 2), 0.5) - constants::diameterIntersection / 15, 0.0);
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

void Vehicle::setDirection(Intersection* i) {
   // We don't take the direction from road to avoid circular dependencies
   try{
      float d = distance(i);
      if (d == 0)
         throw d;
      direction = { (i->getPosition()[0] - position[0]) / d,
                    (i->getPosition()[1] - position[1]) / d };
   }
   catch (float d) {
#if DEBUG
      std::cerr << "division by 0" << std::endl;
#endif
      exit(-1);
   }
}
