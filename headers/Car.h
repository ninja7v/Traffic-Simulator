#pragma once
// Libraries
#include <array>     // To use arrays
// Header files
#include "Vehicle.h"

class Car : public Vehicle {
public:
   using Vehicle::Vehicle;
   const float Car::getSpeedMax();
   const float Car::getAcceleration();
   const float* Car::getColor();
protected:

private:
   static const float speedMax;
   static const float acceleration;
   static const float color[3];
};
