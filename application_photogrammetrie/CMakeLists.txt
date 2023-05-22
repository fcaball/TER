cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(cloud_viewer)

find_package(PCL 1.2 REQUIRED)

include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

add_executable (ply_to_pcd convert_PLY_to_PCD.cpp)
target_link_libraries (ply_to_pcd ${PCL_LIBRARIES})
add_executable (view_pcd ViewCloud.cpp)
target_link_libraries (view_pcd ${PCL_LIBRARIES})
add_executable (pipeline_pcd pipeline.cpp)
target_link_libraries (pipeline_pcd ${PCL_LIBRARIES})
add_executable (off_to_ply convert_OFF_to_PLY.cpp)
target_link_libraries (off_to_ply ${PCL_LIBRARIES})

