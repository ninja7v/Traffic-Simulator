// Libraries
// Headers
#include "../headers/Constants.h"
#include "../headers/Bike.h"

const double Bike::speedMax     = constants::speedMaxBike;
const double Bike::acceleration = constants::accelerationBike;
const double Bike::width        = constants::widthBike;
const double Bike::height       = constants::heightBike;
const std::array<float, 3> Bike::color{ 0.0f, 0.9f, 0.9f }; // Cyan
const bool Bike::type = true;

double Bike::getSpeedMax() const {
   return speedMax;
}

double Bike::getAcceleration() const {
   return acceleration;
}

double Bike::getWidth() const {
   return width;
}

double Bike::getHeight() const {
   return height;
}

std::array<float, 3> Bike::getColor() const {
   return color;
}

bool Bike::is2Wheeler() const {
   return type;
}
