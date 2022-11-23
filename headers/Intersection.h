/**
 * @brief Define intersections.
 */

#pragma once
// Libraries
#include <array>  // To use arrays
#include <vector> // To use vectors

class Intersection {
public:
   Intersection() = delete;
/** @brief Constructor.
  * @param id Road ID
  * @param pos Position coordinates
  * @returns Car acceleration */
   Intersection(int id, std::array<float, 2> pos);
/** @brief Constructor.
  * @param id Road ID
  * @returns Green / Red */
   bool isRed(int id);
/** @brief Display the intersection as black point.*/
   void displayIntersection();
/** @brief Add an input road in the input vector.
  * @param id Road ID */
   void addInputRoad(int id);
   //int                  getRoadIDGreen(); // for the opimizer
/** @brief Getter.
  * @returns Intersection ID */
   int                  getID();
/** @brief Getter.
  * @returns Position on the grid */
   std::array<float, 2> getPosition();

protected:

private:
/** Intersection identifier. */
   const int idIntersection;
/** Position on the grid. */
   const std::array<float, 2> position;
/** Position coordinates. */
   const std::array<float, 2> coordinates;
/** Input / output road identifiers. */
   std::vector<int> input, output;
   //static float a, b; // for the opimizer
};
