#include <pcl/point_types.h>
#include <pcl/features/normal_3d.h>

{
	//inputs
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
	
	//Create the norma estimation class, and pass the input dataset to it
	pcl::NormalEstimation<pcl::PointXYZ, pcl::Normal> ne;
	ne.setInputCloud(cloud);
	
	//Create an empty kdtree representation and pass it to the normal estimation object.
	//Its content will be filled inside the object, based on the given input dataset 
	pcl::search::KdTree<pcl::PointXYZ>::Ptr tree (new pcl::search::KDTree<pcl::PointXYZ>());
	ne.setSearchMethod (tree);

	//Output datsets
	pcl::PointCloud<pcl::Normal>::Ptr cloud_normals (new pcl::PointCloud<pcl::Normal>);

	//Use all neighbors in a sphere of radius 3cm
	ne.setRadiusSearch(0.03);

	//Compute thee features
	ne.cpmute(*cloud_normals);                                                       
	
	//cloud_normals -> points.size () should have the same size as the input cloud -> points.size()*	
	
}
	
