#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/registration/icp.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/io/ply_io.h>
#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>
#include <pcl/visualization/point_cloud_color_handlers.h>
#include <pcl/filters/filter.h>
#include <pcl/common/impl/centroid.hpp>
#include <pcl/filters/passthrough.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/search/kdtree.h>
#include <pcl/filters/statistical_outlier_removal.h>
#include <algorithm>
#include <vector>


// fusionne deux nuages de points de taille différentes
pcl::PointCloud<pcl::PointXYZ>::Ptr mergePointClouds(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud1, pcl::PointCloud<pcl::PointXYZ>::Ptr cloud2)
{
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_merged(new pcl::PointCloud<pcl::PointXYZ>);
    // ajoute chaque point du nuage de points small dans le nuage de points large
    for (size_t i = 0; i < cloud1->size(); ++i)
    {
        pcl::PointXYZ point = cloud1->points[i];
        cloud_merged->push_back(point);
    }

    for (size_t i = 0; i < cloud2->size(); ++i)
    {
        pcl::PointXYZ point = cloud2->points[i];
        cloud_merged->push_back(point);
    }

    return cloud_merged;
}

bool alreadyInCloud(pcl::PointXYZ point, pcl::PointCloud<pcl::PointXYZ>::Ptr cloud){
  for (size_t i = 0; i < cloud->size(); ++i){
      if(cloud->points[i].x == point.x && cloud->points[i].y == point.y && cloud->points[i].z == point.z){
        return true;
      }
  }

  return false;
}

pcl::PointCloud<pcl::PointXYZ>::Ptr deleteDuplicatePoints(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud){

  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_filtered (new pcl::PointCloud<pcl::PointXYZ>);
  cloud_filtered->push_back(cloud->points[0]);

  for (size_t i = 1; i < cloud->size(); ++i)
  {
    if(!alreadyInCloud(cloud->points[i], cloud_filtered)){
      cloud_filtered->push_back(cloud->points[i]);
    }

  }

  return cloud_filtered;

}

int main(){

pcl::PointCloud<pcl::PointXYZ>::Ptr cloud1 (new pcl::PointCloud<pcl::PointXYZ>);
pcl::PointCloud<pcl::PointXYZ>::Ptr cloud2 (new pcl::PointCloud<pcl::PointXYZ>);
pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_merged (new pcl::PointCloud<pcl::PointXYZ>);
pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_filtered (new pcl::PointCloud<pcl::PointXYZ>);

pcl::io::loadPCDFile<pcl::PointXYZ>("images_par_deux/guitare23.pcd", *cloud1);
pcl::io::loadPCDFile<pcl::PointXYZ>("recalages/recalage_guitare_source12_target23.pcd", *cloud2);

cloud_merged = mergePointClouds(cloud1, cloud2);

std::cout<<cloud_merged->size()<<std::endl;

cloud_filtered = deleteDuplicatePoints(cloud_merged);

pcl::StatisticalOutlierRemoval<pcl::PointXYZ> sor;
sor.setInputCloud(cloud_filtered);
sor.setMeanK(50); // nombre de voisins à considérer pour le calcul de la moyenne et de l'écart type
sor.setStddevMulThresh(0.0001); // facteur de seuil d'écart type pour la suppression des points aberrants
sor.filter(*cloud_filtered);

pcl::io::savePCDFileBinary("nouveaux_nuages/nuage_guitare_123.pcd", *cloud_filtered);

std::cout<<cloud_filtered->size()<<std::endl;

pcl::visualization::PCLVisualizer *viewer = new pcl::visualization::PCLVisualizer("3D Viewer");
viewer->addPointCloud<pcl::PointXYZ> (cloud_filtered, "sample cloud");

while (!viewer->wasStopped ()){
    viewer->spinOnce (100);
}



return 0;
}



#include <pcl/io/pcd_io.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/registration/icp.h>
#include <pcl/visualization/registration_visualizer.h>
#include <pcl/visualization/pcl_visualizer.h>

int
main (int argc, char** argv)
{
//  /////////////////////////////////////////////////////////////////////////////////////////////////////

  if (argc != 3)
  {
    std::cerr << "please specify the paths to the two point clouds to be registered" << std::endl;
    exit (0);
  }
//  /////////////////////////////////////////////////////////////////////////////////////////////////////

//  /////////////////////////////////////////////////////////////////////////////////////////////////////
  pcl::PointCloud<pcl::PointXYZ>::Ptr inputCloud(new pcl::PointCloud<pcl::PointXYZ>);
  pcl::PointCloud<pcl::PointXYZ>::Ptr targetCloud(new pcl::PointCloud<pcl::PointXYZ>);

  if (pcl::io::loadPCDFile<pcl::PointXYZ> (argv[1], *inputCloud) == -1) //* load the file
  {
    PCL_ERROR ("Couldn't read the first .pcd file \n");
    return (-1);
  }

  if (pcl::io::loadPCDFile<pcl::PointXYZ> (argv[2], *targetCloud) == -1) //* load the file
  {
    PCL_ERROR ("Couldn't read the second .pcd file \n");
    return (-1);
  }
//  /////////////////////////////////////////////////////////////////////////////////////////////////////

//  /////////////////////////////////////////////////////////////////////////////////////////////////////
  pcl::PointCloud<pcl::PointXYZ> inputCloudFiltered;
  pcl::PointCloud<pcl::PointXYZ> targetCloudFiltered;

  pcl::VoxelGrid<pcl::PointXYZ> sor;
//  sor.setLeafSize (0.01, 0.01, 0.01);
  //sor.setLeafSize (0.02f, 0.02f, 0.02f);
  //sor.setLeafSize (0.05, 0.05, 0.05);
sor.setLeafSize (0.1, 0.1, 0.1);
  //sor.setLeafSize (0.4, 0.4, 0.4);
 //sor.setLeafSize (0.5, 0.5, 0.5);

  sor.setInputCloud (inputCloud);
  std::cout<<"\n inputCloud->size()="<<inputCloud->size()<<std::endl;
  sor.filter (inputCloudFiltered);
  std::cout<<"\n inputCloudFiltered.size()="<<inputCloudFiltered.size()<<std::endl;

  sor.setInputCloud (targetCloud);
  std::cout<<"\n targetCloud->size()="<<targetCloud->size()<<std::endl;
  sor.filter (targetCloudFiltered);
  std::cout<<"\n targetCloudFiltered.size()="<<targetCloudFiltered.size()<<std::endl;
//  /////////////////////////////////////////////////////////////////////////////////////////////////////

//  /////////////////////////////////////////////////////////////////////////////////////////////////////
//  pcl::PointCloud<pcl::PointXYZ>::ConstPtr source = inputCloud.makeShared();
//  pcl::PointCloud<pcl::PointXYZ>::ConstPtr target = targetCloud.makeShared();

  pcl::PointCloud<pcl::PointXYZ>::ConstPtr source = inputCloudFiltered.makeShared();
  pcl::PointCloud<pcl::PointXYZ>::ConstPtr target = targetCloudFiltered.makeShared();
  

  pcl::PointCloud<pcl::PointXYZ> source_aligned;
//  /////////////////////////////////////////////////////////////////////////////////////////////////////

//  /////////////////////////////////////////////////////////////////////////////////////////////////////
  pcl::RegistrationVisualizer<pcl::PointXYZ, pcl::PointXYZ> registrationVisualizer;

  registrationVisualizer.setMaximumDisplayedCorrespondences (100);
//  /////////////////////////////////////////////////////////////////////////////////////////////////////

//  ///////////////////////////////////////////////////////////////////////////////////////////////////
  pcl::IterativeClosestPoint<pcl::PointXYZ, pcl::PointXYZ> icp;

  icp.setMaximumIterations(10000);

//icp.setMaxCorrespondenceDistance (0.6);
  icp.setMaxCorrespondenceDistance (0.8);
  //icp.setMaxCorrespondenceDistance (1.5);

//icp.setRANSACOutlierRejectionThreshold (0.1);
//icp.setRANSACOutlierRejectionThreshold (0.4);
icp.setRANSACOutlierRejectionThreshold (1.5);
//  icp.setRANSACOutlierRejectionThreshold (5.0);

  icp.setInputSource (source);
  icp.setInputTarget (target);

  // Register the registration algorithm to the RegistrationVisualizer
  registrationVisualizer.setRegistration (icp);

  registrationVisualizer.startDisplay();

  // Start registration process
  icp.align (source_aligned);

  pcl::io::savePCDFileBinary("recalages/recalage_guitare_source12_target23.pcd", source_aligned);

  std::cout << "has converged:" << icp.hasConverged () << " score: " << icp.getFitnessScore () << std::endl;
  std::cout << icp.getFinalTransformation () << std::endl;

  registrationVisualizer.stopDisplay();
//  ///////////////////////////////////////////////////////////////////////////////////////////////////

//  ///////////////////////////////////////////////////////////////////////////////////////////////////
//
//  pcl::IterativeClosestPointNonLinear<pcl::PointXYZ, pcl::PointXYZ> icpnl;
//
//  icpnl.setMaximumIterations(10000);
//
//  icpnl.setMaxCorrespondenceDistance (0.6);
////  icpnl.setMaxCorrespondenceDistance (0.8);
////  icpnl.setMaxCorrespondenceDistance (1.5);
//
////  icpnl.setRANSACOutlierRejectionThreshold (0.1);
//  icpnl.setRANSACOutlierRejectionThreshold (0.8);
////  icpnl.setRANSACOutlierRejectionThreshold (1.5);
////  icpnl.setRANSACOutlierRejectionThreshold (5.0);
//
//  icpnl.setInputCloud  (source);
//  icpnl.setInputTarget (target);
//
//  // Register the registration algorithm to the RegistrationVisualizer
//  registrationVisualizer.setRegistration (icpnl);
//
//  // Start registration process
//  icpnl.align (source_aligned);
//
//  std::cout << "has converged:" << icpnl.hasConverged () << " score: " << icpnl.getFitnessScore () << std::endl;
//  std::cout << icpnl.getFinalTransformation () << std::endl;
//
//  ///////////////////////////////////////////////////////////////////////////////////////////////////

  return 0;
}

