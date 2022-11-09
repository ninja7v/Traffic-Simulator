// Libraries
// Header files
#include "../headers/Constants.h"
#include "../headers/Car.h"

const float Car::speedMax = constants::speedMaxCar;
const float Car::acceleration = constants::accelerationCar;
const float Car::color[3] = { 0, 0, 0.5 }; // Blue

const float Car::getSpeedMax() {
   return speedMax;
}

const float Car::getAcceleration() {
   return acceleration;
}

const float* Car::getColor() {
   return color;
}
