#pragma once

#include <mosquittopp.h>
#include <cstring>
#include <string>
#include <cstdio>
#include "MCP_Manager.h"

#define DEBUG

#define MAX_PAYLOAD 50
#define DEFAULT_KEEP_ALIVE 60

class mqtt_client : public mosqpp::mosquittopp
{
public:
    mqtt_client (const char *id, const char *host, int port);
    ~mqtt_client();
    MCP_Manager *mcp_manager;
    void send_ack(std::string pub, std::string msg);
    void register_mcp_manager(MCP_Manager *mcp_manager_);
    void on_connect(int rc);
    void on_message(const struct mosquitto_message *message);
    void on_subscribe(int mid, int qos_count, const int *granted_qos);
};
