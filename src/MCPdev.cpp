#include "MCPdev.h"
#include "MCP_i2c.h"

void MCP::MCP_Init(uint8_t MCPADDRSS, uint8_t GIPOA_TYPE, uint8_t GIPOA_PULL, uint8_t GIPOB_TYPE, uint8_t GIPOB_PULL){
    mcpAddress = MCPADDRSS;
    mcp_i2c.i2c_init("/dev/i2c-1", mcpAddress);

    mcp_i2c.writeByte(MCPADDRSS);  // expander has I2C address 0x20
    mcp_i2c.writeByte(IODIRA);   // register 0 is the I/O direction register for Port A
    mcp_i2c.writeByte(GIPOA_TYPE);   //  0x00 for all pins to output mode, 0xFF for all pins to input mode

    if (GIPOA_PULL == 0xFF && GIPOA_TYPE == 0xFF){
        mcp_i2c.writeByte(MCPADDRSS);  // expander has I2C address 0x20
        mcp_i2c.writeByte(GPPUA);   // register 0 is the I/O direction register for Port A
        mcp_i2c.writeByte(0xFF);   //  0x00 for all pins to output mode, 0xFF for all pins to input mode
    }

    mcp_i2c.writeByte(MCPADDRSS);  // expander has I2C address 0x20
    mcp_i2c.writeByte(IODIRB);   // register 0 is the I/O direction register for Port A
    mcp_i2c.writeByte(GIPOB_TYPE);   //  0x00 for all pins to output mode, 0xFF for all pins to input mode

    if (GIPOB_PULL == 0xFF && GIPOB_TYPE == 0xFF){
        mcp_i2c.writeByte(MCPADDRSS);  // expander has I2C address 0x20
        mcp_i2c.writeByte(GPPUB);   // register 0 is the I/O direction register for Port A
        mcp_i2c.writeByte(0xFF);   //  0x00 for all pins to output mode, 0xFF for all pins to input mode
        
    }
}

uint8_t MCP::readRaw(uint8_t side){
    uint8_t r_value = 0; 
    mcp_i2c.writeByte(mcpAddress); 
    mcp_i2c.writeByte(side);
    uint8_t v = mcp_i2c.readByte();
    print(v);
    return ~v;
}

void MCP::writeRaw(uint8_t side, uint8_t memory){
    mcp_i2c.writeByte(mcpAddress);
    mcp_i2c.writeByte(side);  
    mcp_i2c.writeByte(convert_bits(memory));   
    
}

bool MCP::read_io(uint8_t io_number){
    uint16_t value =  uint16_t(readRaw(GPIOA)) << 8 | uint16_t(readRaw(GPIOB));
    
    uint16_t mask = 1 << io_number;
    if((value & mask) > 0)
        return true;
    else        
        return false;
}


void MCP::write_io(uint8_t io_number, bool state){
    uint8_t side;
    if(io_number < 8){
        side = GPIOA;
    }
    else{
        side = GPIOA;
        io_number = io_number - 8;
    }
    uint8_t mask = (1 << io_number);
    uint8_t value = readRaw(side);
    if (state && (value & mask) == 0){
            value |= mask;
    }
    else if ((value & mask) > 0){
        value &= ~mask;

    }
    mcp_i2c.writeByte(mcpAddress); 
    mcp_i2c.writeByte(side);
    mcp_i2c.writeByte(value);
}

uint8_t MCP::convert_bits(uint8_t bits){
    uint8_t tmp = bits;
    int s = sizeof(bits) * 8 - 1;
    for (bits>>= 1; bits; bits>>= 1){   
    tmp <<= 1;
    tmp |= bits& 1;
    s--;
    }
    tmp <<= s;
    return tmp;
}
void MCP::print(uint8_t v){
for (uint8_t i = 0 ; i < (sizeof(v)*8) ; ++i){
       if ((v & (1 << i )) > 0) 
           printf("1");
       else
           printf("0"); 
           
    }
    printf("\n"); 
}