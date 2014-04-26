#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__

#include <map>
#include <string>

#define LEVEL_COUNT 20

class Constants
{
public:
	static std::map<std::string, int> createMap();
private:
	Constants();
	virtual ~Constants();
};
#endif