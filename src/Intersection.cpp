// Libraries
#include <GL/glut.h>    // To display
#include <GLFW/glfw3.h> // To display
#include <time.h>       // To use clock()
// Header files
#include "../headers/Constants.h"
#include "../headers/Global.h"
#include "../headers/Intersection.h"

Intersection::Intersection() {

}

Intersection::Intersection(int n = 0, std::array<float, 2> pos = { 0, 0 })
   :idIntersection(n), position(pos) {
}

bool Intersection::isRed(int id) {
   //non constant with every different intersection
   //return (rl->numberOfCars() > rd->numberOfCars() == 0) ? false : true;
   //constant with every identical intersection
   int currentPeriod = ((clock() - global::t0) / constants::period);
   return (input[currentPeriod % input.size()] == id) ? true : false;
}

void Intersection::displayIntersection() {
   glColor3f(0.0f, 0.0f, 0.0f);
   GLfloat x = position[0] * constants::ratioX + constants::margin;
   GLfloat y = position[1] * constants::ratioY + constants::margin;
   GLfloat radius = 25;
   int i;
   int triangleAmount = 20; //# of triangles used to draw circle

   //GLfloat radius = 0.8f; //radius
   GLfloat twicePi = 2.0f * 3.1415;

   glBegin(GL_TRIANGLE_FAN);
   glVertex2f(x, y); // center of circle
   for (i = 0; i <= triangleAmount; i++) {
      glVertex2f(
         x + (radius * cos(i * twicePi / triangleAmount)),
         y + (radius * sin(i * twicePi / triangleAmount))
      );
   }
   glEnd();


   /*glEnable(GL_POINT_SMOOTH);
   glEnableClientState(GL_VERTEX_ARRAY);
   GLfloat point[] = { (float)posX * constants::ratioX + constants::margin, (float)posY * constants::ratioY + constants::margin };
   glColor3f(0.0f, 0.0f, 0.0f);
   glScalef(1.f, 1.f, 0);
   glPointSize(30);
   glVertexPointer(2, GL_FLOAT, 0, point);
   glDrawArrays(GL_POINTS, 0, 1);
   glDisableClientState(GL_VERTEX_ARRAY);
   glDisable(GL_POINT_SMOOTH);*/
}

void Intersection::addInputRoad(int id) {
   input.push_back(id);
}

std::array<float, 2> Intersection::getPosition() {
   return position;
}

int Intersection::getID() {
   return idIntersection;
}

int Intersection::getDurationTrafficLight() {
   return durationTrafficLight;
}

int Intersection::getPeriodTrafficLight() {
   return periodTrafficLight;
}
