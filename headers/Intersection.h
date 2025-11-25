/**
 * @brief Define intersections.
 */

#pragma once
// Libraries
#include <array>  // To use arrays
#include <vector> // To use vectors
// Headers
#include "IntersectionOperator.h"

class Road;

class Intersection {
public:
   Intersection() = delete;
/** @brief Constructor.
  * @param id Road ID
  * @param pos Position coordinates
  * @returns Car acceleration */
   Intersection(const int id, const std::vector<double> pos);
/** @brief Destructor.
   //~Intersection();
/** @brief Get trafic light color.
  * @param id Road ID
  * @returns true:Red / false:Green */
   const bool isRed(const int id) const;
/** @brief Display the intersection as black point.*/
   void displayIntersection() const;
/** @brief Add an input road in the input vector.
  * @param r Road pointer */
   void addInputRoad(Road* r);
   //int                  getRoadIDGreen(); // for the opimizer
/** @brief Getter.
  * @returns Intersection ID */
   const int getID() const;
/** @brief Getter.
  * @returns Position on the grid */
   const std::vector<double> getPosition() const;

   bool operator == (const Intersection i);

   /** @brief Update the intersection lights using RL. */
   void update();

protected:

private:
/** Intersection identifier. */
   const int idIntersection;
/** Position on the grid. */
   const std::vector<double> position;
/** Position coordinates. */
   const std::array<double, 2> coordinates;
/** Input / output road identifiers. */
   std::vector<int> input, output;
   std::vector<Road*> inputRoads;

   // RL components
/** operator to decide traffic light actions */
   IntersectionOperator* op;
/** Index of the current green road in 'input' vector */
   int currentGreenRoadIndex; // Index in 'input' vector
/** Last state observed */
   std::vector<int> lastState;
/** Last action taken */
   int lastAction;
/** Time of the last traffic light switch */
   clock_t lastSwitchTime;
};
