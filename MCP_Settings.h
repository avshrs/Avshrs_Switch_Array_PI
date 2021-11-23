#ifndef MCP_SETTINGS_H
#define MCP_SETTINGS_H

#include "vars.h"
#include <iostream>
#include <fstream>
#include <fcntl.h>    /* For O_RDWR */
#include <unistd.h>   /* For open(), creat() */
#include <stdio.h>
#include <cstring>
class MCP_Settings {
    public: 
        struct IN_SETTINGS{
            uint8_t related_output=0;
            bool in_alarm_armed=false;
            
        };
        
        struct OUT_SETTINGS{
            bool out_enabled=true;
            bool out_bistable=false; 
            bool out_disabled_by_alarm=false;

            
        };

        IN_SETTINGS in_settings[64];
        OUT_SETTINGS out_settings[64];

        void set_io_relation(uint8_t in, uint8_t out);
        uint8_t get_io_relation(uint8_t in);
        
        void set_in_alarm_armed(uint8_t in, bool flag);
        bool get_in_alarm_armed(uint8_t in);

        void set_out_status(uint8_t out, bool status);
        bool get_out_status(uint8_t out);

        void set_out_bistable(uint8_t out, bool status);
        bool get_out_bistable(uint8_t out);

        void set_out_disable_by_alarm(uint8_t out, bool flag);
        bool get_out_disable_by_alarm(uint8_t out);

        void save_settings();
        void read_settings();
};

#endif // MCP_SETTINGS_H