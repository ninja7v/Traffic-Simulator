#pragma once
// Libraries
#include <array>  // To use arrays
#include <vector> // To use vectors

class Intersection {
public:
   Intersection();
   Intersection(int id, std::array<float, 2> pos);
   bool isRed(int id);
   void displayIntersection();
   void addInputRoad(int id);
   int                  getID();
   int                  getDurationTrafficLight();
   int                  getPeriodTrafficLight();
   std::array<float, 2> getPosition();

protected:

private:
   int idIntersection, durationTrafficLight, periodTrafficLight;
   std::array<float, 2> position;
   std::vector<int> input, output;
};
