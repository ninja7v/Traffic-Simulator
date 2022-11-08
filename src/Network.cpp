// Libraries
#include <cstdlib>      // To use rand()
#include <string>       // To debug
#include <iostream>     // To use input/output
#include <list>         // To use lists
//#include <algorithm>
#include <GL/glut.h>    // To display
#include <GLFW/glfw3.h> // To display
#include <time.h>       // To use clock()
// Header files
#include "omp.h"        // To parallelize
#include "../headers/Global.h"
#include "../headers/Car.h"
#include "../headers/Truck.h"
#include "../headers/Network.h"

Network::Network() {
   // Intersections
   std::array<float, 2> position = {0, 0};
#pragma omp parallel for
   for (int k = 0; k < constants::nbIntersections; k++) {
      bool validPosition = false;
      while (!validPosition) {
         position[0] = rand() % constants::sizeX;
         position[1] = rand() % constants::sizeY;
         if (!Intersections.empty()) {
            for (Intersection* i : Intersections) {
               if (!(i->getPosition() == position)) {
                  validPosition = true;
               }
            }
         }
         else {
            validPosition = true;
         }
      }
      Intersections.push_back(new Intersection(k, position));
   }
#if DEBUG
   std::cout << "x   Intersection initialized" << std::endl;
#endif
   // Roads
   for (Intersection* const& i : Intersections) {
      int nbConnections = rand() % 3 + 1;
      int id = 0;
      int idIntersection;
      bool validIntersection = false;
      for (int k = 0; k < nbConnections; k++) {
         validIntersection = false;
         while (!validIntersection) {
            idIntersection = rand() % constants::nbIntersections;
            if (!(map.getConnection(i->getID(), idIntersection) != nullptr || (idIntersection == i->getID()))) {
               validIntersection = true;
            }
         }
         Road* r(new Road(id, i, Intersections[idIntersection]));
         Roads.push_back(r);
         map.setConnection(i->getID(), idIntersection, r);
         Intersections[idIntersection]->addInputRoad(r->getID());
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
   glfwMakeContextCurrent(window);
   glViewport(0.0f, 0.0f, constants::SCREEN_WIDTH, constants::SCREEN_HEIGHT); // specifies the part of the window to which OpenGL will draw (in pixels), convert from normalised to pixels
   glMatrixMode(GL_PROJECTION); // projection matrix defines the properties of the camera that views the objects in the world coordinate frame. Here you typically set the zoom factor, aspect ratio and the near and far clipping planes
   glLoadIdentity(); // replace the current matrix with the identity matrix and starts us a fresh because matrix transforms such as glOrpho and glRotate cumulate, basically puts us at (0, 0, 0)
   glOrtho(0, constants::SCREEN_WIDTH, 0, constants::SCREEN_HEIGHT, 0, 1); // essentially set coordinate system
   glMatrixMode(GL_MODELVIEW); // (default matrix mode) modelview matrix defines how your objects are transformed (meaning translation, rotation and scaling) in your world
   glLoadIdentity(); // same as above comment
#if DEBUG
   std::cout << "|_|   Windows created" << std::endl;
#endif
   // Initialize time
   global::t0 = clock();
   while (!glfwWindowShouldClose(window)) {
      glClear(GL_COLOR_BUFFER_BIT);
      // Roads
#pragma omp parallel for
      for (Road* const& r : Roads) {
         r->displayRoad();
      }
      // Intersections
#pragma omp parallel for
      for (Intersection* i : Intersections) {
         i->displayIntersection();
      }
      // Vehicle
      this->addVehicle();
      this->updateVehiclesPosition();
      std::list<std::list<Vehicle*>::iterator> toDelete;
#pragma omp parallel for
      for (auto v = Vehicles.begin(); v != Vehicles.end(); v++)
         if ((*v)->getStatus())
            toDelete.push_back(v);
         else
            (*v)->displayVehicle();
#pragma omp parallel for
      for (auto it : toDelete)
         Vehicles.erase(it);

      // Timer 
      glClearColor(0.1f, 0.5f, 0.1f, 0);
      //glColor3f(1.0f, 1.0f, 1.0f);
      //timer.displayTime(std::to_string(timer.timer(timeMax)));
      // Swap front and back buffers
      glfwSwapBuffers(window);
      // Poll for and process events
      glfwPollEvents();
#if DEBUG
      //std::cout << global::numberOfVehicle << std::endl;
      //std::cout << "Frame displayed." << std::endl;
#endif
   }
   glfwTerminate();
}

void Network::addVehicle() {
   auto target = [&]() {return Intersections[rand() % constants::nbIntersections];};
#pragma omp parallel for
   for (Road* r : Roads) {
      if (((r->containVehicle() && r->getVehicles().back()->distance(r->getStart()) > constants::distanceSecurity) ||
           !r->containVehicle()) &&
            rand() % 1000 < constants::flow) {
         Intersection* destination = target();
         if (rand() % 2 == 0) {
            Car* v = new Car(r->getStart(), r->getEnd(), r->getID(), destination, map.track(r->getStart(), destination));
            Vehicles.push_back(v);
            r->addVehicle(v);
         }
         else {
            Truck* v = new Truck(r->getStart(), r->getEnd(), r->getID(), destination, map.track(r->getStart(), destination));
            Vehicles.push_back(v);
            r->addVehicle(v);
         }
         global::numberOfVehicles += 1;
#if DEBUG
         std::cout << "+   o-o   Vehicle added" << std::endl;
#endif
      }
   }
}

void Network::updateVehiclesPosition() {
#pragma omp parallel for
   for (Road* r : Roads) {
      r->moveVehicle();
   }
}

void Network::optimization(bool travelDirection) {
// for a constant duration, there are 2 variables to optimize:
// "duration" and "start" (phase)
}

void Network::resetVehicles() {
#pragma omp parallel for
   for (Vehicle* v : Vehicles) {
      delete v;
   }
   global::numberOfVehicles = 0;
};
