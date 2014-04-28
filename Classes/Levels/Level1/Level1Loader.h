#ifndef _LEVEL1_LOADER_h
#define _LEVEL1_LOADER_h

#include "cocos2d.h"
#include "Level1Layer.h"
#include "extensions/cocos-ext.h"
#include "cocosbuilder/CocosBuilder.h"

class MainGameLoader : public cocosbuilder::LayerLoader
{
public: 
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(MainGameLoader, loader);
protected:
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(Level1Layer);
};

#endif