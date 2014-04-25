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

void MainGameLayer::onNodeLoaded(Node * node,  NodeLoader * nodeLoader) {
    auto ccRotateBy = RotateBy::create(20.0f, 360);
    auto ccRepeatForever = RepeatForever::create(ccRotateBy);
	this->mInvItem1->runAction(ccRepeatForever);

	// set touch listener
	setDoorTouchListener();
	setInventarItemsTouchListener();
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
		this->mDoor->setTexture(TextureCache::getInstance()->addImage("exit.png"));

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

	listener1->onTouchMoved = [](Touch* touch, Event* event){
    };

    //Process the touch end event
    listener1->onTouchEnded = [=](Touch* touch, Event* event){
        auto target = static_cast<Sprite*>(event->getCurrentTarget());
        log("sprite onTouchesEnded.. ");
        target->setOpacity(255);
        //Reset zOrder and the display sequence will change
		if (target == this->mInvItem2)
        {
            this->mInvItem2->setZOrder(100);
        }
        else if(target == this->mInvItem2)
        {
            this->mInvItem2->setZOrder(0);
        }

    };
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this->mInvItem1);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), this->mInvItem2);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), this->mInvItem3);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), this->mInvItem4);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), this->mInvItem5);
}