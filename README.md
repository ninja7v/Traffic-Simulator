# 🚦🚗🚛🏍️ Traffic Simulator

**GUI for road traffic simulation coded in C++ by Luc and Claire PREVOST.**

![traffic_simulator](https://user-images.githubusercontent.com/52052772/202865554-04ef6c69-5e1e-49a1-bf79-edb52018b80e.png)

📃 INSTRUCTIONS
===============
## 🚀Execution
Traffic Simulator requires the folowing dependencies:
- [GLFW](https://www.glfw.org/download)
- [GLUT](https://www.opengl.org/resources/libraries/glut/glut_downloads.php)
- [stb](https://github.com/nothings/stb)
and uses from std:
- [Array](https://en.cppreference.com/w/cpp/container/array)
- [List](https://www.cplusplus.com/reference/list/list/)
- [Iterator](https://pypi.org/project/numpy/)
- [Time](https://www.cplusplus.com/reference/ctime/time/)
- [Iostream](https://www.cplusplus.com/reference/iostream/) (in debug mode)

The easyest way to execute the program is with Visual Studio: open the .sln file and hit F5!

After launching the program, a window pops up with a random network.

## ⚙️Parameters
### 🕸Network
A network has a size (X, Y), a flow, a maximal number of car and a boost parameter. The flow gives the frequency of appearance of cars in the network. The boost parameter accelerate the simulation by keeping the ratios.
### ⚫🚦Intersections
Intersections have a positon and input/output roads as parameters. Each intersection is initialized with a random points on a squared grid. Intersections manages the traffic lights. Input roads have the green light one by one.
### 🛣Roads
Roads have a speed limit, lenght parameter. Each road is initialized with 2 intersections.
### 🚗🚛🏍️Vehicules
There are 3 types of vehicules: cars, trucks and motorcycles. Each of them have a maximum speed and an acceleration parameter. They have a smooth displacement. Every Vehicules is initialized with a random road with a random target intersection. Their itinerary is obtained using the Dijkstra algorithm.
### 💻Optimizer
⚠️No implemented yet⚠️
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
- S = first car spedd / speed max
- D = the distance of the first car / max distance
We can therefore define the folowing function:
road index green = argmax{α*N(i)+ß*S(i)+(1-α-ß)*D(i)}
with α,ß constants to be found by the optimizer, and i the road index.
α and ß will tell which parameter is the most important to consider.
We initialized them both at 0.33 to give a neutral initialization.
#### Under the hood
As this is a non differentiable problem, we discretize the set of solution, find the values of the control points, and fill the set of solution by doing a 2D interpolation.
Finally, be find the maximum value of this set.

Now it is your turn to create traffic jams !

Thank you for using Traffic Simulator 🙂

> Just simulate !
