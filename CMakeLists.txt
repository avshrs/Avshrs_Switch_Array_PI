cmake_minimum_required(VERSION 2.8.9)
project(MCI_swich_array)
 
#Bring the headers, such as Student.h into the project
include_directories(include)
 
#Can manually add the sources using the set command as follows:
#set(SOURCES src/mainapp.cpp src/Student.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -lmosquittopp -mosquittopp -lwiringPi")

# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pthread -mosquittopp -lmosquittopp -lwiringPi")


#However, the file(GLOB...) allows for wildcard additions:
file(GLOB SOURCES  "src/*.cpp")
 
add_executable(MCI_swich_array ${SOURCES})

# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
