#pragma once
#include <cstdint>
#include <string>

#define    FORCE        (0xFF) 
#define    NFORCE       (0x00) 

#define    MPC1         (0x00)  
#define    MPC2         (0x01) 
#define    MPC3         (0x02)  
#define    MPC4         (0x03) 
#define    MPC5         (0x04)  
#define    MPC6         (0x05) 
#define    MPC7         (0x06)  
#define    MPC8         (0x07) 


#define  MCP1_ADDR      (0x20)
#define  MCP2_ADDR      (0x21)
#define  MCP3_ADDR      (0x22)  
#define  MCP4_ADDR      (0x23) 
#define  MCP5_ADDR      (0x24) 
#define  MCP6_ADDR      (0x25) 
#define  MCP7_ADDR      (0x26) 
#define  MCP8_ADDR      (0x27) 


#define    GPIOA        (0x12)  
#define    GPIOB        (0x13) 

#define    SIDEA        (0x00)  
#define    SIDEB        (0x01) 

#define  MCP_OUT        (0x00)
#define  MCP_IN         (0xFF) 
#define  MCP_PULLUP     (0xFF)
#define  MCP_NOT_PULLUP (0x00)

#define     OUT_STATE       (1<<0)  // bit 1 << 0 - output 1 - Enable | Disable output 
#define     OUT_TYPE        (1<<1)  // bit 1 << 1 - output 1 - Bistable | 0 - Monostable
#define     OUT_OFFBYALARM  (1<<2)  // bit 1 << 2 - output 1 - OFF by Armed Alarm |  0 none
#define     OUT_ONBYALARM   (1<<3)  // bit 1 << 4 - output 1 - ? ON by Activated Alarm | 0 None
// #define     OUT_       (1<<4)
// #define     OUT_       (1<<5)
// #define     OUT_       (1<<6)
// #define     OUT_       (1<<7)

#define     IN_SWITCH       (1<<0)  // bit 1 << 0 - output 1 - Switch input
#define     IN_ACTIVEALARM  (1<<1)  // bit 1 << 1 - output 1 - activated alarm input 
#define     IN_ARMEDALARM   (1<<2)  // bit 1 << 2 - output 1 - armed alarm input
#define     IN_TWILIGHT     (1<<3)  // bit 1 << 4 - output 1 - PIR alarm input
#define     IN_PIRALARM     (1<<4)  
// #define     IN_       (1<<5)
// #define     IN_       (1<<6)
// #define     IN_       (1<<7)


struct SERIALMCPFRAME{
    uint8_t INSTRUCTIONS = 0;          
    uint8_t CONFIG = 0; 
    uint8_t IONUMBER = 0;
    uint8_t VALUE = 0;
    char NAME[30] ;
  
};
struct IO_ADDRESS{
    uint8_t MCP_ADDRESS=0;
    uint8_t MCP_SIDE=0;
    uint8_t MCP_NUMBER=0;
};

struct MCP_Data
{
    uint8_t chipset;
    uint8_t side;
    uint8_t io;
}; 


struct MCP_values
{
    uint8_t v0;
    uint8_t v1;
    uint8_t v2;
    uint8_t v3;
    uint8_t v4;
    uint8_t v5;
    uint8_t v6;
    uint8_t v7;
}; 

struct Output_conf{
    int nr;
    std::string name;
    std::string type;
    bool default_state;
    bool enabled;
    bool bistable;
    bool input_related;
};

struct Input_conf{
    int nr;
    std::string name;
    std::string type;
    bool enabled;
    bool enabledOutputRelated;
    int output_related;
};

struct Mqtt_config{
    std::string ClientId;
    std::string ServerIp;
    std::string username;
    std::string password;
    int serverPort;
    std::string keepAliveTopic;
    std::string keepAliveMsg;
    std::string outSubstring;
    std::string outPubstring;
    std::string inSubstring;
    std::string inPubstring;
    std::string ONMsg;
    std::string OFFMsg;
    std::string ONTIMEMsg;
};

struct I2c1_config{
    uint8_t out1Address;
    std::string out1Path;
    bool out1enable;

    uint8_t out2Address;
    std::string out2Path;
    bool out2enable;

    uint8_t out3Address;
    std::string out3Path;
    bool out3enable;

    uint8_t out4Address;
    std::string out4Path;
    bool out4enable;

    uint8_t out5Address;
    std::string out5Path;
    bool out5enable;

    uint8_t out6Address;
    std::string out6Path;
    bool out6enable;

    uint8_t out7Address;
    std::string out7Path;
    bool out7enable;

    uint8_t out8Address;
    std::string out8Path;
    bool out8enable;

    uint8_t in1Address;
    std::string in1Path;
    bool in1enable;

    uint8_t in2Address;
    std::string in2Path;
    bool in2enable;

    uint8_t in3Address;
    std::string in3Path;
    bool in3enable;

    uint8_t in4Address;
    std::string in4Path;
    bool in4enable;

    uint8_t input_len;
    uint8_t output_len;
};