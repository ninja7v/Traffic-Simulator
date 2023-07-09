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
   Intersection(int id, std::vector<float> pos);
/** @brief Destructor.
   //~Intersection();
/** @brief Get trafic light color.
  * @param id Road ID
  * @returns true:Red / false:Green */
   const bool isRed(int id);
/** @brief Display the intersection as black point.*/
   void displayIntersection();
/** @brief Add an input road in the input vector.
  * @param id Road ID */
   void addInputRoad(const int id);
   //int                  getRoadIDGreen(); // for the opimizer
/** @brief Getter.
  * @returns Intersection ID */
   const int                getID() const;
/** @brief Getter.
  * @returns Position on the grid */
   const std::vector<float> getPosition();

   bool operator == (const Intersection i);

protected:

private:
/** Intersection identifier. */
   const int idIntersection;
/** Position on the grid. */
   const std::vector<float> position;
/** Position coordinates. */
   const std::array<float, 2> coordinates;
/** Input / output road identifiers. */
   std::vector<int> input, output;
   //static float a, b; // for the opimizer
};
