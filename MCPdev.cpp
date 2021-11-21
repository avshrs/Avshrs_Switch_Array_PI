#include "MCPdev.h"


void MCP::MCP_Init(uint8_t MCPADDRSS, uint8_t nr_, uint8_t GIPO_TYPE, uint8_t GIPO_PULL){
    nr = nr_;

    wiringPiSetup();
    mcp23017Setup(nr, MCPADDRSS);

    if (GIPO_TYPE == 0xFF){
        for( int i =0 ; i< 16 ;i++ ){
            pinMode(nr + i, INPUT);
            if (GIPO_PULL==0xFF){
                  pullUpDnControl (nr + i, PUD_UP);
            }
        }
    }
    else{
        for(int i =0; i< 16; i++ ){
            pinMode(nr + i, OUTPUT);
        }
    }
}

uint8_t MCP::read_io(uint8_t io_number){
    return digitalRead(nr+io_number);
}

MCP_values MCP::read_all(){
    MCP_values data;
    uint8_t data_[16];
    for( int i =0 ; i< 16 ;i++ ){
        data_[i] = digitalRead(nr+i);
    }
    data.v0 = data_[0];
    data.v1 = data_[1];
    data.v2 = data_[2];
    data.v3 = data_[3];
    data.v4 = data_[4];
    data.v5 = data_[5];
    data.v6 = data_[6];
    data.v7 = data_[7];
    
    return data;
}

void MCP::write_io(uint8_t io_number, uint8_t value){
    digitalWrite(nr + io_number, value);

}
void MCP::write_all(uint8_t values){
    for( int i =0 ; i< 16 ;i++ ){
        digitalWrite(nr + i, values);
    }
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
