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
   const double  getSpeedMax() const;
/** @brief Getter.
    @returns Bike acceleration*/
   const double  getAcceleration() const;
/** @brief Getter.
    @returns Bike width*/
   const double  getWidth() const;
/** @brief Getter.
    @returns Bike height*/
   const double  getHeight() const;
/** @brief Getter.
    @returns Bike color*/
   const double* getColor() const;
/** @brief Getter.
    @returns Bike type*/
   const bool    is2Wheeler() const;
protected:

private:
/** Parameters common to all bikes. */
   static const double speedMax, acceleration, width, height, color[3];
   static const bool type;
};
