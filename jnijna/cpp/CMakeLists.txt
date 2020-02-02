cmake_minimum_required( VERSION 3.10 )
set(PROJECT_NAME libopus)
project(${PROJECT_NAME})

# set CMAKE_INSTALL_PREFIX
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_LIST_DIR}/build CACHE PATH "..." FORCE)
endif()
set(EXECUTABLE_OUTPUT_PATH bin)
set(LIBRARY_OUTPUT_PATH lib)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
# Disable ZERO_CHECK project
set(CMAKE_SUPPRESS_REGENERATION true)

# Default to `release` build if nothing was specified
if(NOT CMAKE_BUILD_TYPE)
  message(STATUS "No build type selected, default to release")
  set(CMAKE_BUILD_TYPE release)
endif()

if(MSVC)
  add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

set(TARGET_LIBRARIES
  ${CMAKE_HOME_DIRECTORY}/libs/opus.lib
)

add_library(${PROJECT_NAME} SHARED
  ${CMAKE_HOME_DIRECTORY}/src/libopus.cpp
  ${CMAKE_HOME_DIRECTORY}/src/libopus.h
)
target_include_directories(${PROJECT_NAME} PRIVATE
  ${CMAKE_HOME_DIRECTORY}/include
)
target_link_libraries(${PROJECT_NAME}
  ${TARGET_LIBRARIES}
)

find_package(Java REQUIRED)
find_package(JNI REQUIRED)
if (JNI_FOUND)
  set(JNILIB_NAME jnilibopus)
  add_library(${JNILIB_NAME} SHARED
    ${CMAKE_HOME_DIRECTORY}/src/jnilibopus.cpp
    ${CMAKE_HOME_DIRECTORY}/src/jnilibopus.h
  )
  target_include_directories(${JNILIB_NAME} PRIVATE
    ${CMAKE_HOME_DIRECTORY}/include
    ${JNI_INCLUDE_DIRS}
  )
  target_link_libraries(${JNILIB_NAME}
    ${TARGET_LIBRARIES}
    ${JNI_LIBRARIES}
  )
endif()
