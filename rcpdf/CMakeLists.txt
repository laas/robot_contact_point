cmake_minimum_required(VERSION 2.4.6)
include($ENV{ROS_ROOT}/core/rosbuild/rosbuild.cmake)

set(ROS_BUILD_TYPE RelWithDebInfo)

rosbuild_init()

#set the default path for built executables to the "bin" directory
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
#set the default path for built libraries to the "lib" directory
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

rosbuild_add_boost_directories()
rosbuild_add_library(${PROJECT_NAME} src/parser.cpp)
target_link_libraries(${PROJECT_NAME} tinyxml)

rosbuild_add_executable(check_rcpdf src/check_rcpdf.cpp)
target_link_libraries(check_rcpdf ${PROJECT_NAME})
