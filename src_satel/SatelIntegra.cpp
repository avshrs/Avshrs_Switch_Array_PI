#include <list>

#include "SatelIntegra.h"



#ifdef _DEBUG
#define DEBUG_SatelIntegra
#endif

#define SATEL_TEMP_POLL_INTERVAL_MS 120*1000 // 120 sec
#define HEARTBEAT_INTERVAL_MS 12*1000 // 12 sec

#define round(a) ( int ) ( a + .5 )

using SatelModel = struct
{
	unsigned int id;
	const char* name;
	unsigned int zones;
	unsigned int outputs;
};

#define TOT_MODELS 9

constexpr std::array<SatelModel, TOT_MODELS> models{
	{
		{ 0, "Integra 24", 24, 20 },		   //
		{ 1, "Integra 32", 32, 32 },		   //
		{ 2, "Integra 64", 64, 64 },		   //
		{ 3, "Integra 128", 128, 128 },		   //
		{ 4, "Integra 128 WRL SIM300", 128, 128 }, //
		{ 132, "Integra 128 WRL LEON", 128, 128 }, //
		{ 66, "Integra 64 Plus", 64, 64 },	   //
		{ 67, "Integra 128 Plus", 128, 128 },	   //
		{ 72, "Integra 256 Plus", 256, 256 },	   //
	}						  
};

#define MAX_LENGTH_OF_ANSWER 63 * 2 + 4 + 1

SatelIntegra::SatelIntegra(const int ID, const std::string &IPAddress, const unsigned short IPPort, const std::string& userCode, const int pollInterval) :
	m_modelIndex(-1),
	m_data32(false),
	m_socket(INVALID_SOCKET),
	m_IPPort(IPPort),
	m_IPAddress(IPAddress),
	m_pollInterval(pollInterval)
{
	
	m_HwdID = ID;
	memset(m_newData, 0, sizeof(m_newData));

	// clear last local state of zones and outputs
	m_zonesLastState = {};
	m_outputsLastState = {};
	m_isOutputSwitch = {};
	m_isTemperature = {};
	m_isPartitions = {};
	m_armLastState = {};
	m_alarmLast = false;

	errorCodes[1] = "requesting user code not found";
	errorCodes[2] = "no access";
	errorCodes[3] = "selected user does not exist";
	errorCodes[4] = "selected user already exists";
	errorCodes[5] = "wrong code or code already exists";
	errorCodes[6] = "telephone code already exists";
	errorCodes[7] = "changed code is the same";
	errorCodes[8] = "other error";
	errorCodes[17] = "can not arm, but can use force arm";
	errorCodes[18] = "can not arm";

	// decode user code from string to BCD
	if (userCode.empty())CheckAddress();

	uint64_t result(0);
	for (unsigned int i = 0; i < 16; ++i)
	{
		result = result << 4;

		if (i < userCode.size())
		{
			result += (userCode[i] - 48);
		}
		else
		{
			result += 0x0F;
		}
	}
	for (unsigned int i = 0; i < 8; ++i)
	{
		unsigned int c = (unsigned int)(result >> ((7 - i) * 8));
		m_userCode[i] = c;
	}

	if (m_pollInterval < 500)
	{
		m_pollInterval = 500;
	}

CheckAddress();
ConnectToIntegra();
GetInfo();
}

bool SatelIntegra::CheckAddress()
{
	m_addr.sin_family = AF_INET;
	m_addr.sin_port = htons(m_IPPort);

	unsigned long ip;
	ip = inet_addr(m_IPAddress.c_str());

	if (ip != INADDR_NONE)
	{
		m_addr.sin_addr.s_addr = ip;
	}
	else
	{
		hostent *he = gethostbyname(m_IPAddress.c_str());
		if (he == nullptr)
		{
			std::cout << "Cannot resolve host name" << std::endl; 	
			return false;
		}
		std::memcpy(&(m_addr.sin_addr), he->h_addr_list[0], 4);
	}
	return true;
}

void SatelIntegra::ReadLoop(){
	while(true){
		ReadZonesStatesAll();
		ReadOutputsStatesAll();
		ReadArmStatesAll();
		ReadAlarm();
		usleep(10000);
	}
}

bool SatelIntegra::ConnectToIntegra()
{
	if (m_socket != INVALID_SOCKET)
		return true;

	m_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (m_socket == INVALID_SOCKET)
	{
		std::cout << "Unable to create socket" << std::endl; 
		// //Log(//Log_ERROR, "Unable to create socket");
		return false;
	}

	if (connect(m_socket, (const sockaddr*)&m_addr, sizeof(m_addr)) == SOCKET_ERROR)
	{
		std::cout << "Unable to connect to specified IP Address: " <<  m_IPAddress << std::endl; 
		DestroySocket();
		return false;
	}
	return true;
}

void SatelIntegra::DestroySocket()
{
	if (m_socket != INVALID_SOCKET)
	{
		std::cout << "Destroy socket" << std::endl; 
		closesocket(m_socket);
		m_socket = INVALID_SOCKET;
	}
}

bool SatelIntegra::ReadNewData()
{
	unsigned char cmd[2];
	cmd[0] = 0x7F; // list of new data
	if (SendCommand(cmd, 1, m_newData, 6) > 0)
	{
		return true;
	}
	else{
		return false;
	}
}
bool SatelIntegra::GetInfo()
{
	unsigned char buffer[15];

	unsigned char cmd[1];
	cmd[0] = 0x7E; // Integra version
	if (SendCommand(cmd, 1, buffer, 15) > 0)
	{
		for (unsigned int i = 0; i < TOT_MODELS; ++i)
		{
			if (models[i].id == buffer[1])
			{
				m_modelIndex = i; // finded Integra type
				std::cout << " buffer[1]: " << models[i].id  << std::endl; 
				break;
			}
		}
		if (m_modelIndex > -1)
		{
			unsigned char cmd[1];
			cmd[0] = 0x1A; // RTC
			if (SendCommand(cmd, 1, buffer, 10) > 0)
			{

				unsigned char cmd[1];
				cmd[0] = 0x7C; // INT-RS/ETHM version
				if (SendCommand(cmd, 1, buffer, 13) > 0)
				{
					m_data32 = ((buffer[12] & 1) == 1) && (m_modelIndex == 72); // supported and required 256 PLUS
					std::cout << std::hex << " int-rs/ethm: " << m_data32 << std::endl; 
					return true;
				}
				std::cout<<"unknown version of ETHM-1"<<std::endl;	
			}
			else
			{
				std::cout<<"Unknown basic status"<<std::endl;	
			}
		}
		else
		{	
			std::cout<<"Unknown model"<<std::endl;	
		}
	}
	else
	{
		std::cout<<"Get info about Integra is failed"<<std::endl;
	}

	return false;
}



void SatelIntegra::ReadZonesStatesAll(){
	unsigned char buffer[33];
	unsigned char cmd[2];
	cmd[0] = 0x00; // read zones violation
	if (SendCommand(cmd, 1 + m_data32, buffer, 17 + m_data32 * 16) > 0)
	{
		unsigned int byteNumber;
		unsigned int bitNumber;
		for(int i = 1; i < 129; i++){
			byteNumber = i / 8;
			bitNumber = i % 8;
			in_state[i] = (buffer[byteNumber + 1] >> bitNumber) & 0x01;
		}
	}
	else
	{
		std::cout<<"Send Read Inputs failed"<<std::endl;
	}
}
void SatelIntegra::ReadOutputsStatesAll(){
	unsigned char buffer[33];
	unsigned char cmd[2];
	cmd[0] = 0x17; // read outputs state
	if (SendCommand(cmd, 1 + m_data32, buffer, 17 + m_data32 * 16) > 0)
	{
		unsigned int byteNumber;
		unsigned int bitNumber;
		for(int i = 1; i < 129; i++){
			byteNumber = i / 8;
			bitNumber = i % 8;
			out_state[i] = (buffer[byteNumber + 1] >> bitNumber) & 0x01;
		}
	}
	else
	{
		std::cout<<"Send Read Outputs failed"<<std::endl;
	}
}

void SatelIntegra::ReadArmStatesAll()
{
	unsigned char buffer[5];
	unsigned char cmd[1];
	cmd[0] = 0x0A; // read armed partition
	if (SendCommand(cmd, 1, buffer, 5) > 0)
	{	
		for(int i = 1; i < 33; i++){
			unsigned int byteNumber = i / 8;
			unsigned int bitNumber = i % 8;
			arm_state[i] = (buffer[byteNumber + 1] >> bitNumber) & 0x01;
		}
	}
	else
	{
		std::cout<<"Send Read Arm State failed"<<std::endl;
	}
}

void SatelIntegra::ReadAlarm()
{
	unsigned char buffer[5];
	unsigned char cmd[1];
	cmd[0] = 0x13; // read partitions alarm
	if (SendCommand(cmd, 1, buffer, 5) > 0)
	{	
		alarm_state = false;
		for (unsigned int index = 0; index < 4; ++index)
		{
			if (buffer[index + 1])
			{
				alarm_state = true;
				break;
			}
		}
	}
	else
	{
		std::cout<<"Send Get Alarm partitions failed"<<std::endl;
	}
}


bool SatelIntegra::ArmPartitions(const int partition, const int mode)
{

	if (mode > 3)
	{
	
		return false;
	}

	unsigned char buffer[2];

	unsigned char cmd[13] = { 0 };
	cmd[0] = (unsigned char)(0x80 + mode); // arm in mode 0
	for (unsigned int i = 0; i < 8; ++i)
	{
		cmd[i + 1] = m_userCode[i];
	}

	unsigned char byteNumber = (partition - 1) / 8;
	unsigned char bitNumber = (partition - 1) % 8;

	cmd[byteNumber + 9] = 0x01 << bitNumber;

	if (SendCommand(cmd, 13, buffer, 1) == -1) // arm
	{
		return false;
	}

	m_armLastState[partition - 1] = true;
	return true;
}

bool SatelIntegra::DisarmPartitions(const int partition)
{
#ifdef DEBUG_SatelIntegra
	//Log(//Log_STATUS, "disarming partition %d", partition);
#endif

	unsigned char buffer[2];

	unsigned char cmd[13];
	cmd[0] = 0x84; // disarm
	for (unsigned int i = 0; i < 8; ++i)
	{
		cmd[i + 1] = m_userCode[i];
	}

	unsigned char byteNumber = (partition - 1) / 8;
	unsigned char bitNumber = (partition - 1) % 8;

	cmd[byteNumber + 9] = 0x01 << bitNumber;

	if (SendCommand(cmd, 13, buffer, 1) == -1) // disarm
	{
		return false;
	}

	m_armLastState[partition - 1] = false;
	return true;
}

std::string SatelIntegra::ISO2UTF8(const std::string &name)
{
	char cp1250[] = "\xB9\xE6\xEA\xB3\xF1\xF3\x9C\x9F\xBF\xA5\xC6\xCA\xA3\xD1\xD3\x8C\x8F\xAF";
	char utf8[] = "\xC4\x85\xC4\x87\xC4\x99\xC5\x82\xC5\x84\xC3\xB3\xC5\x9B\xC5\xBA\xC5\xBC\xC4\x84\xC4\x86\xC4\x98\xC5\x81\xC5\x83\xC3\x93\xC5\x9A\xC5\xB9\xC5\xBB";

	std::string UTF8Name;
	for (char i : name)
	{
		bool changed = false;
		for (int j = 0; j < static_cast<int>(sizeof(cp1250)); ++j)
		{
			if (i == cp1250[j])
			{
				UTF8Name += utf8[j * 2];
				UTF8Name += utf8[j * 2 + 1];
				changed = true;
				break;
			}
		}
		if (!changed)
		{
			UTF8Name += i;
		}
	}
	return UTF8Name;
}



void calculateCRC(const unsigned char* pCmd, unsigned int length, unsigned short &result)
{
	unsigned short crc = 0x147A;

	for (unsigned int i = 0; i < length; ++i)
	{
		crc = (crc << 1) | (crc >> 15);
		crc = crc ^ 0xFFFF;
		crc = crc + (crc >> 8) + pCmd[i];
	}

	result = crc;
}

int SatelIntegra::SendCommand(const unsigned char* cmd, const unsigned int cmdLength, unsigned char *answer, const int expectedLength)
{
	std::lock_guard<std::mutex> lock(m_mutex);

	if (!ConnectToIntegra())
	{
		return -1;
	}

	std::pair<unsigned char*, unsigned int> cmdPayload;
	cmdPayload = getFullFrame(cmd, cmdLength);

	//Send cmd
	if (send(m_socket, (const char*)cmdPayload.first, cmdPayload.second, 0) < 0)
	{
		// //Log(//Log_ERROR, "Send command '%02X' failed", cmdPayload.first[2]);
		DestroySocket();
		delete[] cmdPayload.first;
		return -1;
	}

	delete[] cmdPayload.first;

	unsigned char buffer[MAX_LENGTH_OF_ANSWER];
	// Receive answer
	fd_set rfds;
	FD_ZERO(&rfds);
	FD_SET(m_socket, &rfds);

	struct timeval tv;
	tv.tv_sec = 3;
	tv.tv_usec = 0;
	if (select(m_socket + 1, &rfds, nullptr, nullptr, &tv) < 0)
	{
		// //Log(//Log_ERROR, "connection lost.");
		DestroySocket();
		return -1;
	}

	int totalRet = 0;
	do
	{
		int ret = recv(m_socket, (char*)&buffer[totalRet], MAX_LENGTH_OF_ANSWER - totalRet, 0);
		totalRet += ret;
		if ((ret <= 0) || (totalRet >= MAX_LENGTH_OF_ANSWER))
		{
			// //Log(//Log_ERROR, "bad data length received (totalRet %d)", totalRet);
			DestroySocket();
			return -1;
		}
	} while (totalRet < expectedLength);

	// remove special chars
	int offset = 0;
	for (int i = 0; i < totalRet; i++)
	{
		buffer[i] = buffer[i + offset];
		if (buffer[i] == 0xFE && buffer[i + 1] == 0xF0)
		{
			++offset;
			totalRet--;
		}
	}
	buffer[totalRet] = 0x00; // not needed but look nice :)

	if (totalRet > 6)
	{
		if (buffer[0] == 0xFE && buffer[1] == 0xFE && buffer[totalRet - 1] == 0x0D && buffer[totalRet - 2] == 0xFE) // check prefix and sufix
		{
			if ((buffer[2] != 0xEF) && ((totalRet - 6) != expectedLength))
			{
				std::cout <<  "bad data length received" << std::endl;
				// //Log(//Log_ERROR, "bad data length received (expectedLength %d, totalRet %d, cmd %X, cmdLength %d)", expectedLength, totalRet - 6, cmd[0], cmdLength);
				DestroySocket();
				return -1;
			}

			unsigned int answerLength = 0;
			for (int i = 0; i < totalRet - 6; i++) // skip prefix, suffix and crc
			{
				answer[i] = buffer[i + 2];
			}
			answerLength = totalRet - 6; // answer = frame - prefix - suffix - crc

			unsigned short crc;
			calculateCRC(answer, answerLength, crc);
			if ((crc & 0xFF) == buffer[totalRet - 3] && (crc >> 8) == buffer[totalRet - 4]) // check crc
			{
				if (buffer[2] == 0xEF)
				{
					if (buffer[3] == 0x00 || buffer[3] == 0xFF)
					{
						return 0;
					}
					const char *error = "other errors";

					auto it = errorCodes.find(buffer[3]);
					if (it != errorCodes.end())
					{
						error = it->second;
					}
					std::cout <<  "receive error: " << error<< std::endl;
					return -1;
				}
				return answerLength;
			}
			std::cout <<  "receive bad CRC" << std::endl;
			return -1;
		}
		if (buffer[0] == 16)
		{
			std::cout <<  "busy" << std::endl;
			return -1;
		}
		std::cout <<  "received bad frame (prefix or sufix)" << std::endl;
		return -1;
	}
	std::cout <<  "received frame is too short." << std::endl;

	DestroySocket();
	return -1;
}

std::pair<unsigned char*, unsigned int> SatelIntegra::getFullFrame(const unsigned char* pCmd, const unsigned int cmdLength)
{
	std::list<unsigned char> result;

	for (unsigned int i = 0; i < cmdLength; ++i)
	{
		result.push_back(pCmd[i]);
	}

	// add CRC
	unsigned short crc;
	calculateCRC(pCmd, cmdLength, crc);
	result.push_back(crc >> 8);
	result.push_back(crc & 0xFF);
	// check special value
	// add prefix
	result.push_front(0xFE);
	result.push_front(0xFE);
	// add sufix
	result.push_back(0xFE);
	result.push_back(0x0D);

	unsigned int resultSize = result.size();
	unsigned char* pResult = new unsigned char[resultSize];
	std::memset(pResult, 0, resultSize);
	std::list<unsigned char>::iterator it = result.begin();
	for (unsigned int index = 0; it != result.end(); ++it, ++index)
	{
		pResult[index] = *it;
	}

	return { pResult, resultSize };
}
