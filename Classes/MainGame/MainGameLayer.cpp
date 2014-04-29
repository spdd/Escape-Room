﻿#include "MainGameLayer.h"
#include "../TestHeader/TestHeaderLayerLoader.h"
#include "../Levels/Level1/Level1Loader.h"

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
{
	this->isOpenDoor = false;
	this->levelNumber = 0;
	this->currentInvItemNumber = -1;
	for (int i = 0; i < 5; i++) {
		itemsSolutionArray[i] = 0;
	}
}

MainGameLayer::~MainGameLayer() 
{
	CC_SAFE_RELEASE_NULL(mDoor);
    CC_SAFE_RELEASE_NULL(mInvItem1);
    CC_SAFE_RELEASE_NULL(mInvItem2);
    CC_SAFE_RELEASE_NULL(mInvItem3);
    CC_SAFE_RELEASE_NULL(mInvItem4);
	CC_SAFE_RELEASE_NULL(mInvItem5);
}

bool MainGameLayer::init()
{
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

	//auto listener1 = EventListenerTouchOneByOne::create();
	//listener1->setSwallowTouches(true);
	//listener1->onTouchBegan = CC_CALLBACK_2(MainGameLayer::onTouchBegan, this);
	//listener1->onTouchMoved = CC_CALLBACK_2(MainGameLayer::onTouchMoved, this);
    //listener1->onTouchEnded = CC_CALLBACK_2(MainGameLayer::onTouchEnded, this);
	//this->getEventDispatcher()->addEventListenerWithFixedPriority(listener1, 1);
    //_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);

	return true;
}

void MainGameLayer::onEnterTransitionDidFinish()
{
    
}

#pragma mark Node Loaded from ccbi Section
#pragma mark -

/**
*	Node loaded from ccbi file event 
**/
void MainGameLayer::onNodeLoaded(Node * node,  NodeLoader * nodeLoader) {
    auto ccRotateBy = RotateBy::create(20.0f, 360);
    auto ccRepeatForever = RepeatForever::create(ccRotateBy);
	this->mInvItem1->runAction(ccRepeatForever);

	// set touch listener
	setDoorTouchListener();
	setInventarItemsTouchListener();
}

#pragma mark Settings Menu Section
#pragma mark -

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
/**
*	Assigh sprite member from ccbi file
**/
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

#pragma mark Touch Events Section
#pragma mark -

/**
*	Door touch events 
**/

void MainGameLayer::setDoorTouchListener()
{
	auto listener1 = EventListenerTouchOneByOne::create();
	listener1->setSwallowTouches(true);

	listener1->onTouchBegan = [](Touch* touch, Event* event) {
        // event->getCurrentTarget() returns the *listener's* sceneGraphPriority node.
		//onTouchBegan(touch, event);
        auto target = static_cast<Sprite*>(event->getCurrentTarget());

        //Get the position of the current point relative to the button
        Point locationInNode = target->convertToNodeSpace(touch->getLocation());
        Size s = target->getContentSize();
        Rect rect = Rect(0, 0, s.width, s.height);

        //Check the click area
        if (rect.containsPoint(locationInNode))
        {			
			//target->setColor(Color3B::RED);
			log("sprite tag:%d  began... x = %f, y = %f",target->getTag(),  locationInNode.x, locationInNode.y);
            target->setOpacity(180);
            return true;
        }
        return false;
    };

	listener1->onTouchMoved = [](Touch* touch, Event* event){
        auto target = static_cast<Sprite*>(event->getCurrentTarget());
        //Move the position of current button sprite
        //target->setPosition(target->getPosition() + touch->getDelta());
    };

    //Process the touch end event
    listener1->onTouchEnded = [=](Touch* touch, Event* event){
        auto target = static_cast<Sprite*>(event->getCurrentTarget());
        log("sprite onTouchesEnded.. ");
        target->setOpacity(255);
        //Reset zOrder and the display sequence will change
		if (target == this->mDoor)
        {
            this->mDoor->setZOrder(100);
        }
        else if(target == this->mDoor)
        {
            this->mDoor->setZOrder(0);
        }
		if(!isOpenDoor) {
			this->mDoor->setTexture(TextureCache::getInstance()->addImage("exit.png"));
			this->openScene("ccb/Levels/Level1.ccbi", "Level1Layer", Level1Loader::loader());
		}

    };
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this->mDoor);
}

/**
*	Inventar items touch events 
**/
void MainGameLayer::setInventarItemsTouchListener()
{
	auto listener1 = EventListenerTouchOneByOne::create();
	listener1->setSwallowTouches(true);

	listener1->onTouchBegan = [](Touch* touch, Event* event) {
        // event->getCurrentTarget() returns the *listener's* sceneGraphPriority node.
		//onTouchBegan(touch, event);
        auto target = static_cast<Sprite*>(event->getCurrentTarget());

        //Get the position of the current point relative to the button
        Point locationInNode = target->convertToNodeSpace(touch->getLocation());
        Size s = target->getContentSize();
        Rect rect = Rect(0, 0, s.width, s.height);

        //Check the click area
        if (rect.containsPoint(locationInNode))
        {			
			//target->setColor(Color3B::RED);
			log("sprite tag:%d  began... x = %f, y = %f",target->getTag(),  locationInNode.x, locationInNode.y);
            target->setOpacity(180);
            return true;
        }
        return false;
    };

	listener1->onTouchMoved = [](Touch* touch, Event* event){};

    //Process the touch end event
    listener1->onTouchEnded = [=](Touch* touch, Event* event){
        auto target = static_cast<Sprite*>(event->getCurrentTarget());
        log("sprite onTouchesEnded.. ");
        target->setOpacity(255);
        //Reset zOrder and the display sequence will change
		if (target == this->mInvItem1) {
			this->currentInvItemNumber = 1;
            this->mInvItem2->setZOrder(100);
        } else if(target == this->mInvItem2) {
			this->currentInvItemNumber = 2;
			if(levelNumber > 0)
				inventoryLogicCallback();
            this->mInvItem2->setZOrder(0);
        } else if(target == this->mInvItem3) {
			this->currentInvItemNumber = 3;
        } else if(target == this->mInvItem4) {
			this->currentInvItemNumber = 4;
        } else if(target == this->mInvItem5) {
			this->currentInvItemNumber = 5;
        }

    };
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this->mInvItem1);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), this->mInvItem2);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), this->mInvItem3);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), this->mInvItem4);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), this->mInvItem5);
}

void MainGameLayer::openScene(const char * pCCBFileName, const char * nodeName, NodeLoader * nodeLoader) {
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

int MainGameLayer::getItemIndexNumber()
{
	for (int i = 0; i < itemsSolutionArray.size(); i++) {
		if(itemsSolutionArray[i] == 0)
			return i;
	}
	return 0;
}

