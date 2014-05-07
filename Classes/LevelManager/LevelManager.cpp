#include "LevelManager.h"
#include "../Levels/Level1/Level1Loader.h"
#include "../Levels/Level2/Level2Loader.h"
#include "../Levels/Level3/Level3Loader.h"

LevelManager* LevelManager::mInstance = nullptr;

LevelManager::LevelManager() {}
LevelManager::~LevelManager() {}

LevelManager* LevelManager::getInstance() 
{
	if(!mInstance) {
		mInstance = new LevelManager;
		mInstance->mLevels = Constants::createMap();
	}

	return mInstance;
}

void LevelManager::loadFromJson(std::string jsonStr)
{
	// parse json string
	rapidjson::Document doc;
	doc.Parse<0>(jsonStr.c_str());
	if(doc.IsObject()) {
		for(auto it = doc.MemberonBegin(); it != doc.MemberonEnd(); ++it) {
            std::string key = it->name.GetString();
            int value = it->value.GetInt();         
			mInstance->mLevels.insert(make_pair(key, value));
        }		
	}
}

std::string LevelManager::toString() 
{
	rapidjson::Document document;
	document.SetObject();
	// must pass an allocator when the object may need to allocate memory
	rapidjson::Document::AllocatorType& allocator = document.GetAllocator();

	for(auto imap : mInstance->mLevels) {
		document.AddMember(imap.first.c_str(), imap.second, allocator);
	}
	// Convert JSON document to string
	rapidjson::StringBuffer strbuf;
	rapidjson::Writer<rapidjson::StringBuffer> writer(strbuf);
	document.Accept(writer);

	return strbuf.GetString();
}

void LevelManager::setLevelComplete() 
{
	std::string key =  "level" + std::to_string(currentLevelNumber);
	mInstance->mLevels[key] = 1;
	saveLocal();
}

void LevelManager::saveLocal()
{
	cocos2d::UserDefault::getInstance()->setStringForKey("gameLevels", toString()); 
}

int LevelManager::getLastLevelNumber()
{
	std::string jsonStr = cocos2d::UserDefault::getInstance()->getStringForKey("gameLevels");
	if(!jsonStr.empty())
		loadFromJson(jsonStr);

	int i = 1;
	for(auto imap : mInstance->mLevels) {
		if(imap.second == 0 && i == 1) {
			currentLevelNumber = 1;
			return 1;
		}
		i++;
		if(imap.second == 0) {
			currentLevelNumber = i;
			return i;
		}
	}
	return 0;
}

void LevelManager::loadNextLevel() 
{
	
}

cocosbuilder::NodeLoader* LevelManager::getLevelLoader(int curLevelNumber)
{
	switch (curLevelNumber)
	{
	case 1:
		return Level1Loader::loader();
	case 2:
		return Level2Loader::loader();
	case 3:
		return Level3Loader::loader();
	default:
		break;
	}
	//T type;
	//std::string classStrName =  "Level" + std::to_string(curLevelNumber) + "Loader";
	//std::stringstream convert(classStrName);
	//convert >> type;
	//return type::loader();
	//return mInstance->strToType<cocosbuilder::LayerLoader>(classStrName)::loader();
	//return mInstance->levelsLoaderArray[curLevelNumber - 1];
	return Level1Loader::loader();
}



