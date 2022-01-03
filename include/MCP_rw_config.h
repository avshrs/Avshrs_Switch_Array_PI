#pragma once
#include "vars.h"
#include <vector>

class MCP_rw_config{
    public:
    int max_out = 64;
    int max_in = 64;

    Mqtt_config mqtt_config;
    I2c1_config i2c1_config;

    std::vector< Output_conf > output_conf_;
    std::vector< Input_conf > input_conf_;

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
};
