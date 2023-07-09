#pragma once
// Libraries
//#include <array>     // To use arrays // already included in Intersection.h
#include <list>      // To use lists
// Header files
#include "Global.h"
#include "Intersection.h"

class Road;
/**
 * @brief Define vehicles.
 */
class Vehicle {
public:
/** @brief Constructor.
  * @param i1 Start Intersection
  * @param i2 End Intersection
  * @param id Vehicle ID
  * @param target Destination
  * @param track Itinerary
  * @returns Vehicle*/
   Vehicle(Intersection* i1, Intersection* i2, int id, Intersection* target, std::list<Road*> track);
/** @brief Destructor. */
   ~Vehicle();
/** @brief Theoritical speed function.
  * @param dist Distance with the front obstacle
  * @return Speed */
   float breakingSpeed(const float dist);
/** @brief Adjust the speed to approach the theoritical speed function.
  * @param v Vehicle in front */
   void moveToVehicle(Vehicle* v);
/** @brief Adjust the speed to approach the theoritical speed function.
  * @param i Intersection in front
  * @param idRoad Road ID of the Road the Vehicle is*/
   void moveToIntersection(Intersection* i, const int idRoad);
/** @brief Update Vehicle itilerary when arriving at the end of the Road. */
   void updateItinerary();
/** @brief Display the Vehicle. */
   void displayVehicle();
/** @brief GPS.
  * @return Next Road fromt the itinerary */
   Road* nextRoad();
/** @brief Calculate the distance with the front Vehicle.
  * @param v Vehicle in front
  * @return Distance */
   const float distance(Vehicle* v);
/** @brief Calculate the distance with the front Intersection.
  * @param i Intersection in front
  * @return Distance */
   const float distance(Intersection* i);
/** @brief Getter.
  * @return Vehicle ID */
   const int            getID() const;
/** @brief Getter.
  * @return Arrived at destination? */
   bool                 getStatus() const;
/** @brief Getter.
  * @return Vehicle Speed */
   float                getSpeed() const;
/** @brief Getter.
  * @return Vehicle destination */
   Intersection*        getDestination() const;
/** @brief Getter.
  * @return Vehicle itinerary */
   std::list<Road*>     getItinerary() const;
/** @brief Getter.
  * @return Vehicle position */
   std::vector<float>   getPosition() const;
/** @brief Getter.
  * @return Vehicle speed max */
   virtual const float  getSpeedMax() const = 0;
/** @brief Getter.
  * @return Vehicle acceleration */
   virtual const float  getAcceleration() const = 0;
/** @brief Getter.
  * @return Vehicle width */
   virtual const float  getWidth() const = 0;
/** @brief Getter.
  * @return Vehicle height */
   virtual const float  getHeight() const = 0;
/** @brief Getter.
  * @return Vehicle color */
   virtual const float* getColor() const = 0;
/** @brief Setter. */
   void setDirection(Intersection* i);
/** @brief Setter. */
   void setPosition(const std::vector<float>);
/** @brief Setter. */
   void setStatus(const bool arrived);

protected:
/** Vehicle ID. */
   const int idVehicle;
   //int tc = 0;
/** Arrived at destination? */
   bool isArrived = false;
/** Vehicle speed. */
   float speed;
/** Vehicle destination. */
   Intersection* destination;
/** Vehicle position. */
   std::vector<float> position;
/** Vehicle direction. */
   std::array<float, 2> direction;
/** Vehicle itinerary. */
   std::list<Road*> itinerary;
private:

};
