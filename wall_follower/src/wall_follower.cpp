// ROS Libraries
#include "ros/ros.h"
#include "geometry_msgs/Twist.h" // Motor Commands
#include "sensor_msgs/LaserScan.h" // Laser Data
#include "tf/transform_listener.h" // tf Tree

// C++ Libraries
#include <iostream>
#include <cmath>
#include <algorithm>
#include <stack>

// ROS Publisher:Motor Commands, Subscriber:Laser Data, and Messages:Laser Messages & Motor Messages
ros::Publisher motor_command_publisher;
ros::Subscriber laser_subscriber;
sensor_msgs::LaserScan laser_msg;
geometry_msgs::Twist motor_command;

// The laser_callback function will be called each time a laser scan data is received
void laser_callback(const sensor_msgs::LaserScan::ConstPtr& scan_msg)
{
    std::cout<<"called back"<<std::endl;
    motor_command.angular.z=-0.3; 
    motor_command.linear.x=0.7;
    motor_command_publisher.publish(motor_command);
}

int main(int argc, char** argv)
{
    // Initialize a ROS node
    ros::init(argc, argv, "Wall_follower_node");

    // Create a ROS NodeHandle object
    ros::NodeHandle n;

    // Inform ROS master that we will be publishing a message of type geometry_msgs::Twist on the robot actuation topic with a publishing queue size of 100
    motor_command_publisher = n.advertise<geometry_msgs::Twist>("/mobile_base/commands/velocity", 100);

    // Subscribe to the /scan topic and call the laser_callback function
    laser_subscriber = n.subscribe("/scan", 1000, laser_callback);

    // Enter an infinite loop where the laser_callback function will be called when new laser messages arrive
    ros::Duration time_between_ros_wakeups(0.001);
    while (ros::ok()) {
        ros::spinOnce();
        time_between_ros_wakeups.sleep();
    }

    return 0;
}
