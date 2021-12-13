#include "MCP_logger.h"
#include <iostream>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <math.h>
#include <fstream>
#include <string>


void MCP_logger::log(std::string str, std::string className){
  std::ofstream file;
  file.open ("MCP_logger.txt");
  std::cout << gate_date() << " | " << className << " | " << str << std::endl;
  file << gate_date() << " | " << className << " | " << str <<"\n";
    file.close();
}

std::string MCP_logger::gate_date(){
    char buffer[26];
    int millisec;
    struct tm* tm_info;
    struct timeval tv;

    gettimeofday(&tv, NULL);

    millisec = lrint(tv.tv_usec/1000.0); // Round to nearest millisec
    if (millisec>=1000) { // Allow for rounding up to nearest second
        millisec -=1000;
        tv.tv_sec++;
    }

    tm_info = localtime(&tv.tv_sec);

    strftime(buffer, 26, "%Y:%m:%d %H:%M:%S", tm_info);
    std::string date(buffer);
    date +="-";
    date += std::to_string(millisec);

  return date;
}