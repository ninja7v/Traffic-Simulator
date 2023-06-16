/**
 * @brief Define roads.
 */

#pragma once
// Libraries
//#include <array> // To use arrays // alreads included in vehicle.h
//#include <list>  // To use lists // alreads included in vehicle.h
// Header files
#include "Global.h"
#include "Intersection.h"
#include "Vehicle.h"

class Road {
public:
   Road() = delete;
/** @brief Constructor.
  * @param id Road ID
  * @param begin Start
  * @param end Arrival
  * @returns Road */
   Road(int id, Intersection* begin, Intersection* end);
/** @brief Destructor. */
   ~Road();
/** @brief Check if the Road contain vehicles.
  * @returns Road */
   bool containVehicle();
///** @brief Count the number of vehicle.
//  * @returns Number of vehicles */
//   int countVehicles(); // For the Optimizer
/** @brief Add vehicle to the Road.
  * @param v Vehicle to add */
   void addVehicle(Vehicle* v);
/** @brief Remove the first vehicle of the Road. */
   void removeVehicle();
/** @brief Advance the vehicle for the next frame. */
   void moveVehicle();
/** @brief Display the Road without the Vehicle on it. */
   void displayRoad();
/** @brief Display the traffic light at the end of the Road. */
   void displayLight();
/** @brief Getter.
  * @return Road ID*/
   const int                  getID();
/** @brief Getter.
  * @return Road lenght */
   const float                getLength();
/** @brief Getter.
  * @return Road ID */
   Intersection*              getStart();
/** @brief Getter.
  * @return Start Intersection */
   Intersection*              getEnd();
/** @brief Getter.
  * @return End Intersection */
   std::list<Vehicle*>        getVehicles();
/** @brief Getter.
  * @return Orientation of the Road */
   const std::array<float, 2> getDirection();

protected:

private:
/** Road identifier */
   const int idRoad;
/** Road length */
   const float length;
/** Start Intersection */
   Intersection* i1;
/** End Intersection */
   Intersection* i2;
/** Vehicle on the Road */
   std::list<Vehicle*> Vehicles;
/** Orientation of the Road */
   std::array<float, 2> direction;
/** Road coordinates */
   const float roadCoordinates[6];
/** Roadside left coordinates */
   const float sideLeft[6];
/** Roadside right coordinates */
   const float sideRight[6];
/** Traffic light coordinates */
   const float lightCoordinates[2];
};
