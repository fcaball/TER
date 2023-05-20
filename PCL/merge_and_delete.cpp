#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/registration/icp.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/io/ply_io.h>
#include <pcl/io/vtk_io.h>
#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>
#include <pcl/visualization/point_cloud_color_handlers.h>
#include <pcl/octree/octree.h>

// fusionne deux nuages de points de taille différentes
pcl::PointCloud<pcl::PointXYZ>::Ptr mergePointClouds(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud1 pcl::PointCloud<pcl::PointXYZ>::Ptr cloud2)
{
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_merged;
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

int main(){

pcl::PointCloud<pcl::PointXYZ>::Ptr cloud1 (new pcl::PointCloud<pcl::PointXYZ>);
pcl::PointCloud<pcl::PointXYZ>::Ptr cloud2 (new pcl::PointCloud<pcl::PointXYZ>);
pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_merged (new pcl::PointCloud<pcl::PointXYZ>);

pcl::io::loadPCDFile<pcl::PointXYZ>("statue2et3.pcd", *cloud1);
pcl::io::loadPCDFile<pcl::PointXYZ>("recalage_source12_target23.pcd", *cloud2);

cloud_merged = mergePointClouds(cloud1, cloud2)

std::cout<<cloud_merged->size()<<std::endl;

pcl::io::savePCDFileBinary("nouveaux_nuages/nuage_123.pcd", cloud_merged);


pcl::visualization::PCLVisualizer *viewer = new pcl::visualization::PCLVisualizer("3D Viewer");
viewer->addPointCloud<pcl::PointXYZ> (cloud_merged, "sample cloud");

while (!viewer->wasStopped ()){
    viewer->spinOnce (100);
}



return 0;
}

