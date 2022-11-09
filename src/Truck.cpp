// Libraries
// Header files
#include "../headers/Constants.h"
#include "../headers/Truck.h"

const float Truck::speedMax = constants::speedMaxTruck;
const float Truck::acceleration = constants::accelerationTruck;
const float Truck::color[3] = {0.7, 0.7, 0}; // Yellow

const float Truck::getSpeedMax() {
   return speedMax;
}

const float Truck::getAcceleration() {
   return acceleration;
}

const float* Truck::getColor() {
   return color;
}
