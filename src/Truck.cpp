// Libraries
// Header files
#include "../headers/Constants.h"
#include "../headers/Truck.h"

const float Truck::speedMax     = constants::speedMaxTruck;
const float Truck::acceleration = constants::accelerationTruck;
const float Truck::width        = constants::widthTruck;
const float Truck::height       = constants::heightTruck;
const float Truck::color[3] = {0.0, 0.0, 0.9}; // Dark blue
const bool  Truck::type = false;

const float Truck::getSpeedMax() const {
   return speedMax;
}

const float Truck::getAcceleration() const {
   return acceleration;
}

const float Truck::getWidth() const {
   return width;
}

const float Truck::getHeight() const {
   return height;
}

const float* Truck::getColor() const {
   return color;
}

const bool   Truck::is2Wheeler() const {
   return type;
}
