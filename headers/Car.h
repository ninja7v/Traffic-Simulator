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
    @returns Car maximum speed.*/
   const float  getSpeedMax();
/** @brief Getter.
    @returns Car acceleration.*/
   const float  getAcceleration();
/** @brief Getter.
    @returns Car width.*/
   const float  getWidth();
/** @brief Getter.
    @returns Car height.*/
   const float  getHeight();
/** @brief Getter.
    @returns Car color.*/
   const float* getColor();
protected:

private:
/** Parameters common to all cars. */
   static const float speedMax, acceleration, width, height, color[3];
};
