/**
 * @brief Define relevant constants of the simulator.
 */

#pragma once
// Libraries
#include<algorithm> // To use max()

enum LearningType {
      Q_LEARNING,
      DQN
   };

namespace constants {
/** @defgroup Network parameters */
/**@{*/
/** Number of possible positions on the X axis for the intersections. It must be a positive number. */
   constexpr int sizeX{ 110 };
/** Number of possible positions on the Y axis for the intersections. It must be a positive number. */
   constexpr int sizeY{ 70 };
/** Overall speed of the simulation. It must be a positive number. */
   constexpr double boost{ 1.0 };
/** Scale of the representation. It must be a positive number. */
   constexpr double zoom{ 1.0 };
/**@}*/
/** @defgroup Road parameters */
/**@{*/
/** Width Road in pixel. It must be a positive number. */
   constexpr double widthRoad{ 10 * zoom };
/**@}*/
/** @defgroup Vehicle parameters */
/**@{*/
/** Frequency of appearance of vehicles. It must be in [0, 99]. */
   constexpr int flow{ 10 };
/** Maximum number of vehicle simultaneously. It must be a positive number. */
   constexpr int nbVehicleMax{ 70 };
/** Maximum car speed. It must be a positive number. */
   constexpr double speedMaxCar  { 0.3  * boost };
/** Maximum Bike speed. It must be a positive number. */
   constexpr double speedMaxBike { 0.4 * boost };
/** Maximum Truck speed. It must be a positive number. */
   constexpr double speedMaxTruck{ 0.2 * boost };
/** Car acceleration per frame. It must be a positive number. */
   constexpr double accelerationCar  { 0.003 * boost };
/** Bike acceleration per frame. It must be a positive number. */
   constexpr double accelerationBike { 0.004 * boost };
/** Truck acceleration per frame. It must be a positive number. */
   constexpr double accelerationTruck{ 0.002 * boost };
/** Car width in pixel. It must be a positive number. */
   constexpr double widthCar  { 2 * zoom };
/** Bike width in pixel. It must be a positive number. */
   constexpr double widthBike { 1 * zoom };
/** Truck width in pixel. It must be a positive number. */
   constexpr double widthTruck{ 3 * zoom };
/** Car height in pixel. It must be a positive number. */
   constexpr double heightCar  { 5 * zoom };
/** Bike height in pixel. It must be a positive number. */
   constexpr double heightBike {  3 * zoom };
/** Truck height in pixel. It must be a positive number. */
   constexpr double heightTruck{ 10 * zoom };
/** Vehicle light diameter. It must be a positive number. */
   constexpr double diameterHeadlight{ 1 * zoom };
/** Security gab between a vehicle and an obstacle. It must be a positive number. */
   constexpr double distanceSecurity{ 0.5 * zoom };
/**@}*/
/** @defgroup Intersection parameters */
/**@{*/
/** Number of Intersection in the network. It must be a positive number. */
   constexpr int nbIntersections{ std::max(sizeX, sizeY) / 10 }; // To have something visible < 15
/** Distance between intersections. It must be a positive number. */
   constexpr int minGap{ static_cast<int>(10 * zoom) }; // pi*minGap^2*nbIntersections<sizeX*sizeY
/** Traffic light period. It must be a positive number. */
   constexpr int period{ static_cast<int>(1000 / boost) };
/** Intersection diameter in pixel. It must be a positive number. */
   constexpr double diameterIntersection{ 20 * zoom };
/**@}*/
/** @defgroup Window parameters */
/**@{*/
/** Step for the sizeX and sizeY parameters. It must be a positive number. */
   constexpr int interval{ static_cast<int>(8 * zoom) };
/** Distance between the network and the frame of the window. It must be a positive number. */
   constexpr int margin  { static_cast<int>(50 * zoom) };
/** Window width. */
   constexpr int SCREEN_WIDTH { sizeX * interval + 2*margin };
/** Window height. */
   constexpr int SCREEN_HEIGHT{ sizeY * interval + 2*margin };
/** Ratio for the X axis. */
   constexpr int ratioX{ /*1*/(SCREEN_WIDTH - 2*margin) / (sizeX - 1) };  // If sizeX>1
/** Ratio for the Y axis. */
   constexpr int ratioY{ /*1*/(SCREEN_HEIGHT - 2*margin) / (sizeY - 1) }; // If sizeY>1
/**@}*/
/** @defgroup Learning parameters */
/**@{*/
/** Learning type. */
   constexpr LearningType learningType{ LearningType::Q_LEARNING };
/**@}*/
}


