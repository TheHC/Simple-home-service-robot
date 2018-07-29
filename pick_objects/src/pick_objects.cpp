#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <std_msgs/Bool.h>

// Define a client for to send goal requests to the move_base server through a SimpleActionClient
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;
std_msgs::Bool msg; // to send position to the add_marker node 

int main(int argc, char** argv){
  // Initialize the simple_navigation_goals node
  ros::init(argc, argv, "pick_objects");

  ros::NodeHandle n;
  ros::Publisher chatter=n.advertise<std_msgs::Bool>("Pick_or_Drop",1000);// define topic where to send to the add_marker node the position
  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  // Wait 5 sec for move_base action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  move_base_msgs::MoveBaseGoal goal;

  // set up the frame parameters
  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp = ros::Time::now();

  // Define a position and orientation for the robot to reach
  // Move to the pick_up destination 
  goal.target_pose.pose.position.x = -2.8246;
  goal.target_pose.pose.position.y = 2.7;
  goal.target_pose.pose.orientation.w = 1.0;

   // Send the goal position and orientation for the robot to reach
  ROS_INFO("Sending pickup destination");
  ac.sendGoal(goal);

  // Wait an infinite time for the results
  ac.waitForResult();
   
  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
    {ROS_INFO("Reached pickup destination");
     msg.data=true;
     chatter.publish(msg);
     ros::Duration(5).sleep();
	}
  else
    ROS_INFO("The base failed to reach the pick_up the destination");

  // Define a position and orientation for the robot to reach
  // Move to the drop_off destination 
  goal.target_pose.pose.position.x = 5.3512;
  goal.target_pose.pose.position.y = -0.61;
  goal.target_pose.pose.orientation.w = 1.0;

   // Send the goal position and orientation for the robot to reach
  ROS_INFO("Sending drop_off destination");
  ac.sendGoal(goal);

  // Wait an infinite time for the results
  ac.waitForResult();
  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
    {ROS_INFO("Reached drop_off destination");
     msg.data=false;
     chatter.publish(msg);
     ros::Duration(5).sleep();
	}
  else
    ROS_INFO("The base failed to reach the drop_off destination");

  return 0;
}
