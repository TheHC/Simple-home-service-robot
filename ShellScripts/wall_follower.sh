#!/bin/sh 
xterm -e "roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=$HOME_WORLD
" & sleep 10
xterm -e "rosrun gmapping slam_gmapping" & sleep 5
xterm -e "roslaunch turtlebot_rviz_launchers view_navigation.launch" & sleep 5
xterm -e "rosrun wall_follower wall_follower "
