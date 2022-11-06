#pragma once
// Libraries
#include <algorithm> //for pow

namespace constants {
   // Network
   constexpr int sizeX{ 9 };
   constexpr int sizeY{ 6 };
   constexpr float boost{ 5.0f };
   // Roads
   constexpr int width{ 20 };
   constexpr float speedLimit{ 0.003f };
   constexpr int nbRoads{ (sizeX * (sizeY - 1)) + (sizeY * (sizeX - 1)) };
   constexpr int capacity{ 4 };
   // Cars
   constexpr float flow{ 1 }; // in [0, 99]
   constexpr float speedMaxCar{ 0.002f * boost };
   constexpr float speedMaxTruck{ 0.0001f * boost };
   constexpr float accelerationCar{ 0.000002f * boost };
   constexpr float accelerationTruck{ 0.0000002f * boost };
   constexpr float distanceSecurity{ 0.1f };
   //constexpr float coefficient{ speedMax * distanceSecurity };
   // Intersections
   constexpr int nbIntersections{ sizeX * sizeY / 4 };
   constexpr int furthest{ sizeX + sizeY - 1 };
   constexpr int period{ (int)(1000 / boost) };
   //constexpr int durationMax{ (int)(flow / speedMax) * 20 };
   constexpr int limitTest{ (int)(period / 5) + 1 };
   constexpr int stepTest{ period / 5 };
   // Window
   constexpr int SIZE{ 100 };
   constexpr int margin{ 100 };
   constexpr int SCREEN_WIDTH{ sizeX * SIZE + 2*margin };
   constexpr int SCREEN_HEIGHT{ sizeY * SIZE + 2*margin };
   constexpr int ratioX{ /*1*/(SCREEN_WIDTH - 2*margin) / (sizeX - 1) };  // If sizeX>1
   constexpr int ratioY{ /*1*/(SCREEN_HEIGHT - 2*margin) / (sizeY - 1) }; // If sizeY>1
   constexpr int timeMax{ 100 };//milisecond
}
