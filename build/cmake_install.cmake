# Install script for directory: /home/local/NEATO/running.gao/Downloads/2-in-2_ToF_Cam_Pattern_Test

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share" TYPE FILE FILES "/home/local/NEATO/running.gao/Downloads/2-in-2_ToF_Cam_Pattern_Test/build/royale-config.cmake")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share" TYPE FILE FILES "/home/local/NEATO/running.gao/Downloads/2-in-2_ToF_Cam_Pattern_Test/royale/cmake/Modules/FindOpenNI2.cmake")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share" TYPE FILE FILES "/home/local/NEATO/running.gao/Downloads/2-in-2_ToF_Cam_Pattern_Test/royale/cmake/Modules/FindNumpy.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/local/NEATO/running.gao/Downloads/2-in-2_ToF_Cam_Pattern_Test/build/royale/cmake/configure/cmake_install.cmake")
  include("/home/local/NEATO/running.gao/Downloads/2-in-2_ToF_Cam_Pattern_Test/build/royale/cmake/sign/cmake_install.cmake")
  include("/home/local/NEATO/running.gao/Downloads/2-in-2_ToF_Cam_Pattern_Test/build/royale/contrib/gtest/cmake_install.cmake")
  include("/home/local/NEATO/running.gao/Downloads/2-in-2_ToF_Cam_Pattern_Test/build/royale/spectre/cmake_install.cmake")
  include("/home/local/NEATO/running.gao/Downloads/2-in-2_ToF_Cam_Pattern_Test/build/royale/source/core/cmake_install.cmake")
  include("/home/local/NEATO/running.gao/Downloads/2-in-2_ToF_Cam_Pattern_Test/build/royale/source/components/imager/cmake_install.cmake")
  include("/home/local/NEATO/running.gao/Downloads/2-in-2_ToF_Cam_Pattern_Test/build/royale/source/components/record/cmake_install.cmake")
  include("/home/local/NEATO/running.gao/Downloads/2-in-2_ToF_Cam_Pattern_Test/build/platform/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/local/NEATO/running.gao/Downloads/2-in-2_ToF_Cam_Pattern_Test/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
