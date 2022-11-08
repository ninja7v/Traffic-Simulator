// Libraries
#include <list>      // To use lists
#include <cstdlib>   // To use rand()
#include <iostream>  // To use input/output
#include <GL/glut.h> // To display
#include <time.h>    // To use clock()
#include <array>     // To use arrays
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
