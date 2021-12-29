cmake_minimum_required(VERSION 2.8.9)
project(MCI_swich_array)
add_compile_options(-Wall -Wextra -Wpedantic -Werror)


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
file(GLOB mSOURCES  "src/MCP_i2c.cpp 
                     src/MCP_Manager.cpp 
                     src/MCP_Mosquitto.cpp
                     src/MCP_Settings.cpp
                     src/MCPdev.cpp
                     src/Settings_server.cpp
                     src/socket_server.cpp" )
 
file(GLOB sSOURCES  "src/SatelIntegra.cpp" )                     

add_executable(MCI_swich_array "src/main.cpp" ${mSOURCES})
add_executable(MCI_Satel_Listener "src/satelMain.cpp" ${sSOURCES})

target_link_libraries(MCI_swich_array  ${libs})
