#pragma once
// Libraries
//#include <list>   // To manipulate lists //already included in vehicle.h
//#include <vector> // To manipulate vectors // already included in Intersection.h
// Header files
#include "Constants.h"
//#include "Intersection.h" //already include in Road.h
#include "Road.h"
#include "Map.h"

//we consider a Manhatan network
class Network {
public:
   Network();
   void displayNetwork();

protected:

private:
   Map map;
   int min, max, timeMax, bestTime;
   bool change;
   std::vector<Intersection*> Intersections;
   std::vector<Road*> Roads;
   std::list<Vehicle*> Vehicles;

   void addVehicle();
   void updateVehiclesPosition();
   void resetVehicles();
   void optimization(bool travelDirection);
};
