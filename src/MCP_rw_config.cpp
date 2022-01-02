#include "MCP_rw_config.h"
// #include <yaml-cpp>
#include <yaml-cpp/yaml.h>
#include <iostream>
#include <string>


void read_config(){
    YAML::Node config = YAML::LoadFile("config.yaml");

    std::cout << "name:" << config["name"].as<std::string>() << std::endl;
    std::cout << "sex:" << config["sex"].as<std::string>() << std::endl;
    std::cout << "age:" << config["age"].as<int>() << std::endl;
    std::cout << "skills c++:" << config["skills"]["c++"].as<int>() << std::endl;
    std::cout << "skills java:" << config["skills"]["java"].as<int>() << std::endl;
    std::cout << "skills android:" << config["skills"]["android"].as<int>() << std::endl;
    std::cout << "skills python:" << config["skills"]["python"].as<int>() << std::endl;

}
    
