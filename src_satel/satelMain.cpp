#include "SatelIntegra.h"
#include "MCP_Mosquitto.h"
#include <thread>
#include <string>
#include <iomanip>
#include <ctime>


char client_id[] = "Satel_Listener";
char host[] = "192.168.1.96";
int port = 1883;
mqtt_client mqtt_(client_id, host, port);

SatelIntegra sa(67, "192.168.1.240", 25197, "1234", 60);

unsigned int count[129] = {0};

void th1(){
    std::cout<< "read loop" << std::endl;
    sa.ReadLoop();
}

void chechViolation(){
    std::cout<< "chechViolation" << std::endl;
    int out = 0;
    while(true){
        out = 100-1;
        if(sa.out_state[out] == true){
            // std::cout<< "out_state violated 100" << std::endl;
            if(std::time(nullptr) - count[out] > 59 ){
                // salon
                auto t = std::time(nullptr);
                auto tm = *std::localtime(&t);
                std::cout << std::put_time(&tm, "%d-%m-%Y %H-%M-%S | ");
                std::cout<< "Out_state violated 100 Salon" << std::endl;
                std::string msg = "ON_TIME_60";
                mqtt_.publish(NULL, "MCP_OUT_S_12", msg.length(), msg.c_str());
                count[out] = std::time(nullptr);
            }
            
        }
        
        out = 101-1;
        if(sa.out_state[out] == true){
            // std::cout<< "out_state violated 101" << std::endl;
            if(std::time(nullptr) - count[out] > 59 ){
                auto t = std::time(nullptr);
                auto tm = *std::localtime(&t);
                std::cout << std::put_time(&tm, "%d-%m-%Y %H-%M-%S | ");
                std::cout<< "Out_state violated 101 Kuchnia" << std::endl;
                // kuchnia
                std::string msg = "ON_TIME_60";
                mqtt_.publish(NULL, "MCP_OUT_S_18", msg.length(), msg.c_str());
                count[out] = std::time(nullptr);
            }
        }
        out = 102-1;
        if(sa.out_state[out] == true){
            // std::cout<< "out_state violated 102" << std::endl;
            if(std::time(nullptr) - count[out] > 59 ){
                auto t = std::time(nullptr);
                auto tm = *std::localtime(&t);
                std::cout << std::put_time(&tm, "%d-%m-%Y %H-%M-%S | ");
                std::cout<< "Out_state violated 102 Wiatrolap" << std::endl;
                // wiatrołap
                std::string msg = "ON_TIME_60";
                mqtt_.publish(NULL, "MCP_OUT_S_11", msg.length(), msg.c_str());
                count[out] = std::time(nullptr);
            }
        }
        out = 103-1;
        if(sa.out_state[out] == true){
            // std::cout<< "out_state violated 103" << std::endl;
            if(std::time(nullptr) - count[out] > 59 ){
                auto t = std::time(nullptr);
                auto tm = *std::localtime(&t);
                std::cout << std::put_time(&tm, "%d-%m-%Y %H-%M-%S | ");
                std::cout<< "Out_state violated 103 Garaz" << std::endl;
                // garaz
                std::string msg = "ON_TIME_600";
                mqtt_.publish(NULL, "MCP_OUT_S_22", msg.length(), msg.c_str());
                count[out] = std::time(nullptr);
            }
        }
        usleep(10000);
       

    }
}


int main(){ 
    std::thread t1(th1);
    usleep(100000);
    chechViolation();
}
