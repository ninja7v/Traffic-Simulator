#pragma once
// Libraries
#include<algorithm> // Tu use max()

namespace constants {
   // Network
   constexpr int sizeX{ 11 };
   constexpr int sizeY{ 7 };
   constexpr int nbRoads{ (sizeX * (sizeY - 1)) + (sizeY * (sizeX - 1)) };
   constexpr float boost{ 5.0f };
   constexpr float zoom{ 1.0f };
   // Roads
   constexpr float widthRoad{ 15 * zoom };
   constexpr float speedLimit{ 0.003f * boost };
   // Vehicles
   constexpr float flow{ 1 }; // in [0, 99]
   constexpr float speedMaxCar  { 0.002f  * boost };
   constexpr float speedMaxBike { 0.002f * boost };
   constexpr float speedMaxTruck{ 0.0015f * boost };
   constexpr float accelerationCar  { 0.000003f * boost };
   constexpr float accelerationBike { 0.000004f * boost };
   constexpr float accelerationTruck{ 0.000002f * boost };
   constexpr float widthCar  { 5 * zoom };
   constexpr float widthBike { 3 * zoom };
   constexpr float widthTruck{ 7 * zoom };
   constexpr float heightCar  { 11 * zoom };
   constexpr float heightBike { 7 * zoom };
   constexpr float heightTruck{ 20 * zoom };
   constexpr float distanceSecurity{ 0.2f };
   constexpr float nbCarMax{ 40 };
   // Intersections
   constexpr int nbIntersections{ std::max(sizeX, sizeY) }; // To have something visible -> o(n)
   constexpr int period{ (int)(5000 / boost) };
   constexpr float radiusIntersection{ 20 * zoom };
   // Window
   constexpr int interval{ (int)(80 * zoom) };
   constexpr int margin  { (int)(50 * zoom) };
   constexpr int SCREEN_WIDTH { sizeX * interval + 2*margin };
   constexpr int SCREEN_HEIGHT{ sizeY * interval + 2*margin };
   constexpr int ratioX{ /*1*/(SCREEN_WIDTH - 2*margin) / (sizeX - 1) };  // If sizeX>1
   constexpr int ratioY{ /*1*/(SCREEN_HEIGHT - 2*margin) / (sizeY - 1) }; // If sizeY>1
   constexpr int timeMax{ 100 }; // Miliseconds
}
