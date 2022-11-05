#pragma once
// Libraries
#include <array>     // To use arrays
// Header files
#include "Global.h"
#include "Intersection.h"

class Road;

class Car {
public:

   Car(Intersection* i1, Intersection* i2, int id, Intersection* target, std::list<Road*> track);
   float speedFunction(float dist);
   float phi(bool red);
   void moveToCar(Car* c);
   void moveToIntersection(Intersection* i, int idRoad);
   void displayCar();
   Road* nextRoad();
   void updateDirection(Intersection* i);
   void updateItinerary();
   float distance(Car* c);
   float distance(Intersection* i);
   int                  getID();
   float                getSpeed();
   Intersection*        getDestination();
   std::list<Road*>     getItinerary();
   std::array<float, 2> getPosition();
   void                 setPosition(std::array<float, 2>);
protected:

private:
   int idCar, tc = 0;
   float speed;
   std::array<float, 2> position;
   Intersection* destination;
   std::list<Road*> itinerary;
   std::array<float, 2> direction;
};
