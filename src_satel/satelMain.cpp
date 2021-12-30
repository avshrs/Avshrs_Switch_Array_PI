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
    int salon = 100-1;
    int kuchnia = 101-1;
    int wiatrolap = 102-1;
    int garaz = 103-1;
    int lazienka = 104-1;
    int korytarz = 105-1;
    
    while(true){
        
        if(sa.out_state[salon] == true){
            // std::cout<< "out_state violated 100" << std::endl;
            if(std::time(nullptr) - count[salon] > 59 ){
                // salon
                auto t = std::time(nullptr);
                auto tm = *std::localtime(&t);
                std::cout << std::put_time(&tm, "%d-%m-%Y %H-%M-%S | ");
                std::cout<< "Out_state violated 100 Salon" << std::endl;
                std::string msg = "ON_TIME_60";
                mqtt_.publish(NULL, "MCP_OUT_S_12", msg.length(), msg.c_str());
                count[salon] = std::time(nullptr);
            }
        }
        
        if(sa.out_state[kuchnia] == true){
            // std::cout<< "out_state violated 101" << std::endl;
            if(std::time(nullptr) - count[kuchnia] > 59 ){
                auto t = std::time(nullptr);
                auto tm = *std::localtime(&t);
                std::cout << std::put_time(&tm, "%d-%m-%Y %H-%M-%S | ");
                std::cout<< "Out_state violated 101 Kuchnia" << std::endl;
                // kuchnia
                std::string msg = "ON_TIME_60";
                mqtt_.publish(NULL, "MCP_OUT_S_18", msg.length(), msg.c_str());
                count[kuchnia] = std::time(nullptr);
            }
        }
        
        if(sa.out_state[wiatrolap] == true){
            // std::cout<< "out_state violated 102" << std::endl;
            if(std::time(nullptr) - count[wiatrolap] > 59 ){
                auto t = std::time(nullptr);
                auto tm = *std::localtime(&t);
                std::cout << std::put_time(&tm, "%d-%m-%Y %H-%M-%S | ");
                std::cout<< "Out_state violated 102 Wiatrolap" << std::endl;
                // wiatrołap
                std::string msg = "ON_TIME_60";
                mqtt_.publish(NULL, "MCP_OUT_S_11", msg.length(), msg.c_str());
                count[wiatrolap] = std::time(nullptr);
            }
        }
        
        if(sa.out_state[garaz] == true){
            // std::cout<< "out_state violated 103" << std::endl;
            if(std::time(nullptr) - count[garaz] > 59 ){
                auto t = std::time(nullptr);
                auto tm = *std::localtime(&t);
                std::cout << std::put_time(&tm, "%d-%m-%Y %H-%M-%S | ");
                std::cout<< "Out_state violated 103 Garaz" << std::endl;
                // garaz
                std::string msg = "ON_TIME_600";
                mqtt_.publish(NULL, "MCP_OUT_S_22", msg.length(), msg.c_str());
                count[garaz] = std::time(nullptr);
            }
        }
        if(sa.out_state[lazienka] == true){
            // std::cout<< "out_state violated 103" << std::endl;
            if(std::time(nullptr) - count[lazienka] > 5 ){
                auto t = std::time(nullptr);
                auto tm = *std::localtime(&t);
                std::cout << std::put_time(&tm, "%d-%m-%Y %H-%M-%S | ");
                std::cout<< "Out_state violated 103 Lazienka" << std::endl;
                // garaz
                std::string msg = "ON_TIME_60";
                mqtt_.publish(NULL, "MCP_OUT_S_6", msg.length(), msg.c_str());
                count[lazienka] = std::time(nullptr);
            }
        }
        if(sa.out_state[korytarz] == true){
            // std::cout<< "out_state violated 103" << std::endl;
            if(std::time(nullptr) - count[korytarz] > 5 ){
                auto t = std::time(nullptr);
                auto tm = *std::localtime(&t);
                std::cout << std::put_time(&tm, "%d-%m-%Y %H-%M-%S | ");
                std::cout<< "Out_state violated 103 Korytarz" << std::endl;
                // garaz
                std::string msg = "ON_TIME_60";
                mqtt_.publish(NULL, "MCP_OUT_S_8", msg.length(), msg.c_str());
                count[korytarz] = std::time(nullptr);
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
