#pragma once
// Libraries
#include <array>  // To use arrays
#include <vector> // To use vectors

class Intersection {
public:
   Intersection() = delete;
   Intersection(int id, std::array<float, 2> pos);
   bool isRed(int id);
   void displayIntersection();
   void addInputRoad(int id);
   //int                  getRoadIDGreen(); // for the opimizer
   int                  getID();
   std::array<float, 2> getPosition();

protected:

private:
   const int idIntersection;
   const std::array<float, 2> position;
   const std::array<float, 2> coordinates;
   std::vector<int> input, output;
   //static float a, b; // for the opimizer
};
