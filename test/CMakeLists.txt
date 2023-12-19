cmake_minimum_required(VERSION 3.5)
project(tracker_unit_test)

## Compile as C++11
# add_compile_options(-std=c++11)
# message(STATUS "Compiling with C++11")

## System dependencies are found with CMake's conventions
# find_package(Boost REQUIRED COMPONENTS system)
find_package(OpenCV REQUIRED)
message(STATUS "OpenCV include path: ${OpenCV_INCLUDE_DIRS}")

## Setup the compiler flags. Make sure the flags attributes
## for your usage before constructing and building the project.
## Build type (default to Release if not specified)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

###########
## Build ##
###########

# Specify additional locations of header files
# Your package locations should be listed before other locations
include_directories(
  # include
)

# Declare a C++ library
add_library(tracker STATIC
  ../src/PatternTracker.cpp
)

## Add cmake target dependencies of the library
## as an example, code may need to be generated before libraries
## either from message generation or dynamic reconfigure
# add_dependencies(${PROJECT_NAME} ${${PROJECT_NAME}_EXPORTED_TARGETS})

## Add include directories of the library
target_include_directories(tracker PUBLIC 
  ../include
  ${OpenCV_INCLUDE_DIRS}
)

## Google unit esting section
## Include the `FetchContent` for making the google unit test content available.
## By declare the google test content from github, make it available for doing
## some testing of the corresponding library (ex. tracker in this test)
include(FetchContent)
FetchContent_Declare(
  googletest 
  GIT_REPOSITORY https://github.com/google/googletest.git 
  GIT_TAG release-1.11.0
)
FetchContent_MakeAvailable(googletest) 

## Declare a C++ executable
## With catkin_make all packages are built within a single CMake context
## The recommended prefix ensures that target names across packages don't collide
add_executable(tracker_ut utest.cpp)

## Specify libraries to link a library or executable target against
target_link_libraries(tracker_ut PRIVATE 
  tracker
  ${OpenCV_LIBS}
  gtest gtest_main
)

## Rename C++ executable without prefix
## The above recommended prefix causes long target names, the following renames the
## target back to the shorter version for ease of user use

## Add cmake target dependencies of the executable
## same as for the library above
# add_dependencies(${PROJECT_NAME}_node ${${PROJECT_NAME}_EXPORTED_TARGETS})

#############
## Install ##
#############
# all install targets should use catkin DESTINATION variables

## Mark executable scripts (Python etc.) for installation
## in contrast to setup.py, you can choose the destination
# catkin_install_python(PROGRAMS
#  scripts/script1.py
#  scripts/script2.py
#  DESTINATION ${PACKAGE_BIN_DESTINATION}
# )

## Mark cpp header files for installation
# install(DIRECTORY include/${PROJECT_NAME}/
#  DESTINATION ${PACKAGE_INCLUDE_DESTINATION}
#  FILES_MATCHING PATTERN "*.h"
#  PATTERN ".svn" EXCLUDE
# )

## Mark other files for installation (e.g. launch and bag files, etc.)
# install(FILES
#  # myfile1
#  # myfile2
#  DESTINATION ${\PACKAGE_SHARE_DESTINATION}
# )

#############
## Testing ##
#############

## Add gtest based cpp test target and link libraries
# if(TARGET ${PROJECT_NAME}-test)
#   target_link_libraries(${PROJECT_NAME}-test ${PROJECT_NAME})
# endif()

## Including enable_testing(), so that signal to CMake that project will have tests, 
## and it sets up the necessary infrastructure for running tests. 
## After that, you can use the `add_test()` command in test-related to your project.
enable_testing()

## ssociates the test with the command needed to run the tests
add_test(
  NAME tracker_unit_test
  COMMAND tracker_ut
)

# Exported Targets (if applicable)
# install(TARGETS tracker
#   EXPORT tracker-targets
#   ARCHIVE DESTINATION lib
#   LIBRARY DESTINATION lib
#   RUNTIME DESTINATION bin
# )