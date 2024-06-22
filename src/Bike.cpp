// Libraries
// Header files
#include "../headers/Constants.h"
#include "../headers/Bike.h"

const double Bike::speedMax     = constants::speedMaxBike;
const double Bike::acceleration = constants::accelerationBike;
const double Bike::width        = constants::widthBike;
const double Bike::height       = constants::heightBike;
const double Bike::color[3] = { 0.0, 0.9, 0.9 }; // Cyan
const bool Bike::type = true;

const double Bike::getSpeedMax() const {
   return speedMax;
}

const double Bike::getAcceleration() const {
   return acceleration;
}

const double Bike::getWidth() const {
   return width;
}

const double Bike::getHeight() const {
   return height;
}

const double* Bike::getColor() const {
   return color;
}

const bool   Bike::is2Wheeler() const {
   return type;
}
