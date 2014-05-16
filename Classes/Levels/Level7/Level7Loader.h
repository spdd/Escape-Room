#ifndef _Level7_LOADER_h
#define _Level7_LOADER_h

#include "cocos2d.h"
#include "Level7Layer.h"
#include "extensions/cocos-ext.h"
#include "cocosbuilder/CocosBuilder.h"

class Level7Loader : public cocosbuilder::LayerLoader
{
public: 
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(Level7Loader, loader);
protected:
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(Level7Layer);
};

#endif