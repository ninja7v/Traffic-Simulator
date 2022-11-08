// Libraries
#include <list>      // To use lists
#include <cstdlib>   // To use rand()
#include <iostream>  // To use input/output
#include <GL/glut.h> // To display
#include <time.h>    // To use clock()
#include <array>     // To use arrays
// Header files
#include "../headers/Constants.h"
#include "../headers/Truck.h"

const float Truck::speedMax = constants::speedMaxTruck;
const float Truck::acceleration = constants::accelerationTruck;
const float Truck::color[3] = {0.7, 0.7, 0}; // Yellow

const float Truck::getSpeedMax() {
   return speedMax;
}

const float Truck::getAcceleration() {
   return acceleration;
}

const float* Truck::getColor() {
   return color;
}
