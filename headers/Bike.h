/**
 * @brief Define bike attributes.
 */

#pragma once
// Libraries
// Header files
#include "Vehicle.h"

class Bike : public Vehicle {
public:
   using Vehicle::Vehicle;
/** @brief Getter.
    @returns Bike maximum speed*/
   const float  getSpeedMax();
/** @brief Getter.
    @returns Bike acceleration*/
   const float  getAcceleration();
/** @brief Getter.
    @returns Bike width*/
   const float  getWidth();
/** @brief Getter.
    @returns Bike height*/
   const float  getHeight();
/** @brief Getter.
    @returns Bike color*/
   const float* getColor();
protected:

private:
/** Parameters common to all bikes. */
   static const float speedMax, acceleration, width, height, color[3];
};
