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
	inventoryLogicCallback = [this]() { this->item2FuncCallback(); };
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
	
}