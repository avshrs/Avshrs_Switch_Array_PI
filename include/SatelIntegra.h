#pragma once

#include <string>
#include <unistd.h>
#include <stdio.h>
#include <cstdint>
#include <cstring>
#include <stdlib.h>
#include <netinet/in.h>
#include <iostream>
#include <mutex>
#include <map>
#include <thread>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#define INVALID_SOCKET (int)(~0)
#define SOCKET_ERROR   -1
#define closesocket(s) close(s);
class SatelIntegra{
    public:
		SatelIntegra(int ID, const std::string &IPAddress, unsigned short IPPort, const std::string &userCode, int pollInterval);

    public:
		bool arm_state[32] = {false};
		bool alarm_state = false;

		bool in_state[128] = {false};
		std::string in_name[128];
		
		bool out_state[128] = {false};
		std::string out_name[128];

    public:
		void ReadZonesStatesAll();
		void ReadOutputsStatesAll();
		void ReadArmStatesAll();
		void ReadAlarm();


		bool ReadEvents();
		bool ArmPartitions(int partition, int mode = 0);
		bool DisarmPartitions(int partition);
		void UpdateOutputName(int Idx, const unsigned char *name);
		
	private:	  
		bool CheckAddress();
		void DestroySocket();
		bool ConnectToIntegra();
		bool ReadNewData();
		bool GetInfo();


		
		std::string ISO2UTF8(const std::string &name);
		
		std::pair<unsigned char *, unsigned int> getFullFrame(const unsigned char *pCmd, unsigned int cmdLength);
		int SendCommand(const unsigned char *cmd, unsigned int cmdLength, unsigned char *answer, int expectedLength);

		private:
		int m_HwdID;
		int m_modelIndex;
		bool m_data32;
		sockaddr_in m_addr;
		int m_socket;
		const unsigned short m_IPPort;
		const std::string m_IPAddress;
		int m_pollInterval;
		std::shared_ptr<std::thread> m_thread;
		std::map<unsigned int, const char *> errorCodes;
		// filled by 0x7F command
		unsigned char m_newData[7];

		// password to Integra
		unsigned char m_userCode[8];

		// TODO maybe create dynamic array ?
		std::array<bool, 256> m_zonesLastState;
		std::array<bool, 256> m_outputsLastState;
		std::array<bool, 256> m_isOutputSwitch;
		std::array<bool, 256> m_isTemperature;
		std::array<bool, 32> m_isPartitions;
		std::array<bool, 32> m_armLastState;

		// thread-safe for read and write
		std::mutex m_mutex;

		bool m_alarmLast;
};
