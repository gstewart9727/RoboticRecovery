# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/gabriel/Documents/RoboticRecovery

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/gabriel/Documents/RoboticRecovery

# Include any dependencies generated for this target.
include CMakeFiles/Robotic-Recovery.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Robotic-Recovery.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Robotic-Recovery.dir/flags.make

CMakeFiles/Robotic-Recovery.dir/detectnet-camera.cpp.o: CMakeFiles/Robotic-Recovery.dir/flags.make
CMakeFiles/Robotic-Recovery.dir/detectnet-camera.cpp.o: detectnet-camera.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gabriel/Documents/RoboticRecovery/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Robotic-Recovery.dir/detectnet-camera.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Robotic-Recovery.dir/detectnet-camera.cpp.o -c /home/gabriel/Documents/RoboticRecovery/detectnet-camera.cpp

CMakeFiles/Robotic-Recovery.dir/detectnet-camera.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Robotic-Recovery.dir/detectnet-camera.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gabriel/Documents/RoboticRecovery/detectnet-camera.cpp > CMakeFiles/Robotic-Recovery.dir/detectnet-camera.cpp.i

CMakeFiles/Robotic-Recovery.dir/detectnet-camera.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Robotic-Recovery.dir/detectnet-camera.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gabriel/Documents/RoboticRecovery/detectnet-camera.cpp -o CMakeFiles/Robotic-Recovery.dir/detectnet-camera.cpp.s

CMakeFiles/Robotic-Recovery.dir/detectnet-camera.cpp.o.requires:

.PHONY : CMakeFiles/Robotic-Recovery.dir/detectnet-camera.cpp.o.requires

CMakeFiles/Robotic-Recovery.dir/detectnet-camera.cpp.o.provides: CMakeFiles/Robotic-Recovery.dir/detectnet-camera.cpp.o.requires
	$(MAKE) -f CMakeFiles/Robotic-Recovery.dir/build.make CMakeFiles/Robotic-Recovery.dir/detectnet-camera.cpp.o.provides.build
.PHONY : CMakeFiles/Robotic-Recovery.dir/detectnet-camera.cpp.o.provides

CMakeFiles/Robotic-Recovery.dir/detectnet-camera.cpp.o.provides.build: CMakeFiles/Robotic-Recovery.dir/detectnet-camera.cpp.o


CMakeFiles/Robotic-Recovery.dir/graphics.cpp.o: CMakeFiles/Robotic-Recovery.dir/flags.make
CMakeFiles/Robotic-Recovery.dir/graphics.cpp.o: graphics.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gabriel/Documents/RoboticRecovery/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Robotic-Recovery.dir/graphics.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Robotic-Recovery.dir/graphics.cpp.o -c /home/gabriel/Documents/RoboticRecovery/graphics.cpp

CMakeFiles/Robotic-Recovery.dir/graphics.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Robotic-Recovery.dir/graphics.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gabriel/Documents/RoboticRecovery/graphics.cpp > CMakeFiles/Robotic-Recovery.dir/graphics.cpp.i

CMakeFiles/Robotic-Recovery.dir/graphics.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Robotic-Recovery.dir/graphics.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gabriel/Documents/RoboticRecovery/graphics.cpp -o CMakeFiles/Robotic-Recovery.dir/graphics.cpp.s

CMakeFiles/Robotic-Recovery.dir/graphics.cpp.o.requires:

.PHONY : CMakeFiles/Robotic-Recovery.dir/graphics.cpp.o.requires

CMakeFiles/Robotic-Recovery.dir/graphics.cpp.o.provides: CMakeFiles/Robotic-Recovery.dir/graphics.cpp.o.requires
	$(MAKE) -f CMakeFiles/Robotic-Recovery.dir/build.make CMakeFiles/Robotic-Recovery.dir/graphics.cpp.o.provides.build
.PHONY : CMakeFiles/Robotic-Recovery.dir/graphics.cpp.o.provides

CMakeFiles/Robotic-Recovery.dir/graphics.cpp.o.provides.build: CMakeFiles/Robotic-Recovery.dir/graphics.cpp.o


CMakeFiles/Robotic-Recovery.dir/main.cpp.o: CMakeFiles/Robotic-Recovery.dir/flags.make
CMakeFiles/Robotic-Recovery.dir/main.cpp.o: main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gabriel/Documents/RoboticRecovery/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/Robotic-Recovery.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Robotic-Recovery.dir/main.cpp.o -c /home/gabriel/Documents/RoboticRecovery/main.cpp

CMakeFiles/Robotic-Recovery.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Robotic-Recovery.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gabriel/Documents/RoboticRecovery/main.cpp > CMakeFiles/Robotic-Recovery.dir/main.cpp.i

CMakeFiles/Robotic-Recovery.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Robotic-Recovery.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gabriel/Documents/RoboticRecovery/main.cpp -o CMakeFiles/Robotic-Recovery.dir/main.cpp.s

CMakeFiles/Robotic-Recovery.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/Robotic-Recovery.dir/main.cpp.o.requires

CMakeFiles/Robotic-Recovery.dir/main.cpp.o.provides: CMakeFiles/Robotic-Recovery.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/Robotic-Recovery.dir/build.make CMakeFiles/Robotic-Recovery.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/Robotic-Recovery.dir/main.cpp.o.provides

CMakeFiles/Robotic-Recovery.dir/main.cpp.o.provides.build: CMakeFiles/Robotic-Recovery.dir/main.cpp.o


# Object files for target Robotic-Recovery
Robotic__Recovery_OBJECTS = \
"CMakeFiles/Robotic-Recovery.dir/detectnet-camera.cpp.o" \
"CMakeFiles/Robotic-Recovery.dir/graphics.cpp.o" \
"CMakeFiles/Robotic-Recovery.dir/main.cpp.o"

# External object files for target Robotic-Recovery
Robotic__Recovery_EXTERNAL_OBJECTS =

Robotic-Recovery: CMakeFiles/Robotic-Recovery.dir/detectnet-camera.cpp.o
Robotic-Recovery: CMakeFiles/Robotic-Recovery.dir/graphics.cpp.o
Robotic-Recovery: CMakeFiles/Robotic-Recovery.dir/main.cpp.o
Robotic-Recovery: CMakeFiles/Robotic-Recovery.dir/build.make
Robotic-Recovery: /usr/local/cuda/lib64/libcudart_static.a
Robotic-Recovery: /usr/lib/aarch64-linux-gnu/librt.so
Robotic-Recovery: /usr/local/lib/libjetson-inference.so
Robotic-Recovery: /usr/local/lib/libjetson-utils.so
Robotic-Recovery: /usr/local/cuda/lib64/libcudart_static.a
Robotic-Recovery: /usr/lib/aarch64-linux-gnu/librt.so
Robotic-Recovery: CMakeFiles/Robotic-Recovery.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/gabriel/Documents/RoboticRecovery/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable Robotic-Recovery"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Robotic-Recovery.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Robotic-Recovery.dir/build: Robotic-Recovery

.PHONY : CMakeFiles/Robotic-Recovery.dir/build

CMakeFiles/Robotic-Recovery.dir/requires: CMakeFiles/Robotic-Recovery.dir/detectnet-camera.cpp.o.requires
CMakeFiles/Robotic-Recovery.dir/requires: CMakeFiles/Robotic-Recovery.dir/graphics.cpp.o.requires
CMakeFiles/Robotic-Recovery.dir/requires: CMakeFiles/Robotic-Recovery.dir/main.cpp.o.requires

.PHONY : CMakeFiles/Robotic-Recovery.dir/requires

CMakeFiles/Robotic-Recovery.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Robotic-Recovery.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Robotic-Recovery.dir/clean

CMakeFiles/Robotic-Recovery.dir/depend:
	cd /home/gabriel/Documents/RoboticRecovery && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/gabriel/Documents/RoboticRecovery /home/gabriel/Documents/RoboticRecovery /home/gabriel/Documents/RoboticRecovery /home/gabriel/Documents/RoboticRecovery /home/gabriel/Documents/RoboticRecovery/CMakeFiles/Robotic-Recovery.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Robotic-Recovery.dir/depend

