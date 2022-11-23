/**
 * @brief Map of the Network.
 */

#pragma once
// Libraries
//#include <list> // To use lists // already included in vehicle.h
// Header files
#include "Intersection.h"
#include "Constants.h"
#include "Road.h"

class Map {
public:
/** @brief Default constructor.
  * @returns Map*/
   Map();
/** @brief Obtain the optimal itinerary between 2 intersections using the Dijksra Algorithm.
  * Source: https://www.tutorialspoint.com/cplusplus-program-for-dijkstra-s-shortest-path-algorithm
  * Condition: the graph must be strongly connected to ensure the existence of a solution.
  * @returns Road */
   std::list<Road*> track(Intersection* begin, Intersection* end);
/** @brief Getter to obtain the road between 2 intersections.
  * @param a Start
  * @param b Arrival
  * @returns Road */
   Road* getConnection(int a, int b);
/** @brief Setter to build the road between 2 intersections.
  * @param a Start
  * @param b Arrival
  * @param r New Road */
   void  setConnection(int a, int b, Road* r);

protected:

private:
   // Theses array are filled in the network contructor
/** Adjacency matrix for the roads. It is filled in the Network contructor. */
   Road* connections[constants::nbIntersections][constants::nbIntersections];
/** Adjacency matrix for the distances. It is filled in the Network contructor. */
   float cost[constants::nbIntersections][constants::nbIntersections]{ 9999 };
};
