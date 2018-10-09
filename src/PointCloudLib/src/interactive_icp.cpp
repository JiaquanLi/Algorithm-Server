#include"interactive_icp.h"
#include <iostream>
#include <string>
#include "logging.h"
#include <vector>
using namespace std;


bool next_iteration = false;

typedef struct tagPOINT_3D
{
	double x;  //mm world coordinate x
	double y;  //mm world coordinate y
	double z;  //mm world coordinate z
	double r;
} POINT_WORLD;


void print4x4Matrix(const Eigen::Matrix4d & matrix, char* strReturn)
{
	char cMessage[500];
	memset(cMessage, '\0', 500);
	printf("Rotation matrix :\n");
	printf("    | %6.3f %6.3f %6.3f | \n", matrix(0, 0), matrix(0, 1), matrix(0, 2));
	printf("R = | %6.3f %6.3f %6.3f | \n", matrix(1, 0), matrix(1, 1), matrix(1, 2));
	printf("    | %6.3f %6.3f %6.3f | \n", matrix(2, 0), matrix(2, 1), matrix(2, 2));
	printf("Translation vector :\n");
	printf("t = < %6.3f, %6.3f, %6.3f >\n\n", matrix(0, 3), matrix(1, 3), matrix(2, 3));

	sprintf(cMessage, "R0= %6.3f %6.3f %6.3f R1= %6.3f %6.3f %6.3f R2= %6.3f %6.3f %6.3f T= %6.3f %6.3f %6.3f \r\n",
	        matrix(0, 0), matrix(0, 1), matrix(0, 2),
	        matrix(1, 0), matrix(1, 1), matrix(1, 2),
	        matrix(2, 0), matrix(2, 1), matrix(2, 2),
	        matrix(0, 3), matrix(1, 3), matrix(2, 3));
	//printf(cMessage);
	strcpy(strReturn, cMessage);
	return ;
}

void keyboardEventOccurred(const pcl::visualization::KeyboardEvent& event,
                           void* nothing)
{
	if (event.getKeySym() == "space" && event.keyDown())
		next_iteration = true;
}

bool CreatePcd(char* fileScr, char* filePcdDes)
{
	int number_Txt;
	FILE *fp_txt;
	tagPOINT_3D TxtPoint;
	vector<tagPOINT_3D> m_vTxtPoints;
	fp_txt = fopen(fileScr, "r");

	if (fp_txt)
	{
		while (fscanf(fp_txt, "%lf %lf %lf", &TxtPoint.x, &TxtPoint.y, &TxtPoint.z) != EOF)
		{
			m_vTxtPoints.push_back(TxtPoint);
		}
	}
	else
	{
		cout << "txt数据加载失败！" << endl;
		return false;
	}
	number_Txt = m_vTxtPoints.size();
	pcl::PointCloud<pcl::PointXYZ> cloud;


	// Fill in the cloud data
	cloud.width = number_Txt;
	cloud.height = 1;
	cloud.is_dense = false;
	cloud.points.resize(cloud.width * cloud.height);


	for (size_t i = 0; i < cloud.points.size(); ++i)
	{
		cloud.points[i].x = m_vTxtPoints[i].x;
		cloud.points[i].y = m_vTxtPoints[i].y;
		cloud.points[i].z = m_vTxtPoints[i].z;
	}
	pcl::io::savePCDFileASCII(filePcdDes, cloud);
	std::cerr << "Saved " << cloud.points.size() << filePcdDes << std::endl;
	for (size_t i = 0; i < cloud.points.size(); ++i)
		//std::cerr << "    " << cloud.points[i].x << " " << cloud.points[i].y << " " << cloud.points[i].z << std::endl;


		return true;

}

ApiPCL::ApiPCL():cloud_in(new PointCloudT),cloud_tr(new PointCloudT),cloud_icp(new PointCloudT)
{
	iterations = 1;

	if (pcl::io::loadPCDFile(pcdIcp, *cloud_icp) < 0)
	{
		PCL_ERROR("Error loading cloud %s.\n", pcdIcp);
		//return false;
	}
	std::cout << "\nLoaded file " << pcdIcp << " (" << cloud_icp->size() << " points) in " << std::endl;
}

ApiPCL::~ApiPCL()
{
	//delete cloud_in;
	//delete cloud_icp;
	//delete cloud_tr;
}

void ApiPCL:: SetMaxIterations(int iterNumber)
{
	iterations = iterNumber;
	cout << "Set max iterations: " << iterNumber << endl;
	log_print(LOG_DEBUG, "ICP_SetMaxIterations", "MaxIterations=%d", iterations);
}
bool ApiPCL::CreateLoadIcpPcdFile(char* templetFileTxt)
{
	if (CreatePcd(templetFileTxt, pcdIcp) == false) {
		log_print(LOG_DEBUG, "ICP_ERROR", "Create PCD %s ", pcdIcp);
		return false;
	}

	if (pcl::io::loadPCDFile(pcdIcp, *cloud_icp) < 0)
	{
		PCL_ERROR("Error loading cloud %s.\n", pcdIcp);
		return false;
	}
	std::cout << "\nLoaded file " << pcdIcp << " (" << cloud_icp->size() << " points) in " << std::endl;
	return true;
}

/*
* fileTarget: target image ,current get image
* fileIcp : tempelete image contain pont cloud for close to the target image
* result: matrix string
*/

bool ApiPCL::InteractiveIcp(char* fileTarget, char* result)
{
	char strMessage[500];
	//char *pcdTarget = (char*)"target.pcd";
	//char *pcdIcp = (char*)"icp.pcd";
	if (CreatePcd(fileTarget, pcdTarget) == false)
		return false;
	//if (CreatePcd(fileIcp, pcdIcp) == false)
	//	return false;
	// Defining a rotation matrix and translation vector
	Eigen::Matrix4d transformation_matrix = Eigen::Matrix4d::Identity();
	// The point clouds we will be using
	//PointCloudT::Ptr cloud_in(new PointCloudT);  // Original point cloud
	//PointCloudT::Ptr cloud_tr(new PointCloudT);  // Transformed point cloud
	//PointCloudT::Ptr cloud_icp(new PointCloudT);  // ICP output point cloud

	//Read Pcd files
	pcl::console::TicToc time;

	time.tic();
	if (pcl::io::loadPCDFile(pcdTarget, *cloud_in) < 0)
	{
		PCL_ERROR("Error loading cloud %s.\n", pcdTarget);
		return false;
	}
	std::cout << "\nLoaded file " << pcdTarget << " (" << cloud_in->size() << " points) in " << time.toc() << " ms\n" << std::endl;

	//time.tic();
	//if (pcl::io::loadPCDFile(pcdIcp, *cloud_icp) < 0)
	//{
	//	PCL_ERROR("Error loading cloud %s.\n", pcdIcp);
	//	return false;
	//}
	//std::cout << "\nLoaded file " << pcdIcp << " (" << cloud_icp->size() << " points) in " << time.toc() << " ms\n" << std::endl;

	*cloud_tr = *cloud_icp;  // We backup cloud_icp  cloud_tr for later use

	time.tic();
	pcl::IterativeClosestPoint<PointT, PointT> icp;
	icp.setMaximumIterations(iterations);
	icp.setInputSource(cloud_icp);
	icp.setInputTarget(cloud_in);
	icp.align(*cloud_icp);
	icp.setMaximumIterations(1);  // We set this variable to 1 for the next time we will call .align () function
	std::cout << "Applied " << iterations << " ICP iteration(s) in " << time.toc() << " ms" << std::endl;

	if (icp.hasConverged())
	{
		std::cout << "\nICP has converged, score is " << icp.getFitnessScore() << std::endl;
		std::cout << "\nICP transformation " << iterations << " : cloud_icp -> cloud_in" << std::endl;
		transformation_matrix = icp.getFinalTransformation().cast<double>();
		print4x4Matrix(transformation_matrix, strMessage);
		std::cout << "pcl res:" << strMessage << endl;
		strcpy(result, strMessage);
		return true;
	}
	else
	{
		PCL_ERROR("\nICP has not converged.\n");
		return false;
	}

	// Visualization
	pcl::visualization::PCLVisualizer viewer("ICP demo");
	// Create two vertically separated viewports
	int v1(0);
	int v2(1);
	viewer.createViewPort(0.0, 0.0, 0.5, 1.0, v1);
	viewer.createViewPort(0.5, 0.0, 1.0, 1.0, v2);

	// The color we will be using
	float bckgr_gray_level = 0.0;  // Black
	float txt_gray_lvl = 1.0 - bckgr_gray_level;

	// Original point cloud is white
	pcl::visualization::PointCloudColorHandlerCustom<PointT> cloud_in_color_h(cloud_in, (int)255 * txt_gray_lvl, (int)255 * txt_gray_lvl,
	        (int)255 * txt_gray_lvl);
	viewer.addPointCloud(cloud_in, cloud_in_color_h, "cloud_in_v1", v1);
	viewer.addPointCloud(cloud_in, cloud_in_color_h, "cloud_in_v2", v2);

	// Transformed point cloud is green
	pcl::visualization::PointCloudColorHandlerCustom<PointT> cloud_tr_color_h(cloud_tr, 20, 180, 20);
	viewer.addPointCloud(cloud_tr, cloud_tr_color_h, "cloud_tr_v1", v1);

	// ICP aligned point cloud is red
	pcl::visualization::PointCloudColorHandlerCustom<PointT> cloud_icp_color_h(cloud_icp, 180, 20, 20);
	viewer.addPointCloud(cloud_icp, cloud_icp_color_h, "cloud_icp_v2", v2);

	// Adding text descriptions in each viewport
	viewer.addText("White: Original point cloud\nGreen: Matrix transformed point cloud", 10, 15, 16, txt_gray_lvl, txt_gray_lvl, txt_gray_lvl, "icp_info_1", v1);
	viewer.addText("White: Original point cloud\nRed: ICP aligned point cloud", 10, 15, 16, txt_gray_lvl, txt_gray_lvl, txt_gray_lvl, "icp_info_2", v2);

	std::stringstream ss;
	ss << iterations;
	std::string iterations_cnt = "ICP iterations = " + ss.str();
	viewer.addText(iterations_cnt, 10, 60, 16, txt_gray_lvl, txt_gray_lvl, txt_gray_lvl, "iterations_cnt", v2);

	// Set background color
	viewer.setBackgroundColor(bckgr_gray_level, bckgr_gray_level, bckgr_gray_level, v1);
	viewer.setBackgroundColor(bckgr_gray_level, bckgr_gray_level, bckgr_gray_level, v2);

	// Set camera position and orientation
	viewer.setCameraPosition(-3.68332, 2.94092, 5.71266, 0.289847, 0.921947, -0.256907, 0);
	viewer.setSize(1280, 1024);  // Visualiser window size

	// Register keyboard callback :
	viewer.registerKeyboardCallback(&keyboardEventOccurred, (void*)NULL);

	// Display the visualiser
	while (!viewer.wasStopped())
	{
		viewer.spinOnce();

		// The user pressed "space" :
		if (next_iteration)
		{
			// The Iterative Closest Point algorithm
			time.tic();
			icp.align(*cloud_icp);
			std::cout << "Applied 1 ICP iteration in " << time.toc() << " ms" << std::endl;

			if (icp.hasConverged())
			{
				printf("\033[11A");  // Go up 11 lines in terminal output.
				printf("\nICP has converged, score is %+.0e\n", icp.getFitnessScore());
				std::cout << "\nICP transformation " << ++iterations << " : cloud_icp -> cloud_in" << std::endl;
				transformation_matrix *= icp.getFinalTransformation().cast<double>();  // WARNING /!\ This is not accurate! For "educational" purpose only!
				//print4x4Matrix(transformation_matrix);  // Print the transformation between original pose and current pose

				ss.str("");
				ss << iterations;
				std::string iterations_cnt = "ICP iterations = " + ss.str();
				viewer.updateText(iterations_cnt, 10, 60, 16, txt_gray_lvl, txt_gray_lvl, txt_gray_lvl, "iterations_cnt");
				viewer.updatePointCloud(cloud_icp, cloud_icp_color_h, "cloud_icp_v2");
				//return true;
			}
			else
			{
				PCL_ERROR("\nICP has not converged.\n");
				return false;
			}
		}
		next_iteration = false;
	}
	return true;
}
