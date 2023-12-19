cmake_minimum_required(VERSION 3.5)
project(tracker)

## Compile as C++11
# add_compile_options(-std=c++11)
# message(STATUS "Compiling with C++11")

## System dependencies are found with CMake's conventions
# find_package(Boost REQUIRED COMPONENTS system)
find_package(OpenCV REQUIRED)
message(STATUS "OpenCV INCLUDE PATH: ${OpenCV_INCLUDE_DIRS}")

###########
## Build ##
###########

# Specify additional locations of header files
# Your package locations should be listed before other locations
include_directories(
    # include
    ${OpenCV_INCLUDE_DIRS}
)

## Declare a C++ library
add_library(tracker STATIC
  src/PatternTracker.cpp
)

## Add cmake target dependencies of the library
## as an example, code may need to be generated before libraries
## either from message generation or dynamic reconfigure
# add_dependencies(${PROJECT_NAME} ${${PROJECT_NAME}_EXPORTED_TARGETS})

## Add include directories of the library
target_include_directories(tracker PUBLIC
  include
)

## Declare a C++ executable
## With all packages are built within a single CMake context
## The recommended prefix ensures that target names across packages don't collide
add_executable(main main.cpp)

## Specify libraries to link a library or executable target against
target_link_libraries(main PUBLIC 
  tracker
  ${OpenCV_LIBS}
)

## Rename C++ executable without prefix
## The above recommended prefix causes long target names, the following renames the
## target back to the shorter version for ease of user use

## Add cmake target dependencies of the executable
## same as for the library above
# add_dependencies(${PROJECT_NAME} ${${PROJECT_NAME}_EXPORTED_TARGETS})

#############
## Install ##
#############
# all install targets should use catkin DESTINATION variables

## Mark executable scripts (Python etc.) for installation
## in contrast to setup.py, you can choose the destination
# catkin_install_python(PROGRAMS
#   scripts/script1.py
#   scripts/script2.py
#   DESTINATION ${PACKAGE_BIN_DESTINATION}
# )

## Mark cpp header files for installation
# install(DIRECTORY include/${PROJECT_NAME}/
#   DESTINATION ${PACKAGE_INCLUDE_DESTINATION}
#   FILES_MATCHING PATTERN "*.h"
#   PATTERN ".svn" EXCLUDE
# )

## Mark other files for installation (e.g. launch and bag files, etc.)
# install(FILES
#   # myfile1
#   # myfile2
#   DESTINATION ${\PACKAGE_SHARE_DESTINATION}
# )

