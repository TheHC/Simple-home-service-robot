# Simple-home-service-robot

The project's aim is to simulate a home service robot that can navigate in a previously unknown environnement ( built in gazebo). At first the robot navigates the world using a wall following algorithm. Then maps it's environnement using gmapping ( laser-based SLAM) and produces a grid map of the world. The robot then uses this map to localize itself with the AMCL (adaptive Monte Carlo localization) and then plan a path and autonomosly naviguate to a any point in the environnement. 

# Installation

Use wstool to be able to use git and ROS without conflicts. 
To install, use:
```sh
$ sudo apt-get install python-wstool
```
or when that is not possible, fall back to pip:
```sh
$ sudo pip install -U wstool
```
More documentation on wstool can be found at http://wiki.ros.org/wstool.

# Usage
Run the script env_init to set export some project specific path variables and prepare the environnement;
The final simulation can be seen by running the script home_service.sh.

# Todos

    -Add more details on the README
    -Add the possibility to choose a different world for the simulation 
    -Add another robot model ( a model using 4-wheels)

