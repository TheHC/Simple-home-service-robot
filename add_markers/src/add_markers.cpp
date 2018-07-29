#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <std_msgs/Bool.h>

  // Set our initial shape type to be a cube
   uint32_t shape = visualization_msgs::Marker::SPHERE;

  
   visualization_msgs::Marker marker;
    ros::Publisher marker_pub;
    ros::Subscriber sub;
   // Set the frame ID and timestamp.  See the TF tutorials for information on these.
    
void callback(const std_msgs::Bool::ConstPtr& msg)
{
 if(msg->data)
	{
	
     	marker.color.a = 0.0;
     	marker.action = visualization_msgs::Marker::ADD;	
     	marker_pub.publish(marker);
     	ros::Duration(5).sleep();
	}
 else 
	{
	 marker.pose.position.x = 5.3512;
    	 marker.pose.position.y = -0.61;
	 marker.pose.position.z = 1;
	 marker.pose.orientation.x = 0.0;
	 marker.pose.orientation.y = 0.0;
	 marker.pose.orientation.z = 0.0;
	 marker.pose.orientation.w = 1.0;
	 marker.color.r = 0.0f;
    	 marker.color.g = 1.0f;
    	 marker.color.b = 0.0f;
     	 marker.color.a = 1.0;
   	 marker.action = visualization_msgs::Marker::ADD;
  	 marker_pub.publish(marker);

	}

}
 

int main( int argc, char** argv )
 {
  ros::init(argc, argv, "add_markers");
  ros::NodeHandle n;
  ros::Rate r(1);
  marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
  sub=n.subscribe("Pick_or_Drop",1,callback);
   marker.header.frame_id = "/map";
    marker.header.stamp = ros::Time::now();
 
    // Set the namespace and id for this marker.  This serves to create a unique ID
   // Any marker sent with the same namespace and id will overwrite the old one
    marker.ns = "basic_shapes";
    marker.id = 0;

    // Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
    marker.type = shape;

    // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
    marker.action = visualization_msgs::Marker::ADD;

     // Set the pose of the marker : at pickup destination
     marker.pose.position.x = -2.8246;
    marker.pose.position.y = 2.7;
    marker.pose.position.z = 1;
    marker.pose.orientation.x = 0.0;
    marker.pose.orientation.y = 0.0;
    marker.pose.orientation.z = 0.0;
    marker.pose.orientation.w = 1.0;
 
    // Set the scale of the marker -- 1x1x1 here means 1m on a side
    marker.scale.x = 0.5;
    marker.scale.y = 0.5;
    marker.scale.z = 0.5;
 
    // Set the color -- be sure to set alpha to something non-zero!
    marker.color.r = 0.0f;
    marker.color.g = 1.0f;
    marker.color.b = 0.0f;
    marker.color.a = 1.0;
    
    marker.action = visualization_msgs::Marker::ADD;
     while (marker_pub.getNumSubscribers() < 1)
    {
      if (!ros::ok())
       {
        return 0;
      }
      ROS_WARN_ONCE("Please create a subscriber to the marker");
      sleep(1);
     }
     marker_pub.publish(marker);

    marker_pub.publish(marker);
    ros::Duration(5).sleep();
     
    ros::Duration time_between_ros_wakeups(0.001);
    while (ros::ok()) {
        ros::spinOnce();
        time_between_ros_wakeups.sleep();
    }
   
 }
