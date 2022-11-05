#pragma once
// Libraries
#include <list> // To manipulate lists
// Header files
#include "Global.h"
#include "Intersection.h"
#include "Car.h"

class Road {
public:
   Road();
   Road(int n, Intersection* begin, Intersection* end);
   bool containCar();
   int numberOfCars();
   void addCar(Car* c);
   void removeCar();
   void moveCar();
   void displayRoad();
   int                  getID();
   float                getLength();
   Intersection*        getStart();
   Intersection*        getEnd();
   std::list<Car*>      getCars();
   std::array<float, 2> getDirection();

protected:

private:
   int idRoad;
   float length;
   Intersection* i1;
   Intersection* i2;
   std::list<Car*> cars;
   std::array<float, 2> direction;
};
