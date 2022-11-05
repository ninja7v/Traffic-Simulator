// Libraries
#include <list>         // To manipulate lists
#include <iostream>     // To use input/output
#include <GL/glut.h>    // To display
#include <GLFW/glfw3.h> // To display
#include <iterator>
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

bool Road::containCar() {
   return (cars.empty()) ? false : true;
}

int Road::numberOfCars() {
   return cars.size();
}

void Road::addCar(Car* c) {
   // Add at the end
   cars.push_back(c);
   // Update direction
   c->updateDirection(i2);
   // Update itinerary
   c->updateItinerary();
   // Set the car at the intersection
   c->setPosition(i1->getPosition());
}

void Road::removeCar() {
   // Remove at the begining
   cars.pop_front();
}

void Road::moveCar() {
   // Condition contain car
   if (containCar()) {
      // For the first car
      Car* c = cars.front();
      // Conditions at the intersection
      if (c->distance(i2) < 0.001f) {
         if (c->nextRoad() == nullptr) {
            this->removeCar();
            delete c;
            global::numberOfCars -= 1;
            std::cout << "--------------------------------------" << std::endl;
         }
         else if ((c->nextRoad()->containCar() && c->distance(i1) > constants::distanceSecurity) || !c->nextRoad()->containCar()) {
            c->nextRoad()->addCar(c);
            this->removeCar();
         }
      }
      else {
         c->moveToIntersection(i2, idRoad);
      }
      // For the folowing cars
      if (cars.size() > 1) {
         std::list<Car*>::iterator c;
         Car* carNext = *cars.begin();
         for (Car* c : cars) {
            c->moveToCar(carNext);
            carNext = c;
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
   GLfloat twoPi = 2.0f * 3.1415;
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

std::list<Car*> Road::getCars() {
   return cars;
}

std::array<float, 2> Road::getDirection() {
   return direction;
}
