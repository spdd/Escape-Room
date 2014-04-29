#include "Level1Layer.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocosbuilder;

Level1Layer::Level1Layer() : MainGameLayer() 
	
{
	this->mInvObject1 = nullptr;
	this->levelNumber = 1;
}
Level1Layer::~Level1Layer() 
{
	CC_SAFE_RELEASE_NULL(mInvObject1);
}

void Level1Layer::onNodeLoaded(Node * node,  NodeLoader * nodeLoader) {
	MainGameLayer::onNodeLoaded(node, nodeLoader);
	// callbacks for inventory touches
	//inventoryLogicCallback = [this]() { this->item2FuncCallback(); };
}

/**
*	Assigh sprite member from ccbi file
**/
bool Level1Layer::onAssignCCBMemberVariable(Ref * pTarget, const char * pMemberVariableName, Node * pNode) {
	MainGameLayer::onAssignCCBMemberVariable(pTarget, pMemberVariableName, pNode);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mInvObject1", Sprite *, this->mInvObject1);
    return false;
}

#pragma mark Inventory Items Callback Logic
#pragma mark -

void Level1Layer::item2FuncCallback()
{
	auto ccRotateBy = RotateBy::create(20.0f, 360);
    auto ccRepeatForever = RepeatForever::create(ccRotateBy);
	this->mInvItem2->runAction(ccRepeatForever);
}

#pragma mark Game Objects Touch Logic
#pragma mark -

void Level1Layer::setGameObjectTouchListener()
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

		if (target->getTag() == this->mInvObject1->getTag()) {
			if(!this->isInvItem1Selected) {
				// todo set simple inventory images
				int index = this->getItemIndexNumber();
				cocos2d::Sprite* itemSprite = this->itemsSpriteArray[index];
				//itemSprite->setTexture(TextureCache::getInstance()->addImage("exit.png"));
				this->itemsCallbackArray[index] = [this]() { this->gameInvObject1FuncCallback(); };
				
				this->itemsSolutionArray[index] = 1;
			}
			else {
				
			}
        }

    };
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this->mInvObject1);
	//_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), this->mInvItem2);
}

void Level1Layer::gameInvObject1FuncCallback()
{
	//item->setTexture(TextureCache::getInstance()->addImage("exit.png"));
	this->isInvItem1Selected = true;
	// todo set highlines inventory images
}

void Level1Layer::gameInvObjToGameObj()
{
	if(this->isInvItem1Selected)
		;
}