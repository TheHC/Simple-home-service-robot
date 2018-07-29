#!/bin/sh 
xterm -e "roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=$UGLY_W_WORLD
" & sleep 10
xterm -e "roslaunch turtlebot_gazebo amcl_demo.launch map_file:=/home/workspace/ros_catkin_ws/src/Simple-home-service-robot/Worlds/Ugly_W_map.yaml" & sleep 5
xterm -e "roslaunch turtlebot_rviz_launchers view_navigation_with_markers.launch" & sleep 5
xterm -e "rosrun pick_objects pick_objects" & sleep 1
xterm -e "rosrun add_markers add_markers" 
