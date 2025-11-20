// Libraries
// Header files
#include "../headers/Constants.h"
#include "../headers/Car.h"

const double Car::speedMax     = constants::speedMaxCar;
const double Car::acceleration = constants::accelerationCar;
const double Car::width        = constants::widthCar;
const double Car::height       = constants::heightCar;
const double Car::color[3] = { 0.0, 0.4, 0.9 }; // Blue
const bool Car::type = false;

const double Car::getSpeedMax() const {
   return speedMax;
}

const double Car::getAcceleration() const {
   return acceleration;
}

const double Car::getWidth() const {
   return width;
}

const double Car::getHeight() const {
   return height;
}

const double* Car::getColor() const {
   return color;
}

const bool   Car::is2Wheeler() const {
   return type;
}
