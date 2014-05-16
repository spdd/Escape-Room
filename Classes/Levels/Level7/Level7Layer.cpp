#include "Level7Layer.h"
#include "VisibleRect.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocosbuilder;

Level7Layer::Level7Layer() : MainGameLayer() 
	
{
	this->mInvObject1 = nullptr;
	this->mShkaf = nullptr;
	this->levelNumber = 7;

	// enable events
	auto touchListener = EventListenerTouchAllAtOnce::create();
    touchListener->onTouchesEnded = CC_CALLBACK_2(Level7Layer::onTouchesEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	// init physics
	//scheduleUpdate();
}
Level7Layer::~Level7Layer() 
{
	CC_SAFE_RELEASE_NULL(mInvObject1);
	CC_SAFE_RELEASE_NULL(mShkaf);
}

void Level7Layer::onNodeLoaded(Node * node,  NodeLoader * nodeLoader) {
	MainGameLayer::onNodeLoaded(node, nodeLoader);
	setInvGameObjectTouchListener();
	setGameObjectTouchListener();
	// callbacks for inventory touches
	//inventoryLogicCallback = [this]() { this->item2FuncCallback(); };
}

void Level7Layer::onEnter()
{
    Layer::onEnter();
}

/**
*	Assigh sprite member from ccbi file
**/
bool Level7Layer::onAssignCCBMemberVariable(Ref * pTarget, const char * pMemberVariableName, Node * pNode) {
	MainGameLayer::onAssignCCBMemberVariable(pTarget, pMemberVariableName, pNode);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mInvObject1", Sprite *, this->mInvObject1);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "skaf", Sprite *, this->mShkaf);
    return false;
}

#pragma mark Inventory Items Callback Logic

#pragma mark Game Objects Touch Logic

void Level7Layer::setInvGameObjectTouchListener()
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
        //log("sprite onTouchesEnded.. ");

		if (target == this->mInvObject1) {
			if(!this->isInvItem1Selected) {
				// todo set simple inventory images
				int index = this->getItemIndexNumber();
				this->invItem1Index = getItemIndexNumber();
				mInvItem1->setTexture(TextureCache::getInstance()->addImage("item_key.png"));

				std::function<void()> func = [this] { this->gameInvObject1FuncCallback(); };
				this->addFunctor(index, func);
				this->itemsSolutionArray[index] = 1;
			}
			else {
				
			}
        }

    };
	//_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this->mInvObject1);
	//_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), this->mInvItem2);
}

void Level7Layer::setGameObjectTouchListener()
{
	auto listener1 = EventListenerTouchOneByOne::create();
	listener1->setSwallowTouches(true);

	listener1->onTouchBegan = [](Touch* touch, Event* event) {
        auto target = static_cast<Sprite*>(event->getCurrentTarget());

        //Get the position of the current point relative to the button
        Point locationInNode = target->convertToNodeSpace(touch->getLocation());
        Size s = target->getContentSize();
        Rect rect = Rect(0, 0, s.width, s.height);

        //Check the click area
        if (rect.containsPoint(locationInNode))
        {			
			log("sprite tag:%d  began... x = %f, y = %f",target->getTag(),  locationInNode.x, locationInNode.y);
            //target->setOpacity(180);
            return true;
        }
        return false;
    };

	listener1->onTouchMoved = [](Touch* touch, Event* event){
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
        target->setPosition((target->getPosition().x + touch->getDelta().x), target->getPosition().y);
	};

    //Process the touch end event
    listener1->onTouchEnded = [=](Touch* touch, Event* event){
        auto target = static_cast<Sprite*>(event->getCurrentTarget());
        //log("sprite onTouchesEnded.. ");
		//target->setVisible(false);
		//target->setZOrder(0);
		if (target == this->mInvObject1) {
			if(this->isInvItem1Selected) {
				// todo implm logic for open door
				this->gameInvObjToGameObj();
			}
        }
    };
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this->mShkaf);
}

void Level7Layer::gameInvObject1FuncCallback()
{
	if(this->invItem1Index != -1)
		this->itemsSpriteArray[this->invItem1Index]->setTexture(TextureCache::getInstance()->addImage("item_key_sel.png"));
	
	log("sprite vector:%d",itemsSpriteArray.size());
	
	this->isInvItem1Selected = true;
	this->isOpenDoor = true;
}

void Level7Layer::gameInvObjToGameObj()
{
	
}