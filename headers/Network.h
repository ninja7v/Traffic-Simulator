/**
 * @brief Class making the link between every element.
 */

#pragma once
// Libraries
#include <list>   // To use lists
#include <vector> // To use vectors
#include <memory> // To use smart pointers
// Header files
//#include "Intersection.h" //already include in Road.h
#include "Road.h"
#include "Map.h"
//#include <memory> // To use smart pointers // already included in Vehicle.h

class Network {
public:
/** @brief Default constructor.
  * @returns Network */
   Network();
/** @brief Network display. */
   void displayNetwork();

protected:

private:
/** Road Map. */
   Map map;
/** Intersections. */
   std::vector<Intersection*> Intersections;
/** Roads. */
   std::vector<Road*> Roads;
/** Vehicles */
   std::list<std::shared_ptr<Vehicle>> Vehicles;
/** @brief Add vehicle to the simulation. */
   void addVehicle();
/** @brief Move the Vehicle for the next frame. */
   void updateVehiclesPosition();
///** @brief Remove all Vehicle. */
//   void resetVehicles(); // Unused
};
