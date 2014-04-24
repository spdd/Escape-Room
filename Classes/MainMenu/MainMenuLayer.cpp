#include "../TestHeader/TestHeaderLayerLoader.h"
#include "../MainGame/MainGameLoader.h"
#include "MainMenuLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocosbuilder;

MainMenuLayer::MainMenuLayer() {}

MainMenuLayer::~MainMenuLayer() 
{
//    CC_SAFE_RELEASE_NULL(mAnimationManager);
//    CC_SAFE_RELEASE(mLeftButton);
//    CC_SAFE_RELEASE(mRightButton);
//    CC_SAFE_RELEASE(mTimeLabel);
//    CC_SAFE_RELEASE(mDistanceLabel);
}

bool MainMenuLayer::init()
{
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    return true;
}

void MainMenuLayer::onEnterTransitionDidFinish()
{
    
}

void MainMenuLayer::openScene(const char * pCCBFileName, const char * nodeName, NodeLoader * nodeLoader) {
    /* Create an autorelease NodeLoaderLibrary. */
    NodeLoaderLibrary * ccNodeLoaderLibrary = NodeLoaderLibrary::newDefaultNodeLoaderLibrary();

    ccNodeLoaderLibrary->registerNodeLoader("TestHeaderLayer", TestHeaderLayerLoader::loader());
    if(nodeName != NULL && nodeLoader != NULL) {
        ccNodeLoaderLibrary->registerNodeLoader(nodeName, nodeLoader);
    }

    /* Create an autorelease CCBReader. */
    cocosbuilder::CCBReader * ccbReader = new cocosbuilder::CCBReader(ccNodeLoaderLibrary);
    ccbReader->autorelease();

    /* Read a ccbi file. */
    // Load the scene from the ccbi-file, setting this class as
    // the owner will cause lblTestTitle to be set by the CCBReader.
    // lblTestTitle is in the TestHeader.ccbi, which is referenced
    // from each of the test scenes.
    auto node = ccbReader->readNodeGraphFromFile(pCCBFileName, this);

    //this->mTestTitleLabelTTF->setString(pCCBFileName);

    auto scene = Scene::create();
    if(node != NULL) {
        scene->addChild(node);
    }

    /* Push the new scene with a fancy transition. */
    Color3B transitionColor;
    transitionColor.r = 0;
    transitionColor.g = 0;
    transitionColor.b = 0;
    
    Director::getInstance()->pushScene(TransitionFade::create(0.5f, scene, transitionColor));
}

void MainMenuLayer::onNodeLoaded(cocos2d::Node * node,  cocosbuilder::NodeLoader * nodeLoader) {
    //auto ccRotateBy = RotateBy::create(20.0f, 360);
    //auto ccRepeatForever = RepeatForever::create(ccRotateBy);
    //this->mBurstSprite->runAction(ccRepeatForever);
}

//bool TitleScene::onAssignCCBMemberVariable(cocos2d::Object *pTarget, const char *pMemberVariableName, cocos2d::Node *pNode)
//{
//    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mStartConrolButton", ControlButton*, this->mStartConrolButton);
//    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mBg2", Sprite*, this->mBg2);
//    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mBg3", Sprite*, this->mBg3);
//    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLeftButton", MenuItemImage*, this->mLeftButton);
//    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mRightButton", MenuItemImage*, this->mRightButton);
//    
//    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mTime", LabelTTF*, this->mTimeLabel);
//    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mDistance", LabelTTF*, this->mDistanceLabel);
//    return false;
//}

SEL_MenuHandler MainMenuLayer::onResolveCCBCCMenuItemSelector(Ref * pTarget, const char * pSelectorName) {
	CCLOG("name = %s", pSelectorName);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onPressButton", MainMenuLayer::onMenuItemAClicked);
	//CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onPressButton", MainMenuLayer::tappedPlayButton);
    return NULL;    
}

Control::Handler MainMenuLayer::onResolveCCBCCControlSelector(Ref * pTarget, const char *pSelectorName)
{
    CCLOG("name = %s", pSelectorName);
    
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPlayPressedd", MainMenuLayer::tappedPlayButton);
    return NULL;
}

void MainMenuLayer::tappedPlayButton(Ref * pTarget, Control::EventType pControlEventType)
{
	CCLOG("tappedPlayButton eventType = %d", pControlEventType);
	//Scene* scene = MapSceneLoader::scene();
    //TransitionProgressInOut* trans = TransitionProgressInOut::create(1, scene);
    //Director::getInstance()->replaceScene(trans);
}

void MainMenuLayer::onMenuItemAClicked(cocos2d::Ref *pSender) {
	CCLOG("onMenuItemAClicked");
    this->openScene("MainGameScene.ccbi", "MainGameLayer", MainGameLoader::loader());
}