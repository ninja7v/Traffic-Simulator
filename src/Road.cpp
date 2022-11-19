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

Road::Road() {

}

Road::Road(int n, Intersection* begin, Intersection* end)
   : idRoad(n), i1(begin), i2(end) {
   length = pow(pow(begin->getPosition()[0] - end->getPosition()[0], 2) +
                pow(begin->getPosition()[1] - end->getPosition()[1], 2), 0.5);
   direction = { (end->getPosition()[0] - begin->getPosition()[0]) / length,
                 (end->getPosition()[1] - begin->getPosition()[1]) / length };
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
   // Remove at the begining
   Vehicles.pop_front();
}

void Road::moveVehicle() {
   // Condition contain car
   if (containVehicle()) {
      // For the first car
      Vehicle* v = Vehicles.front();
      bool atIntersection = v->distance(i2) < 0.1f;
      if (atIntersection) {
         if (v->nextRoad() == nullptr) {
            this->removeVehicle();
            //Network::removeVehicle(v);
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
      else {
         v->moveToIntersection(i2, idRoad);
      }
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
   // Road
   glScalef(1.f, 1.f, 0);
   glColor3f(0.3f, 0.3f, 0.3f); // Grey
   GLfloat lineRoad[] = { direction[1] * constants::widthRoad / 2 + i1->getPosition()[0] * constants::ratioX + constants::margin,
                         -direction[0] * constants::widthRoad / 2 + i1->getPosition()[1] * constants::ratioY + constants::margin, 0,
                          direction[1] * constants::widthRoad / 2 + i2->getPosition()[0] * constants::ratioX + constants::margin,
                         -direction[0] * constants::widthRoad / 2 + i2->getPosition()[1] * constants::ratioY + constants::margin, 0};
   glLineWidth(constants::widthRoad);
   glVertexPointer(3, GL_FLOAT, 0, lineRoad);
   glDrawArrays(GL_LINES, 0, 2);
   // Sides left
   glScalef(1.f, 1.f, 0);
   glColor3f(1.0f, 1.0f, 1.0f); // White
   GLfloat lineSideLeft[] = { i1->getPosition()[0] * constants::ratioX + constants::margin,
                              i1->getPosition()[1] * constants::ratioY + constants::margin, 0,
                              i2->getPosition()[0] * constants::ratioX + constants::margin,
                              i2->getPosition()[1] * constants::ratioY + constants::margin, 0 };
   glLineWidth(constants::widthRoad /10);
   glVertexPointer(3, GL_FLOAT, 0, lineSideLeft);
   glDrawArrays(GL_LINES, 0, 2);
   // Sides right
   glScalef(1.f, 1.f, 0);
   glColor3f(1.0f, 1.0f, 1.0f); // White
   GLfloat lineSideRight[] = { direction[1] * constants::widthRoad + i1->getPosition()[0] * constants::ratioX + constants::margin,
                              -direction[0] * constants::widthRoad + i1->getPosition()[1] * constants::ratioY + constants::margin, 0,
                               direction[1] * constants::widthRoad + i2->getPosition()[0] * constants::ratioX + constants::margin,
                              -direction[0] * constants::widthRoad + i2->getPosition()[1] * constants::ratioY + constants::margin, 0 };
   glLineWidth(constants::widthRoad / 10);
   glVertexPointer(3, GL_FLOAT, 0, lineSideRight);
   glDrawArrays(GL_LINES, 0, 2);
   glDisableClientState(GL_VERTEX_ARRAY);
   glDisable(GL_LINE_SMOOTH);
}

void Road::displayLight() {
   if (i2->isRed(idRoad)) {
      glColor3f(1.0f, 0.0f, 0.0f); // Red
   }
   else {
      glColor3f(0.0f, 1.0f, 0.0f); // Green
   }
   GLfloat x =  direction[1] * constants::widthRoad / 2 + ((float)i2->getPosition()[0] - direction[0] / 6) * constants::ratioX + constants::margin;
   GLfloat y = -direction[0] * constants::widthRoad / 2 + ((float)i2->getPosition()[1] - direction[1] / 6) * constants::ratioY + constants::margin;
   GLfloat radius = constants::widthRoad / 2.5;
   GLfloat twoPi = 2.0f * 3.1415f;
   int i;
   int n = 10; // # of triangles used to draw circle
   glBegin(GL_TRIANGLE_FAN);
   glVertex2f(x, y); // center of circle
   for (i = 0; i <= n; i++) {
      glVertex2f(
         x + (radius * cos(i * twoPi / n)),
         y + (radius * sin(i * twoPi / n))
      );
   }
   glEnd();
   glLineWidth(constants::widthRoad / 5);
   glColor3f(0.0f, 0.0f, 0.0f); // Black
   glBegin(GL_LINE_LOOP);
   for (i = 0; i <= n; i++) {
      glVertex2f(
         x + (radius * cos(i * twoPi / n)),
         y + (radius * sin(i * twoPi / n))
      );
   }
   glEnd();
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
