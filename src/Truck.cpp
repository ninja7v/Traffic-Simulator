// Libraries
// Header files
#include "../headers/Constants.h"
#include "../headers/Truck.h"

const double Truck::speedMax     = constants::speedMaxTruck;
const double Truck::acceleration = constants::accelerationTruck;
const double Truck::width        = constants::widthTruck;
const double Truck::height       = constants::heightTruck;
const double Truck::color[3] = {0.0, 0.0, 0.9}; // Dark blue
const bool Truck::type = false;

const double Truck::getSpeedMax() const {
   return speedMax;
}

const double Truck::getAcceleration() const {
   return acceleration;
}

const double Truck::getWidth() const {
   return width;
}

const double Truck::getHeight() const {
   return height;
}

const double* Truck::getColor() const {
   return color;
}

const bool   Truck::is2Wheeler() const {
   return type;
}
