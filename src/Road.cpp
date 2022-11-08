// Libraries
#include <list>         // To manipulate lists
#include <iostream>     // To use input/output
#include <GL/glut.h>    // To display
#include <GLFW/glfw3.h> // To display
//#include <iterator>
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
   // Add at the end
   Vehicles.push_back(v);
   // Update direction
   v->updateDirection(i2);
   // Update itinerary
   v->updateItinerary();
   // Set the car at the intersection
   v->setPosition(i1->getPosition());
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
      // Conditions at the intersection
      if (v->distance(i2) < 0.001f) {
         if (v->nextRoad() == nullptr) {
            this->removeVehicle();
            //Network::removeVehicle(v);
            delete v;
            //v->setStatus(true);
            global::numberOfVehicles -= 1;
#if DEBUG
            std::cout << "-   o-o   Vehicle deleted" << std::endl;
#endif
         }
         else if ((v->nextRoad()->containVehicle() && v->distance(i1) > constants::distanceSecurity) || !v->nextRoad()->containVehicle()) {
            v->nextRoad()->addVehicle(v);
            this->removeVehicle();
         }
      }
      else {
         v->moveToIntersection(i2, idRoad);
      }
      // For the folowing cars
      if (Vehicles.size() > 1) {
         std::list<Vehicle*>::iterator v;
         Vehicle* VehicleNext = *Vehicles.begin();
         for (Vehicle* v : Vehicles) {
            v->moveToVehicle(VehicleNext);
            VehicleNext = v;
         }
      }
   }
}

void Road::displayRoad() {
   glEnable(GL_LINE_SMOOTH);
   glEnableClientState(GL_VERTEX_ARRAY);
   // Road
   glScalef(1.f, 1.f, 0);
   glColor3f(0.3f, 0.3f, 0.3f);
   GLfloat lineRoad[] = { direction[1] * constants::width / 2 + i1->getPosition()[0] * constants::ratioX + constants::margin,
                         -direction[0] * constants::width / 2 + i1->getPosition()[1] * constants::ratioY + constants::margin, 0,
                          direction[1] * constants::width / 2 + i2->getPosition()[0] * constants::ratioX + constants::margin,
                         -direction[0] * constants::width / 2 + i2->getPosition()[1] * constants::ratioY + constants::margin, 0};
   glLineWidth(constants::width);
   glVertexPointer(3, GL_FLOAT, 0, lineRoad);
   glDrawArrays(GL_LINES, 0, 2);
   // Sides left
   glScalef(1.f, 1.f, 0);
   glColor3f(1.0f, 1.0f, 1.0f);
   GLfloat lineSideLeft[] = { i1->getPosition()[0] * constants::ratioX + constants::margin,
                              i1->getPosition()[1] * constants::ratioY + constants::margin, 0,
                              i2->getPosition()[0] * constants::ratioX + constants::margin,
                              i2->getPosition()[1] * constants::ratioY + constants::margin, 0 };
   glLineWidth(constants::width /10);
   glVertexPointer(3, GL_FLOAT, 0, lineSideLeft);
   glDrawArrays(GL_LINES, 0, 2);
   // Sides right
   glScalef(1.f, 1.f, 0);
   glColor3f(1.0f, 1.0f, 1.0f);
   GLfloat lineSideRight[] = { direction[1] * constants::width + i1->getPosition()[0] * constants::ratioX + constants::margin,
                              -direction[0] * constants::width + i1->getPosition()[1] * constants::ratioY + constants::margin, 0,
                               direction[1] * constants::width + i2->getPosition()[0] * constants::ratioX + constants::margin,
                              -direction[0] * constants::width + i2->getPosition()[1] * constants::ratioY + constants::margin, 0 };
   glLineWidth(constants::width /10);
   glVertexPointer(3, GL_FLOAT, 0, lineSideRight);
   glDrawArrays(GL_LINES, 0, 2);
   glDisableClientState(GL_VERTEX_ARRAY);
   glDisable(GL_LINE_SMOOTH);
   // Trafic light
   if (i2->isRed(idRoad)) {
      glColor3f(1.0f, 0.0f, 0.0f);
   }
   else {
      glColor3f(0.0f, 1.0f, 0.0f);
   }
   GLfloat x =  direction[1] * constants::width /2 + ((float)i2->getPosition()[0] - direction[0]/4) * constants::ratioX + constants::margin;
   GLfloat y = -direction[0] * constants::width /2 + ((float)i2->getPosition()[1] - direction[1]/4) * constants::ratioY + constants::margin;
   GLfloat radius = 10;
   GLfloat twoPi = 2.0f * 3.1415f;
   int i;
   int n = 10; //# of triangles used to draw circle
   glBegin(GL_TRIANGLE_FAN);
   glVertex2f(x, y); // center of circle
   for (i = 0; i <= n; i++) {
      glVertex2f(
         x + (radius * cos(i * twoPi / n)),
         y + (radius * sin(i * twoPi / n))
      );
   }
   glEnd();
   glLineWidth(5);
   glColor3f(0.0f, 0.0f, 0.0f);
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
