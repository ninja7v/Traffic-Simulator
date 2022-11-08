#pragma once
// Libraries
#include <array>     // To use arrays
// Header files
#include "Vehicle.h"

class Truck : public Vehicle {
public:
   using Vehicle::Vehicle;
   const float getSpeedMax();
   const float getAcceleration();
   const float* getColor();
protected:

private:
   static const float speedMax;
   static const float acceleration;
   static const float color[3];
};
