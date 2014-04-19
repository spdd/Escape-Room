//
//  TitleSceneLoader.h
//  Cocos2dxSRPGQuest
//
//  Created by kyokomi on 2013/09/29.
//
//

#ifndef Cocos2dxSRPGQuest_TitleSceneLoader_h
#define Cocos2dxSRPGQuest_TitleSceneLoader_h

#include "cocos2d.h"
#include "MainMenuLoader.h"
#include "MainMenuLayer.h"
#include "extensions/cocos-ext.h"
#include "cocosbuilder/CocosBuilder.h"

class MainMenuLoader : public cocosbuilder::LayerLoader
{
public: 
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(MainMenuLoader, loader);
    static cocos2d::Scene* createScene();
    //CREATE_FUNC(TitleSceneLoader);
protected:
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(MainMenuLayer);
};

#endif
