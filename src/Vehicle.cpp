// Libraries
//#include <array>     // To use arrays // already included in vehicle.h
//#include <list>      // To use lists // already included in vehicle.h
#include <GL/glut.h> // To display
#include <iostream>  // To debug
//#include <algorithm>  // To use max // already included in Constants.h
// Header files
#include "../headers/Constants.h"
#include "../headers/Vehicle.h"

Vehicle::Vehicle(Intersection* i1, Intersection* i2, const int id, Intersection* target, const std::list<Road*> track)
   : idVehicle(id), destination(target), itinerary(track) {
   if (i1)
      position = i1->getPosition();
   setDirection(i2);
   isArrived = false;
   isBraking = false;
   speed = 0.0; // Unit is pixel per seconds
}

Vehicle::~Vehicle(){}

double Vehicle::breakingSpeed(const double d) {
   //// Breaking speed function choice:
   // - Constant (order 1 -> not smoth)
   //return constants::speedMax;
   // - Sigmoid (warning: f(0) != 0)
   //return this->getSpeedMax() / (1.0 + exp(-d + 2*constants::distanceSecurity));
   // - Underwood
   //return constants::speedMax * (1.0 - exp(-pow(d - constants::distanceSecurity, 2.0)));
   // - Squared
   return getSpeedMax() * pow(d, 2) / (pow(d, 2) + 5.0 * constants::distanceSecurity);
}

void Vehicle::moveToVehicle(const std::shared_ptr<Vehicle> v) {
   if (v)
   {
      const double previousSpeed = speed;
      // Distance with the intersection ahead
      const double d = distance(v);
      // Update speed
      if (d < constants::distanceSecurity)
         speed = 0.0; // Pound!
      else
         speed = (speed < breakingSpeed(d)) ? speed + getAcceleration() : (speed + breakingSpeed(d)) / 2.0;
      // Move
      position[0] += direction[0] * speed;
      position[1] += direction[1] * speed;
      // Braking ?
      isBraking = previousSpeed > speed;
   }
}

void Vehicle::moveToIntersection(Intersection* i, const int idRoad) {
   if (i)
   {
      const double previousSpeed = speed;
      // Distance with the intersection ahead
      const double d = distance(i);
      // Update speed
      if (i->isRed(idRoad))
         if (d < constants::distanceSecurity)
            speed = 0.0; // Pound!
         else
            speed = (speed < breakingSpeed(d)) ? speed + getAcceleration() : (speed + breakingSpeed(d)) / 2.0;
      else
         speed = (speed < getSpeedMax()) ? speed + getAcceleration() : getSpeedMax();
      // To add: case where next road is full
      // Move
      const double s = speed;
      try {
         position[0] += direction[0] * s;
         position[1] += direction[1] * s;
         if (distance(i) > d)
            throw position;
      }
      catch (std::array<double, 2> pos) {
         std::cout << "The vehicle is escaping!" << std::endl;
         exit(-1);
      }
      // Braking ?
      isBraking = previousSpeed > speed;
   }
}

void Vehicle::updateItinerary() {
   if (!itinerary.empty()) {
      itinerary.pop_front();
   }
}

void Vehicle::displayVehicle() {
   const double W = getWidth();
   const double H = getHeight();
   const double center[2] = { direction[1] * constants::widthRoad / 2 + position[0] * constants::ratioX + constants::margin,
                             -direction[0] * constants::widthRoad / 2 + position[1] * constants::ratioY + constants::margin };
   // Body
   const double frame[4][2] = { {center[0] - direction[0] * H - direction[1] * W,
                                 center[1] + direction[0] * W - direction[1] * H},
                                {center[0] - direction[0] * H + direction[1] * W,
                                 center[1] - direction[0] * W - direction[1] * H},
                                {center[0] + direction[0] * H + direction[1] * W,
                                 center[1] - direction[0] * W + direction[1] * H},
                                {center[0] + direction[0] * H - direction[1] * W,
                                 center[1] + direction[0] * W + direction[1] * H}, };
   const double* color = getColor();
   if (color)
      glColor3f(static_cast<float>(color[0]), static_cast<float>(color[1]), static_cast<float>(color[2]));
   glBegin(GL_QUADS);
   glEnableClientState(GL_VERTEX_ARRAY);
   for (int i = 0; i < 4; ++i) {
      glVertex2f(static_cast<float>(frame[i][0]) , static_cast<float>(frame[i][1]));
   }
   glEnd();
   // Lights
   glPointSize(constants::diameterHeadlight);
   glEnable(GL_POINT_SMOOTH);
   glBegin(GL_POINTS);
   glColor3f(1.0f, 1.0f, 0.0f); // Yellow
   if (is2Wheeler()) {
      const double front[2] = { center[0] + direction[0] * H,
                                center[1] + direction[1] * H };
      glVertex2f(static_cast<float>(front[0]), static_cast<float>(front[1]));
   }
   else {
      const double front[2][2] = { {center[0] + direction[0] * H + direction[1] * W,
                                    center[1] - direction[0] * W + direction[1] * H},
                                   {center[0] + direction[0] * H - direction[1] * W,
                                    center[1] + direction[0] * W + direction[1] * H}, };
      glVertex2f(static_cast<float>(front[0][0]), static_cast<float>(front[0][1]));
      glVertex2f(static_cast<float>(front[1][0]), static_cast<float>(front[1][1]));
   }
   if (isBraking)
      glColor3f(1.0f, 0.0f, 0.0f); // Red
   else
      glColor3f(0.5f, 0.0f, 0.0f); // Dark Red
   if (is2Wheeler()) {
      const double rear[2] = {center[0] - direction[0] * H ,
                              center[1] - direction[1] * H};
      glVertex2f(static_cast<float>(rear[0]), static_cast<float>(rear[1]));
   }
   else {
      const double rear[2][2] = { {center[0] - direction[0] * H - direction[1] * W,
                                   center[1] + direction[0] * W - direction[1] * H},
                                  {center[0] - direction[0] * H + direction[1] * W,
                                   center[1] - direction[0] * W - direction[1] * H}, };
      glVertex2f(static_cast<float>(rear[0][0]), static_cast<float>(rear[0][1]));
      glVertex2f(static_cast<float>(rear[1][0]), static_cast<float>(rear[1][1]));
   }
   glEnd();
   glDisable(GL_POINT_SMOOTH);
}

Road* Vehicle::nextRoad() {
   return (itinerary.empty()) ? nullptr : itinerary.front();
}

const double Vehicle::distance(const std::shared_ptr<Vehicle> v) {
   return v ? std::max(sqrt(pow(position[0] - v->position[0], 2) + pow(position[1] - v->position[1], 2)) - (this->getHeight() + v->getHeight()) / 7.0, 0.0) :
              0.0;
}

const double Vehicle::distance(Intersection* i) {
   return i ? std::max(sqrt(pow(position[0] - i->getPosition()[0], 2) + pow(position[1] - i->getPosition()[1], 2)) - (this->getHeight() + constants::diameterIntersection) / 12.0, 0.0) :
              0.0;
}

const int Vehicle::getID() const {
   return idVehicle;
}

bool Vehicle::getStatus() const {
   return isArrived;
}

double Vehicle::getSpeed() const {
   return speed;
}

Intersection* Vehicle::getDestination() const {
   return destination;
}

std::list<Road*> Vehicle::getItinerary() const {
   return itinerary;
}

std::vector<double> Vehicle::getPosition() const {
   return position;
}

void Vehicle::setDirection(Intersection* i) {
   if (i)
   {
      // We don't take the direction from road to avoid circular dependencies
      try{
         double d = sqrt(pow((i->getPosition()[0] - position[0]), 2) + pow((i->getPosition()[1] - position[1]), 2));
         if (d == 0.0)
            throw  std::runtime_error("Division by zero");
         direction = { (i->getPosition()[0] - position[0]) / d,
                       (i->getPosition()[1] - position[1]) / d };
      }
      catch (const std::runtime_error& e) {
         std::cerr << e.what() << std::endl;
         exit(-1);
      }
   }
}

void Vehicle::setPosition(const std::vector<double> pos) {
   position = pos;
}

void Vehicle::setNewItinerary(std::list<Road*> track) {
   itinerary = track;
}

void Vehicle::setStatus(const bool arrived) {
   isArrived = arrived;
}
