cmake_minimum_required(VERSION 2.8.9)
project(MCI_swich_array)

include_directories(include)


set(CMAKE_CXX_FLAGS "-li2c ${CMAKE_CXX_FLAGS}")

set(CMAKE_EXE_LINKER_FLAGS "-li2c ${CMAKE_EXE_LINKER_FLAGS} ")

set(libs 
/usr/lib/arm-linux-gnueabihf/libmosquittopp.so
/usr/lib/arm-linux-gnueabihf/libpthread.so
/usr/lib/arm-linux-gnueabihf/libi2c.so
)

set(INCLUDE_HEADER_FILES
"include/*.h"
)
file(GLOB SOURCES  "src/*.cpp")
 
add_executable(MCI_swich_array ${SOURCES})

target_link_libraries(MCI_swich_array  ${libs})