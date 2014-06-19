#ifndef __JSON_UTILS_H__
#define __JSON_UTILS_H__

#include <string>
#include <map>
#include <vector>

class PokerBase;
class JSONUtils
{
public:
	static std::string toJSONString(std::map<std::string, std::string>);
	static std::string toJSONString(std::map<std::string, PokerBase*>);

	static std::map<std::string, std::string> toMap(std::string);
	static std::vector<std::string> toVector(std::string);
}

#endif