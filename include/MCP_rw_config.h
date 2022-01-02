#pragma once
#include "vars.h"
class MCP_rw_config{
    public:
    int max_out = 64;
    int max_in = 64;
    Output_conf output_conf[64];
    Input_conf input_conf[64];
    Mqtt_config mqtt_config;
    I2c1_config i2c1_config;

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
    int get_in_output_related(int in);

    std::string get_mqtt_ClientId();
    std::string get_mqtt_ip();
    int get_mqtt_port();
    std::string get_mqtt_keepAliveTopic();
    std::string get_mqtt_keepAliveMsg();
    std::string get_mqtt_outSubsring();
    std::string get_mqtt_outPubsring();
    std::string get_mqtt_outONMsg();
    std::string get_mqtt_outOFFMsg();
};
