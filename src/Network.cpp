// Libraries
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h> // To use stbi_load()
//#include <GL/glut.h>       // To display
#include <GLFW/glfw3.h>    // To display
#include <time.h>          // To use clock()
//#include <thread>          // To use threads // Not used yet, but to display a waiting image in the future
#include <unordered_map>   // To use unordered_map
//#include <vector>          // To vectors // Already included
//#include <array>           // To arrays // Already included
#include <delaunator.hpp>  // To compute the Delaunay triangulation
#if DEBUG
#include <iostream>        // To use input/output
#endif
// Header files
#include "../headers/Global.h"
#include "../headers/Car.h"
#include "../headers/Bike.h"
#include "../headers/Truck.h"
#include "../headers/Network.h"

Network::Network() {
   // Intersections
   //std::unordered_map<std::array<float, 2>, Intersection*> card;
   std::vector<double> positions; // x0, y0, x1, y1, ...
   std::array<float, 2> position;
   int k;
   float x, y;
   auto distance = [&](std::array<float, 2> p) {
      return (float)pow(pow(x - p[0], 2) + pow(y - p[1], 2), 0.5);
   };
   srand(time(nullptr));
   for (k = 0; k < constants::nbIntersections; k++) {
      bool validPosition = false;
      while (!validPosition) {
         validPosition = true;
         x = rand() % constants::sizeX;
         y = rand() % constants::sizeY;
         if (!Intersections.empty())
            for (Intersection* i : Intersections)
               if (distance(i->getPosition()) < constants::minGap)
                  validPosition = false;
      }
      positions.push_back(x);
      positions.push_back(y);
      position[0] = positions[2 * k];
      position[1] = positions[2 * k + 1];
      Intersections.push_back(new Intersection(k, position));
      //card.emplace(position, Intersections.back());
   }
#if DEBUG
   std::cout << "x   Intersection initialized" << std::endl;
#endif
   // Roads
   /*delaunator::Delaunator d(positions); // Informations here: https://github.com/delfrrr/delaunator-cpp
   std::array<float, 2> begin;
   std::array<float, 2> end;
   int id = 0;
   for (std::size_t i = 0; i < d.triangles.size(); i += 3) {
      begin[0] = d.coords[2 * d.triangles[i    ]    ];
      begin[1] = d.coords[2 * d.triangles[i    ] + 1];
      end[0]   = d.coords[2 * d.triangles[i + 1]    ];
      end[1]   = d.coords[2 * d.triangles[i + 1] + 1];
      Road* r0(new Road(id, card[begin], card[end]));
      Roads.push_back(r0);
      map.setConnection(card[begin]->getID(), card[end]->getID(), r0);
      card[end]->addInputRoad(r0->getID());
      id++;
      begin[0] = d.coords[2 * d.triangles[i + 1]    ];
      begin[1] = d.coords[2 * d.triangles[i + 1] + 1];
      end[0]   = d.coords[2 * d.triangles[i + 2]    ];
      end[1]   = d.coords[2 * d.triangles[i + 2] + 1];
      Road* r1(new Road(id, card[begin], card[end]));
      Roads.push_back(r1);
      map.setConnection(card[begin]->getID(), card[end]->getID(), r1);
      card[end]->addInputRoad(r1->getID());
      id++;
      begin[0] = d.coords[2 * d.triangles[i + 2]    ];
      begin[1] = d.coords[2 * d.triangles[i + 2] + 1];
      end[0]   = d.coords[2 * d.triangles[i    ]    ];
      end[1]   = d.coords[2 * d.triangles[i    ] + 1];
      Road* r2(new Road(id, card[begin], card[end]));
      Roads.push_back(r2);
      map.setConnection(card[begin]->getID(), card[end]->getID(), r2);
      card[end]->addInputRoad(r2->getID());
      id++;
   }*/
   int id = 0;
   for (Intersection* const& i : Intersections) {
      int nbConnections = rand() % 3 + 1;
      int idIntersection;
      bool validIntersection = false;
      for (int k = 0; k < nbConnections; k++) {
         validIntersection = false;
         while (!validIntersection) {
            idIntersection = rand() % constants::nbIntersections;
            if (map.getConnection(i->getID(), idIntersection) == nullptr && (idIntersection != i->getID())) {
               validIntersection = true;
            }
         }
         // One-way road
         Road* r0(new Road(id, i, Intersections[idIntersection]));
         Roads.push_back(r0);
         map.setConnection(i->getID(), idIntersection, r0);
         Intersections[idIntersection]->addInputRoad(r0->getID());
         id += 1;
         // Two-way road
         Road* r1(new Road(id, Intersections[idIntersection], i));
         Roads.push_back(r1);
         map.setConnection(idIntersection, i->getID(), r1);
         i->addInputRoad(r1->getID());
         id += 1;
      }
   }
#if DEBUG
   std::cout << "=   Roads initialized" << std::endl;
   std::cout << "*   Network initialized" << std::endl;
#endif
}

void Network::displayNetwork() {
   // Create windows
   GLFWwindow* window;
   glfwInit();
   window = glfwCreateWindow(constants::SCREEN_WIDTH, constants::SCREEN_HEIGHT, "Traffic Simulator", NULL, NULL);
   // Add icon
   int width, height, channels; // Doesn't need to be initialized
   unsigned char* pixels = stbi_load("Graphics/logo_TS.png", &width, &height, &channels, 4);
   GLFWimage logo;
   logo.width  = width;
   logo.height = height;
   logo.pixels = pixels;
   glfwSetWindowIcon(window, 1, &logo);
   // Do some stuff
   glfwMakeContextCurrent(window);
   glViewport(0.0f, 0.0f, constants::SCREEN_WIDTH, constants::SCREEN_HEIGHT); // specifies the part of the window to which OpenGL will draw (in pixels), convert from normalised to pixels
   glMatrixMode(GL_PROJECTION); // projection matrix defines the properties of the camera that views the objects in the world coordinate frame. Here you typically set the zoom factor, aspect ratio and the near and far clipping planes
   glLoadIdentity(); // replace the current matrix with the identity matrix and starts us a fresh because matrix transforms such as glOrpho and glRotate cumulate, basically puts us at (0, 0, 0)
   glOrtho(0, constants::SCREEN_WIDTH, 0, constants::SCREEN_HEIGHT, 0, 1); // essentially set coordinate system
   glMatrixMode(GL_MODELVIEW); // (default matrix mode) modelview matrix defines how your objects are transformed (meaning translation, rotation and scaling) in your world
   glLoadIdentity(); // same as above comment
#if DEBUG
   std::cout << "|_|   Windows created" << std::endl;
   //int T1 = global::t0; // For the frame timer
#endif
   // Initialize time
   global::t0 = clock();
   while (!glfwWindowShouldClose(window)) {
      glClear(GL_COLOR_BUFFER_BIT);
      // Set background color
      glClearColor(0.1f, 0.5f, 0.1f, 0); // Green
      // Roads
      for (Road* const& r : Roads)
         r->displayRoad();
      // Vehicle
      this->addVehicle();
      this->updateVehiclesPosition();
      std::list<std::list<Vehicle*>::iterator> toDelete;
      for (auto v = Vehicles.begin(); v != Vehicles.end(); v++)
         if ((*v)->getStatus())
            toDelete.push_back(v);
         else
            (*v)->displayVehicle();
      for (auto it : toDelete) {
         Vehicles.erase(it);
#if DEBUG
         //std::cout << "-   o-o   Vehicle deleted" << std::endl;
#endif
      }
      // Intersections
      for (Intersection* i : Intersections) {
         i->displayIntersection();
      }
      // Traffic lights
      for (Road* const& r : Roads) {
         r->displayLight();
      }
      // Swap front and back buffers
      glfwSwapBuffers(window);
      // Poll for and process events
      glfwPollEvents();
#if DEBUG
      //std::cout << global::numberOfVehicle << std::endl;
      //std::cout << "Frame displayed " << clock() - T1  << "ms" << std::endl;
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
                                   return Intersections[destination];};
   if (Vehicles.size() < constants::nbVehicleMax)
      for (Road* r : Roads) {
         if (((r->containVehicle() && r->getVehicles().back()->distance(r->getStart()) > 0.001) ||
              !r->containVehicle()) &&
               rand() % 100 < constants::flow) {
            Intersection* destination = target(r->getEnd()->getID());
            Vehicle* v;
            switch (rand() % 3) {
               case 0:{
                  v = new Car(r->getStart(), r->getEnd(), r->getID(), destination, map.track(r->getEnd(), destination));
                  break;
               }
               case 1:{
                  v = new Bike(r->getStart(), r->getEnd(), r->getID(), destination, map.track(r->getEnd(), destination));
                  break;
               }
               case 2:{
                  v = new Truck(r->getStart(), r->getEnd(), r->getID(), destination, map.track(r->getEnd(), destination));
                  break;
               }
            }
            Vehicles.push_back(v);
            r->addVehicle(v);
            global::numberOfVehicles += 1;
#if DEBUG
            //std::cout << "+   o-o   Vehicle added " << std::endl;
#endif
         }
      }
}

void Network::updateVehiclesPosition() {
   for (Road* r : Roads)
      r->moveVehicle();
}

// Unused
//void Network::resetVehicles() {
//   for (Vehicle* v : Vehicles) {
//      delete v;
//   }
//   global::numberOfVehicles = 0;
//};
