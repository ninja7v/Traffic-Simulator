#pragma once
// Libraries
//#include <list> // To use lists // already included in vehicle.h
// Header files
#include "Intersection.h"
#include "Constants.h"
#include "Road.h"

class Map {
public:
   Map();
   Road* connection(Intersection* i1, Intersection* i2);
   std::list<Road*> track(Intersection* begin, Intersection* end);
   Road* getConnection(int a, int b);
   void  setConnection(int a, int b, Road* r);
protected:

private:
   // This array is filled in the network contructor
   Road* connections[constants::nbIntersections][constants::nbIntersections];
};
