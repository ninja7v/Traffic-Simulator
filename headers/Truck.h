#pragma once
// Libraries
// Header files
#include "Vehicle.h"

class Truck : public Vehicle {
public:
   using Vehicle::Vehicle;
   const float  getSpeedMax();
   const float  getAcceleration();
   const float* getColor();
protected:

private:
   static const float speedMax, acceleration, color[3];
};
