//
//  TitleSceneLoader.cpp
//  Cocos2dxSRPGQuest
//
//  Created by kyokomi on 2013/09/29.
//
//
#include "MainMenuLoader.h"

cocos2d::Scene* MainMenuLoader::createScene()
{
    cocosbuilder::NodeLoaderLibrary* nodeLoaderLibrary = cocosbuilder::NodeLoaderLibrary::newDefaultNodeLoaderLibrary();
    nodeLoaderLibrary->registerNodeLoader("MainMenuLayer", MainMenuLoader::loader());
    
    cocosbuilder::CCBReader* ccbReader = new cocosbuilder::CCBReader(nodeLoaderLibrary);
    cocos2d::Node* node = ccbReader->readNodeGraphFromFile("ccb/MainScene.ccbi");
    
    cocos2d::Scene* pScene = cocos2d::Scene::create();
    if (node != NULL)
    {
        pScene->addChild(node);
    }
    ccbReader->release();
    
    return pScene;
}