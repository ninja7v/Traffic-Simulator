/**
 * @brief Define roads.
 */

#pragma once
// Libraries
//#include <array> // To use arrays // alreads included in vehicle.h
//#include <list>  // To use lists // alreads included in vehicle.h
// Headers
#include "Intersection.h"
#include "Vehicle.h"
//#include <memory> // To use smart pointers // already included in Vehicle.h

class Road {
public:
   Road() = delete;
/** @brief Constructor.
  * @param id Road ID
  * @param begin Start
  * @param end Arrival
  * @returns Road */
   Road(const int id, Intersection* begin, Intersection* end);
/** @brief Destructor. */
   ~Road();
/** @brief Check if the Road contain vehicles.
  * @returns Road */
   bool containVehicle() const;
///** @brief Count the number of vehicle.
//  * @returns Number of vehicles */
//   int countVehicles(); // For the Optimizer
/** @brief Add vehicle to the Road.
  * @param v Vehicle to add */
   void addVehicle(std::shared_ptr<Vehicle> v);
/** @brief Remove the first vehicle of the Road. */
   void removeVehicle();
/** @brief Advance the vehicles for the next frame. */
   void moveVehicles();
/** @brief Display the Road without the Vehicle on it. */
   void displayRoad() const;
/** @brief Display the traffic light at the end of the Road. */
   void displayLight() const;
/** @brief Getter.
  * @return Road ID*/
   int                   getID() const;
/** @brief Getter.
  * @return Road lenght */
   double                getLength() const;
/** @brief Getter.
  * @return Road ID */
   Intersection*         getStart() const;
/** @brief Getter.
  * @return Start Intersection */
   Intersection*         getEnd() const;
/** @brief Getter.
  * @return End Intersection */
   std::list<std::shared_ptr<Vehicle>> getVehicles() const;
/** @brief Getter.
  * @return Orientation of the Road */
   std::array<double, 2> getDirection() const;

protected:

private:
/** Road identifier */
   const int idRoad;
/** Road length */
   const double length;
/** Start Intersection */
   Intersection* i1;
/** End Intersection */
   Intersection* i2;
/** Vehicle on the Road */
   std::list<std::shared_ptr<Vehicle>> Vehicles;
/** Orientation of the Road */
   std::array<double, 2> direction;
/** Road coordinates */
   const double roadCoordinates[6];
/** Roadside left coordinates */
   const double sideLeft[6];
/** Roadside right coordinates */
   const double sideRight[6];
/** Traffic light coordinates */
   const double lightCoordinates[2];
};
