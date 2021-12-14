

extern "C" {
    #include <linux/i2c.h>
    #include <linux/i2c-dev.h>
    #include <i2c/smbus.h>
    #include <sys/ioctl.h>
}
#include <unistd.h>
#include <fcntl.h>
#include "MCP_i2c.h"
#include <stdlib.h>
#include <iostream>

#include <iomanip>
#include <ctime>


void MCP_i2c::i2c_init(std::string filename, uint8_t address){
    file_i2c = open(filename.c_str(), O_RDWR);
    if (file_i2c < 0 ) {
            auto t = std::time(nullptr);
            auto tm = *std::localtime(&t);
            std::cout << std::put_time(&tm, "%d-%m-%Y %H-%M-%S | ");
            printf("Failed to open the i2c bus \n");
    }
    if (ioctl(file_i2c, I2C_SLAVE, address) < 0) {
            auto t = std::time(nullptr);
            auto tm = *std::localtime(&t);
            std::cout << std::put_time(&tm, "%d-%m-%Y %H-%M-%S | ");
            printf("Failed to acquire bus access and/or talk to slave.\n");
    }
}

uint8_t MCP_i2c::readByte(uint8_t reg){
    auto res = i2c_smbus_read_byte_data(file_i2c, reg);
    if (res<0){
        auto t = std::time(nullptr);
        auto tm = *std::localtime(&t);
        std::cout << std::put_time(&tm, "%d-%m-%Y %H-%M-%S | ") << std::hex << reg << " | " << "i2c-error: " << std::dec <<res;
        printf("Failed to read from the i2c bus.\n");
        return 0;
    }
    else {
        uint8_t d = static_cast<uint8_t>(res);
        return d;
    }
}


void MCP_i2c::writeByte(uint8_t side, uint8_t buffer_){
    unsigned short buffer = static_cast<uint8_t>(buffer_);
    i2c_smbus_write_byte_data(file_i2c, side, buffer_);
}
