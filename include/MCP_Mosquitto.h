#pragma once

#include <mosquittopp.h>
#include <cstring>
#include <string>
#include <cstdio>
#include <vector>
class MCP_Manager;
#include "MCP_rw_config.h"

// #define DEBUG

#define MAX_PAYLOAD 50
#define DEFAULT_KEEP_ALIVE 60

class mqtt_client : public mosqpp::mosquittopp
{
public:
    mqtt_client (const char *id, const char *host, int port);

    MCP_Manager *mcp_manager;
    MCP_rw_config *mcp_cfg;
    void pub_state(int out, bool sate);
    void register_mcp_manager(MCP_Manager *mcp_manager_);
    void register_mcp_config(MCP_rw_config *mcp_cfg_);
    void client_loop_forever();
    void register_subs();
    void unregister_subs();
    void on_connect(int rc);
    void on_error();
    void on_disconnect(int rc);
    void on_message(const struct mosquitto_message *message);
    void on_subscribe(int mid, int qos_count, const int *granted_qos);
private:
    std::vector<std::string> parse_string(std::string str, char delimiter);

};
