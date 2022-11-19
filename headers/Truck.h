#pragma once
// Libraries
// Header files
#include "Vehicle.h"

class Truck : public Vehicle {
public:
   using Vehicle::Vehicle;
   const float  getSpeedMax();
   const float  getAcceleration();
   const float  getWidth();
   const float  getHeight();
   const float* getColor();
protected:

private:
   static const float speedMax, acceleration, width, height, color[3];
};
