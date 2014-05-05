#ifndef __LevelManager__
#define __LevelManager__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "cocosbuilder/CocosBuilder.h"
#include <map>
#include "../Constants/Constants.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"

class LevelManager
{
    public:
		std::map<std::string, int> mLevels;
        static LevelManager* getInstance();
		void setLevelComplete();
		void loadNextLevel();
		void resetLevels();

		cocosbuilder::NodeLoader* getLevelLoader(int curLevelNumber);
    
    protected:
        static LevelManager* mInstance;
        
    private:
		int currentLevelNumber;

        LevelManager();
        ~LevelManager();
		void loadFromJson(std::string jsonStr);
		std::string toString();
		void saveLocal();
		int getLastLevelNumber();
};
#endif