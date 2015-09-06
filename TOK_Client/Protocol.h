#include <iostream>
#include <string>
const std::string TOKEN = "&$&";

class Protocol
{
public:
	enum PROTOCOL {SEND_NICKNAME, SEND_READYSTATE, SEND_ACCESS_USER_NUM, SEND_MAXIMUM_USERNUM, SEND_GAMESTAGE,
				   USER_TURN_CHANGE};
	enum PROTOCOL_TYPE {BROADCAST, NOTIFICATION};

	typedef struct Message
	{
		PROTOCOL_TYPE type;
		PROTOCOL protocol;
		char message[100];
	};
	Protocol();
	~Protocol();
	std::string MakeTheProtocol(PROTOCOL_TYPE&, PROTOCOL&, const char* msg);
	std::string MakeTheProtocol(const PROTOCOL_TYPE&, const PROTOCOL&, const char* msg);
	bool TranslateProtocol(const std::string& str, Message& result);
};

