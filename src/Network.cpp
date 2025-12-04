// Libraries
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h> // To use stbi_load()
#include <GLFW/glfw3.h>    // To display
#include <ctime>           // To use clock()
#include <unordered_map>   // To use unordered_map
#include <vector>          // To vectors
#include <array>           // To arrays
#include <delaunator.hpp>  // To compute the Delaunay triangulation
#if DEBUG
#include <iostream>        // To use input/output
#endif
// Headers
#include "../headers/Global.h"
#include "../headers/Car.h"
#include "../headers/Bike.h"
#include "../headers/Truck.h"
#include "../headers/Network.h"

struct VectorHash {
   size_t operator()(const std::vector<double>& vec) const {
      size_t seed = 0;
      for (const auto& i : vec) {
         seed ^= std::hash<double>{}(i)+0 + (seed << 6) + (seed >> 2);//+0x9e3779b9
      }
      return seed;
   }
};

struct VectorEqual {
   bool operator()(const std::vector<double>& vec1, const std::vector<double>& vec2) const {
      return vec1 == vec2;
   }
};

Network::Network() {
   srand(static_cast<unsigned int>(time(nullptr)));
   auto distance = [&](std::vector<double> p1, std::vector<double> p2) {
      return sqrt(pow(p2[0] - p1[0], 2) + pow(p2[1] - p1[1], 2));
   };
   auto isPositionValid = [&](const std::vector<double>& p) {
      for (const auto& i : Intersections) {
         if (i && distance(p, i->getPosition()) < constants::minGap) {
            return false;
         }
      }
      return true;
   };
   std::unordered_map<const std::vector<double>, Intersection*, VectorHash, VectorEqual> card; //
   std::vector<double> positions; // x0, y0, x1, y1, ...
   for (int k = 0; k < constants::nbIntersections; k++) {
      std::vector<double> position(2);
      do {
         position[0] = rand() % constants::sizeX;
         position[1] = rand() % constants::sizeY;
      } while (!isPositionValid(position));
      positions.push_back(position[0]);
      positions.push_back(position[1]);
      Intersections.push_back(std::make_unique<Intersection>(k, position));
      card.emplace(position, Intersections.back().get()); //
   }
#if DEBUG
   std::cout << "x   Intersection initialized" << std::endl;
#endif
   // Roads
   delaunator::Delaunator d(positions); // Informations here: https://github.com/delfrrr/delaunator-cpp
   int id = 0;
   for (size_t i = 0; i < d.triangles.size(); i += 3) {
      // 3 iterations for the 3 sides
      for (int j = 0; j < 3; j ++) {
         int l = j == 2 ? 0 : j + 1;
         std::vector<double> begin{d.coords[2 * d.triangles[i + j]],
                                   d.coords[2 * d.triangles[i + j] + 1]};
         std::vector<double> end{d.coords[2 * d.triangles[i + l]],
                                 d.coords[2 * d.triangles[i + l] + 1]};
         auto r = std::make_unique<Road>(id, card[begin], card[end]);
         if (r)
         {
            Road* r_ptr = r.get();
            Roads.push_back(std::move(r));
            map.setConnection(card[begin]->getID(), card[end]->getID(), r_ptr);
            card[end]->addInputRoad(r_ptr);
            id++;
         }
      }
   }
#if DEBUG
   std::cout << "=   Roads initialized" << std::endl;
   std::cout << "*   Network initialized" << std::endl;
#endif
}

void Network::displayNetwork() {
   // Initialize GLFW
   if (!glfwInit()) {
      return;
   }
   // Create windows
   GLFWwindow* window = glfwCreateWindow(constants::SCREEN_WIDTH, constants::SCREEN_HEIGHT, "Traffic Simulator", nullptr, nullptr);
   if (!window) {
      glfwTerminate();
      return;
   }
   // Add icon
   int width, height, channels; // Doesn't need to be initialized
   unsigned char* pixels = stbi_load("Graphics/logo_TS.png", &width, &height, &channels, 4);
   if (pixels) {
      GLFWimage logo;
      logo.width  = width;
      logo.height = height;
      logo.pixels = pixels;
      glfwSetWindowIcon(window, 1, &logo);
   }
   // Make the window's context current
   glfwMakeContextCurrent(window);
   glViewport(0, 0, constants::SCREEN_WIDTH, constants::SCREEN_HEIGHT); // specifies the part of the window to which OpenGL will draw (in pixels)
   glMatrixMode(GL_PROJECTION); // Projection matrix defines the properties of the camera that views the objects in the world coordinate frame
   glLoadIdentity();            // Replace the current matrix with the identity matrix and starts us a fresh one
   glOrtho(0, constants::SCREEN_WIDTH, 0, constants::SCREEN_HEIGHT, 0, 1); // Set coordinate system
   glMatrixMode(GL_MODELVIEW);  // (default matrix mode) modelview matrix defines how objects are transformed (meaning translation, rotation and scaling)
   glLoadIdentity();            // same as above comment
   glClearColor(0.1f, 0.5f, 0.1f, 0); // Set background color as green
#if DEBUG
   std::cout << "[]   Windows created" << std::endl;
   //int T1 = global::t0; // For the frame timer
#endif
   // Initialize time
   global::t0 = clock();
   while (!glfwWindowShouldClose(window)) {
      glClear(GL_COLOR_BUFFER_BIT);
      // Roads
      for (const auto& r_ptr : Roads) {
         Road* r = r_ptr.get();
         if (r)
         {
            r->displayRoad();
            map.updateConnection(r);
         }
      }
      // Vehicle
      this->addVehicle();
      this->updateVehiclesPosition();
      Vehicles.remove_if([](std::shared_ptr<Vehicle> v) {
                            if (v->getStatus()) {
                               return true; // Remove the vehicle
                            }
                            v->displayVehicle();
                            return false; // Keep the vehicle
                         });
#if DEBUG
         //std::cout << "-   o-o   Vehicle deleted" << std::endl;
#endif
      // Intersections
      for (const auto& i_ptr : Intersections) {
         Intersection* i = i_ptr.get();
         if (i) {
            i->update(); // Update RL logic
            i->displayIntersection();
         }
      }
      // Traffic lights
      for (const auto& r_ptr : Roads) {
         Road* r = r_ptr.get();
         if (r)
            r->displayLight();
      }
      // Swap front and back buffers
      glfwSwapBuffers(window);
      // Poll for and process events
      glfwPollEvents();
#if DEBUG
      //std::cout << global::numberOfVehicles << std::endl;
      //std::cout << "Frame displayed " << clock() - T1 << "ms" << std::endl; // average frame time: 70ms
      //T1 = clock();
#endif
   }
   glfwTerminate();
}

void Network::addVehicle() {
   // To Do: add check target
   auto target = [&](int idStart) {int destination;
                                   do {destination = rand() % constants::nbIntersections;
                                   } while (destination == idStart);
                                   return Intersections[destination].get();};
   if (Vehicles.size() < constants::nbVehicleMax)
      for (const auto& r_ptr : Roads) {
         Road* r = r_ptr.get();
         if (r &&
             ((r->containVehicle() && r->getVehicles().back()->distance(r->getStart()) > 0.001) ||
              !r->containVehicle()) &&
             rand() % 100 < constants::flow) {
            Intersection* destination = target(r->getEnd()->getID());
            // Generate a random number to select the vehicle type
            int vehicleType = rand() % 3;
            // Create the appropriate vehicle based on the random type
            std::shared_ptr<Vehicle> v;
            switch (vehicleType) {
               case 0:{
                  v = std::make_shared<Car>(r->getStart(), r->getEnd(), r->getID(), destination, map.track(r->getEnd(), destination));
                  break;
               }
               case 1:{
                  v = std::make_shared<Bike>(r->getStart(), r->getEnd(), r->getID(), destination, map.track(r->getEnd(), destination));
                  break;
               }
               case 2:{
                  v = std::make_shared<Truck>(r->getStart(), r->getEnd(), r->getID(), destination, map.track(r->getEnd(), destination));
                  break;
               }
            }
            Vehicles.push_back(v);
            r->addVehicle(v);
            global::numberOfVehicles += 1;
         }
      }
}

void Network::updateVehiclesPosition() {
   for (const auto& r_ptr : Roads) {
      Road* r = r_ptr.get();
      if (r)
         r->moveVehicles();
   }
}

// Unused
//void Network::resetVehicles() {
//   for (Vehicle* v : Vehicles) {
//      if (v)
//         delete v; v = nullptr;
//   }
//   global::numberOfVehicles = 0;
//};
