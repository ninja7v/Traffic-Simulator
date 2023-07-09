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
   const float getSpeedMax() const;
/** @brief Getter.
    @returns Car acceleration*/
   const float getAcceleration() const;
/** @brief Getter.
    @returns Car width*/
   const float getWidth() const;
/** @brief Getter.
    @returns Car height*/
   const float getHeight() const;
/** @brief Getter.
    @returns Car color*/
   const float* getColor() const;
/** @brief Getter.
    @returns Car type*/
   const bool   is2Wheeler() const;
protected:

private:
/** Parameters common to all cars. */
   static const float speedMax, acceleration, width, height, color[3];
   static const bool type;
};
