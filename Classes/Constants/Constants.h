#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__

#include <map>

#define LEVEL_COUNT 20

class Constants
{
private:
	static std::map<std::string, int> initData = createMap();
private:
	static std::map<std::string, int> createMap()
	{
		std::map<std::string, int> m;
		for (int i = 0; i < LEVEL_COUNT; i++)
		{
			std::string key = "level" + std::to_string(i + 1);
			map[key] = 0;
		}
		return m;
	}
}
#endif