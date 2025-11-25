#include <iostream>
#include <cassert>
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
   Intersection* i1 = new Intersection(1, { 0.0, 0.0 });
   Intersection* i2 = new Intersection(2, { 0.0, 10.0 });
   Intersection* target(i2);
   Road* r = new Road(1, i1, i2);
   std::list<Road*> track(1, r);
   std::shared_ptr<Vehicle> car = std::make_shared<Car>(i1, i2, 1, target, track);
   assert(i1);
   assert(i2);
   assert(target);
   assert(r);
   assert(car);

   const bool expect_contain_vehicle = false;
   const bool actual_contain_vehicle = r->containVehicle();
   assert(expect_contain_vehicle == actual_contain_vehicle);
   // When the countVehicles() function is active:
   //const int expect_count_vehicles = 0;
   //const int actual_count_vehicles = r.countVehicles();
   //assert(expect_contain_vehicle == actual_contain_vehicle);
   const bool expect_ID = 1;
   const bool actual_ID = r->getID();
   assert(expect_ID == actual_ID);
   const double expect_lenght = 10.0;
   const double actual_lenght = r->getLength();
   assert(expect_contain_vehicle == actual_contain_vehicle);
   const Intersection* expect_start_intersection = i1;
   const Intersection* actual_start_intersection = r->getStart();
   assert(expect_start_intersection == actual_start_intersection);
   const Intersection* expect_end_intersection = i2;
   const Intersection* actual_end_intersection = r->getEnd();
   assert(expect_end_intersection == actual_end_intersection);
   const std::array<double, 2> expect_direction = { 0.0, 1.0 };
   const std::array<double, 2> actual_direction = r->getDirection();
   assert(expect_direction == actual_direction);
   r->addVehicle(car);
   const bool expect_vehicle_added = true;
   const bool actual_vehicle_added = r->containVehicle();
   assert(expect_vehicle_added == actual_vehicle_added);
   std::list<std::shared_ptr<Vehicle>> expect_list_vehicle = r->getVehicles();
   std::list<std::shared_ptr<Vehicle>> actual_list_vehicle { car };
   assert(expect_list_vehicle == actual_list_vehicle);
   r->removeVehicle();
   const bool expect_vehicle_removed = false;
   const bool actual_vehicle_removed = r->containVehicle();
   assert(expect_vehicle_removed == actual_vehicle_removed);
   // To be checked:
   //void moveVehicles();
   //void displayRoad();
   //void displayLight();

   delete i1; i1 = nullptr;
   delete i2; i2 = nullptr;
   target = nullptr;
   delete r; r = nullptr;
}

// Unit tests for Map class
void testsMap() {
   Intersection* i1 = new Intersection(1, { 0.0, 0.0 });
   Intersection* i2 = new Intersection(2, { 0.0, 10.0 });
   Road* r = new Road(1, i1, i2);
   Map m;
   assert(i1);
   assert(i2);
   assert(r);

   m.setConnection(1, 2, r);
   m.updateConnection(r);
   const Road* expect_connection = r;
   const Road* actual_connection = m.getConnection(1, 2);
   assert(expect_connection == actual_connection);
   const std::list<Road*> expect_track = { r };
   const std::list<Road*> actual_track = m.track(i1, i2);
   assert(expect_track == actual_track);

   delete i1; i1 = nullptr;
   delete i2; i2 = nullptr;
   delete r; r = nullptr;
}

// Unit tests for Intersection class
void testsIntersection() {
   Intersection i1(1, { 0.0, 0.0 });
   Intersection i2(2, { 0.0, 0.0 });
   Road* r = new Road(1, &i1, &i2);;

   i1.addInputRoad(r);
   const double expect_ID = 1;
   const double actual_ID = i1.getID();
   assert(expect_ID == actual_ID);
   const bool expect_red = false;
   const bool actual_red = i1.isRed(actual_ID);
   assert(expect_red == actual_red);
   const std::vector<double> expect_position = { 0.0, 0.0 };
   const std::vector<double> actual_position = i1.getPosition();
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

// Unit tests for Vehicle class
void testsVehicle() {
   std::cout << "testVehicle" << std::endl;
   Intersection* i1 = new Intersection(1, { 0.0, 0.0 });
   Intersection* i2 = new Intersection(2, { 0.0, 10.0 });
   Intersection* target(i2);
   Road* r = new Road(1, i1, i2);
   std::list<Road*> track(1, r);
   std::shared_ptr<Vehicle> car = std::make_shared<Car>(i1, i2, 1, target, track);
   assert(r);
   assert(car);

   const double expect_distance_vehicle = 0.0;
   const double actual_breaking_vehicle = car->distance(car);
   assert(expect_distance_vehicle == actual_breaking_vehicle);
   const double expect_distance_intersection = 0.0;
   const double actual_breaking_intersection = car->distance(i1);
   assert(expect_distance_intersection == actual_breaking_intersection);
   const double expect_breaking_speed = 0.0;
   const double actual_breaking_speed = car->breakingSpeed(0.0);
   assert(expect_breaking_speed == actual_breaking_speed);
   const int expect_id = 1;
   const int actual_id = car->getID();
   assert(expect_id == actual_id);
   const bool expect_status = false;
   const bool actual_status = car->getStatus();
   assert(expect_status == actual_status);
   const double expect_speed = 0.0;
   const double actual_speed = car->getSpeed();
   assert(expect_speed == actual_speed);
   const Intersection* expect_destination = i2;
   const Intersection* actual_destination = car->getDestination();
   assert(expect_destination == actual_destination);
   const std::list<Road*> expect_itinerary = track;
   const std::list<Road*> actual_itinerary = car->getItinerary();
   assert(expect_itinerary == actual_itinerary);
   const std::vector<double> expect_position = i1->getPosition();
   const std::vector<double> actual_position = car->getPosition();
   assert(expect_position == actual_position);
   Road* expected_next_road = r;
   Road* actual_next_road = car->nextRoad();
   assert(expected_next_road == actual_next_road);
   car->setNewItinerary(track);
   const std::list<Road*> expect_new_itinerary = track;
   const std::list<Road*> actual_new_itinerary = car->getItinerary();
   assert(expect_itinerary == actual_itinerary);
   car->updateItinerary();
   const std::list<Road*> expect_updated_itinerary {};
   const std::list<Road*> actual_updated_itinerary = car->getItinerary();
   assert(expect_itinerary == actual_itinerary);
   // To be checked:
   //void moveToVehicle(Vehicle * v);
   //void moveToIntersection(Intersection * i, int idRoad);
   //void displayVehicle();

   delete i1; i1 = nullptr;
   delete i2; i2 = nullptr;
   target = nullptr;
   delete r; r = nullptr;
}

// Unit tests for Bike class
void testsBike() {
   Intersection* i1 = new Intersection(1, { 0.0, 0.0 });
   Intersection* i2 = new Intersection(2, { 0.0, 10.0 });
   Intersection* target(i2);
   Road* r = new Road(1, i1, i2);
   std::list<Road*> track(1, r);
   Bike bike(i1, i2, 1, target, track);
   assert(i1);
   assert(i2);
   assert(target);
   assert(r);

   const double expect_speedMax = constants::speedMaxBike;
   const double actual_speedMax = bike.getSpeedMax();
   assert(expect_speedMax == actual_speedMax);
   const double expect_acceleration = constants::accelerationBike;
   const double actual_acceleration = bike.getAcceleration();
   assert(expect_acceleration == actual_acceleration);
   const double expect_width = constants::widthBike;
   const double actual_width = bike.getWidth();
   assert(expect_width == actual_width);
   const double expect_height = constants::heightBike;
   const double actual_height = bike.getHeight();
   assert(expect_height == actual_height);
   const double  expect_color[3] = { 0.0, 0.9, 0.9 };
   const double* actual_color    = bike.getColor();
   for (int i = 0; i < 3; i++) {
      assert(expect_color[i] == actual_color[i]);
   }

   delete i1; i1 = nullptr;
   delete i2; i2 = nullptr;
   target = nullptr;
   delete r; r = nullptr;
}

// Unit tests for Car class
void testsCar() {
   Intersection* i1 = new Intersection(1, { 0.0, 0.0 });
   Intersection* i2 = new Intersection(2, { 0.0, 10.0 });
   Intersection* target(i2);
   Road* r = new Road(1, i1, i2);
   std::list<Road*> track(1, r);
   Car car(i1, i2, 1, target, track);
   assert(i1);
   assert(i2);
   assert(target);
   assert(r);

   const double expect_speedMax = constants::speedMaxCar;
   const double actual_speedMax = car.getSpeedMax();
   assert(expect_speedMax == actual_speedMax);
   const double expect_acceleration = constants::accelerationCar;
   const double actual_acceleration = car.getAcceleration();
   assert(expect_acceleration == actual_acceleration);
   const double expect_width = constants::widthCar;
   const double actual_width = car.getWidth();
   assert(expect_width == actual_width);
   const double expect_height = constants::heightCar;
   const double actual_height = car.getHeight();
   assert(expect_height == actual_height);
   const double  expect_color[3] = { 0.0, 0.4, 0.9 };
   const double* actual_color    = car.getColor();
   for (int i = 0; i < 3; i++) {
      assert(expect_color[i] == actual_color[i]);
   }

   delete i1; i1 = nullptr;
   delete i2; i2 = nullptr;
   target = nullptr;
   delete r; r = nullptr;
}

// Unit tests for Truck class
void testsTruck() {
   std::cout << "testTruck" << std::endl;
   Intersection* i1 = new Intersection(1, { 0.0, 0.0 });
   Intersection* i2 = new Intersection(2, { 0.0, 10.0 });
   Intersection* target(i2);
   Road* r = new Road(1, i1, i2);
   std::list<Road*> track(1, r);
   Truck truck(i1, i2, 1, target, track);
   assert(i1);
   assert(i2);
   assert(target);
   assert(r);

   const double expect_speedMax = constants::speedMaxTruck;
   const double actual_speedMax = truck.getSpeedMax();
   assert(expect_speedMax == actual_speedMax);
   const double expect_acceleration = constants::accelerationTruck;
   const double actual_acceleration = truck.getAcceleration();
   assert(expect_acceleration == actual_acceleration);
   const double expect_width = constants::widthTruck;
   const double actual_width = truck.getWidth();
   assert(expect_width == actual_width);
   const double expect_height = constants::heightTruck;
   const double actual_height = truck.getHeight();
   assert(expect_height == actual_height);
   const double  expect_color[3] = { 0.0, 0.0, 0.9 };
   const double* actual_color    = truck.getColor();
   for (int i = 0; i < 3; i++) {
      assert(expect_color[i] == actual_color[i]);
   }

   delete i1; i1 = nullptr;
   delete i2; i2 = nullptr;
   target = nullptr;
   delete r; r = nullptr;
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
   std::cout << "All tests passed!" << std::endl;
}
