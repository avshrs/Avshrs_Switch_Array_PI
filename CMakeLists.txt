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
file(GLOB mSOURCES  "src/*.cpp" )
 
file(GLOB sSOURCES  "src_satel/SatelIntegra.cpp" "src_satel/MCP_Mosquitto_satel.cpp"
                    )                     

add_executable(MCI_swich_array "src/main.cpp" ${mSOURCES})
target_link_libraries(MCI_swich_array  ${libs})

add_executable(MCI_Satel_Listener "src_satel/satelMain.cpp" ${sSOURCES})
target_link_libraries(MCI_Satel_Listener  ${libs})
