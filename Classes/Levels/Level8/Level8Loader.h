#ifndef _Level8_LOADER_h
#define _Level8_LOADER_h

#include "cocos2d.h"
#include "Level8Layer.h"
#include "extensions/cocos-ext.h"
#include "cocosbuilder/CocosBuilder.h"

class Level8Loader : public cocosbuilder::LayerLoader
{
public: 
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(Level8Loader, loader);
protected:
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(Level8Layer);
};

#endif