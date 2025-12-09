/**
 * @brief Define bikes.
 */

#pragma once
// Libraries
// Headers
#include "Vehicle.h"

class Bike : public Vehicle {
public:
   using Vehicle::Vehicle;
   /** @brief Getter.
       @returns Bike maximum speed*/
   double getSpeedMax() const;
   /** @brief Getter.
       @returns Bike acceleration*/
   double getAcceleration() const;
   /** @brief Getter.
       @returns Bike width*/
   double getWidth() const;
   /** @brief Getter.
       @returns Bike height*/
   double getHeight() const;
   /** @brief Getter.
       @returns Bike color*/
   std::array<double, 3> getColor() const;
   /** @brief Getter.
       @returns Bike type*/
   bool is2Wheeler() const;
protected:

private:
   /** Parameters common to all bikes. */
   static const double width, height;
   static const std::array<double, 3> color;
   static const bool type;
};
