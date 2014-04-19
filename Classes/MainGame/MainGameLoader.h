#ifndef _MainGameLoader_h
#define _MainGameLoader_h

#include "cocos2d.h"
#include "MainGameLayer.h"
#include "extensions/cocos-ext.h"
#include "cocosbuilder/CocosBuilder.h"

class MainGameLoader : public cocosbuilder::LayerLoader
{
public: 
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(MainGameLoader, loader);
protected:
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(MainGameLayer);
};

#endif