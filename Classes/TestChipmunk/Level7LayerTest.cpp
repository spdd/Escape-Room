#include "Level7LayerTest.h"
#include "VisibleRect.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocosbuilder;

Level7TestLayer::Level7TestLayer() : MainGameLayer() 
	
{
	this->mInvObject1 = nullptr;
	this->mPol = nullptr;
	this->mBorderBottom = nullptr;
	this->mBorderTop = nullptr;
	this->mWall = nullptr;
	this->mPotolok = nullptr;
	this->levelNumber = 7;
#if CC_ENABLE_CHIPMUNK_INTEGRATION

	// enable events
	auto touchListener = EventListenerTouchAllAtOnce::create();
    touchListener->onTouchesEnded = CC_CALLBACK_2(Level7TestLayer::onTouchesEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	// init physics
    initPhysics();
	_spriteTexture = Director::getInstance()->getTextureCache()->addImage("door.png");
	scheduleUpdate();
#endif
}
Level7TestLayer::~Level7TestLayer() 
{
	CC_SAFE_RELEASE_NULL(mInvObject1);
	CC_SAFE_RELEASE_NULL(mPol);
	CC_SAFE_RELEASE_NULL(mBorderBottom);
	CC_SAFE_RELEASE_NULL(mBorderTop);
	CC_SAFE_RELEASE_NULL(mWall);
	CC_SAFE_RELEASE_NULL(mPotolok);

#if CC_ENABLE_CHIPMUNK_INTEGRATION
    // manually Free rogue shapes
    for( int i=0;i<4;i++) {
        cpShapeFree( _walls[i] );
    }

    cpSpaceFree( _space );

    Device::setAccelerometerEnabled(false);
#endif
}

void Level7TestLayer::onNodeLoaded(Node * node,  NodeLoader * nodeLoader) {
	MainGameLayer::onNodeLoaded(node, nodeLoader);
	setInvGameObjectTouchListener();
	// callbacks for inventory touches
	//inventoryLogicCallback = [this]() { this->item2FuncCallback(); };

	//auto body = PhysicsBody::createCircle(this->mDoor->getContentSize().width / 2);
	//this->mDoor->setPhysicsBody(body);
}

void Level7TestLayer::initPhysics()
{
#if CC_ENABLE_CHIPMUNK_INTEGRATION    
    // init chipmunk
    //cpInitChipmunk();

    _space = cpSpaceNew();

    _space->gravity = cpv(0, -100);

    //
    // rogue shapes
    // We have to free them manually
    //
    // bottom
    _walls[0] = cpSegmentShapeNew( _space->staticBody,
        cpv(VisibleRect::leftBottom().x,VisibleRect::leftBottom().y),
        cpv(VisibleRect::rightBottom().x, VisibleRect::rightBottom().y), 0.0f);

    // top
    _walls[1] = cpSegmentShapeNew( _space->staticBody, 
        cpv(VisibleRect::leftTop().x, VisibleRect::leftTop().y),
        cpv(VisibleRect::rightTop().x, VisibleRect::rightTop().y), 0.0f);

    // left
    _walls[2] = cpSegmentShapeNew( _space->staticBody,
        cpv(VisibleRect::leftBottom().x,VisibleRect::leftBottom().y),
        cpv(VisibleRect::leftTop().x,VisibleRect::leftTop().y), 0.0f);

    // right
    _walls[3] = cpSegmentShapeNew( _space->staticBody, 
        cpv(VisibleRect::rightBottom().x, VisibleRect::rightBottom().y),
        cpv(VisibleRect::rightTop().x, VisibleRect::rightTop().y), 0.0f);

    for( int i=0;i<4;i++) {
        _walls[i]->e = 1.0f;
        _walls[i]->u = 1.0f;
        cpSpaceAddStaticShape(_space, _walls[i] );
    }

    // Physics debug layer
    _debugLayer = PhysicsDebugNode::create(_space);
    this->addChild(_debugLayer, 100);
#endif
}

void Level7TestLayer::update(float delta)
{
    // Should use a fixed size step based on the animation interval.
    int steps = 2;
    float dt = Director::getInstance()->getAnimationInterval()/(float)steps;

    for(int i=0; i<steps; i++){
        cpSpaceStep(_space, dt);
    }
}

void Level7TestLayer::addTarget()
{
    auto actionBy = SkewBy::create(2, 0.0f, -90.0f);
    auto actionByBack = actionBy->reverse();
	auto actionMoveDone = CallFuncN::create( this, 
        callfuncN_selector(Level7TestLayer::spriteMoveFinished));

	this->mDoor->runAction( Sequence::create(actionBy, actionMoveDone, NULL));
}

void Level7TestLayer::spriteMoveFinished(Node* sender)
{
	this->mDoor->setVisible(false);
}

void Level7TestLayer::onEnter()
{
    Layer::onEnter();
}

void Level7TestLayer::onTouchesEnded(const std::vector<Touch*>& touches, Event* event)
{
    //Add a new body/atlas sprite at the touched location

    for( auto &touch: touches)
    {
        auto location = touch->getLocation();
    }
}

/**
*	Assigh sprite member from ccbi file
**/
bool Level7TestLayer::onAssignCCBMemberVariable(Ref * pTarget, const char * pMemberVariableName, Node * pNode) {
	MainGameLayer::onAssignCCBMemberVariable(pTarget, pMemberVariableName, pNode);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mInvObject1", Sprite *, this->mInvObject1);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "pol", Sprite *, this->mPol);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "borderBottom", Sprite *, this->mBorderBottom);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "borderTop", Sprite *, this->mBorderTop);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "potolok", Sprite *, this->mPotolok);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "wall", Sprite *, this->mWall);
    return false;
}

#pragma mark Inventory Items Callback Logic

#pragma mark Game Objects Touch Logic

void Level7TestLayer::setInvGameObjectTouchListener()
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

void Level7TestLayer::setGameObjectTouchListener()
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

void Level7TestLayer::gameInvObject1FuncCallback()
{
	if(this->invItem1Index != -1)
		this->itemsSpriteArray[this->invItem1Index]->setTexture(TextureCache::getInstance()->addImage("item_key_sel.png"));
	
	log("sprite vector:%d",itemsSpriteArray.size());
	
	this->isInvItem1Selected = true;
	this->isOpenDoor = true;
}

void Level7TestLayer::gameInvObjToGameObj()
{
	
}