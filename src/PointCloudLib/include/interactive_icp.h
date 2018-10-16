
#ifndef INTERACTIVE_ICP_H_
#define INTERACTIVE_ICP_H_

#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/registration/icp.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/console/time.h>


typedef pcl::PointXYZ PointT;
typedef pcl::PointCloud<PointT> PointCloudT;

class ApiPCL
{
public:
	ApiPCL();
	~ApiPCL();
	bool InteractiveIcp(char* fileTarget, char* result);
	void SetMaxIterations(int iterNumber);
	bool CreateLoadIcpPcdFile(char* templetFileTxt);
	void SetIcpFilter(float filter);
private:
	int iterations ;//= 100;  // Default number of ICP iterations
	float filter;
	PointCloudT::Ptr cloud_in;  // Original point cloud
	PointCloudT::Ptr cloud_tr;  // Transformed point cloud
	const PointCloudT::Ptr cloud_icp;  // ICP output point cloud

	char *pcdTarget = (char*)"target.pcd";
	char *pcdIcp = (char*)"icp.pcd";

};

#endif
