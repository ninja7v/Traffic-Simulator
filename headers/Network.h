#pragma once
// Libraries
#include <list>   // To manipulate lists
#include <vector> // To manipulate vectors
// Header files
#include "Constants.h"
#include "Global.h"
#include "Intersection.h"
#include "Road.h"
#include "Car.h"
//#include "Timer.h"
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
   //Timer timer;
   //Intersection i[constants::nbIntersections];
   std::vector<Intersection*> Intersections;
   //Road r[2][constants::sizeX][constants::sizeY];
   std::vector<Road*> Roads;
   std::list<Car*> Cars;
   int optimum[2][constants::sizeX - 1][constants::sizeY - 1];

   void addCars();
   void updateCarsPosition();
   void resetCars();
   void optimization(bool travelDirection);
};
