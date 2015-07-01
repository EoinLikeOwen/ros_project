#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <laser_geometry/laser_geometry.h>
#include <tf/transform_broadcaster.h>
class My_Filter { 
	public :
		My_Filter();
		void scanCallback (const sensor_msgs::LaserScan::ConstPtr& scan);
	private:
		ros::NodeHandle node_;
		laser_geometry::LaserProjection projector_;
		tf::TransformListener tfListener_;
//		tf::StampedTransform transform;
		ros::Publisher point_cloud_publisher_;
		ros::Subscriber scan_sub_;
		tf::Transform transform;
		tf::TransformBroadcaster br;

};

My_Filter::My_Filter(){
	scan_sub_ = node_.subscribe<sensor_msgs::LaserScan>("/scan", 100, &My_Filter::scanCallback, this);
	point_cloud_publisher_ =node_.advertise<sensor_msgs::PointCloud2> ("/cloud", 100, false);


/*	try{
		tfListener_.lookupTransform("/world", "/link1", ros::Time(0), transform);
	}
	catch(tf::TransformException ex){
		ROS_ERROR("%s",ex.what());
		ros::Duration(1.0).sleep();
	}*/
}

void My_Filter::scanCallback(const sensor_msgs::LaserScan::ConstPtr& scan){
	
	transform.setOrigin (tf::Vector3(0,0,0));
	transform.setRotation(tf::Quaternion(0,1,0,1));
	br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "laser", "link1"));
	sensor_msgs::PointCloud2 cloud;
	try{
		projector_.transformLaserScanToPointCloud("link1", *scan, cloud, tfListener_);
	}
	catch( tf::TransformException& e){
		std::cout << e.what();
		return;
	}
	point_cloud_publisher_.publish(cloud);
}

int main( int argc, char** argv)
{
	ros::init(argc, argv, "my_filter");
	My_Filter filter;

	ros::spin();

	return 0;
}


