// Libraries
// Header files
#include "../headers/Constants.h"
#include "../headers/Bike.h"

const float Bike::speedMax     = constants::speedMaxBike;
const float Bike::acceleration = constants::accelerationBike;
const float Bike::width        = constants::widthBike;
const float Bike::height       = constants::heightBike;
const float Bike::color[3] = { 0.0, 0.9, 0.9 }; // Cyan

const float Bike::getSpeedMax() {
   return speedMax;
}

const float Bike::getAcceleration() {
   return acceleration;
}

const float Bike::getWidth() {
   return width;
}

const float Bike::getHeight() {
   return height;
}

const float* Bike::getColor() {
   return color;
}
