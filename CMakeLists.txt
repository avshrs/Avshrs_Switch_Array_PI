cmake_minimum_required(VERSION 2.8.9)
project(SwitchArray)
add_compile_options(-Wall -Wextra -Wpedantic -Werror)


include_directories(include)


set(CMAKE_CXX_FLAGS "-li2c ${CMAKE_CXX_FLAGS}")

set(CMAKE_EXE_LINKER_FLAGS "-li2c ${CMAKE_EXE_LINKER_FLAGS} ")

set(libs 
/usr/lib/arm-linux-gnueabihf/libmosquittopp.so
/usr/lib/arm-linux-gnueabihf/libpthread.so
/usr/lib/arm-linux-gnueabihf/libi2c.so
/usr/lib/arm-linux-gnueabihf/libyaml-cpp.so
)

set(INCLUDE_HEADER_FILES "include/*.h" )
file(GLOB mSOURCES  "src/*.cpp" )
                 

add_executable(SwitchArray "src/main.cpp" ${mSOURCES})
target_link_libraries(SwitchArray  ${libs})

