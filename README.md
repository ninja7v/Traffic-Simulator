# 🚦🚗🚛 Traffic Simulator

The first release TS1 is out!

**GUI for road traffic simulation coded in C++ by Luc and Claire PREVOST.**

![traffic_simulator](https://user-images.githubusercontent.com/52052772/202865554-04ef6c69-5e1e-49a1-bf79-edb52018b80e.png)

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

The easyest way to execute the program is with Visual Studio: open the .sln file and hit F5!

After launching the program, a window pops up with a random case.

## ⚙️Parameters
### 🕸Network
A network has a size (X, Y), a flow and a boost parameter. The flow gives the amout of car in the network. The boost parameter accelerate the simulation by keeping the ratios.
### ❌🚦Intersections
Intersections have a traffic light period parameter. Each intersection is initialized with a random points on the network's grid. Input roads have the green traffic light one by one.
### 🛣Roads
Roads have a speed limit, lenght parameter. Each road is initialized with 2 intersections.
### 🚗🚛Vehicules
Vehicules have a maximum speed, an acceleration and a security distance parameter. Each Vehicules is initialized with a random taget intersection on a random from a random intersection. Their itinerary is obtained using the Dijkstra algorithm and move smoothly on the network.
### 💻Optimizer
Incoming :)

Now it is your turn to create traffic jams !

Thank you for using Traffic Simulator 🙂

> Just simulate !
