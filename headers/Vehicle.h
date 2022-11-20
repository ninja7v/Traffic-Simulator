#pragma once
// Libraries
//#include <array>     // To use arrays // already included in Intersection.h
#include <list>      // To use lists
// Header files
#include "Global.h"
#include "Intersection.h"

class Road;

class Vehicle {
public:
   Vehicle(Intersection* i1, Intersection* i2, int id, Intersection* target, std::list<Road*> track);
   float breakingSpeed(float dist);
   void moveToVehicle(Vehicle* v);
   void moveToIntersection(Intersection* i, int idRoad);
   void updateItinerary();
   void displayVehicle();
   Road* nextRoad();
   float distance(Vehicle* v);
   float distance(Intersection* i);
   int                  getID();
   bool                 getStatus();
   float                getSpeed();
   Intersection*        getDestination();
   std::list<Road*>     getItinerary();
   std::array<float, 2> getPosition();
   const virtual float  getSpeedMax()     = 0;
   const virtual float  getAcceleration() = 0;
   const virtual float  getWidth()        = 0;
   const virtual float  getHeight()       = 0;
   const virtual float* getColor()        = 0;
   void                 setDirection(Intersection* i);
   void                 setStatus(bool arrived);
   void                 setPosition(std::array<float, 2>);

protected:
   const int idVehicle;
   //int tc = 0;
   bool isArrived = false;
   float speed;
   Intersection* destination;
   std::array<float, 2> position;
   std::array<float, 2> direction;
   std::list<Road*> itinerary;
private:

};
