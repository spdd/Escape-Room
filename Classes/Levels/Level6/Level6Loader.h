#ifndef _Level6_LOADER_h
#define _Level6_LOADER_h

#include "cocos2d.h"
#include "Level6Layer.h"
#include "extensions/cocos-ext.h"
#include "cocosbuilder/CocosBuilder.h"

class Level6Loader : public cocosbuilder::LayerLoader
{
public: 
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(Level6Loader, loader);
protected:
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(Level6Layer);
};

#endif