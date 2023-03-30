cmake_minimum_required(VERSION 3.24)
project(RayTracingInOneWeek)

set(CMAKE_CXX_STANDARD 17)

add_executable(RayTracingInOneWeek main.cpp ppm_files.cpp ppm_files.h vec3.h ray.h hittable.cpp hittable.h objects.cpp objects.h constants.h debug_fun.cpp debug_fun.h vec3.cpp camera.cpp camera.h)
