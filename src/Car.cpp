// Libraries
#include <list>      // To use lists
#include <cstdlib>   // To use rand()
#include <iostream>  // To use input/output
#include <GL/glut.h> // To display
#include <time.h>    // To use clock()
#include <array>     // To use arrays
// Header files
#include "Constants.h"
#include "Global.h"
#include "Car.h"

Car::Car(Intersection* i1, Intersection* i2, int id, Intersection* target, std::list<Road*> track)
   : idCar(id), destination(target), itinerary(track) {
   position = i1->getPosition();
   updateDirection(i2);
   speed = 0.0f; // Unit is pixel per seconds
}

float Car::speedFunction(float dist) {
   // Constant
   //return constants::speedMax;
   // Simple
   //return constants::speedMax - (constants::coefficient / dist);
   // Greenshield
   return constants::speedMaxCar * (1 - (float)pow(constants::distanceSecurity / dist, 2.0));
   // Underwood
   //return constants::speedMax * (1 - exp(-pow(dist - constants::distanceSecurity, 2.0)));
}

float Car::phi(bool red) {
   return (red) ? 0 : 1.0f;
}

void Car::moveToCar(Car* c) {
   // Distance with the car ahead
   float d = distance(c);
   // Updating speed
   if (d < constants::distanceSecurity) {
      speed = 0; // Pound!
   }
   else {
      speed = (speed < speedFunction(d)) ? speed + constants::accelerationCar : speedFunction(d);
   }
   // Moving
   float coef = speed * (clock() - tc) / 1;
   position[0] += direction[0] * coef;
   position[1] += direction[1] * coef;
   tc = clock();
}

void Car::moveToIntersection(Intersection* i, int idRoad) {
   // Taking traffic light information
   bool isRed = i->isRed(idRoad) ? true : false;
   // Distance with the intersection ahead
   float d = distance(i);
   // Updating speed
   if (isRed) {
      if (d < constants::distanceSecurity) {
         speed = (speed < speedFunction(d)) ? speed + constants::accelerationCar : constants::speedMaxCar;
      }
      else {
         speed = (speed < speedFunction(d)) ? speed + constants::accelerationCar : speedFunction(d);
      }
   }
   else {
      speed = (speed < constants::speedMaxCar) ? speed + constants::accelerationCar : constants::speedMaxCar;
   }
   // Moving
   float coef = speed * (clock() - tc) / 1;
   position[0] += direction[0] * coef;
   position[1] += direction[1] * coef;
   tc = clock();
}

void Car::displayCar() {
   float size = 15;
   float frame[4][2] = { {direction[1] * constants::width / 2 + (- direction[0] - direction[1]/2) * size + position[0] * constants::ratioX + constants::margin,
                         -direction[0] * constants::width / 2 + (+ direction[0]/2 - direction[1]) * size + position[1] * constants::ratioY + constants::margin},
                         {direction[1] * constants::width / 2 + (- direction[0] + direction[1]/2) * size + position[0] * constants::ratioX + constants::margin,
                         -direction[0] * constants::width / 2 + (- direction[0]/2 - direction[1]) * size + position[1] * constants::ratioY + constants::margin},
                         {direction[1] * constants::width / 2 + (+ direction[0] + direction[1]/2) * size + position[0] * constants::ratioX + constants::margin,
                         -direction[0] * constants::width / 2 + (- direction[0]/2 + direction[1]) * size + position[1] * constants::ratioY + constants::margin},
                         {direction[1] * constants::width / 2 + (+ direction[0] - direction[1]/2) * size + position[0] * constants::ratioX + constants::margin,
                         -direction[0] * constants::width / 2 + (+ direction[0]/2 + direction[1]) * size + position[1] * constants::ratioY + constants::margin}, };
   glColor3f(0.0f, 0.0f, 0.5f);
   glBegin(GL_QUADS);
   glEnableClientState(GL_VERTEX_ARRAY);
   glVertex2f(frame[0][0], frame[0][1]);
   glVertex2f(frame[1][0], frame[1][1]);
   glVertex2f(frame[2][0], frame[2][1]);
   glVertex2f(frame[3][0], frame[3][1]);
   glEnd();
   glFlush();
   glDrawArrays(GL_QUADS, 0, 1);
   glEnableClientState(GL_VERTEX_ARRAY);
   /*GLfloat point[] = { posX * constants::ratioX, posY * constants::ratioY };
   glPointSize(15);
   glColor3f(0.0f, 0.0f, 0.5f);
   glVertexPointer(2, GL_FLOAT, 0, point);
   glDrawArrays(GL_POINTS, 0, 1);*/
}

Road* Car::nextRoad() {
   return (itinerary.empty()) ? nullptr : itinerary.front();
}

void Car::updateDirection(Intersection* i) {
   float d = distance(i);
   direction = { (i->getPosition()[0] - position[0]) / d,
                 (i->getPosition()[1] - position[1]) / d };
}

void Car::updateItinerary() {
   if (!itinerary.empty()) {
      itinerary.pop_front();
   }
}

float Car::distance(Car* c) {
   return pow(pow(position[0] - c->position[0], 2) + pow(position[1] - c->position[1], 2), 0.5);
}

float Car::distance(Intersection* i) {
   return pow(pow(position[0] - i->getPosition()[0], 2) + pow(position[1] - i->getPosition()[1], 2), 0.5);
}

int Car::getID() {
   return idCar;
}

float Car::getSpeed() {
   return speed;
}

Intersection* Car::getDestination() {
   return destination;
}

std::list<Road*> Car::getItinerary() {
   return itinerary;
}

std::array<float, 2> Car::getPosition() {
   return position;
}

void Car::setPosition(std::array<float, 2> pos) {
   position = pos;
}
