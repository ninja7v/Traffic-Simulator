# 🚦🚗🚛 Traffic Simulator

⚠️ Warning: this project is under constuction ⚠️

⚠️ Incoming : Menu with QT + Car itinerary fixed + Sereval type of car + Traffic light optimizer ⚠️

**GUI for raad traffic simulation coded in C++ by Luc PREVOST and Claire PREVOST.**

![traffic_simulator](https://user-images.githubusercontent.com/52052772/142062951-265998b8-a934-4cf3-bd30-fee10bccfbaa.png)

📃 INSTRUCTIONS
===============
## 🚀Execution
Traffic Simulator requires the folowing dependencies:
- [GLFW](https://www.glfw.org/download)
- [GLUT](https://www.opengl.org/resources/libraries/glut/glut_downloads.php)
- [Iostream](https://www.cplusplus.com/reference/iostream/)
- [Iterator](https://pypi.org/project/numpy/)
- [List](https://www.cplusplus.com/reference/list/list/)
- [Time](https://www.cplusplus.com/reference/ctime/time/)

To execute it, set the all the files in the same folder, compile the _Main.cpp_ file and run it.

After launching the program, a window pops up with a default case.

## ⚙️Parameters
### 🕸Network
A network has a size (X, Y) and a boost parameter. The boost parameter accelerate the simulation by keeping the ratios.
### ❌🚦Intersections
Intersections have a number of intersection and a traffic light period parameter. Each intersection is initialized with a random points on the network's grid. Input roads have the green traffic light one by one.
### 🛣Roads
Roads have a speed limit, a number of road and a car capacity parameter. Each road is initialized with 2 intersections.
### 🚗🚛Vehicules
Vehicules have a flow parameter, which gives the amout of car in the network. They also have a maximum speed, an acceleration and a security distance parameter. Each Vehicules is initialized with a random taget intersection on a random from a random intersection. Then their itinerary is obtained using the Dijkstra algorithm.
### 💻Optimizer
Incoming :)

Now it is your turn to create traffic jams !

Thank you for using Traffic Simulator 🙂

> Just simulate !
