# Install script for directory: /home/pi/catkin_ws_mavros/src/mavros/mavros_msgs

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/pi/catkin_ws_mavros/install")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  
      if (NOT EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}")
        file(MAKE_DIRECTORY "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}")
      endif()
      if (NOT EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/.catkin")
        file(WRITE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/.catkin" "")
      endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/pi/catkin_ws_mavros/install/_setup_util.py")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/pi/catkin_ws_mavros/install" TYPE PROGRAM FILES "/home/pi/catkin_ws_mavros/build/mavros_msgs/catkin_generated/installspace/_setup_util.py")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/pi/catkin_ws_mavros/install/env.sh")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/pi/catkin_ws_mavros/install" TYPE PROGRAM FILES "/home/pi/catkin_ws_mavros/build/mavros_msgs/catkin_generated/installspace/env.sh")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/pi/catkin_ws_mavros/install/setup.bash;/home/pi/catkin_ws_mavros/install/local_setup.bash")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/pi/catkin_ws_mavros/install" TYPE FILE FILES
    "/home/pi/catkin_ws_mavros/build/mavros_msgs/catkin_generated/installspace/setup.bash"
    "/home/pi/catkin_ws_mavros/build/mavros_msgs/catkin_generated/installspace/local_setup.bash"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/pi/catkin_ws_mavros/install/setup.sh;/home/pi/catkin_ws_mavros/install/local_setup.sh")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/pi/catkin_ws_mavros/install" TYPE FILE FILES
    "/home/pi/catkin_ws_mavros/build/mavros_msgs/catkin_generated/installspace/setup.sh"
    "/home/pi/catkin_ws_mavros/build/mavros_msgs/catkin_generated/installspace/local_setup.sh"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/pi/catkin_ws_mavros/install/setup.zsh;/home/pi/catkin_ws_mavros/install/local_setup.zsh")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/pi/catkin_ws_mavros/install" TYPE FILE FILES
    "/home/pi/catkin_ws_mavros/build/mavros_msgs/catkin_generated/installspace/setup.zsh"
    "/home/pi/catkin_ws_mavros/build/mavros_msgs/catkin_generated/installspace/local_setup.zsh"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/pi/catkin_ws_mavros/install/.rosinstall")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/pi/catkin_ws_mavros/install" TYPE FILE FILES "/home/pi/catkin_ws_mavros/build/mavros_msgs/catkin_generated/installspace/.rosinstall")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/mavros_msgs/msg" TYPE FILE FILES
    "/home/pi/catkin_ws_mavros/src/mavros/mavros_msgs/msg/ADSBVehicle.msg"
    "/home/pi/catkin_ws_mavros/src/mavros/mavros_msgs/msg/ActuatorControl.msg"
    "/home/pi/catkin_ws_mavros/src/mavros/mavros_msgs/msg/Altitude.msg"
    "/home/pi/catkin_ws_mavros/src/mavros/mavros_msgs/msg/AttitudeTarget.msg"
    "/home/pi/catkin_ws_mavros/src/mavros/mavros_msgs/msg/BatteryStatus.msg"
    "/home/pi/catkin_ws_mavros/src/mavros/mavros_msgs/msg/CamIMUStamp.msg"
    "/home/pi/catkin_ws_mavros/src/mavros/mavros_msgs/msg/CommandCode.msg"
    "/home/pi/catkin_ws_mavros/src/mavros/mavros_msgs/msg/CompanionProcessStatus.msg"
    "/home/pi/catkin_ws_mavros/src/mavros/mavros_msgs/msg/OnboardComputerStatus.msg"
    "/home/pi/catkin_ws_mavros/src/mavros/mavros_msgs/msg/DebugValue.msg"
    "/home/pi/catkin_ws_mavros/src/mavros/mavros_msgs/msg/EstimatorStatus.msg"
    "/home/pi/catkin_ws_mavros/src/mavros/mavros_msgs/msg/ExtendedState.msg"
    "/home/pi/catkin_ws_mavros/src/mavros/mavros_msgs/msg/FileEntry.msg"
    "/home/pi/catkin_ws_mavros/src/mavros/mavros_msgs/msg/GlobalPositionTarget.msg"
    "/home/pi/catkin_ws_mavros/src/mavros/mavros_msgs/msg/HilActuatorControls.msg"
    "/home/pi/catkin_ws_mavros/src/mavros/mavros_msgs/msg/HilControls.msg"
    "/home/pi/catkin_ws_mavros/src/mavros/mavros_msgs/msg/HilGPS.msg"
    "/home/pi/catkin_ws_mavros/src/mavros/mavros_msgs/msg/HilSensor.msg"
    "/home/pi/catkin_ws_mavros/src/mavros/mavros_msgs/msg/HilStateQuaternion.msg"
    "/home/pi/catkin_ws_mavros/src/mavros/mavros_msgs/msg/HomePosition.msg"
    "/home/pi/catkin_ws_mavros/src/mavros/mavros_msgs/msg/LandingTarget.msg"
    "/home/pi/catkin_ws_mavros/src/mavros/mavros_msgs/msg/LogData.msg"
    "/home/pi/catkin_ws_mavros/src/mavros/mavros_msgs/msg/LogEntry.msg"
    "/home/pi/catkin_ws_mavros/src/mavros/mavros_msgs/msg/ManualControl.msg"
    "/home/pi/catkin_ws_mavros/src/mavros/mavros_msgs/msg/Mavlink.msg"
    "/home/pi/catkin_ws_mavros/src/mavros/mavros_msgs/msg/MountControl.msg"
    "/home/pi/catkin_ws_mavros/src/mavros/mavros_msgs/msg/OpticalFlowRad.msg"
    "/home/pi/catkin_ws_mavros/src/mavros/mavros_msgs/msg/OverrideRCIn.msg"
    "/home/pi/catkin_ws_mavros/src/mavros/mavros_msgs/msg/Param.msg"
    "/home/pi/catkin_ws_mavros/src/mavros/mavros_msgs/msg/ParamValue.msg"
    "/home/pi/catkin_ws_mavros/src/mavros/mavros_msgs/msg/PositionTarget.msg"
    "/home/pi/catkin_ws_mavros/src/mavros/mavros_msgs/msg/RCIn.msg"
    "/home/pi/catkin_ws_mavros/src/mavros/mavros_msgs/msg/RCOut.msg"
    "/home/pi/catkin_ws_mavros/src/mavros/mavros_msgs/msg/RTCM.msg"
    "/home/pi/catkin_ws_mavros/src/mavros/mavros_msgs/msg/RadioStatus.msg"
    "/home/pi/catkin_ws_mavros/src/mavros/mavros_msgs/msg/State.msg"
    "/home/pi/catkin_ws_mavros/src/mavros/mavros_msgs/msg/StatusText.msg"
    "/home/pi/catkin_ws_mavros/src/mavros/mavros_msgs/msg/Thrust.msg"
    "/home/pi/catkin_ws_mavros/src/mavros/mavros_msgs/msg/TimesyncStatus.msg"
    "/home/pi/catkin_ws_mavros/src/mavros/mavros_msgs/msg/Trajectory.msg"
    "/home/pi/catkin_ws_mavros/src/mavros/mavros_msgs/msg/VFR_HUD.msg"
    "/home/pi/catkin_ws_mavros/src/mavros/mavros_msgs/msg/VehicleInfo.msg"
    "/home/pi/catkin_ws_mavros/src/mavros/mavros_msgs/msg/Vibration.msg"
    "/home/pi/catkin_ws_mavros/src/mavros/mavros_msgs/msg/Waypoint.msg"
    "/home/pi/catkin_ws_mavros/src/mavros/mavros_msgs/msg/WaypointList.msg"
    "/home/pi/catkin_ws_mavros/src/mavros/mavros_msgs/msg/WaypointReached.msg"
    "/home/pi/catkin_ws_mavros/src/mavros/mavros_msgs/msg/WheelOdomStamped.msg"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/mavros_msgs/srv" TYPE FILE FILES
    "/home/pi/catkin_ws_mavros/src/mavros/mavros_msgs/srv/CommandBool.srv"
    "/home/pi/catkin_ws_mavros/src/mavros/mavros_msgs/srv/CommandHome.srv"
    "/home/pi/catkin_ws_mavros/src/mavros/mavros_msgs/srv/CommandInt.srv"
    "/home/pi/catkin_ws_mavros/src/mavros/mavros_msgs/srv/CommandLong.srv"
    "/home/pi/catkin_ws_mavros/src/mavros/mavros_msgs/srv/CommandTOL.srv"
    "/home/pi/catkin_ws_mavros/src/mavros/mavros_msgs/srv/CommandTriggerControl.srv"
    "/home/pi/catkin_ws_mavros/src/mavros/mavros_msgs/srv/CommandTriggerInterval.srv"
    "/home/pi/catkin_ws_mavros/src/mavros/mavros_msgs/srv/CommandVtolTransition.srv"
    "/home/pi/catkin_ws_mavros/src/mavros/mavros_msgs/srv/FileChecksum.srv"
    "/home/pi/catkin_ws_mavros/src/mavros/mavros_msgs/srv/FileClose.srv"
    "/home/pi/catkin_ws_mavros/src/mavros/mavros_msgs/srv/FileList.srv"
    "/home/pi/catkin_ws_mavros/src/mavros/mavros_msgs/srv/FileMakeDir.srv"
    "/home/pi/catkin_ws_mavros/src/mavros/mavros_msgs/srv/FileOpen.srv"
    "/home/pi/catkin_ws_mavros/src/mavros/mavros_msgs/srv/FileRead.srv"
    "/home/pi/catkin_ws_mavros/src/mavros/mavros_msgs/srv/FileRemove.srv"
    "/home/pi/catkin_ws_mavros/src/mavros/mavros_msgs/srv/FileRemoveDir.srv"
    "/home/pi/catkin_ws_mavros/src/mavros/mavros_msgs/srv/FileRename.srv"
    "/home/pi/catkin_ws_mavros/src/mavros/mavros_msgs/srv/FileTruncate.srv"
    "/home/pi/catkin_ws_mavros/src/mavros/mavros_msgs/srv/FileWrite.srv"
    "/home/pi/catkin_ws_mavros/src/mavros/mavros_msgs/srv/LogRequestData.srv"
    "/home/pi/catkin_ws_mavros/src/mavros/mavros_msgs/srv/LogRequestEnd.srv"
    "/home/pi/catkin_ws_mavros/src/mavros/mavros_msgs/srv/LogRequestList.srv"
    "/home/pi/catkin_ws_mavros/src/mavros/mavros_msgs/srv/MountConfigure.srv"
    "/home/pi/catkin_ws_mavros/src/mavros/mavros_msgs/srv/MessageInterval.srv"
    "/home/pi/catkin_ws_mavros/src/mavros/mavros_msgs/srv/ParamGet.srv"
    "/home/pi/catkin_ws_mavros/src/mavros/mavros_msgs/srv/ParamPull.srv"
    "/home/pi/catkin_ws_mavros/src/mavros/mavros_msgs/srv/ParamPush.srv"
    "/home/pi/catkin_ws_mavros/src/mavros/mavros_msgs/srv/ParamSet.srv"
    "/home/pi/catkin_ws_mavros/src/mavros/mavros_msgs/srv/SetMavFrame.srv"
    "/home/pi/catkin_ws_mavros/src/mavros/mavros_msgs/srv/SetMode.srv"
    "/home/pi/catkin_ws_mavros/src/mavros/mavros_msgs/srv/StreamRate.srv"
    "/home/pi/catkin_ws_mavros/src/mavros/mavros_msgs/srv/VehicleInfoGet.srv"
    "/home/pi/catkin_ws_mavros/src/mavros/mavros_msgs/srv/WaypointClear.srv"
    "/home/pi/catkin_ws_mavros/src/mavros/mavros_msgs/srv/WaypointPull.srv"
    "/home/pi/catkin_ws_mavros/src/mavros/mavros_msgs/srv/WaypointPush.srv"
    "/home/pi/catkin_ws_mavros/src/mavros/mavros_msgs/srv/WaypointSetCurrent.srv"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/mavros_msgs/cmake" TYPE FILE FILES "/home/pi/catkin_ws_mavros/build/mavros_msgs/catkin_generated/installspace/mavros_msgs-msg-paths.cmake")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE DIRECTORY FILES "/home/pi/catkin_ws_mavros/devel/.private/mavros_msgs/include/mavros_msgs")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/roseus/ros" TYPE DIRECTORY FILES "/home/pi/catkin_ws_mavros/devel/.private/mavros_msgs/share/roseus/ros/mavros_msgs")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/common-lisp/ros" TYPE DIRECTORY FILES "/home/pi/catkin_ws_mavros/devel/.private/mavros_msgs/share/common-lisp/ros/mavros_msgs")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/gennodejs/ros" TYPE DIRECTORY FILES "/home/pi/catkin_ws_mavros/devel/.private/mavros_msgs/share/gennodejs/ros/mavros_msgs")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  execute_process(COMMAND "/usr/bin/python2" -m compileall "/home/pi/catkin_ws_mavros/devel/.private/mavros_msgs/lib/python2.7/dist-packages/mavros_msgs")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/python2.7/dist-packages" TYPE DIRECTORY FILES "/home/pi/catkin_ws_mavros/devel/.private/mavros_msgs/lib/python2.7/dist-packages/mavros_msgs")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/pi/catkin_ws_mavros/build/mavros_msgs/catkin_generated/installspace/mavros_msgs.pc")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/mavros_msgs/cmake" TYPE FILE FILES "/home/pi/catkin_ws_mavros/build/mavros_msgs/catkin_generated/installspace/mavros_msgs-msg-extras.cmake")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/mavros_msgs/cmake" TYPE FILE FILES
    "/home/pi/catkin_ws_mavros/build/mavros_msgs/catkin_generated/installspace/mavros_msgsConfig.cmake"
    "/home/pi/catkin_ws_mavros/build/mavros_msgs/catkin_generated/installspace/mavros_msgsConfig-version.cmake"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/mavros_msgs" TYPE FILE FILES "/home/pi/catkin_ws_mavros/src/mavros/mavros_msgs/package.xml")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mavros_msgs" TYPE DIRECTORY FILES "/home/pi/catkin_ws_mavros/src/mavros/mavros_msgs/include/mavros_msgs/" FILES_MATCHING REGEX "/[^/]*\\.h$")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/pi/catkin_ws_mavros/build/mavros_msgs/gtest/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/pi/catkin_ws_mavros/build/mavros_msgs/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
