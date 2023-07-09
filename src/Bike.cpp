// Libraries
// Header files
#include "../headers/Constants.h"
#include "../headers/Bike.h"

const float Bike::speedMax     = constants::speedMaxBike;
const float Bike::acceleration = constants::accelerationBike;
const float Bike::width        = constants::widthBike;
const float Bike::height       = constants::heightBike;
const float Bike::color[3] = { 0.0, 0.9, 0.9 }; // Cyan

const float Bike::getSpeedMax() const {
   return speedMax;
}

const float Bike::getAcceleration() const {
   return acceleration;
}

const float Bike::getWidth() const {
   return width;
}

const float Bike::getHeight() const {
   return height;
}

const float* Bike::getColor() const {
   return color;
}
