#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/io/ply_io.h>
#include <pcl/io/vtk_io.h>
#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>
#include <pcl/kdtree/kdtree_flann.h>
#include <pcl/features/normal_3d.h>
#include <pcl/surface/gp3.h>
#include <pcl/surface/marching_cubes.h>

int main(int argc, char** argv)
{

    pcl::visualization::PCLVisualizer *viewer = new pcl::visualization::PCLVisualizer("3D Viewer");

    //viewer->addCoordinateSystem(5.0);
    viewer->setBackgroundColor(0.5, 0.5, 0.5);

    //Load du nuage de point
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PointCloud<pcl::Normal>::Ptr normals(new pcl::PointCloud<pcl::Normal>);
    pcl::PointCloud<pcl::PointNormal>::Ptr cloudNormals(new pcl::PointCloud<pcl::PointNormal>);

    pcl::io::loadPLYFile<pcl::PointXYZ>("statue_test.ply", *cloud);

    pcl::NormalEstimation<pcl::PointXYZ, pcl::Normal> normalEstimation;
    normalEstimation.setInputCloud(cloud);
    normalEstimation.setRadiusSearch(0.03);
    pcl::search::KdTree<pcl::PointXYZ>::Ptr kdtree(new pcl::search::KdTree<pcl::PointXYZ>);
    normalEstimation.setSearchMethod(kdtree);
    normalEstimation.compute(*normals);

    pcl::concatenateFields(*cloud, *normals, *cloudNormals);
    pcl::search::KdTree<pcl::PointNormal>::Ptr kdtree2(new pcl::search::KdTree<pcl::PointNormal>);
    kdtree2->setInputCloud(cloudNormals);

    pcl::GreedyProjectionTriangulation<pcl::PointNormal> triangulation;
    pcl::PolygonMesh triangles;

    triangulation.setSearchRadius(23);
    triangulation.setMu(2.5);
    triangulation.setMaximumNearestNeighbors(600);
    triangulation.setMaximumSurfaceAngle(M_PI/4);
    triangulation.setNormalConsistency(false);
    triangulation.setMinimumAngle(M_PI/18);
    triangulation.setMaximumAngle(M_PI);

    triangulation.setInputCloud(cloudNormals);
    triangulation.setSearchMethod(kdtree2);
    triangulation.reconstruct(triangles);

    pcl::io::savePLYFile("points_triangle.ply", triangles);

    viewer->addPointCloud<pcl::PointXYZ> (cloud, "sample cloud");

    while (!viewer->wasStopped ())
        viewer->spinOnce (100);

  return 0;
}