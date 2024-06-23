# 🚦🚗🚛🏍️ Traffic Simulator

**GUI for a road traffic simulation coded in C++ by Luc and Claire PREVOST.**

![image](https://github.com/ninja7v/Traffic-Simulator/assets/52052772/60a4df3c-e24d-481e-af9f-d78af2ad7364)

📃 INSTRUCTIONS
===============
## 🚀Execution
Traffic Simulator requires the folowing dependencies:
- [GLFW](https://www.glfw.org/download)
- [GLUT](https://www.opengl.org/resources/libraries/glut/glut_downloads.php)
- [stb](https://github.com/nothings/stb)

and uses from std:
- [Array](https://cplusplus.com/reference/array/array/)
- [List](https://cplusplus.com/reference/list/list/)
- [Vector](https://cplusplus.com/reference/vector/vector/)
- [Iterator](https://cplusplus.com/reference/iterator/iterator/)
- [Algorithm](https://cplusplus.com/reference/algorithm/)
- [Time](https://cplusplus.com/reference/ctime/time/)
- [Iostream](https://cplusplus.com/reference/iostream/) (in debug mode)
- [Cassert](https://cplusplus.com/reference/cassert/) (in debug mode for unit tests)

The easyest way to execute the program is with Visual Studio: open the .sln file and hit F5!

After launching the program, a window pops up with a random network.

## ⚙️Parameters
Relevants parameters are stored in the *Constants.h* file.
### 🕸Network
A network has a size (X, Y), a flow, a maximal number of car and a boost parameter.
The flow gives the frequency of appearance of cars in the network.
The boost parameter accelerate the simulation by keeping the ratios.
### ⚫🚦Intersections
Intersections have a positon and input/output roads as parameters.
Each intersection is initialized with a random points on a squared grid.
Intersections manages the traffic lights. Input roads have the green light one by one.
### 🛣Roads
Roads have a lenght parameter and contains a list of vehicle.
They are initialised by doing a [Delaunay triangulation](https://en.wikipedia.org/wiki/Delaunay_triangulation).
This gives a nice visuals by avoiding overlay and crossy roads, but also ensure the existence of a path between two intersections.
More specifically, we use the [Bowyer-Watson algorithm](https://en.wikipedia.org/wiki/Bowyer%E2%80%93Watson_algorithm) from the [delaunator-cpp](https://github.com/delfrrr/delaunator-cpp) library.
### 🚗🚛🏍️Vehicles
There are 3 types of vehicles:
- Cars 🚗
- Trucks 🚛
- Bikes 🏍️

Each of them have a maximum speed and an acceleration parameter.
They have a smooth displacement.
Every Vehicules is initialized on a random road with a random target intersection.
Their itinerary is obtained using the Dijkstra algorithm.
Finally, the vehicles are not Britich, they drive on the right lane.
### 💻Optimizer
⚠️Not implemented yet⚠️
#### Approach of the problem
We are making a real time optimizer to optimize the discrete traffic flow, playing with traffic light having a non constant period.
Below is a descrition of our approach to the problem.
The relevant local input data at each intersection are:
- the number of road

and for each road:
- the number of vehicule
- the speed of the first car
- the distance of the first car

we can then introduce the folowing normalized parameters:
- N = number of cars / road capacity
- S = first car speed / speed max
- D = the distance of the first car / max distance

We can therefore define the folowing function: ***road index green = argmax{αN(i)+ßS(i)+(1-α-ß)D(i)}***

with α,ß constants to be found by the optimizer, and i the road index.
α and ß will tell which parameter is the most important to consider.
We initialized them both at 1/3 to give a neutral initialization.
#### Under the hood
As this is a non differentiable problem, we discretize the set of solution, find the values of the control points, and fill the set of solution by doing a 2D interpolation.
Finally, we find the maximum value of this set.

## 📖Documentation
This code is well commented for [Doxygen](https://www.doxygen.nl/index.html).
Hence for more informations, a full documentation can be generated with Doxygen.

Now it is your turn to create traffic jams !

Thank you for using Traffic Simulator 🙂

> Just simulate !
