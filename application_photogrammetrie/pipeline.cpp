#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/registration/icp.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/visualization/registration_visualizer.h>
#include <pcl/io/ply_io.h>
#include <pcl/point_types.h>
#include <pcl/visualization/point_cloud_color_handlers.h>
#include <pcl/filters/filter.h>
#include <pcl/common/impl/centroid.hpp>
#include <pcl/filters/passthrough.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/search/kdtree.h>
#include <pcl/filters/statistical_outlier_removal.h>
#include <algorithm>
#include <vector>
#include <pcl/io/vtk_io.h>
#include <pcl/surface/concave_hull.h>
#include <pcl/surface/convex_hull.h>
#include <string>

#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSTLReader.h>
#include <vtkPolyDataReader.h>

using namespace std;
using namespace pcl;
using namespace pcl::io;
using namespace pcl::console;


// fusionne deux nuages de points de taille différentes
pcl::PointCloud<pcl::PointXYZ>::Ptr mergePointClouds(pcl::PointCloud<pcl::PointXYZ> cloud1, pcl::PointCloud<pcl::PointXYZ>::Ptr cloud2)
{
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_merged(new pcl::PointCloud<pcl::PointXYZ>);
    // ajoute chaque point du nuage de points small dans le nuage de points large
    for (size_t i = 0; i < cloud1.size(); ++i)
    {
        pcl::PointXYZ point = cloud1.points[i];
        cloud_merged->push_back(point);
    }

    for (size_t i = 0; i < cloud2->size(); ++i)
    {
        pcl::PointXYZ point = cloud2->points[i];
        cloud_merged->push_back(point);
    }

    return cloud_merged;
}

//Verifie si un point est deja dans le nuage
bool alreadyInCloud(pcl::PointXYZ point, pcl::PointCloud<pcl::PointXYZ>::Ptr cloud){
  for (size_t i = 0; i < cloud->size(); ++i){
      if(cloud->points[i].x == point.x && cloud->points[i].y == point.y && cloud->points[i].z == point.z){
        return true;
      }
  }

  return false;
}

//Supprime les doublons
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

//Effectue un recalage lineaire entre deux nuages de points
pcl::PointCloud<pcl::PointXYZ>::Ptr linearReadjustment(const std::string &path1, const std::string &path2, const std::string &path3, float leaf_size, int max_correspondance, int max_iterations, float max_distance, float ransac_threshold){

  pcl::PointCloud<pcl::PointXYZ>::Ptr inputCloud(new pcl::PointCloud<pcl::PointXYZ>);
  pcl::PointCloud<pcl::PointXYZ>::Ptr targetCloud(new pcl::PointCloud<pcl::PointXYZ>);
  pcl::PointCloud<pcl::PointXYZ>::Ptr mergedCloud(new pcl::PointCloud<pcl::PointXYZ>);

  //Source cloud recaler
  pcl::PointCloud<pcl::PointXYZ> source_aligned;

   if (pcl::io::loadPCDFile<pcl::PointXYZ> (path1, *inputCloud) == -1)
  {
    PCL_ERROR ("Couldn't read the first .pcd file \n");
    exit(-1);
  }

  if (pcl::io::loadPCDFile<pcl::PointXYZ> (path2, *targetCloud) == -1)
  {
    PCL_ERROR ("Couldn't read the second .pcd file \n");
    exit(-1);
  }

  if (pcl::io::savePCDFileBinary<pcl::PointXYZ> (path3, source_aligned) == -1)
  {
    PCL_ERROR ("Couldn't save the final .pcd file \n");
    exit(-1);
  }

  pcl::PointCloud<pcl::PointXYZ> inputCloudFiltered;
  pcl::PointCloud<pcl::PointXYZ> targetCloudFiltered;

  pcl::VoxelGrid<pcl::PointXYZ> sor;
  sor.setLeafSize (leaf_size, leaf_size, leaf_size);

  //Filter source cloud
  sor.setInputCloud (inputCloud);
  std::cout<<"\n inputCloud->size()="<<inputCloud->size()<<std::endl;
  sor.filter (inputCloudFiltered);
  std::cout<<"\n inputCloudFiltered.size()="<<inputCloudFiltered.size()<<std::endl;

  //Filter target cloud
  sor.setInputCloud (targetCloud);
  std::cout<<"\n targetCloud->size()="<<targetCloud->size()<<std::endl;
  sor.filter (targetCloudFiltered);
  std::cout<<"\n targetCloudFiltered.size()="<<targetCloudFiltered.size()<<std::endl;

  pcl::PointCloud<pcl::PointXYZ>::ConstPtr source = inputCloudFiltered.makeShared();
  pcl::PointCloud<pcl::PointXYZ>::ConstPtr target = targetCloudFiltered.makeShared();

  pcl::RegistrationVisualizer<pcl::PointXYZ, pcl::PointXYZ> registrationVisualizer;

  registrationVisualizer.setMaximumDisplayedCorrespondences (max_correspondance);

  pcl::IterativeClosestPoint<pcl::PointXYZ, pcl::PointXYZ> icp;

  icp.setMaximumIterations(max_iterations);

  icp.setMaxCorrespondenceDistance(max_distance);

  icp.setRANSACOutlierRejectionThreshold(ransac_threshold);

  icp.setInputSource (source);
  icp.setInputTarget (target);

  //registrationVisualizer.setRegistration (icp);

  //registrationVisualizer.startDisplay();

  icp.align(source_aligned);

  std::cout << "has converged:" << icp.hasConverged () << " score: " << icp.getFitnessScore () << std::endl;
  std::cout << icp.getFinalTransformation () << std::endl;

  //registrationVisualizer.stopDisplay();

  mergedCloud = mergePointClouds(source_aligned, targetCloud);
  mergedCloud = deleteDuplicatePoints(mergedCloud);

  pcl::io::savePCDFileBinary(path3, *mergedCloud);

  return mergedCloud;

}

void pipeline(std::vector<std::string> &filePaths, float leaf_size, int max_correspondance, int max_iterations, float max_distance, float ransac_threshold){

  pcl::PointCloud<pcl::PointXYZ>::Ptr finalCloud(new pcl::PointCloud<pcl::PointXYZ>);

  while(filePaths.size()>1){
    std::string newPath = filePaths[0].substr(0, filePaths[0].length()-4);
    string path = filePaths[1].substr(0, filePaths[1].length()-4);
    newPath += "::";
    newPath += path[path.length()-1];
    newPath += ".pcd";
    cout<<newPath<<endl;
    finalCloud = linearReadjustment(filePaths[0], filePaths[1], newPath, leaf_size, max_correspondance, max_iterations, max_distance, ransac_threshold);
    filePaths[0] = newPath;
    filePaths.erase(filePaths.begin()+1);
  }

  pcl::io::loadPCDFile<pcl::PointXYZ> (filePaths[0], *finalCloud);

  pcl::visualization::PCLVisualizer *viewer = new pcl::visualization::PCLVisualizer("3D Viewer");
  viewer->addPointCloud<pcl::PointXYZ> (finalCloud, "final cloud");

  while (!viewer->wasStopped ()){
    viewer->spinOnce (100);
  }


}

void VTK_viewer(const char* pathToMesh){
  vtkSmartPointer<vtkPolyDataReader> reader = vtkSmartPointer<vtkPolyDataReader>::New();
  reader->SetFileName(pathToMesh);
  reader->Update();

  vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputData(reader->GetOutput());

  vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
  renderer->AddActor(actor);
  renderer->SetBackground(0.1, 0.2, 0.4); // RGB values (0-1 range)

  vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  renderWindow->SetSize(800, 600); // Adjust the size as needed

  vtkSmartPointer<vtkRenderWindowInteractor> interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);

  interactor->Initialize();
  interactor->Start();

}


void compute(PointCloud<PointXYZ>::ConstPtr cloud_in, bool convex_concave_hull, float alpha, PolygonMesh &mesh_out)
{
  if (!convex_concave_hull)
  {
    print_info ("Computing the convex hull of a cloud with %lu points.\n", cloud_in->size ());
    ConvexHull<PointXYZ> convex_hull;
    convex_hull.setInputCloud (cloud_in);
    convex_hull.reconstruct (mesh_out);
  }
  else
  {
    print_info ("Computing the concave hull (alpha shapes) with alpha %f of a cloud with %lu points.\n", alpha, cloud_in->size ());
    ConcaveHull<PointXYZ> concave_hull;
    concave_hull.setInputCloud (cloud_in);
    concave_hull.setAlpha (alpha);
    concave_hull.reconstruct (mesh_out);
  }
}

pcl::PolygonMesh computeAndSaveMesh(const std::string &inputPath, const std::string &outputPath, float alpha, bool convex_concave_hull){

  pcl::PointCloud<pcl::PointXYZ>::Ptr inputCloud(new pcl::PointCloud<pcl::PointXYZ>);

  pcl::io::loadPCDFile<pcl::PointXYZ> (inputPath, *inputCloud);

  pcl::PolygonMesh mesh_out;
  compute(inputCloud, convex_concave_hull, alpha, mesh_out);
  pcl::io::saveVTKFile(outputPath, mesh_out);

  return mesh_out;

}

void pipeline_to_mesh(std::vector<std::string> &filePaths, bool convex_concave_hull, float leaf_size, int max_correspondance, int max_iterations, float max_distance, float ransac_threshold, float alpha, const std::string &meshPath){

  pcl::PointCloud<pcl::PointXYZ>::Ptr finalCloud(new pcl::PointCloud<pcl::PointXYZ>);
  pcl::PolygonMesh mesh_out;
      cout<<"t"<<endl;
  while(filePaths.size()>1){

    std::string newPath = filePaths[0].substr(0, filePaths[0].length()-4);
    string path = filePaths[1].substr(0, filePaths[1].length()-4);
    newPath += "::";
    newPath += path[path.length()-1];
    newPath += ".pcd";

    finalCloud = linearReadjustment(filePaths[0], filePaths[1], newPath, leaf_size, max_correspondance, max_iterations, max_distance, ransac_threshold);
    filePaths[0] = newPath;
    filePaths.erase(filePaths.begin()+1);
  }
  
  mesh_out = computeAndSaveMesh(filePaths[0], meshPath, alpha, convex_concave_hull);

  const char* finalmeshpath = meshPath.c_str();

  VTK_viewer(finalmeshpath);
}



int main(int argc, char** argv){
  vector<string> filePaths;
  int nbPCDFiles=atoi(argv[1]);

  for(int i=1;i<nbPCDFiles;i++){
      string path=argv[2];
      path+="pointcloud";
      path+=to_string(i);
      path+="::";
      path+=to_string((i+1));
      path+=".pcd";      
      filePaths.push_back(path); 
  }

  string pathMesh=argv[2];
  pathMesh+="mesh.vtk";
  
  if(atoi(argv[4])==0){
    pipeline(filePaths, 0.5, 100, 1000, 0.8, 0.4);
  }else if(atoi(argv[4])==1){
    pipeline_to_mesh(filePaths,  true,  0.5, 100, 1000, 0.8, 0.4,atof(argv[3]),pathMesh);
  }



  return 0;
}
