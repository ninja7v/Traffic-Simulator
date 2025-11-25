// Libraries
// Headers
#include "../headers/Constants.h"
#include "../headers/Car.h"

const double Car::speedMax     = constants::speedMaxCar;
const double Car::acceleration = constants::accelerationCar;
const double Car::width        = constants::widthCar;
const double Car::height       = constants::heightCar;
const std::array<float, 3> Car::color{ 0.0f, 0.4f, 0.9f }; // Blue
const bool Car::type = false;

double Car::getSpeedMax() const {
   return speedMax;
}

double Car::getAcceleration() const {
   return acceleration;
}

double Car::getWidth() const {
   return width;
}

double Car::getHeight() const {
   return height;
}

std::array<float, 3> Car::getColor() const {
   return color;
}

bool Car::is2Wheeler() const {
   return type;
}
