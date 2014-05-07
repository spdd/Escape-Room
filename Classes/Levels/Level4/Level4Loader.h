#ifndef _Level4_LOADER_h
#define _Level4_LOADER_h

#include "cocos2d.h"
#include "Level4Layer.h"
#include "extensions/cocos-ext.h"
#include "cocosbuilder/CocosBuilder.h"

class Level4Loader : public cocosbuilder::LayerLoader
{
public: 
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(Level4Loader, loader);
protected:
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(Level4Layer);
};

#endif