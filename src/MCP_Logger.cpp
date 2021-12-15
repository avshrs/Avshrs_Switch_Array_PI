#include "MCP_logger.h"
#include <iostream>
#include <iomanip>
#include <ctime>

void MCP_logger::log(std::string str, std::string className){
  // std::ofstream file;
  // file.open ("MCP_logger.txt");
  auto t = std::time(nullptr);
  auto tm = *std::localtime(&t);
  std::cout << std::put_time(&tm, "%d-%m-%Y %H-%M-%S") << className << " | " << str << std::endl;
  // file << gate_date() << " | " << className << " | " << str <<"\n";
     // file.close();
}
