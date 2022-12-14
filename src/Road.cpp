// Libraries
//#include <list>         // To use lists // already included in vehicle.h
//#include <GL/glut.h>    // To display
#include <GLFW/glfw3.h> // To display
#if DEBUG
#include <iostream>     // To use input/output
#endif
// Header files
#include "../headers/Road.h"
#include "../headers/constants.h"

Road::Road(int n, Intersection* begin, Intersection* end)
   : idRoad(n), i1(begin), i2(end),
     length(pow(pow(begin->getPosition()[0] - end->getPosition()[0], 2) +
                  pow(begin->getPosition()[1] - end->getPosition()[1], 2), 0.5)),
     direction{ (end->getPosition()[0] - begin->getPosition()[0]) / length,
                (end->getPosition()[1] - begin->getPosition()[1]) / length },
     roadCoordinates{ direction[1] * constants::widthRoad / 2 + i1->getPosition()[0] * constants::ratioX + constants::margin,
                     -direction[0] * constants::widthRoad / 2 + i1->getPosition()[1] * constants::ratioY + constants::margin, 0,
                      direction[1] * constants::widthRoad / 2 + i2->getPosition()[0] * constants::ratioX + constants::margin,
                     -direction[0] * constants::widthRoad / 2 + i2->getPosition()[1] * constants::ratioY + constants::margin, 0 },
     sideLeft{ i1->getPosition()[0] * constants::ratioX + constants::margin,
               i1->getPosition()[1] * constants::ratioY + constants::margin, 0,
               i2->getPosition()[0] * constants::ratioX + constants::margin,
               i2->getPosition()[1] * constants::ratioY + constants::margin, 0 },
     sideRight{ direction[1] * constants::widthRoad + i1->getPosition()[0] * constants::ratioX + constants::margin,
               -direction[0] * constants::widthRoad + i1->getPosition()[1] * constants::ratioY + constants::margin, 0,
                direction[1] * constants::widthRoad + i2->getPosition()[0] * constants::ratioX + constants::margin,
               -direction[0] * constants::widthRoad + i2->getPosition()[1] * constants::ratioY + constants::margin, 0 },
     lightCoordinates{ direction[1] * constants::widthRoad / 2 + ((float)i2->getPosition()[0] - direction[0] / 6) * constants::ratioX + constants::margin,
                      -direction[0] * constants::widthRoad / 2 + ((float)i2->getPosition()[1] - direction[1] / 6) * constants::ratioY + constants::margin }{
}

bool Road::containVehicle() {
   return (Vehicles.empty()) ? false : true;
}

int Road::CountVehicles() {
   return Vehicles.size();
}

void Road::addVehicle(Vehicle* v) {
   Vehicles.push_back(v);
   v->setPosition(i1->getPosition());
   v->setDirection(i2);
}

void Road::removeVehicle() {
   Vehicles.pop_front();
}

void Road::moveVehicle() {
   if (containVehicle()) {
      // For the first car
      Vehicle* v = Vehicles.front();
      const bool atIntersection = v->distance(i2) < 0.1f;
      if (atIntersection) {
         if (v->nextRoad() == nullptr) {
            this->removeVehicle();
            v->setStatus(true);
            delete v;
            global::numberOfVehicles -= 1;
         }
         else {
            bool isEnoughSpace = v->nextRoad()->containVehicle() && v->nextRoad()->getVehicles().back()->distance(i2) > constants::distanceSecurity;
            if (!v->nextRoad()->containVehicle() || isEnoughSpace) {
               v->nextRoad()->addVehicle(v);
               v->updateItinerary();
               this->removeVehicle();
            }
         }
      }
      else
         v->moveToIntersection(i2, idRoad);
      // For the folowing cars
      // We ignore the case atIntersection = true, were the first car is gone
      if (Vehicles.size() > 1) {
         std::list<Vehicle*>::iterator v;
         Vehicle* VehicleNext = *Vehicles.begin();
         for (v = std::next(Vehicles.begin()); v != Vehicles.end(); ++v){//(Vehicle* v : Vehicles) {
            (*v)->moveToVehicle(VehicleNext);
            VehicleNext = (*v);
         }
      }
   }
}

void Road::displayRoad() {
   glEnable(GL_LINE_SMOOTH);
   glEnableClientState(GL_VERTEX_ARRAY);
   glScalef(1.f, 1.f, 0);
   // Road
   glColor3f(0.3f, 0.3f, 0.3f); // Grey
   glLineWidth(constants::widthRoad);
   glVertexPointer(3, GL_FLOAT, 0, roadCoordinates);
   glDrawArrays(GL_LINES, 0, 2);
   // Sides
   glColor3f(1.0f, 1.0f, 1.0f); // White
   glLineWidth(constants::widthRoad /10);
   glVertexPointer(3, GL_FLOAT, 0, sideLeft);
   glDrawArrays(GL_LINES, 0, 2);
   glVertexPointer(3, GL_FLOAT, 0, sideRight);
   glDrawArrays(GL_LINES, 0, 2);
   glDisableClientState(GL_VERTEX_ARRAY);
   glDisable(GL_LINE_SMOOTH);
}

void Road::displayLight() {
   // Outline
   glColor3f(0.0f, 0.0f, 0.0f); // Black
   glPointSize(constants::widthRoad);
   glEnable(GL_POINT_SMOOTH);
   glBegin(GL_POINTS);
   glVertex2f(lightCoordinates[0], lightCoordinates[1]);
   glEnd();
   // Outline without overlay
   //const GLfloat twoPi = 6.283f; // = 2.0f * 3.1415f
   //const int nStep = 10; // # of triangles used to draw ´the circle
   //const GLfloat step = 6.283f / nStep;
   //glLineWidth(constants::widthRoad / 5);
   //glColor3f(0.0f, 0.0f, 0.0f); // Black
   //glBegin(GL_LINE_LOOP);
   //for (int i = 0; i <= nStep; i++)
   //   glVertex2f(
   //      lightCoordinates[0] + (diameter * cos(i * step) / 2),
   //      lightCoordinates[1] + (diameter * sin(i * step) / 2)
   //   );
   //glEnd();
   // Inside
   if (i2->isRed(idRoad))
      glColor3f(1.0f, 0.0f, 0.0f); // Red
   else
      glColor3f(0.0f, 1.0f, 0.0f); // Green
   glPointSize(constants::widthRoad * 0.7);
   glBegin(GL_POINTS);
   glVertex2f(lightCoordinates[0], lightCoordinates[1]);
   glEnd();
   glDisable(GL_POINT_SMOOTH);
}

int Road::getID() {
   return idRoad;
}

float Road::getLength() {
   return length;
}

Intersection* Road::getStart() {
   return i1;
}

Intersection* Road::getEnd() {
   return i2;
}

std::list<Vehicle*> Road::getVehicles() {
   return Vehicles;
}

std::array<float, 2> Road::getDirection() {
   return direction;
}
