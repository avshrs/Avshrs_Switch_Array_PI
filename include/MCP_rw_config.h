#pragma once
#include "vars.h"
class MCP_rw_config{
    public:
    unsigned int max_out = 64;
    unsigned int max_in = 64;
    Output_conf output_conf[64];
    Input_conf intput_conf[64];

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
    int get_in_outputRelated(int in);
};
