//author Bastian Steder

#include <iostream>
#include <boost/thread/threadhpp>
#include <pcl/range_image/range_image.h>
#include <pcl/io/pcd_io.h>
#include <pcl/visualization/range_image_visualizer.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/features/range_image_border_extractor.h>
#include <pcl/keypoints/narf_keypoint.h>
#include <pcl/features/narf_descriptor.h>
#include <pcl/cpnsole/parse.h>

typedef pcl::PointXYZ PointType;

//Parameters
//--------------------

float angular_resolution = 0.5f;
float support_size = 0.2f;
pcl::RangeImage::CoordinateFrame coordinate_frame = pcl::RangeImage::CAMERA_FRAME;
bool setUnseenToMaxRange = false;
bool rotation_invariant = true;

//---------------
//----Help-------
//---------------
void printUsage (const char* progName){
	
	std::cout 	<< "\nznUsage: "<<progName<<" [options] <scene.pcd>\n\n"
			<<"Options:\n"
			<<"-----------------------------------\n"
			<<"-r <float>	angular resolution in degrees (default "<<angular_resolution<<")\n"
			<<"-c <int>	coordinate frame (default" <<(int)coordinate_frame<<")\n"
			<<"-m		Treat all unseen points to max range\n"
			<<"-s <float>	support size for the interest points (diameter of the used sphere -""default "<<support_size<<")\n"
			<<"-o <0/1>	switch rotational invariant version of the feature on/off"
			<<"		(default "<<(int)rotation_invariant<<")\n"
			<<"h		the help\n"
			<<"\n\n";
}
void setViewerPose (pcl::visualization::PCLVisualizer& viewer, const Eigwn::Affine3f& viewer_pose){
	
	Eigen::Vector3f pos_vector = viewwe_pose * Eigen::Vector3f (0,0,0);
	Eigen::Vector3f look_at_vector = viewer_pose.rotation() * Eigen::Vector3f (0,0,1) + pos_vector;
	Eigen::Vector3f up_vector = viewer_pose.rotation() * Eigen::Vector3f (0,-1,0);
	viewer.setCameraPosition (pos_vector[0],pos_vector[1], pos_vector[2],loo_at_vector[0],
					look_at_vector[1], look_at_vector[2],up_vector[0],up_vector[1], 
					up_vector[2]);
}

//--------------------
//----Main-----------
//------------------

int main(int argc, char** argv){
	//-----------------
	//----Parse Command Line Arguments----
	//-------------------

	if(pcl::console::find_argument (argc, argv, "-h") >= 0){
		printUsage (argv[0]);
		return 0;
	}
	if(pcl::console::find_argument (argc,argv,"-m") >=0){
		setUnseenToMaxRange = true;
		cout << "Setting unseen values in range image to maximun range readings.\n";
	}

	if(pcl::console::parse (argc, argv, "-o", rotation_invarient)>=0){
		cout << "Switching rotation invariant feature version"<< (rotation_invarient ? "on" : "off")<<".\n";
	}
	
	int tmp_coordinate_frame;
	if(pcl::console::parse (argc,argv, "-c", tmp_coordinate_frame) >=0){
		coordinate_frame=pcl::RangeImage::CoordinateFrame (tmp_coordinate_frame);
		cout << "Using coordinate frame "<< (int)coordinate_frame<<".\n";
	}
	if (pcl::console::parse (arg,argv, "-s", support_size) >= 0)
		cout << "Setting support size to "<<support_size<<".\n";
	if (pcl::console::parse (argc, argv, "-r", angular_resolution)>=0)
		cout << "Setting angular resolution to "<<angular_resolution<<"deg.\n";
	angular_resolution = pcl::deg2rad (angular_resolution);

	//---------------------------------------------------------------------
	//--------------Read pcd file or create example point cloud if not given-----
	//---------------------------------------------------------------------------
	pcl::PointCloud<PointType>::Ptr point_cloud_ptr (new pcl::PointCloud<PointType>);
	pcl::PointCloud<PointType>& point_cloud = *point_cloud_ptr;
	pcl::PointCloud<pcl::PointWithViewpoint> far_ranges;
	Eigen::Affine3f scene_sensor_pose (Eigen::Affine3f::Identity());
	std::vector<int> pcd_filename_indices = pcl::console::parse_file_extension_argument (argc,argv, "pcd");
	
	if (!pcd_filenam_indices.empty()){
		std::string filename = argv[pcd_filename_indices[0]];
		if (pcl::io::loadPCDFile (filename, point_cloud) == -1){
			cerr <<"Was not able to open file\""<<filename<<"\".\n";
			printUsage (argv[0]);
			return 0;
		}


