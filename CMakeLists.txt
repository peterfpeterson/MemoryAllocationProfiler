cmake_minimum_required(VERSION 3.20)

project(memprofiler VERSION 0.0.1)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

find_package(HDF5 REQUIRED COMPONENTS CXX)
find_package(Nexus 4.4 REQUIRED)

add_executable(mem_profiler main.cpp)

add_executable(pushback pushback.cpp)

add_executable(nexusopenclose nexusopenclose.cpp)
target_link_libraries(nexusopenclose PRIVATE Nexus::nexus Nexus::nexuscpp)
