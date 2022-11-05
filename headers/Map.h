#pragma once
// Libraries
#include <list>
// Header files
#include "Intersection.h"
#include "Constants.h"
#include "Road.h"
#include "Car.h"

class Map
{public:
   Map();
   Road* connection(Intersection* i1, Intersection* i2);
   std::list<Road*> track(Intersection* begin, Intersection* end);
   Road* getConnection(int a, int b);
   void setConnection(int a, int b, Road* r);
protected:

private:
   Road* connections[constants::nbIntersections][constants::nbIntersections];
};
