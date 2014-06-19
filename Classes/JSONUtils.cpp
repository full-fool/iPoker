#include "JSONUtils.h"


std::string JSONUtils::toJSONString(std::map<std::string, std::string> argMap)
{
	/*
	Json::Value data;
	for(std::map<std::string, std::string>::iterator iter = argMap.begin(); iter!=argMap.end(); ++iter)
	{
		data[iter->first] = iter->second;
	}
	return data.toStyledString();
	*/
	return "";
	
}

std::string JSONUtils::toJSONString(std::map<std::string, PokerBase*>)
{
	return "";
}
/*
std::map<std::string, std::string> JSONUtils::toMap(std::string)
{
	
}

std::vector<std::string> JSONUtils::toVector(std::string)
{
	return "";
}
*/