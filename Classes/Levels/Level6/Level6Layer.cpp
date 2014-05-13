#include "Level6Layer.h"

#define FIX_POS(_pos, _min, _max) \
    if (_pos < _min)        \
    _pos = _min;        \
else if (_pos > _max)   \
    _pos = _max;        \

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocosbuilder;

Level6Layer::Level6Layer() : MainGameLayer() 
{
	this->_lastTime = 0.0;
	this->mInvObject1 = nullptr;
	this->levelNumber = 6;
	this->vibroCount = 0;
}
Level6Layer::~Level6Layer() 
{
	Device::setAccelerometerEnabled(false);
	CC_SAFE_RELEASE_NULL(mInvObject1);
	CC_SAFE_RELEASE_NULL(mDoor2);
}

void Level6Layer::onNodeLoaded(Node * node,  NodeLoader * nodeLoader) {
	MainGameLayer::onNodeLoaded(node, nodeLoader);
	setInvGameObjectTouchListener();
	// callbacks for inventory touches
	//inventoryLogicCallback = [this]() { this->item2FuncCallback(); };
	doorEffect();
}

/**
*	Assigh sprite member from ccbi file
**/
bool Level6Layer::onAssignCCBMemberVariable(Ref * pTarget, const char * pMemberVariableName, Node * pNode) {
	MainGameLayer::onAssignCCBMemberVariable(pTarget, pMemberVariableName, pNode);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mInvObject1", Sprite *, this->mInvObject1);
    return false;
}

void Level6Layer::onEnter()
{
	Layer::onEnter();

    Device::setAccelerometerEnabled(true);
    auto listener = EventListenerAcceleration::create(CC_CALLBACK_2(Level6Layer::onAcceleration, this));
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    //_ball = Sprite::create("Images/ball.png");
    //_ball->setPosition(Point(VisibleRect::center().x, VisibleRect::center().y));
    //addChild(_ball);

    //_ball->retain();
}

void Level6Layer::onAcceleration(Acceleration* acc, Event* event)
{
//     double fNow = pAccelerationValue->timestamp;
// 
//     if (_lastTime > 0.0)
//     {
//         auto ptNow = convertToUI
//     }
// 
//     _lastTime = fNow;

    //auto pDir = Director::getInstance();

    /*FIXME: Testing on the Nexus S sometimes _ball is NULL */
    //if ( _ball == NULL ) {
    //    return;
    //}

    //auto ballSize  = _ball->getContentSize();

    //auto ptNow  = _ball->getPosition();
    //auto ptTemp = pDir->convertToUI(ptNow);
	Point p;
	p.x += acc->x;
    p.y -= acc->y;

	if(p.x > 2) {
		// Todo: effect vibrate
		Shaky3D::create(3, Size(15,10), 5, false);
	}

    //ptTemp.x += acc->x * 9.81f;
    //ptTemp.y -= acc->y * 9.81f;

    //auto ptNext = pDir->convertToGL(ptTemp);
    //FIX_POS(ptNext.x, (VisibleRect::left().x+ballSize.width / 2.0), (VisibleRect::right().x - ballSize.width / 2.0));
    //FIX_POS(ptNext.y, (VisibleRect::bottom().y+ballSize.height / 2.0), (VisibleRect::top().y - ballSize.height / 2.0));
    //_ball->setPosition(ptNext);
}

void Level6Layer::doorEffect()
{
	this->mDoor->setVisible(false);
	this->mDoor2 = Sprite::create("door.png");  

	this->_gridNodeTarget = NodeGrid::create();
    auto effect = Shaky3D::create(3, Size(15,10), 5, false);
	
	this->mDoor->getParent()->addChild(this->_gridNodeTarget);
	this->_gridNodeTarget->setPosition(Point(this->mDoor->getPositionX(), this->mDoor->getPositionY()));
	//this->mDoor->runAction(Liquid::create(4, Size(15,10), 5, 5));
	//this->mDoor->runAction(effect);
	if(this->_gridNodeTarget != nullptr) {		
		try{
			this->_gridNodeTarget->addChild(this->mDoor2);
		} catch (const std::exception& ex) {
			// Todo:
		}
		if(vibroCount == 2)
			this->mDoor2->setPosition(Point(this->mDoor->getPositionX(), this->mDoor->getPositionY()));
		//this->mDoor->setVisible(true);
	}
	this->_gridNodeTarget->runAction(effect);

	schedule( schedule_selector(Level6Layer::checkAnim) );
}

void Level6Layer::checkAnim(float dt)
{
    //auto s2 = getChildByTag(kTagBackground);
    if ( _gridNodeTarget->getNumberOfRunningActions() == 0 && _gridNodeTarget->getGrid() != NULL) {
        _gridNodeTarget->setGrid(nullptr);
		mDoor2->setVisible(false);
		if(vibroCount == 3) {
			mDoor->setVisible(true);
			isOpenDoor = true;
		}
	}
}

#pragma mark Inventory Items Callback Logic

#pragma mark Game Objects Touch Logic

void Level6Layer::setInvGameObjectTouchListener()
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

void Level6Layer::setGameObjectTouchListener()
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

		if (target == this->mInvObject1) {
			if(this->isInvItem1Selected) {
				// todo implm logic for open door
				this->gameInvObjToGameObj();
			}
        }
    };
	//_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this->mInvObject1);
}

void Level6Layer::gameInvObject1FuncCallback()
{
	if(this->invItem1Index != -1)
		this->itemsSpriteArray[this->invItem1Index]->setTexture(TextureCache::getInstance()->addImage("item_key_sel.png"));
	
	log("sprite vector:%d",itemsSpriteArray.size());
	
	this->isInvItem1Selected = true;
	this->isOpenDoor = true;
}

void Level6Layer::gameInvObjToGameObj()
{
	
}