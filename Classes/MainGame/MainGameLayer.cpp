#include "MainGameLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocosbuilder;

MainGameLayer::MainGameLayer()
	:mDoor(nullptr),
	mInvItem1(nullptr),
	mInvItem2(nullptr),
	mInvItem3(nullptr),
	mInvItem4(nullptr),
	mInvItem5(nullptr)
{}

MainGameLayer::~MainGameLayer() 
{
	CC_SAFE_RELEASE_NULL(mDoor);
    CC_SAFE_RELEASE(mInvItem1);
    CC_SAFE_RELEASE(mInvItem2);
    CC_SAFE_RELEASE(mInvItem3);
    CC_SAFE_RELEASE(mInvItem4);
	CC_SAFE_RELEASE(mInvItem5);
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

void MainGameLayer::onNodeLoaded(Node * node,  NodeLoader * nodeLoader) {
    auto ccRotateBy = RotateBy::create(20.0f, 360);
    auto ccRepeatForever = RepeatForever::create(ccRotateBy);
	this->mInvItem1->runAction(ccRepeatForever);
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

bool MainGameLayer::onAssignCCBMemberVariable(Ref * pTarget, const char * pMemberVariableName, Node * pNode) {
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "door", Sprite *, this->mDoor);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "invItem1", Sprite *, this->mInvItem1);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "invItem2", Sprite *, this->mInvItem2);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "invItem3", Sprite *, this->mInvItem3);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "invItem4", Sprite *, this->mInvItem4);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "invItem5", Sprite *, this->mInvItem5);
    return false;
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