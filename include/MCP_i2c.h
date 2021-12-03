#ifndef MCPi2c_H
#define MCPi2c_H
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <string>

class MCP_i2c{
    public:
        int file_i2c;
        unsigned char buffer[60];
        int length=2;
        uint8_t address;
        char *filename;

        void writeByte(uint8_t side, uint8_t buffer_);
        void print(uint8_t v);
        uint8_t readByte(uint8_t reg);
        void i2c_init(char * i2c_file, uint8_t address_);
};



#endif //MCPi2c_H



