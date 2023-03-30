cmake_minimum_required(VERSION 3.24)
project(RayTracingInOneWeek)

set(CMAKE_CXX_STANDARD 17)

add_executable(RayTracingInOneWeek main.cpp ppm_files.cpp ppm_files.h vec3.cpp vec3.h Color.cpp Color.h ray.cpp ray.h)
