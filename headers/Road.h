#pragma once
// Libraries
//#include <array> // To use arrays // alreads included in vehicle.h
//#include <list>  // To use lists // alreads included in vehicle.h
// Header files
#include "Global.h"
#include "Intersection.h"
#include "Vehicle.h"

class Road {
public:
   Road();
   Road(int n, Intersection* begin, Intersection* end);
   bool containVehicle();
   int CountVehicles();
   void addVehicle(Vehicle* v);
   void removeVehicle();
   void moveVehicle();
   void displayRoad();
   int                  getID();
   float                getLength();
   Intersection*        getStart();
   Intersection*        getEnd();
   std::list<Vehicle*>  getVehicles();
   std::array<float, 2> getDirection();

protected:

private:
   int idRoad;
   float length;
   Intersection* i1;
   Intersection* i2;
   std::list<Vehicle*> Vehicles;
   std::array<float, 2> direction;
};
