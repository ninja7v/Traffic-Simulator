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

Vehicle::~Vehicle(){}

float Vehicle::breakingSpeed(const float d) {
   // Breaking speed function choice:
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

void Vehicle::moveToIntersection(Intersection* i, const int idRoad) {
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
   const float s = speed * 17; // 17 = average frame time in ms (clock() - tc);
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
   const float center[2] = { direction[1] * constants::widthRoad / 2 + position[0] * constants::ratioX + constants::margin,
                            -direction[0] * constants::widthRoad / 2 + position[1] * constants::ratioY + constants::margin };
   // Body
   const float frame[4][2] = { {center[0] - direction[0] * H - direction[1] * W,
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
   // Lights
   if (is2Wheeler()) {
      const float front[2] = {center[0] + direction[0] * H,
                              center[1] + direction[1] * H};
      const float rear[2]  = {center[0] - direction[0] * H ,
                              center[1] - direction[1] * H};
      glPointSize(constants::diameterHeadlight);
      glEnable(GL_POINT_SMOOTH);
      glBegin(GL_POINTS);
      glColor3f(1.0f, 0.8f, 0.6f); // Yellow
      glVertex2f(front[0], front[1]);
      glColor3f(1.0f, 0.0f, 0.0f); // Red
      glVertex2f(rear[0], rear[1]);
      glEnd();
      glDisable(GL_POINT_SMOOTH);
   }
   else {
      const float front[2][2] = { {center[0] + direction[0] * H + direction[1] * W,
                                   center[1] - direction[0] * W + direction[1] * H},
                                  {center[0] + direction[0] * H - direction[1] * W,
                                   center[1] + direction[0] * W + direction[1] * H}, };
      const float rear[2][2]  = { {center[0] - direction[0] * H - direction[1] * W,
                                   center[1] + direction[0] * W - direction[1] * H},
                                  {center[0] - direction[0] * H + direction[1] * W,
                                   center[1] - direction[0] * W - direction[1] * H}, };
      glPointSize(constants::diameterHeadlight);
      glEnable(GL_POINT_SMOOTH);
      glBegin(GL_POINTS);
      glColor3f(1.0f, 0.8f, 0.6f); // Yellow
      glVertex2f(front[0][0], front[0][1]);
      glVertex2f(front[1][0], front[1][1]);
      glColor3f(1.0f, 0.0f, 0.0f); // Red
      glVertex2f(rear[0][0], rear[0][1]);
      glVertex2f(rear[1][0], rear[1][1]);
      glEnd();
      glDisable(GL_POINT_SMOOTH);
   }
}

Road* Vehicle::nextRoad() {
   return (itinerary.empty()) ? nullptr : itinerary.front();
}

const float Vehicle::distance(Vehicle* v) {
   return std::max(sqrt(pow(position[0] - v->position[0], 2) + pow(position[1] - v->position[1], 2)) - (this->getHeight() + v->getHeight()) / 15, 0.0);
}

const float Vehicle::distance(Intersection* i) {
   // this->getHeight() gives an abort, so we don't take it into the computation
   return std::max(sqrt(pow(position[0] - i->getPosition()[0], 2) + pow(position[1] - i->getPosition()[1], 2)) - constants::diameterIntersection / 15, 0.0);
}

const int Vehicle::getID() const {
   return idVehicle;
}

bool Vehicle::getStatus() const {
   return isArrived;
}

float Vehicle::getSpeed() const {
   return speed;
}

Intersection* Vehicle::getDestination() const {
   return destination;
}

std::list<Road*> Vehicle::getItinerary() const {
   return itinerary;
}

std::vector<float> Vehicle::getPosition() const {
   return position;
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

void Vehicle::setPosition(const std::vector<float> pos) {
   position = pos;
}

void Vehicle::setStatus(const bool arrived) {
   isArrived = arrived;
}
