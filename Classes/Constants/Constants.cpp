#include "Constants.h"

std::map<std::string, int> Constants::createMap()
{
	std::map<std::string, int> m;
	for (int i = 0; i < LEVEL_COUNT; i++)
	{
		std::string key = "level" + std::to_string(i + 1);
		m[key] = 0;
	}
	return m;
}