#pragma once
// Libraries
// Header files
#include "Vehicle.h"

class Car : public Vehicle {
public:
   using Vehicle::Vehicle;
   const float  Car::getSpeedMax();
   const float  Car::getAcceleration();
   const float* Car::getColor();
protected:

private:
   static const float speedMax, acceleration, color[3];
};
