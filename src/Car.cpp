// Libraries
// Header files
#include "../headers/Constants.h"
#include "../headers/Car.h"

const float Car::speedMax     = constants::speedMaxCar;
const float Car::acceleration = constants::accelerationCar;
const float Car::width        = constants::widthCar;
const float Car::height       = constants::heightCar;
const float Car::color[3] = { 0, 0.4, 0.9 }; // Blue

const float Car::getSpeedMax() const {
   return speedMax;
}

const float Car::getAcceleration() const {
   return acceleration;
}

const float Car::getWidth() const {
   return width;
}

const float Car::getHeight() const {
   return height;
}

const float* Car::getColor() const {
   return color;
}
