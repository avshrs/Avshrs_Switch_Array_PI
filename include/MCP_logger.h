#pragma once
#include <string>

class MCP_logger{
    public:
        void log(std::string str, std::string className);

    private:
        std::string gate_date();
};