// Libraries
#include <array> // To use arrays
// Headers
#include "../headers/Constants.h"
#include "../headers/Car.h"

const double Car::width        = constants::widthCar;
const double Car::height       = constants::heightCar;
const std::array<double, 3> Car::color{ 0.0, 0.4, 0.9 }; // Blue
const bool Car::type = false;

double Car::getSpeedMax() const {
   return constants::speedMaxCar;
}

double Car::getAcceleration() const {
   return constants::accelerationCar;
}

double Car::getWidth() const {
   return width;
}

double Car::getHeight() const {
   return height;
}

std::array<double, 3> Car::getColor() const {
   return color;
}

bool Car::is2Wheeler() const {
   return type;
}
