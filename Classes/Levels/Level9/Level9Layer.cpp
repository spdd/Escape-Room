#include "Level9Layer.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocosbuilder;

Level9Layer::Level9Layer() : MainGameLayer() 
	
{
	this->mInvObject1 = nullptr;
	this->mBackButton = nullptr;
	this->mBack1 = nullptr;
	this->mBack2 = nullptr;
	this->mBack3 = nullptr;
	this->mBack4 = nullptr;
	this->levelNumber = 9;
	this->isDoorOneSprite = true;

	this->rotateCount1 = 90;
	this->rotateCount2 = 90;
	this->rotateCount3 = 90;
	this->rotateCount4 = 90;

	runBackMove = false;
}
Level9Layer::~Level9Layer() 
{
	CC_SAFE_RELEASE_NULL(mInvObject1);
	CC_SAFE_RELEASE_NULL(mBackButton);
	CC_SAFE_RELEASE_NULL(mBack1);
	CC_SAFE_RELEASE_NULL(mBack2);
	CC_SAFE_RELEASE_NULL(mBack3);
	CC_SAFE_RELEASE_NULL(mBack4);
}

void Level9Layer::onNodeLoaded(Node * node,  NodeLoader * nodeLoader) {
	MainGameLayer::onNodeLoaded(node, nodeLoader);
	setInvGameObjectTouchListener();
	setGameObjectTouchListener();
	// callbacks for inventory touches
	//inventoryLogicCallback = [this]() { this->item2FuncCallback(); };
}

/**
*	Assigh sprite member from ccbi file
**/
bool Level9Layer::onAssignCCBMemberVariable(Ref * pTarget, const char * pMemberVariableName, Node * pNode) {
	MainGameLayer::onAssignCCBMemberVariable(pTarget, pMemberVariableName, pNode);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mInvObject1", Sprite *, this->mInvObject1);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "backButton", Sprite *, this->mBackButton);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "back1", Sprite *, this->mBack1);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "back2", Sprite *, this->mBack2);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "back3", Sprite *, this->mBack3);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "back4", Sprite *, this->mBack4);
    return false;
}

#pragma mark Inventory Items Callback Logic

#pragma mark Game Objects Touch Logic

void Level9Layer::setInvGameObjectTouchListener()
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

void Level9Layer::setGameObjectTouchListener()
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
            target->setOpacity(180);
            return true;
        }
        return false;
    };

	listener1->onTouchMoved = [](Touch* touch, Event* event){};

    //Process the touch end event
    listener1->onTouchEnded = [=](Touch* touch, Event* event){
        auto target = static_cast<Sprite*>(event->getCurrentTarget());
        //log("sprite onTouchesEnded.. ");

		if (target == this->mBack1 && !(this->rotateCount1 == 360)) {
			this->rotateCount1 = rotateCount1 + 90;
			this->mBack1->setRotation(rotateCount1);
        } else if(target == this->mBack2 && !(this->rotateCount2 == 360)) {
			this->rotateCount2 = rotateCount2 + 90;
			this->mBack2->setRotation(rotateCount2);
		} else if(target == this->mBack3 && !(this->rotateCount3 == 360)) {
			this->rotateCount3 = rotateCount3 + 90;
			this->mBack3->setRotation(rotateCount3);
		} else if(target == this->mBack4 && !(this->rotateCount4 == 360)) {
			this->rotateCount4 = rotateCount4 + 90;
			this->mBack4->setRotation(rotateCount4);
		}

		int summ = rotateCount1 + rotateCount2 + rotateCount3 + rotateCount4;
		if(summ == 1440) {
			this->mBack1->setVisible(false);
			this->mBack2->setVisible(false);
			this->mBack3->setVisible(false);
			this->mBack4->setVisible(false);
			this->mBack1->removeAllChildren();
			this->mBack2->removeAllChildren();
			this->mBack3->removeAllChildren();
			this->mBack4->removeAllChildren();

			this->mBackButton->setVisible(true);

			auto actionBy = MoveTo::create(2, Point(this->mDoor->getPosition().x - 200, this->mDoor->getPosition().y));
			mDoor->runAction(actionBy);
			runBackMove = true;
			isOpenDoor = true;
		}
    };
	//_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this->mBackButton);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this->mBack1);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), this->mBack2);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), this->mBack3);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), this->mBack4);
}

void Level9Layer::gameInvObject1FuncCallback()
{
	if(this->invItem1Index != -1)
		this->itemsSpriteArray[this->invItem1Index]->setTexture(TextureCache::getInstance()->addImage("item_key_sel.png"));
	
	log("sprite vector:%d",itemsSpriteArray.size());
	
	this->isInvItem1Selected = true;
	this->isOpenDoor = true;
}

void Level9Layer::gameInvObjToGameObj()
{
	
}