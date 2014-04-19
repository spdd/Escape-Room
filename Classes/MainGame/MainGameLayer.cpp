#include "MainGameLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocosbuilder;

MainGameLayer::MainGameLayer() {}

MainGameLayer::~MainGameLayer() 
{
//    CC_SAFE_RELEASE_NULL(mAnimationManager);
//    CC_SAFE_RELEASE(mLeftButton);
//    CC_SAFE_RELEASE(mRightButton);
//    CC_SAFE_RELEASE(mTimeLabel);
//    CC_SAFE_RELEASE(mDistanceLabel);
}

bool MainGameLayer::init()
{
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    return true;
}

void MainGameLayer::onEnterTransitionDidFinish()
{
    
}

SEL_MenuHandler MainGameLayer::onResolveCCBCCMenuItemSelector(Ref * pTarget, const char * pSelectorName) {
	CCLOG("name = %s", pSelectorName);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onPressButton", MainGameLayer::onMenuItemAClicked);
	//CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onPressButton", MainMenuLayer::tappedPlayButton);
    return NULL;    
}

Control::Handler MainGameLayer::onResolveCCBCCControlSelector(Ref * pTarget, const char *pSelectorName)
{
    CCLOG("name = %s", pSelectorName);
    
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPlayPressedd", MainGameLayer::tappedPlayButton);
    return NULL;
}

void MainGameLayer::tappedPlayButton(Ref * pTarget, Control::EventType pControlEventType)
{
	CCLOG("tappedPlayButton eventType = %d", pControlEventType);
	//Scene* scene = MapSceneLoader::scene();
    //TransitionProgressInOut* trans = TransitionProgressInOut::create(1, scene);
    //Director::getInstance()->replaceScene(trans);
}

void MainGameLayer::onMenuItemAClicked(cocos2d::Ref *pSender) {
	CCLOG("onMenuItemAClicked");
    //this->openScene("ccb/ccb/TestMenus.ccbi", "TestMenusLayer", MainGameLoader::loader());
}