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
  * @returns Vehicle.*/
   Vehicle(Intersection* i1, Intersection* i2, int id, Intersection* target, std::list<Road*> track);
/** @brief Theoritical speed function.
  * @param dist Distance with the front obstacle
  * @return Speed */
   float breakingSpeed(float dist);
/** @brief Adjust the speed to approach the theoritical speed function.
  * @param v Vehicle in front */
   void moveToVehicle(Vehicle* v);
/** @brief Adjust the speed to approach the theoritical speed function.
  * @param i Intersection in front */
   void moveToIntersection(Intersection* i, int idRoad);
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
   float distance(Vehicle* v);
/** @brief Calculate the distance with the front Intersection.
  * @param i Intersection in front
  * @return Distance */
   float distance(Intersection* i);
/** @brief Getter.
  * @return Vehicle ID */
   int                  getID();
/** @brief Getter.
  * @return Arrived at destination? */
   bool                 getStatus();
/** @brief Getter.
  * @return Vehicle Speed */
   float                getSpeed();
/** @brief Getter.
  * @return Vehicle destination */
   Intersection*        getDestination();
/** @brief Getter.
  * @return Vehicle itinerary */
   std::list<Road*>     getItinerary();
/** @brief Getter.
  * @return Vehicle position */
   std::array<float, 2> getPosition();
/** @brief Getter.
  * @return Vehicle speed max */
   const virtual float  getSpeedMax()     = 0;
/** @brief Getter.
  * @return Vehicle acceleration */
   const virtual float  getAcceleration() = 0;
/** @brief Getter.
  * @return Vehicle width */
   const virtual float  getWidth()        = 0;
/** @brief Getter.
  * @return Vehicle height */
   const virtual float  getHeight()       = 0;
/** @brief Getter.
  * @return Vehicle color */
   const virtual float* getColor()        = 0;
/** @brief Setter.
  * @return Vehicle ID*/
   void                 setDirection(Intersection* i);
/** @brief Setter.
  * @return Vehicle ID*/
   void                 setStatus(bool arrived);
/** @brief Setter.
  * @return Vehicle ID*/
   void                 setPosition(std::array<float, 2>);

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
   std::array<float, 2> position;
/** Vehicle direction. */
   std::array<float, 2> direction;
/** Vehicle itinerary. */
   std::list<Road*> itinerary;
private:

};
