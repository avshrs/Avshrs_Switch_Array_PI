

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



void MCP_i2c::i2c_init(std::string filename_, uint8_t address_){
    filename = filename_;
    address = address_;
    file_i2c = open(filename.c_str(), O_RDWR);
    if (file_i2c < 0 ) {
            auto t = std::time(nullptr);
            auto tm = *std::localtime(&t);
            std::cout << std::put_time(&tm, "%d-%m-%Y %H-%M-%S | ");
            std::cout << "Failed to Open the i2c bus - "<< filename_ << std::endl;
    }
    else{
        auto t = std::time(nullptr);
        auto tm = *std::localtime(&t);
        std::cout << std::put_time(&tm, "%d-%m-%Y %H-%M-%S | ");
        std::cout << "i2c bus open correctly - "<< filename_ <<  std::endl;
    }
    if (ioctl(file_i2c, I2C_SLAVE, address) < 0) {
            auto t = std::time(nullptr);
            auto tm = *std::localtime(&t);
            std::cout << std::put_time(&tm, "%d-%m-%Y %H-%M-%S | ");
            std::cout << "Failed to acquire bus access and/or talk to slave. - on address: " << std::hex << (int) address_ << std::endl;
    }
    else{
        auto t = std::time(nullptr);
        auto tm = *std::localtime(&t);
        std::cout << std::put_time(&tm, "%d-%m-%Y %H-%M-%S | ");
        std::cout << "Acquired bus access and/or talk to slave. - on address: " << std::dec << (int) address_ << std::endl;
    }
}

uint8_t MCP_i2c::readByte(uint8_t reg){
    auto res = i2c_smbus_read_byte_data(file_i2c, reg);
    if (res<0){
        auto t = std::time(nullptr);
        auto tm = *std::localtime(&t);
        std::cout << std::put_time(&tm, "%d-%m-%Y %H-%M-%S | ");
        std::cout << "Read from bus: " << file_i2c;
        std::cout << ", Read from address: " << std::hex << (int) reg << " | " << "i2c-error: " << std::dec <<res;
        std::cout << ", Failed to Read from the i2c bus."<< std::endl;
        std::cout << std::put_time(&tm, "%d-%m-%Y %H-%M-%S | ");
        std::cout << "Retrying I2C init."<< std::endl;
        i2c_init(filename, address);
        usleep(100000);
        return 0;
    }
    else {
        uint8_t d = static_cast<uint8_t>(res);
        return d;
    }
}

uint16_t MCP_i2c::readWord(uint8_t reg){
    auto res = i2c_smbus_read_word_data(file_i2c, reg);
    if (res<0){
        auto t = std::time(nullptr);
        auto tm = *std::localtime(&t);
        std::cout << std::put_time(&tm, "%d-%m-%Y %H-%M-%S | ");
        std::cout << "Read from bus: " << file_i2c;
        std::cout << ", Read from address: " << std::hex << (int) reg << " | " << "i2c-error: " << std::dec <<res;
        std::cout << ", Failed to Read from the i2c bus." << std::endl;
        std::cout << std::put_time(&tm, "%d-%m-%Y %H-%M-%S | ");
        std::cout << "Retrying I2C init."<< std::endl;
        i2c_init(filename, address);
        usleep(100000);
        return 0;
    }
    else {
        return static_cast<uint16_t>(res);
    }
}

void MCP_i2c::writeByte(uint8_t reg, uint8_t buffer_){
    auto res = i2c_smbus_write_byte_data(file_i2c, reg, buffer_);
    if (res<0){
        auto t = std::time(nullptr);
        auto tm = *std::localtime(&t);
        std::cout << std::put_time(&tm, "%d-%m-%Y %H-%M-%S | ");
        std::cout << "Write to bus: " << file_i2c;
        std::cout << ", Write to address: " << std::hex << (int) reg <<" | " << "i2c-error: " << std::dec <<res;
        std::cout << ", Failed to Write to the i2c bus." << std::endl;
        std::cout << std::put_time(&tm, "%d-%m-%Y %H-%M-%S | ");
        std::cout << "Retrying I2C init."<< std::endl;
        i2c_init(filename, address);
        usleep(100000);
        
    }
}

void MCP_i2c::writeWord(uint8_t reg, uint16_t buffer_){
    auto res = i2c_smbus_write_word_data(file_i2c, reg, buffer_);

    if (res<0){
        auto t = std::time(nullptr);
        auto tm = *std::localtime(&t);
        std::cout << std::put_time(&tm, "%d-%m-%Y %H-%M-%S | ");
        std::cout << "Write to bus: " << file_i2c;
        std::cout << ", Write to address: "<< std::hex << (int) reg << " | " << "i2c-error: " << std::dec <<res;
        std::cout << ", Failed to Write to the i2c bus." << std::endl;
        std::cout << std::put_time(&tm, "%d-%m-%Y %H-%M-%S | ");
        std::cout << "Retrying I2C init."<< std::endl;
        i2c_init(filename, address);
        usleep(100000);
    }
}
