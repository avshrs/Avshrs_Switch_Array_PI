#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <i2c/smbus.h>
#include "MCP_i2c.h"
#include <stdlib.h>

void MCP_i2c::i2c_init(char * i2c_file, uint8_t address_){//"/dev/i2c-1"
    address = address_;
    filename = i2c_file;
    file_i2c = open(filename, O_RDWR);
    if (file_i2c < 0 ) {
            printf("Failed to open the i2c bus");
    }
    if (ioctl(file_i2c, I2C_SLAVE, address) < 0) {
            printf("Failed to acquire bus access and/or talk to slave.\n");
    }
}

uint8_t MCP_i2c::readByte(uint8_t reg){
    int8_t res;
    res = i2c_smbus_read_word_data(file_i2c, reg);
    if (res<0){
        printf("Failed to read from the i2c bus.\n");
        return 0;
    }
    else {
        uint8_t d = abs(res);
        return d;
    }
 
}


void MCP_i2c::writeByte(uint8_t side, uint8_t buffer_){
    char buffer = (char)buffer_;
    i2c_smbus_write_word_data(file_i2c, side, buffer_);
    
}
