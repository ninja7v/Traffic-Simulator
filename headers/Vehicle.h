#pragma once
// Libraries
#include <list>      // To use lists
#include <array>     // To use arrays
// Header files
#include "Global.h"
#include "Intersection.h"

class Road;

class Vehicle {
public:
   Vehicle(Intersection* i1, Intersection* i2, int id, Intersection* target, std::list<Road*> track);
   const virtual float getSpeedMax() = 0;
   const virtual float getAcceleration() = 0;
   const virtual float* getColor() = 0;
   float phi(bool red);
   float speedFunction(float dist);
   void moveToVehicle(Vehicle* v);
   void moveToIntersection(Intersection* i, int idRoad);
   Road* nextRoad();
   void updateDirection(Intersection* i);
   void updateItinerary();
   void displayVehicle();
   float distance(Vehicle* v);
   float distance(Intersection* i);
   int                  getID();
   bool                 getStatus();
   float                getSpeed();
   Intersection*        getDestination();
   std::list<Road*>     getItinerary();
   std::array<float, 2> getPosition();
   void                 setStatus(bool arrived);
   void                 setPosition(std::array<float, 2>);

protected:
   int idVehicle, tc = 0;
   bool isArrived = false;
   float speed;
   std::array<float, 2> position;
   Intersection* destination;
   std::list<Road*> itinerary;
   std::array<float, 2> direction;
private:

};
