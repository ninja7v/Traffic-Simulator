/**
 * @brief Define car attributes.
 */

#pragma once
// Libraries
// Header files
#include "Vehicle.h"

class Car : public Vehicle {
public:
   using Vehicle::Vehicle;
/** @brief Getter.
    @returns Car maximum speed*/
   const double  getSpeedMax() const;
/** @brief Getter.
    @returns Car acceleration*/
   const double  getAcceleration() const;
/** @brief Getter.
    @returns Car width*/
   const double  getWidth() const;
/** @brief Getter.
    @returns Car height*/
   const double  getHeight() const;
/** @brief Getter.
    @returns Car color*/
   const double* getColor() const;
/** @brief Getter.
    @returns Car type*/
   const bool    is2Wheeler() const;
protected:

private:
/** Parameters common to all cars. */
   static const double speedMax, acceleration, width, height, color[3];
   static const bool type;
};
