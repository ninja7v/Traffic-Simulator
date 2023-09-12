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
   const double  getSpeedMax() const;
/** @brief Getter.
    @returns Truck acceleration*/
   const double  getAcceleration() const;
/** @brief Getter.
    @returns Truck width*/
   const double  getWidth() const;
/** @brief Getter.
    @returns Truck height*/
   const double  getHeight() const;
/** @brief Getter.
    @returns Truck color*/
   const double* getColor() const;
/** @brief Getter.
    @returns Truck type*/
   const bool    is2Wheeler() const;
protected:

private:
/** Parameters common to all trucks. */
   static const double speedMax, acceleration, width, height, color[3];
   static const bool type;
};
