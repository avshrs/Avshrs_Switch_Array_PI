#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include "MCP_i2c.h"

void MCP_i2c::i2c_init(char * i2c_file, uint8_t address_){//"/dev/i2c-1"
    address = address_<< 1;
    filename = i2c_file;
    if ((file_i2c = open(filename, O_RDWR)) < 0) {
            printf("Failed to open the i2c bus");
    }
}

uint8_t MCP_i2c::readByte(){
    char buffer[1];
    
    if (ioctl(file_i2c, I2C_SLAVE, address) < 0) {
            printf("Failed to acquire bus access and/or talk to slave.\n");
    }
    if (read(file_i2c, buffer, sizeof(buffer)) != sizeof(buffer)){
            printf("Failed to read from the i2c bus.\n");
    }

    return (uint8_t)atoi(buffer);
}


void MCP_i2c::writeByte(uint8_t buffer_){
    char buffer = (char)buffer_;

    if (ioctl(file_i2c, I2C_SLAVE, address) < 0) {
            printf("Failed to acquire bus access and/or talk to slave.\n");
    }
    if (write(file_i2c, &buffer, sizeof(buffer)) != sizeof(buffer)) {
            printf("Failed to write to the i2c bus.\n");
    }    
}
