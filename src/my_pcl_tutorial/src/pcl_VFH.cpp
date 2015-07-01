#include <pcl/point_types.h>
#include <pcl/features/vfh.h>

{
	//input
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);
	pcl::PointCloud<pcl::Normal>::Ptr normals (new pcl::PointCloud<pcl::Normal> ());
	
	//Create the VFH estimation class, and pass the input dataset+normals to it
	pcl::VFHEstimation<pcl::PointXYZ, pcl::Normal, pcl::VFHSignture308> vfh;
	vfh.setInputCloud (cloud);
	vfh.setInputNormals (normals);
	
	//Create an empty kdtree representation, and pass it to the FPFH estimation object.
	pcl::search::KdTree<pcl::PointXYZ>::Ptr tree(new pcl::search::KdTree<pcl::pointXYZ> ());
	vfh.setSearchMethod (tree);

	//Output datasets
	pcl::pointCloud<pcl::VFHSignature308>::Ptr vfhs (new pcl::PointCloud<pcl::VFHSignature308> ());

	//Compute the features
	vfh.compute (*vfhs);

}
