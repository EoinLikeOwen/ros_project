#include <pcl/point_types.h>
#include <pcl/features/fpfh.h>

{
	//inputs
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::pointXYZ>);
	pcl::PointCloud<pcl::Normal>::Ptr normals (new pcl::PointCloud<pcl::Normal>());
	
	//Create the FPFH estimation class, and pass the input dataset+normals to it
	pcl::FPFHEstimation<pcl::PointXYZ, pcl::Normal, pcl::FPFHSignature33> fpfh;
	fpfh.setInputCloud (cloud);
	fpfh.setInputNormals (normals);
	
	//Create an empty kdtree representation, and pass it to the FPFH estimation object.
	//Its content will be filled inside the object, based om the given input dataset (as no other search surface is given)
	pcl::search::KdTree<PointXYZ>::Ptr tree (new pcl::search::KdTree<PointXYZ>);
	
	fpfh.setSearchMethod (tree);

	//Output datasets
	pcl::PointCloud<pcl::FPFHSignture33>::Ptr fpfhs (new pcl::PointCloud<pcl::FPFHSignture33>());

	//Use all neighbors in a sphere of radius 5cm
	fpfh.setRadiusSearch(0.05);

	//Compute the features
	fpfh.compute(*fpfhs);

	//fpfhs -> points.size () should have the same size as the input cloud -> points.size ()*
}
