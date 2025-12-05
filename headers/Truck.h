/**
 * @brief Define trucks.
 */

#pragma once
// Libraries
#include <array> // To use arrays
// Headers
#include "Vehicle.h"

class Truck : public Vehicle {
public:
   using Vehicle::Vehicle;
/** @brief Getter.
    @returns Truck maximum speed*/
   double getSpeedMax() const;
/** @brief Getter.
    @returns Truck acceleration*/
   double getAcceleration() const;
/** @brief Getter.
    @returns Truck width*/
   double getWidth() const;
/** @brief Getter.
    @returns Truck height*/
   double getHeight() const;
/** @brief Getter.
    @returns Truck color*/
   std::array<float, 3> getColor() const;
/** @brief Getter.
    @returns Truck type*/
   bool is2Wheeler() const;
protected:

private:
/** Parameters common to all trucks. */
   static const double width, height;
   static const std::array<float, 3> color;
   static const bool type;
};
