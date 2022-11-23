/**
 * @brief Define truck attributes.
 */

#pragma once
// Libraries
// Header files
#include "Vehicle.h"

class Truck : public Vehicle {
public:
   using Vehicle::Vehicle;
/** @brief Getter.
    @returns Truck maximum speed*/
   const float  getSpeedMax();
/** @brief Getter.
    @returns Truck acceleration*/
   const float  getAcceleration();
/** @brief Getter.
    @returns Truck width*/
   const float  getWidth();
/** @brief Getter.
    @returns Truck height*/
   const float  getHeight();
/** @brief Getter.
    @returns Truck color*/
   const float* getColor();
protected:

private:
/** Parameters common to all trucks. */
   static const float speedMax, acceleration, width, height, color[3];
};
