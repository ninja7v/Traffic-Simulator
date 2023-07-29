#include <iostream>
#include <cassert>
#include <windows.h>
#include <float.h>
#include "../Tests/Test.h"
#include "../headers/Bike.h"
#include "../headers/Car.h"
#include "../headers/Truck.h"
#include "../headers/Constants.h"
//#include "../headers/Intersection.h" //already included in road
#include "../headers/Road.h"
#include "../headers/Map.h"
#include "../headers/Network.h"

// Unit tests for Road class
void testsRoad() {
   Intersection* i1 = new Intersection(1, { 0.0f, 0.0f });
   Intersection* i2 = new Intersection(2, { 0.0f, 10.0f });
   Road r(1, i1, i2);
   const bool expect_contain_vehicle = false;
   const bool actual_contain_vehicle = r.containVehicle();
   assert(expect_contain_vehicle == actual_contain_vehicle);
   // When the countVehicles() function is active:
   //const int expect_count_vehicles = 0;
   //const int actual_count_vehicles = r.countVehicles();
   //assert(expect_contain_vehicle == actual_contain_vehicle);
   const bool expect_ID = 1;
   const bool actual_ID = r.getID();
   assert(expect_ID == actual_ID);
   const float expect_lenght = 10.0;
   const float actual_lenght = r.getLength();
   assert(expect_contain_vehicle == actual_contain_vehicle);
   const Intersection* expect_start_intersection = i1;
   const Intersection* actual_start_intersection = r.getStart();
   assert(expect_start_intersection == actual_start_intersection);
   const Intersection* expect_end_intersection = i2;
   const Intersection* actual_end_intersection = r.getEnd();
   assert(expect_end_intersection == actual_end_intersection);
   const std::array<float, 2> expect_direction = { 0.0, 1.0 };
   const std::array<float, 2> actual_direction = r.getDirection();
   assert(expect_direction == actual_direction);
   // To be checked:
   //void addVehicle(Vehicle * v);
   //void removeVehicle();
   //void moveVehicle();
   //void displayRoad();
   //void displayLight();
   //std::list<Vehicle*> getVehicles();
}

// Unit tests for Map class
void testsMap() {
   Intersection* i1 = new Intersection(1, { 0.0f, 0.0f });
   Intersection* i2 = new Intersection(2, { 0.0f, 10.0f });
   Road* r = new Road(1, i1, i2);
   Map m;
   m.setConnection(1, 2, r);
   const Road* expect_connection = r;
   const Road* actual_connection = m.getConnection(1, 2);
   assert(expect_connection == actual_connection);
   const std::list<Road*> expect_track = { r };
   const std::list<Road*> actual_track = m.track(i1, i2);
   assert(expect_track == actual_track);
}

// Unit tests for Intersection class
void testsIntersection() {
   Intersection i(1, { 0.0f, 0.0f });
   int IDRoad = 1;
   i.addInputRoad(IDRoad);
   const bool expect_red = false;
   const bool actual_red = i.isRed(IDRoad);
   assert(expect_red == actual_red);
   const float expect_ID = 1;
   const float actual_ID = i.getID();
   assert(expect_ID == actual_ID);
   const std::vector<float> expect_position = { 0.0f, 0.0f };
   const std::vector<float> actual_position = i.getPosition();
   assert(expect_position == actual_position);
   // To be checked:
   //void displayIntersection();
}

// Unit tests for Road class
void testsNetwork() {
   Network n;
   // To be checked:
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
   //HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2); // Green
   std::cout << "All tests passed!" << std::endl;
   //system("color 07"); // White
}
