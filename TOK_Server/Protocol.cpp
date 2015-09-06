#include "Protocol.h"

Protocol::Protocol() //: //TOKEN("&$&")
{

}

Protocol::~Protocol()
{

}

std::string Protocol::MakeTheProtocol(PROTOCOL_TYPE& type, PROTOCOL& protocol, const char* msg)
{
	std::string temp;
	temp.append(std::to_string(type));
	temp.append(TOKEN);
	temp.append(std::to_string(protocol));
	temp.append(TOKEN);
	temp.append(msg);
	return temp;
}

std::string Protocol::MakeTheProtocol(const PROTOCOL_TYPE& type, const PROTOCOL& protocol, const char* msg)
{
	std::string temp;
	temp.append(std::to_string(type));
	temp.append(TOKEN);
	temp.append(std::to_string(protocol));
	temp.append(TOKEN);
	temp.append(msg);
	return temp;
}

bool Protocol::TranslateProtocol(const std::string& str, Message& result)
{
	int tokenIdx[2] = {0};
	tokenIdx[0] = str.find(TOKEN);
	tokenIdx[1] = str.find(TOKEN, tokenIdx[0]+1);
	if(tokenIdx[0] == -1 || tokenIdx[1]>str.length())
		return false;

	int	tempIdx = tokenIdx[0]+TOKEN.length();
	int typeSize = tokenIdx[0];
	int protocolSize = tokenIdx[1] - tempIdx;
	
	result.type = static_cast<PROTOCOL_TYPE>(atoi(str.substr(0,typeSize).c_str()));
	result.protocol = static_cast<PROTOCOL>(atoi(str.substr(tempIdx, protocolSize).c_str()));
	tempIdx = tokenIdx[1]+TOKEN.length();
	strcpy(result.message, str.substr(tempIdx, str.length()).c_str());
	
	return true;
}