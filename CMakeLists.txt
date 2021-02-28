# require CMake 2.8 or greater
cmake_minimum_required(VERSION 2.8)

# declare Robotic-Recovery project
project(Robotic-Recovery)

# import jetson-inference and jetson-utils packages.
# note that if you didn't do "sudo make install"
# while building jetson-inference, this will error.
find_package(jetson-utils)
find_package(jetson-inference)

# CUDA and Qt4 and NCurses are required
find_package(CUDA)
find_package(Qt4)

# setup Qt4 for build
include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})

# include header
include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_INCLUDE_DIR})
include_directories(~/Documents/jetson-inference/build/aarch64/include/jetson-inference )
include_directories(~/Documents/jetson-inference/build/aarch64/include/jetson-utils)
include_directories(/usr/include/gstreamer-1.0)
include_directories(/usr/lib/aarch64-linux-gnu/gstreamer-1.0/include)
include_directories(/usr/include/glib-2.0 /usr/include/libxml2)
include_directories(/usr/lib/aarch64-linux-gnu/glib-2.0/include/)
include_directories(include ${realsense_INCLUDE_DIR})

file(GLOB Robotic-Recovery-Src *.cpp)
file(GLOB Robotic-Recovery-Inc *.h )

cuda_add_executable(Robotic-Recovery ${Robotic-Recovery-Src} ${Robotic-Recovery-Inc})

target_link_libraries(Robotic-Recovery jetson-inference)
