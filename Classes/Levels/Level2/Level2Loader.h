#ifndef _LEVEL2_LOADER_h
#define _LEVEL2_LOADER_h

#include "cocos2d.h"
#include "Level2Layer.h"
#include "extensions/cocos-ext.h"
#include "cocosbuilder/CocosBuilder.h"

class Level2Loader : public cocosbuilder::LayerLoader
{
public: 
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(Level2Loader, loader);
protected:
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(Level2Layer);
};

#endif