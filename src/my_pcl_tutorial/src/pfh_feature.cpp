#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/features/pfh.h>
#include <pcl/features/normal_3d.h>

ros::Publisher pub;

void cloud_cb(const sensor_msgs::PointCloud2ConstPtr& input){
	//Convet the sensor_msgs to PCL
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>());
	pcl::PointCloud<pcl::Normal>::Ptr normals (new pcl::PointCloud<pcl::Normal>());
	pcl::fromROSMsg (*input, *cloud);
	
	//Create normal estimation class, and pass the input dataset to it
	pcl::NormalEstimation<pcl::PointXYZ, pcl::Normal> ne;
	ne.setInputCloud (cloud);
	
	//Create an empty kdtree repersentation, and pass it to the normal estimation object
	pcl::search::KdTree<pcl::PointXYZ>::Ptr tree (new pcl::search::KdTree<pcl::PointXYZ> ());
	ne.setSearchMethod (tree);

	//Set normla radius
	ne.setRadiusSearch (0.03);
	
	//Compute the normal
	ne.compute(*normals);

	//Create the PFH estimation class, and pass the input dataset+normals to it	
	pcl::PFHEstimation<pcl::PointXYZ, pcl::Normal, pcl::PFHSignature125> pfh;
	pfh.setInputCloud (cloud);
	pfh.setInputNormals(normals);

	//Using the same tree
	pfh.setSearchMethod(tree);

	//Output datasets
	pcl::PointCloud<pcl::PFHSignature125>::Ptr pfhs (new pcl::PointCloud<pcl::PFHSignature125>());

	//PFH radius larger than normal radius
	pfh.setRadiusSearch(0.05);

	//Compute the PFH
	pfh.compute(*pfhs);

	//Convert PFH to ROS msg
	sensor_msgs::PointCloud2 output;
	pcl::PCLPointCloud2::Ptr pcl_step(new pcl::PCLPointCloud2());
	pcl::toPCLPointCloud2 (*pfhs, *pcl_step);
	pcl_conversions::fromPCL(*pcl_step, output);

	//Publish the Output
	pub.publish(output);
}

int main(int argc, char** argv){
	//initialize ROS
	ros::init(argc, argv, "PFHS_test");
	ros::NodeHandle n;

	//Create ROS ubscriber
	ros::Subscriber sub = n.subscribe("input", 1, cloud_cb);

	//Create ROS publisher
	pub = n.advertise<sensor_msgs::PointCloud2>("output", 1);

	//Spin, right round
	ros::spin();
}
