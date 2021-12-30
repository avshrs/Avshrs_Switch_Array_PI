#pragma once

#include <mosquittopp.h>
#include <cstring>
#include <string>
#include <cstdio>

#define DEBUG

#define MAX_PAYLOAD 50
#define DEFAULT_KEEP_ALIVE 60

class mqtt_client : public mosqpp::mosquittopp
{
public:
    mqtt_client (const char *id, const char *host, int port);
    void on_connect(int rc);
    void on_error();
    void on_disconnect(int rc);
};
