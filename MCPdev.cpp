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

bool MCP::read_io(uint8_t io_number){
    uint8_t state = digitalRead(nr+io_number);
    if(state > 0)
        return false;
    else        
        return true;
}


void MCP::write_io(uint8_t io_number, bool state){
     digitalWrite(nr + io_number, state);
}

// uint8_t MCP::convert_bits(uint8_t bits){
//     uint8_t tmp = bits;
//     int s = sizeof(bits) * 8 - 1;
//     for (bits>>= 1; bits; bits>>= 1){   
//     tmp <<= 1;
//     tmp |= bits& 1;
//     s--;
//     }
//     tmp <<= s;
//     return tmp;
// }
