// Libraries
// Header files
#include "../headers/Constants.h"
#include "../headers/Truck.h"

const float Truck::speedMax     = constants::speedMaxTruck;
const float Truck::acceleration = constants::accelerationTruck;
const float Truck::width        = constants::widthTruck;
const float Truck::height       = constants::heightTruck;
const float Truck::color[3] = {0.0, 0.0, 0.9}; // Dark blue

const float Truck::getSpeedMax() {
   return speedMax;
}

const float Truck::getAcceleration() {
   return acceleration;
}

const float Truck::getWidth() {
   return width;
}

const float Truck::getHeight() {
   return height;
}

const float* Truck::getColor() {
   return color;
}
