/**
 * @brief Define relevant constants of the simulator.
 */

#pragma once
// Libraries
#include<algorithm> // To use max()

namespace constants {
/** @defgroup Network parameters */
/**@{*/
/** Number of possible positions on the X axis for the intersections. It must be a positive number. */
   constexpr int sizeX{ 110 };
/** Number of possible positions on the Y axis for the intersections. It must be a positive number. */
   constexpr int sizeY{ 70 };
/** Overall speed of the simulation. It must be a positive number. */
   constexpr double boost{ 5.0f };
/** Scale of the representation. It must be a positive number. */
   constexpr double zoom{ 1.0f };
/**@}*/
/** @defgroup Road parameters */
/**@{*/
/** Width Road in pixel. It must be a positive number. */
   constexpr double widthRoad{ 15 * zoom };
/**@}*/
/** @defgroup Vehicle parameters */
/**@{*/
/** Frequency of appearance of vehicles. It must be in [0, 99]. */
   constexpr int flow{ 10 };
/** Maximum number of vehicle simultaneously. It must be a positive number. */
   constexpr int nbVehicleMax{ 50 };
/** Maximum car speed. It must be a positive number. */
   constexpr double speedMaxCar  { 0.002f  * boost };
/** Maximum Bike speed. It must be a positive number. */
   constexpr double speedMaxBike { 0.004f * boost };
/** Maximum Truck speed. It must be a positive number. */
   constexpr double speedMaxTruck{ 0.003f * boost };
/** Car acceleration per frame. It must be a positive number. */
   constexpr double accelerationCar  { 0.00003f * boost };
/** Bike acceleration per frame. It must be a positive number. */
   constexpr double accelerationBike { 0.00004f * boost };
/** Truck acceleration per frame. It must be a positive number. */
   constexpr double accelerationTruck{ 0.00002f * boost };
/** Car width in pixel. It must be a positive number. */
   constexpr double widthCar  { 5 * zoom };
/** Bike width in pixel. It must be a positive number. */
   constexpr double widthBike { 3 * zoom };
/** Truck width in pixel. It must be a positive number. */
   constexpr double widthTruck{ 7 * zoom };
/** Car height in pixel. It must be a positive number. */
   constexpr double heightCar  { 11 * zoom };
/** Bike height in pixel. It must be a positive number. */
   constexpr double heightBike {  7 * zoom };
/** Truck height in pixel. It must be a positive number. */
   constexpr double heightTruck{ 20 * zoom };
/** Security gab between a vehicle and an obstacle. It must be a positive number. */
   constexpr double diameterHeadlight{ 2 * zoom };
/** Security gab between a vehicle and an obstacle. It must be a positive number. */
   constexpr double distanceSecurity{ 0.5 * zoom };
/**@}*/
/** @defgroup Intersection parameters */
/**@{*/
/** Number of Intersection in the network. It must be a positive number. */
   constexpr int nbIntersections{ (int)(std::max(sizeX, sizeY) / 10) }; // To have something visible < 15
/** Distance between intersections. It must be a positive number. */
   constexpr int minGap{ (int)(10 * zoom) }; // pi*minGap^2*nbIntersections<sizeX*sizeY
/** Traffic light period. It must be a positive number. */
   constexpr int period{ (int)(5000 / boost) };
/** Intersection diameter in pixel. It must be a positive number. */
   constexpr double diameterIntersection{ 40 * zoom };
/**@}*/
/** @defgroup Window parameters */
/**@{*/
/** Step for the sizeX and sizeY parameters. It must be a positive number. */
   constexpr int interval{ (int)(8 * zoom) };
/** Distance between the network and the frame of the window. It must be a positive number. */
   constexpr int margin  { (int)(50 * zoom) };
/** Window width. */
   constexpr int SCREEN_WIDTH { sizeX * interval + 2*margin };
/** Window height. */
   constexpr int SCREEN_HEIGHT{ sizeY * interval + 2*margin };
/** Ratio for the X axis. */
   constexpr int ratioX{ /*1*/(SCREEN_WIDTH - 2*margin) / (sizeX - 1) };  // If sizeX>1
/** Ratio for the Y axis. */
   constexpr int ratioY{ /*1*/(SCREEN_HEIGHT - 2*margin) / (sizeY - 1) }; // If sizeY>1
/**@}*/
}
