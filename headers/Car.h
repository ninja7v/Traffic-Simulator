/**
 * @brief Define cars.
 */

#pragma once
// Libraries
#include <array> // To use arrays
// Headers
#include "Vehicle.h"

class Car : public Vehicle {
public:
   using Vehicle::Vehicle;
/** @brief Getter.
    @returns Car maximum speed*/
   double getSpeedMax() const;
/** @brief Getter.
    @returns Car acceleration*/
   double getAcceleration() const;
/** @brief Getter.
    @returns Car width*/
   double getWidth() const;
/** @brief Getter.
    @returns Car height*/
   double getHeight() const;
/** @brief Getter.
    @returns Car color*/
   std::array<float, 3> getColor() const;
/** @brief Getter.
    @returns Car type*/
   bool is2Wheeler() const;
protected:

private:
/** Parameters common to all cars. */
   static const double width, height;
   static const std::array<float, 3> color;
   static const bool type;
};
