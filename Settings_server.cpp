#include "Settings_server.h"

void SettingsServer::register_mcp_settings(MCP_Settings *mcp_settings_){
    mcp_settings = mcp_settings_;
}



void SettingsServer::analyze_packet(SERIALMCPFRAME frame){
    // std::cout<<std::hex <<frame.INSTRUCTIONS<<", ";
    // std::cout<<std::hex <<frame.CONFIG<<", ";
    // std::cout<<std::hex <<frame.IONUMBER<<", ";
    // std::cout<<std::hex <<frame.VALUE<<", "<<std::endl;
    if(frame.INSTRUCTIONS == 0x00 & frame.CONFIG == 0x01){
        mcp_settings->set_io_relation(frame.IONUMBER, frame.VALUE);
        std::cout<<"set_io_relation: "<<unsigned(frame.IONUMBER)<<" - "<<unsigned(mcp_settings->get_io_relation(frame.IONUMBER))<<std::endl;
    }
    else if(frame.INSTRUCTIONS == 0x00 & frame.CONFIG == 0x00){
        std::cout<<"get_io_relation: "<<unsigned(frame.IONUMBER)<<" - "<<unsigned(mcp_settings->get_io_relation(frame.IONUMBER))<<std::endl;
    }
    else if(frame.INSTRUCTIONS == 0x01 & frame.CONFIG == 0x01){
        mcp_settings->set_in_alarm_armed(frame.IONUMBER, frame.VALUE);
        std::cout<<"alarm armed input set: "<<unsigned(frame.IONUMBER)<<" - "<<unsigned(mcp_settings->get_in_alarm_armed(frame.IONUMBER))<<std::endl;
    }
    else if(frame.INSTRUCTIONS == 0x01 & frame.CONFIG == 0x00){
        std::cout<<"alarm armed input get: "<<unsigned(frame.IONUMBER)<<" - "<<unsigned(mcp_settings->get_in_alarm_armed(frame.IONUMBER))<<std::endl;
    }
    else if(frame.INSTRUCTIONS == 0x02 & frame.CONFIG == 0x01){
        mcp_settings->set_out_status(frame.IONUMBER, frame.VALUE);
        std::cout<<"set_out_status: "<<unsigned(frame.IONUMBER)<<" - "<<unsigned(mcp_settings->get_out_status(frame.IONUMBER))<<std::endl;
    }
    else if(frame.INSTRUCTIONS == 0x02 & frame.CONFIG == 0x00){
        std::cout<<"get_out_status: "<<unsigned(frame.IONUMBER)<<" - "<<unsigned(mcp_settings->get_out_status(frame.IONUMBER))<<std::endl;
    }
    else if(frame.INSTRUCTIONS == 0x03 & frame.CONFIG == 0x01){
        mcp_settings->set_out_bistable(frame.IONUMBER, frame.VALUE);
        std::cout<<"set_out_bistable: "<<unsigned(frame.IONUMBER)<<" - "<<unsigned(mcp_settings->get_out_bistable(frame.IONUMBER))<<std::endl;
    }
    else if(frame.INSTRUCTIONS == 0x03 & frame.CONFIG == 0x00){
        std::cout<<"get_out_bistable: "<<unsigned(frame.IONUMBER)<<" - "<<unsigned(mcp_settings->get_out_bistable(frame.IONUMBER))<<std::endl;
    }
    else if(frame.INSTRUCTIONS == 0x04 & frame.CONFIG == 0x01){
        mcp_settings->save_settings();
        std::cout<<"read_settings: "<<std::endl;
    }
    else if(frame.INSTRUCTIONS == 0x04 & frame.CONFIG == 0x00){
        mcp_settings->read_settings();
        std::cout<<"read_settings: "<<std::endl;
    }
}

