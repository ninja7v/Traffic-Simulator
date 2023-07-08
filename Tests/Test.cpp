#include <iostream>
#include <cassert>
#include <float.h>
#include "../Tests/Test.h"
#include "../headers/Bike.h"
#include "../headers/Car.h"
#include "../headers/Truck.h"
#include "../headers/Constants.h"
//#include "../headers/Intersection.h" //already included in road
#include "../headers/Road.h"

// Unit tests for Road class
void testsRoad() {
   // To be checked:
   //Road(int id, Intersection * begin, Intersection * end);
   //~Road();
   //bool containVehicle();
   //int countVehicles();
   //void addVehicle(Vehicle * v);
   //void removeVehicle();
   //void moveVehicle();
   //void displayRoad();
   //void displayLight();
   //const int                  getID();
   //const float                getLength();
   //Intersection*              getStart();
   //Intersection*              getEnd();
   //std::list<Vehicle*>        getVehicles();
   //const std::array<float, 2> getDirection();
}

// Unit tests for Map class
void testsMap() {
   // To be checked:
   //Map();
   //std::list<Road*> track(Intersection * begin, Intersection * end);
   //const Road* getConnection(const int a, const int b);
   //void setConnection(const int a, const int b, Road * r);
}

// Unit tests for Intersection class
void testsIntersection() {
   // To be checked:
   //Intersection(int id, std::array<float, 2> pos);
   //const bool isRed(int id);
   //void displayIntersection();
   //void addInputRoad(const int id);
   //const int                  getID();
   //const std::array<float, 2> getPosition();
}

// Unit tests for Road class
void testsNetwork() {
   // To be checked:
   //Network();
   //void displayNetwork();
}

// Unit tests for Truck class
void testsVehicle() {
   std::cout << "testVehicle" << std::endl;
   Intersection* i1 = new Intersection(1, { 0.0f, 0.0f });
   Intersection* i2 = new Intersection(2, { 0.0f, 10.0f });
   Intersection* target(i2);
   Road* r = new Road(1, i1, i2);
   std::list<Road*> track(1, r);
   Car car(i1, i2, 1, target, track);
   car.breakingSpeed(1.0);
   const float expect_distance_vehicle = 0.0;
   const float actual_breaking_vehicle = car.distance(&car);
   assert(expect_distance_vehicle == actual_breaking_vehicle);
   const float expect_distance_intersection = 0.0;
   const float actual_breaking_intersection = car.distance(i1);
   assert(expect_distance_intersection == actual_breaking_intersection);
   const float expect_breaking_speed = 0.0;
   const float actual_breaking_speed = car.breakingSpeed(0.0);
   assert(expect_breaking_speed == actual_breaking_speed);
   const int expect_id = 1;
   const int actual_id = car.getID();
   assert(expect_id == actual_id);
   const bool expect_status = false;
   const bool actual_status = car.getStatus();
   assert(expect_status == actual_status);
   const float expect_speed = 0.0;
   const float actual_speed = car.getSpeed();
   assert(expect_speed == actual_speed);
   const Intersection* expect_destination = i2;
   const Intersection* actual_destination = car.getDestination();
   assert(expect_destination == actual_destination);
   const std::list<Road*> expect_itinerary = track;
   const std::list<Road*> actual_itinerary = car.getItinerary();
   assert(expect_itinerary == actual_itinerary);
   const std::vector<float> expect_position = i1->getPosition();
   const std::vector<float> actual_position = car.getPosition();
   assert(expect_position == actual_position);

   // To be checked:
   //void moveToVehicle(Vehicle * v);
   //void moveToIntersection(Intersection * i, int idRoad);
   //void updateItinerary();
   //void displayVehicle();
   //Road* nextRoad();
}

// Unit tests for Bike class
void testsBike() {
   Intersection* i1 = new Intersection(1, { 0.0f, 0.0f });
   Intersection* i2 = new Intersection(2, { 0.0f, 10.0f });
   Intersection* target(i2);
   Road* r = new Road(1, i1, i2);
   std::list<Road*> track(1, r);
   Bike bike(i1, i2, 1, target, track);

   const float expect_speedMax = constants::speedMaxBike;
   const float actual_speedMax = bike.getSpeedMax();
   assert(expect_speedMax == actual_speedMax);
   const float expect_acceleration = constants::accelerationBike;
   const float actual_acceleration = bike.getAcceleration();
   assert(expect_acceleration == actual_acceleration);
   const float expect_width = constants::widthBike;
   const float actual_width = bike.getWidth();
   assert(expect_width == actual_width);
   const float expect_height = constants::heightBike;
   const float actual_height = bike.getHeight();
   assert(expect_height == actual_height);
   const float  expect_color[3] = { 0.0, 0.9, 0.9 };
   const float* actual_color    = bike.getColor();
   for (int i = 0; i < 3; i++) {
      assert(expect_color[i] == actual_color[i]);
   }

   delete target;
   delete r;
}

// Unit tests for Car class
void testsCar() {
   Intersection* i1 = new Intersection(1, { 0.0f, 0.0f });
   Intersection* i2 = new Intersection(2, { 0.0f, 10.0f });
   Intersection* target(i2);
   Road* r = new Road(1, i1, i2);
   std::list<Road*> track(1, r);
   Car car(i1, i2, 1, target, track);

   const float expect_speedMax = constants::speedMaxCar;
   const float actual_speedMax = car.getSpeedMax();
   assert(expect_speedMax == actual_speedMax);
   const float expect_acceleration = constants::accelerationCar;
   const float actual_acceleration = car.getAcceleration();
   assert(expect_acceleration == actual_acceleration);
   const float expect_width = constants::widthCar;
   const float actual_width = car.getWidth();
   assert(expect_width == actual_width);
   const float expect_height = constants::heightCar;
   const float actual_height = car.getHeight();
   assert(expect_height == actual_height);
   const float  expect_color[3] = { 0.0, 0.4, 0.9 };
   const float* actual_color    = car.getColor();
   for (int i = 0; i < 3; i++) {
      assert(expect_color[i] == actual_color[i]);
   }

   delete target;
   delete r;
}

// Unit tests for Truck class
void testsTruck() {
   std::cout << "testTruck" << std::endl;
   Intersection* i1 = new Intersection(1, { 0.0f, 0.0f });
   Intersection* i2 = new Intersection(2, { 0.0f, 10.0f });
   Intersection* target(i2);
   Road* r = new Road(1, i1, i2);
   std::list<Road*> track(1, r);
   Truck truck(i1, i2, 1, target, track);

   const float expect_speedMax = constants::speedMaxTruck;
   const float actual_speedMax = truck.getSpeedMax();
   assert(expect_speedMax == actual_speedMax);
   const float expect_acceleration = constants::accelerationTruck;
   const float actual_acceleration = truck.getAcceleration();
   assert(expect_acceleration == actual_acceleration);
   const float expect_width = constants::widthTruck;
   const float actual_width = truck.getWidth();
   assert(expect_width == actual_width);
   const float expect_height = constants::heightTruck;
   const float actual_height = truck.getHeight();
   assert(expect_height == actual_height);
   const float  expect_color[3] = { 0.0, 0.0, 0.9 };
   const float* actual_color    = truck.getColor();
   for (int i = 0; i < 3; i++) {
      assert(expect_color[i] == actual_color[i]);
   }

   delete target;
   delete r;
}

// Run all the tests
void runTests() {
   testsRoad();
   testsMap();
   testsIntersection();
   testsNetwork();
   testsVehicle();
   testsBike();
   testsCar();
   testsTruck();
   //system("color 0A");
   std::cout << "All tests passed!" << std::endl;
   //system("color 07");
}
