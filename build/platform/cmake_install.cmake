# Install script for directory: /home/local/NEATO/running.gao/Downloads/2-in-2_ToF_Cam_Pattern_Test/platform

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/local/NEATO/running.gao/Downloads/2-in-2_ToF_Cam_Pattern_Test/build/install")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
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
  set(CMAKE_CROSSCOMPILING "TRUE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libplatform.so.0.0.1"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libplatform.so"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHECK
           FILE "${file}"
           RPATH "$ORIGIN/")
    endif()
  endforeach()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES
    "/home/local/NEATO/running.gao/Downloads/2-in-2_ToF_Cam_Pattern_Test/build/bin/libplatform.so.0.0.1"
    "/home/local/NEATO/running.gao/Downloads/2-in-2_ToF_Cam_Pattern_Test/build/bin/libplatform.so"
    )
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libplatform.so.0.0.1"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libplatform.so"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHANGE
           FILE "${file}"
           OLD_RPATH "/home/local/NEATO/running.gao/Downloads/2-in-2_ToF_Cam_Pattern_Test/royale/spectre/lib/Linux/arm/64Bit:"
           NEW_RPATH "$ORIGIN/")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/opt/fsl-imx-xwayland/4.14-sumo/sysroots/x86_64-pokysdk-linux/usr/bin/aarch64-poky-linux/aarch64-poky-linux-strip" "${file}")
      endif()
    endif()
  endforeach()
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/local/NEATO/running.gao/Downloads/2-in-2_ToF_Cam_Pattern_Test/build/platform/test/cmake_install.cmake")
  include("/home/local/NEATO/running.gao/Downloads/2-in-2_ToF_Cam_Pattern_Test/build/platform/retrieveData/cmake_install.cmake")
  include("/home/local/NEATO/running.gao/Downloads/2-in-2_ToF_Cam_Pattern_Test/build/platform/pattern-testing/cmake_install.cmake")

endif()

