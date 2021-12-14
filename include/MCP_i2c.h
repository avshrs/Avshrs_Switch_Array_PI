#pragma once

#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <string>


class MCP_i2c{
    private:
        int file_i2c;
        int length=2;
    
    private:
        void print(uint8_t v);
    
    public:
        void i2c_init(std::string filename, uint8_t address_);
        
        uint8_t readByte(uint8_t reg);
        void writeByte(uint8_t side, uint8_t buffer_);
        
        uint16_t readWord(uint8_t reg);
        void writeWord(uint8_t reg, uint16_t buffer_);

};

