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
   const float  getSpeedMax() const;
/** @brief Getter.
    @returns Bike acceleration*/
   const float  getAcceleration() const;
/** @brief Getter.
    @returns Bike width*/
   const float  getWidth() const;
/** @brief Getter.
    @returns Bike height*/
   const float  getHeight() const;
/** @brief Getter.
    @returns Bike color*/
   const float* getColor() const;
/** @brief Getter.
    @returns Bike type*/
   const bool   is2Wheeler() const;
protected:

private:
/** Parameters common to all bikes. */
   static const float speedMax, acceleration, width, height, color[3];
   static const bool type;
};
