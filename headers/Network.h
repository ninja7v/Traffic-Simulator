/**
 * @brief Class making the link between every element.
 */

#pragma once
// Libraries
//#include <list>   // To manipulate lists //already included in vehicle.h
//#include <vector> // To manipulate vectors // already included in Intersection.h
// Header files
#include "Constants.h"
//#include "Intersection.h" //already include in Road.h
#include "Road.h"
#include "Map.h"

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
   std::list<Vehicle*> Vehicles;
/** @brief Add vehicle to the simulation. */
   void addVehicle();
/** @brief Move the Vehicle for the next frame. */
   void updateVehiclesPosition();
   //void resetVehicles(); // Unused
};
