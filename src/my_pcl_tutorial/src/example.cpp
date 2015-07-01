#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
//A simple example file for converting using PCL code in ROS
ros::Publisher pub;

void cloud_cb(const sensor_msgs::PointCloud2ConstPtr& input){
	//container for data
	sensor_msgs::PointCloud2 output;

	//Data processing here..

	output = *input;

	pub.publish(output);
}
int main( int argc, char** argv){
	//Initialize ROS
	ros::init (argc, argv, "my_pcl_tutorial");
	ros::NodeHandle nh;

	//Create a ROS subscriber for the input point cloud
	ros::Subscriber sub = nh.subscribe("input", 1, cloud_cb);

	//Create a ROS publisher for the outputpoint cloud
	pub = nh.advertise<sensor_msgs::PointCloud2>("output", 1);

	//Spin
	ros::spin();
}
