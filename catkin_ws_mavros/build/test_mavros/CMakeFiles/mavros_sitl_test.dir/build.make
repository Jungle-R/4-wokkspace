# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

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
CMAKE_SOURCE_DIR = /home/pi/catkin_ws_mavros/src/mavros/test_mavros

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/pi/catkin_ws_mavros/build/test_mavros

# Include any dependencies generated for this target.
include CMakeFiles/mavros_sitl_test.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/mavros_sitl_test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/mavros_sitl_test.dir/flags.make

CMakeFiles/mavros_sitl_test.dir/sitl_test/lib/pid_controller.cpp.o: CMakeFiles/mavros_sitl_test.dir/flags.make
CMakeFiles/mavros_sitl_test.dir/sitl_test/lib/pid_controller.cpp.o: /home/pi/catkin_ws_mavros/src/mavros/test_mavros/sitl_test/lib/pid_controller.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/catkin_ws_mavros/build/test_mavros/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/mavros_sitl_test.dir/sitl_test/lib/pid_controller.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mavros_sitl_test.dir/sitl_test/lib/pid_controller.cpp.o -c /home/pi/catkin_ws_mavros/src/mavros/test_mavros/sitl_test/lib/pid_controller.cpp

CMakeFiles/mavros_sitl_test.dir/sitl_test/lib/pid_controller.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mavros_sitl_test.dir/sitl_test/lib/pid_controller.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/catkin_ws_mavros/src/mavros/test_mavros/sitl_test/lib/pid_controller.cpp > CMakeFiles/mavros_sitl_test.dir/sitl_test/lib/pid_controller.cpp.i

CMakeFiles/mavros_sitl_test.dir/sitl_test/lib/pid_controller.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mavros_sitl_test.dir/sitl_test/lib/pid_controller.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/catkin_ws_mavros/src/mavros/test_mavros/sitl_test/lib/pid_controller.cpp -o CMakeFiles/mavros_sitl_test.dir/sitl_test/lib/pid_controller.cpp.s

CMakeFiles/mavros_sitl_test.dir/sitl_test/lib/sitl_test.cpp.o: CMakeFiles/mavros_sitl_test.dir/flags.make
CMakeFiles/mavros_sitl_test.dir/sitl_test/lib/sitl_test.cpp.o: /home/pi/catkin_ws_mavros/src/mavros/test_mavros/sitl_test/lib/sitl_test.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/catkin_ws_mavros/build/test_mavros/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/mavros_sitl_test.dir/sitl_test/lib/sitl_test.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mavros_sitl_test.dir/sitl_test/lib/sitl_test.cpp.o -c /home/pi/catkin_ws_mavros/src/mavros/test_mavros/sitl_test/lib/sitl_test.cpp

CMakeFiles/mavros_sitl_test.dir/sitl_test/lib/sitl_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mavros_sitl_test.dir/sitl_test/lib/sitl_test.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/catkin_ws_mavros/src/mavros/test_mavros/sitl_test/lib/sitl_test.cpp > CMakeFiles/mavros_sitl_test.dir/sitl_test/lib/sitl_test.cpp.i

CMakeFiles/mavros_sitl_test.dir/sitl_test/lib/sitl_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mavros_sitl_test.dir/sitl_test/lib/sitl_test.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/catkin_ws_mavros/src/mavros/test_mavros/sitl_test/lib/sitl_test.cpp -o CMakeFiles/mavros_sitl_test.dir/sitl_test/lib/sitl_test.cpp.s

# Object files for target mavros_sitl_test
mavros_sitl_test_OBJECTS = \
"CMakeFiles/mavros_sitl_test.dir/sitl_test/lib/pid_controller.cpp.o" \
"CMakeFiles/mavros_sitl_test.dir/sitl_test/lib/sitl_test.cpp.o"

# External object files for target mavros_sitl_test
mavros_sitl_test_EXTERNAL_OBJECTS =

/home/pi/catkin_ws_mavros/devel/.private/test_mavros/lib/libmavros_sitl_test.so: CMakeFiles/mavros_sitl_test.dir/sitl_test/lib/pid_controller.cpp.o
/home/pi/catkin_ws_mavros/devel/.private/test_mavros/lib/libmavros_sitl_test.so: CMakeFiles/mavros_sitl_test.dir/sitl_test/lib/sitl_test.cpp.o
/home/pi/catkin_ws_mavros/devel/.private/test_mavros/lib/libmavros_sitl_test.so: CMakeFiles/mavros_sitl_test.dir/build.make
/home/pi/catkin_ws_mavros/devel/.private/test_mavros/lib/libmavros_sitl_test.so: /usr/lib/arm-linux-gnueabihf/libboost_system.so
/home/pi/catkin_ws_mavros/devel/.private/test_mavros/lib/libmavros_sitl_test.so: /opt/ros/melodic/lib/libcontrol_toolbox.so
/home/pi/catkin_ws_mavros/devel/.private/test_mavros/lib/libmavros_sitl_test.so: /usr/lib/arm-linux-gnueabihf/libtinyxml.so
/home/pi/catkin_ws_mavros/devel/.private/test_mavros/lib/libmavros_sitl_test.so: /opt/ros/melodic/lib/libdynamic_reconfigure_config_init_mutex.so
/home/pi/catkin_ws_mavros/devel/.private/test_mavros/lib/libmavros_sitl_test.so: /opt/ros/melodic/lib/librealtime_tools.so
/home/pi/catkin_ws_mavros/devel/.private/test_mavros/lib/libmavros_sitl_test.so: /home/pi/catkin_ws_mavros/install/lib/libmavros.so
/home/pi/catkin_ws_mavros/devel/.private/test_mavros/lib/libmavros_sitl_test.so: /usr/lib/arm-linux-gnueabihf/libGeographic.so
/home/pi/catkin_ws_mavros/devel/.private/test_mavros/lib/libmavros_sitl_test.so: /opt/ros/melodic/lib/libeigen_conversions.so
/home/pi/catkin_ws_mavros/devel/.private/test_mavros/lib/libmavros_sitl_test.so: /opt/ros/melodic/lib/liborocos-kdl.so.1.4.0
/home/pi/catkin_ws_mavros/devel/.private/test_mavros/lib/libmavros_sitl_test.so: /home/pi/catkin_ws_mavros/install/lib/libmavconn.so
/home/pi/catkin_ws_mavros/devel/.private/test_mavros/lib/libmavros_sitl_test.so: /opt/ros/melodic/lib/libclass_loader.so
/home/pi/catkin_ws_mavros/devel/.private/test_mavros/lib/libmavros_sitl_test.so: /usr/lib/libPocoFoundation.so
/home/pi/catkin_ws_mavros/devel/.private/test_mavros/lib/libmavros_sitl_test.so: /usr/lib/arm-linux-gnueabihf/libdl.so
/home/pi/catkin_ws_mavros/devel/.private/test_mavros/lib/libmavros_sitl_test.so: /opt/ros/melodic/lib/libroslib.so
/home/pi/catkin_ws_mavros/devel/.private/test_mavros/lib/libmavros_sitl_test.so: /opt/ros/melodic/lib/librospack.so
/home/pi/catkin_ws_mavros/devel/.private/test_mavros/lib/libmavros_sitl_test.so: /usr/lib/arm-linux-gnueabihf/libpython2.7.so
/home/pi/catkin_ws_mavros/devel/.private/test_mavros/lib/libmavros_sitl_test.so: /usr/lib/arm-linux-gnueabihf/libboost_program_options.so
/home/pi/catkin_ws_mavros/devel/.private/test_mavros/lib/libmavros_sitl_test.so: /usr/lib/arm-linux-gnueabihf/libtinyxml2.so
/home/pi/catkin_ws_mavros/devel/.private/test_mavros/lib/libmavros_sitl_test.so: /opt/ros/melodic/lib/libtf2_ros.so
/home/pi/catkin_ws_mavros/devel/.private/test_mavros/lib/libmavros_sitl_test.so: /opt/ros/melodic/lib/libactionlib.so
/home/pi/catkin_ws_mavros/devel/.private/test_mavros/lib/libmavros_sitl_test.so: /opt/ros/melodic/lib/libmessage_filters.so
/home/pi/catkin_ws_mavros/devel/.private/test_mavros/lib/libmavros_sitl_test.so: /opt/ros/melodic/lib/libroscpp.so
/home/pi/catkin_ws_mavros/devel/.private/test_mavros/lib/libmavros_sitl_test.so: /usr/lib/arm-linux-gnueabihf/libboost_filesystem.so
/home/pi/catkin_ws_mavros/devel/.private/test_mavros/lib/libmavros_sitl_test.so: /opt/ros/melodic/lib/librosconsole.so
/home/pi/catkin_ws_mavros/devel/.private/test_mavros/lib/libmavros_sitl_test.so: /opt/ros/melodic/lib/librosconsole_log4cxx.so
/home/pi/catkin_ws_mavros/devel/.private/test_mavros/lib/libmavros_sitl_test.so: /opt/ros/melodic/lib/librosconsole_backend_interface.so
/home/pi/catkin_ws_mavros/devel/.private/test_mavros/lib/libmavros_sitl_test.so: /usr/lib/arm-linux-gnueabihf/liblog4cxx.so
/home/pi/catkin_ws_mavros/devel/.private/test_mavros/lib/libmavros_sitl_test.so: /usr/lib/arm-linux-gnueabihf/libboost_regex.so
/home/pi/catkin_ws_mavros/devel/.private/test_mavros/lib/libmavros_sitl_test.so: /opt/ros/melodic/lib/libxmlrpcpp.so
/home/pi/catkin_ws_mavros/devel/.private/test_mavros/lib/libmavros_sitl_test.so: /opt/ros/melodic/lib/libtf2.so
/home/pi/catkin_ws_mavros/devel/.private/test_mavros/lib/libmavros_sitl_test.so: /opt/ros/melodic/lib/libroscpp_serialization.so
/home/pi/catkin_ws_mavros/devel/.private/test_mavros/lib/libmavros_sitl_test.so: /opt/ros/melodic/lib/librostime.so
/home/pi/catkin_ws_mavros/devel/.private/test_mavros/lib/libmavros_sitl_test.so: /opt/ros/melodic/lib/libcpp_common.so
/home/pi/catkin_ws_mavros/devel/.private/test_mavros/lib/libmavros_sitl_test.so: /usr/lib/arm-linux-gnueabihf/libboost_system.so
/home/pi/catkin_ws_mavros/devel/.private/test_mavros/lib/libmavros_sitl_test.so: /usr/lib/arm-linux-gnueabihf/libboost_thread.so
/home/pi/catkin_ws_mavros/devel/.private/test_mavros/lib/libmavros_sitl_test.so: /usr/lib/arm-linux-gnueabihf/libboost_chrono.so
/home/pi/catkin_ws_mavros/devel/.private/test_mavros/lib/libmavros_sitl_test.so: /usr/lib/arm-linux-gnueabihf/libboost_date_time.so
/home/pi/catkin_ws_mavros/devel/.private/test_mavros/lib/libmavros_sitl_test.so: /usr/lib/arm-linux-gnueabihf/libboost_atomic.so
/home/pi/catkin_ws_mavros/devel/.private/test_mavros/lib/libmavros_sitl_test.so: /usr/lib/arm-linux-gnueabihf/libconsole_bridge.so.0.4
/home/pi/catkin_ws_mavros/devel/.private/test_mavros/lib/libmavros_sitl_test.so: /opt/ros/melodic/lib/libcontrol_toolbox.so
/home/pi/catkin_ws_mavros/devel/.private/test_mavros/lib/libmavros_sitl_test.so: /usr/lib/arm-linux-gnueabihf/libtinyxml.so
/home/pi/catkin_ws_mavros/devel/.private/test_mavros/lib/libmavros_sitl_test.so: /opt/ros/melodic/lib/libdynamic_reconfigure_config_init_mutex.so
/home/pi/catkin_ws_mavros/devel/.private/test_mavros/lib/libmavros_sitl_test.so: /opt/ros/melodic/lib/librealtime_tools.so
/home/pi/catkin_ws_mavros/devel/.private/test_mavros/lib/libmavros_sitl_test.so: /home/pi/catkin_ws_mavros/install/lib/libmavros.so
/home/pi/catkin_ws_mavros/devel/.private/test_mavros/lib/libmavros_sitl_test.so: /usr/lib/arm-linux-gnueabihf/libGeographic.so
/home/pi/catkin_ws_mavros/devel/.private/test_mavros/lib/libmavros_sitl_test.so: /opt/ros/melodic/lib/libeigen_conversions.so
/home/pi/catkin_ws_mavros/devel/.private/test_mavros/lib/libmavros_sitl_test.so: /opt/ros/melodic/lib/liborocos-kdl.so.1.4.0
/home/pi/catkin_ws_mavros/devel/.private/test_mavros/lib/libmavros_sitl_test.so: /home/pi/catkin_ws_mavros/install/lib/libmavconn.so
/home/pi/catkin_ws_mavros/devel/.private/test_mavros/lib/libmavros_sitl_test.so: /opt/ros/melodic/lib/libclass_loader.so
/home/pi/catkin_ws_mavros/devel/.private/test_mavros/lib/libmavros_sitl_test.so: /usr/lib/libPocoFoundation.so
/home/pi/catkin_ws_mavros/devel/.private/test_mavros/lib/libmavros_sitl_test.so: /usr/lib/arm-linux-gnueabihf/libdl.so
/home/pi/catkin_ws_mavros/devel/.private/test_mavros/lib/libmavros_sitl_test.so: /opt/ros/melodic/lib/libroslib.so
/home/pi/catkin_ws_mavros/devel/.private/test_mavros/lib/libmavros_sitl_test.so: /opt/ros/melodic/lib/librospack.so
/home/pi/catkin_ws_mavros/devel/.private/test_mavros/lib/libmavros_sitl_test.so: /usr/lib/arm-linux-gnueabihf/libpython2.7.so
/home/pi/catkin_ws_mavros/devel/.private/test_mavros/lib/libmavros_sitl_test.so: /usr/lib/arm-linux-gnueabihf/libboost_program_options.so
/home/pi/catkin_ws_mavros/devel/.private/test_mavros/lib/libmavros_sitl_test.so: /usr/lib/arm-linux-gnueabihf/libtinyxml2.so
/home/pi/catkin_ws_mavros/devel/.private/test_mavros/lib/libmavros_sitl_test.so: /opt/ros/melodic/lib/libtf2_ros.so
/home/pi/catkin_ws_mavros/devel/.private/test_mavros/lib/libmavros_sitl_test.so: /opt/ros/melodic/lib/libactionlib.so
/home/pi/catkin_ws_mavros/devel/.private/test_mavros/lib/libmavros_sitl_test.so: /opt/ros/melodic/lib/libmessage_filters.so
/home/pi/catkin_ws_mavros/devel/.private/test_mavros/lib/libmavros_sitl_test.so: /opt/ros/melodic/lib/libroscpp.so
/home/pi/catkin_ws_mavros/devel/.private/test_mavros/lib/libmavros_sitl_test.so: /usr/lib/arm-linux-gnueabihf/libboost_filesystem.so
/home/pi/catkin_ws_mavros/devel/.private/test_mavros/lib/libmavros_sitl_test.so: /opt/ros/melodic/lib/librosconsole.so
/home/pi/catkin_ws_mavros/devel/.private/test_mavros/lib/libmavros_sitl_test.so: /opt/ros/melodic/lib/librosconsole_log4cxx.so
/home/pi/catkin_ws_mavros/devel/.private/test_mavros/lib/libmavros_sitl_test.so: /opt/ros/melodic/lib/librosconsole_backend_interface.so
/home/pi/catkin_ws_mavros/devel/.private/test_mavros/lib/libmavros_sitl_test.so: /usr/lib/arm-linux-gnueabihf/liblog4cxx.so
/home/pi/catkin_ws_mavros/devel/.private/test_mavros/lib/libmavros_sitl_test.so: /usr/lib/arm-linux-gnueabihf/libboost_regex.so
/home/pi/catkin_ws_mavros/devel/.private/test_mavros/lib/libmavros_sitl_test.so: /opt/ros/melodic/lib/libxmlrpcpp.so
/home/pi/catkin_ws_mavros/devel/.private/test_mavros/lib/libmavros_sitl_test.so: /opt/ros/melodic/lib/libtf2.so
/home/pi/catkin_ws_mavros/devel/.private/test_mavros/lib/libmavros_sitl_test.so: /opt/ros/melodic/lib/libroscpp_serialization.so
/home/pi/catkin_ws_mavros/devel/.private/test_mavros/lib/libmavros_sitl_test.so: /opt/ros/melodic/lib/librostime.so
/home/pi/catkin_ws_mavros/devel/.private/test_mavros/lib/libmavros_sitl_test.so: /opt/ros/melodic/lib/libcpp_common.so
/home/pi/catkin_ws_mavros/devel/.private/test_mavros/lib/libmavros_sitl_test.so: /usr/lib/arm-linux-gnueabihf/libboost_thread.so
/home/pi/catkin_ws_mavros/devel/.private/test_mavros/lib/libmavros_sitl_test.so: /usr/lib/arm-linux-gnueabihf/libboost_chrono.so
/home/pi/catkin_ws_mavros/devel/.private/test_mavros/lib/libmavros_sitl_test.so: /usr/lib/arm-linux-gnueabihf/libboost_date_time.so
/home/pi/catkin_ws_mavros/devel/.private/test_mavros/lib/libmavros_sitl_test.so: /usr/lib/arm-linux-gnueabihf/libboost_atomic.so
/home/pi/catkin_ws_mavros/devel/.private/test_mavros/lib/libmavros_sitl_test.so: /usr/lib/arm-linux-gnueabihf/libconsole_bridge.so.0.4
/home/pi/catkin_ws_mavros/devel/.private/test_mavros/lib/libmavros_sitl_test.so: CMakeFiles/mavros_sitl_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/pi/catkin_ws_mavros/build/test_mavros/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX shared library /home/pi/catkin_ws_mavros/devel/.private/test_mavros/lib/libmavros_sitl_test.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mavros_sitl_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/mavros_sitl_test.dir/build: /home/pi/catkin_ws_mavros/devel/.private/test_mavros/lib/libmavros_sitl_test.so

.PHONY : CMakeFiles/mavros_sitl_test.dir/build

CMakeFiles/mavros_sitl_test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/mavros_sitl_test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/mavros_sitl_test.dir/clean

CMakeFiles/mavros_sitl_test.dir/depend:
	cd /home/pi/catkin_ws_mavros/build/test_mavros && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pi/catkin_ws_mavros/src/mavros/test_mavros /home/pi/catkin_ws_mavros/src/mavros/test_mavros /home/pi/catkin_ws_mavros/build/test_mavros /home/pi/catkin_ws_mavros/build/test_mavros /home/pi/catkin_ws_mavros/build/test_mavros/CMakeFiles/mavros_sitl_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/mavros_sitl_test.dir/depend

