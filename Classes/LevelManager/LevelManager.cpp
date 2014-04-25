#include "LevelManager.h"

LevelManager* LevelManager::mInstance = nullptr;

LevelManager::LevelManager() {}
LevelManager::~LevelManager() {}

LevelManager* LevelManager::getInstance() 
{
	if(!mInstance)
		mInstance = new LevelManager;

	return mInstance;
}


