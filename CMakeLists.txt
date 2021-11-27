cmake_minimum_required(VERSION 2.8.9)
project(MCI_swich_array)
 
#Bring the headers, such as Student.h into the project
include_directories(include)


#Can manually add the sources using the set command as follows:
#set(SOURCES src/mainapp.cpp src/Student.cpp)

# set(CMAKE_CXX_FLAGS "-lwiringPi -lmosquittopp -pthread  ${CMAKE_CXX_FLAGS}")

# set(CMAKE_EXE_LINKER_FLAGS "-lwiringPi -lmosquittopp -pthread  ${CMAKE_EXE_LINKER_FLAGS} ")
set(libs 
/usr/lib/x86_64-linux-gnu/libmosquittopp.so
/usr/lib/x86_64-linux-gnu/libmosquittopp.so.1
/usr/lib/x86_64-linux-gnu/libmosquittopp.so.2.0.10
/usr/lib/libwiringPi.so

/usr/lib/x86_64-linux-gnu/libpthread.so
/usr/lib/x86_64-linux-gnu/libpthread.so.0

)
find_package(libmosquittopp)
find_package(libwiringPi.so)
find_package(libpthread)

set(INCLUDE_HEADER_FILES
"include/*.h"
)
file(GLOB SOURCES  "src/*.cpp")
 
add_executable(MCI_swich_array ${SOURCES})

target_link_libraries(MCI_swich_array  ${libs})