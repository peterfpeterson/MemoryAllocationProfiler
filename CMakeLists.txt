cmake_minimum_required(VERSION 3.20)

project(memprofiler VERSION 0.0.1)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

find_package(HDF5 REQUIRED COMPONENTS CXX)
find_package(Nexus 4.4 REQUIRED)

set(KERNEL_FILES
    mantid/Kernel/inc/MantidKernel/CPUTimer.h
    mantid/Kernel/inc/MantidKernel/Memory.h
    mantid/Kernel/inc/MantidKernel/Timer.h
    mantid/Kernel/src/CPUTimer.cpp
    mantid/Kernel/src/Memory.cpp
    mantid/Kernel/src/Timer.cpp)

set(TYPES_FILES
    mantid/Types/inc/MantidTypes/Core/DateAndTime.h
    mantid/Types/inc/MantidTypes/Core/DateAndTimeHelpers.h
    mantid/Types/inc/MantidTypes/DllConfig.h
    mantid/Types/inc/MantidTypes/Event/TofEvent.h
    mantid/Types/src/Core/DateAndTime.cpp
    mantid/Types/src/Core/DateAndTimeHelpers.cpp
    mantid/Types/src/Event/TofEvent.cpp)

#
add_executable(eventlistb eventlistb.cpp ${KERNEL_FILES} ${TYPES_FILES})
target_include_directories(eventlistb PRIVATE mantid/Kernel/inc/)
target_include_directories(eventlistb PRIVATE mantid/Types/inc/)

#
add_executable(simplevec simplevec.cpp ${KERNEL_FILES})
target_include_directories(simplevec PRIVATE mantid/Kernel/inc/)

#
add_executable(tofevent_classic tofevent_classic.cpp ${KERNEL_FILES}
                                ${TYPES_FILES})
target_include_directories(tofevent_classic PRIVATE mantid/Kernel/inc/)
target_include_directories(tofevent_classic PRIVATE mantid/Types/inc/)

#
add_executable(
  tofevent_int64
  tofevent_int64.cpp mantid/Types/src/Event/TofEventInt64.cpp
  mantid/Types/inc/MantidTypes/Event/TofEventInt64.h ${KERNEL_FILES}
  ${TYPES_FILES})
target_include_directories(tofevent_int64 PRIVATE mantid/Kernel/inc/)
target_include_directories(tofevent_int64 PRIVATE mantid/Types/inc/)

add_executable(pushback pushback.cpp)

#
add_executable(nexusopenclose nexusopenclose.cpp)
target_link_libraries(nexusopenclose PRIVATE Nexus::nexus Nexus::nexuscpp)

#
add_executable(eventlistb2 eventlistb2.cpp)
target_link_libraries(eventlistb2 PRIVATE Nexus::nexus Nexus::nexuscpp)
