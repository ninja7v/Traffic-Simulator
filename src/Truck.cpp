// Libraries
// Headers
#include "../headers/Constants.h"
#include "../headers/Truck.h"

const double Truck::speedMax     = constants::speedMaxTruck;
const double Truck::acceleration = constants::accelerationTruck;
const double Truck::width        = constants::widthTruck;
const double Truck::height       = constants::heightTruck;
const std::array<double, 3> Truck::color{0.0, 0.0, 0.9}; // Dark blue
const bool Truck::type = false;

double Truck::getSpeedMax() const {
   return speedMax;
}

double Truck::getAcceleration() const {
   return acceleration;
}

double Truck::getWidth() const {
   return width;
}

double Truck::getHeight() const {
   return height;
}

std::array<double, 3> Truck::getColor() const {
   return color;
}

bool   Truck::is2Wheeler() const {
   return type;
}
