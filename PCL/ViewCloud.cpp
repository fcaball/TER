#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/console/print.h>
#include <pcl/registration/icp.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/io/ply_io.h>
#include <pcl/io/vtk_io.h>
#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>
#include <pcl/visualization/point_cloud_color_handlers.h>



#include <pcl/console/parse.h>
#include <pcl/console/time.h>
using namespace pcl;
using namespace pcl::io;
using namespace pcl::console;

void
printHelp (int, char **argv)
{
  print_error ("Syntax is: %s [-format 0|1] input.pcd\n", argv[0]);
}

int main(int argc, char** argv)
{
    if (argc < 2)
    {
      printHelp (argc, argv);
      return (-1);
    }
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_src(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::io::loadPCDFile<pcl::PointXYZ>(argv[1], *cloud_src);

    pcl::visualization::PCLVisualizer *viewer = new pcl::visualization::PCLVisualizer("3D Viewer");
    viewer->addPointCloud<pcl::PointXYZ> (cloud_src, "sample cloud");

    while (!viewer->wasStopped ()){
        viewer->spinOnce (100);
    }

    return 0;
}
