#****************************************************************************
# Copyright (C) 2018 pmdtechnologies ag
#
# THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
# KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
# PARTICULAR PURPOSE.
#
#****************************************************************************

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/../inc
    ${CMAKE_CURRENT_SOURCE_DIR}/../../royale/source/core/inc/royale
    )

set(HEADERS
  )

add_compile_options(-std=c++11)

set(SOURCES
  "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/camera.cpp"
    )

link_directories(
    )

add_executable(pattern-testing
    ${HEADERS}
    ${SOURCES}
    )
  
install(TARGETS pattern-testing DESTINATION ${ROYALE_INSTALL_BIN_DIR})

target_link_libraries(pattern-testing platform)


