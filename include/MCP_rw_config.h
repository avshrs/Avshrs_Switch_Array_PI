#pragma once
#include "vars.h"
#include <vector>

class MCP_rw_config{
    public:
 
    Mqtt_config mqtt_config;
    I2c1_config i2c1_config;
    std::string config_path;

    std::vector< Output_conf > output_conf_;
    std::vector< Input_conf > input_conf_;

    void register_config(std::string config_path_);
    void read_config();
    std::string get_out_name(int out);
    std::string get_out_type(int out);
    bool get_out_def_state(int out);
    bool get_out_enabled(int out);
    bool get_out_bistable(int out);
    bool get_out_input_rel(int out);

    std::string get_in_name(int in);
    std::string get_in_type(int in);
    bool get_in_enabled(int in);
    bool get_in_enabledOutputRelated(int in);
    int get_in_output_related(int in);

    std::string get_mqtt_ClientId();
    std::string get_mqtt_ip();
    int get_mqtt_port();
    std::string get_mqtt_keepAliveTopic();
    std::string get_mqtt_keepAliveMsg();
    std::string get_mqtt_outSubstring();
    std::string get_mqtt_outPubstring();
    std::string get_mqtt_inSubstring();
    std::string get_mqtt_inPubstring();
    std::string get_mqtt_ONMsg();
    std::string get_mqtt_OFFMsg();
    std::string get_mqtt_ONTIMEMsg();
    std::string get_mqtt_password();
    std::string get_mqtt_username();
    
    uint8_t get_out1Address();
    std::string get_out1Path();
    bool get_out1enable();
    uint8_t get_out2Address();
    std::string get_out2Path();
    bool get_out2enable();
    uint8_t get_out3Address();
    std::string get_out3Path();
    bool get_out3enable();
    uint8_t get_out4Address();
    std::string get_out4Path();
    bool get_out4enable();
    uint8_t get_out5Address();
    std::string get_out5Path();
    bool get_out5enable();
    uint8_t get_out6Address();
    std::string get_out6Path();
    bool get_out6enable();
    uint8_t get_out7Address();
    std::string get_out7Path();
    bool get_out7enable();
    uint8_t get_out8Address();
    std::string get_out8Path();
    bool get_out8enable();

    uint8_t get_in1Address();
    std::string get_in1Path();
    bool get_in1enable();
    uint8_t get_in2Address();
    std::string get_in2Path();
    bool get_in2enable();
    uint8_t get_in3Address();
    std::string get_in3Path();
    bool get_in3enable();
    uint8_t get_in4Address();
    std::string get_in4Path();
    bool get_in4enable();

    uint8_t get_input_len();
    uint8_t get_output_len();

};
