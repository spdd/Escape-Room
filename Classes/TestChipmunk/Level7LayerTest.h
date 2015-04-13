#ifndef __Level7LayerTest__
#define __Level7LayerTest__

#include "../MainGame/MainGameLayer.h"
#include "chipmunk.h"

class Level7TestLayer : public MainGameLayer
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(Level7TestLayer, create);
	virtual void onNodeLoaded(cocos2d::Node * node, cocosbuilder::NodeLoader * nodeLoader);
	//virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(Ref * pTarget, const char* pSelectorName);
	//virtual cocos2d::extension::Control::Handler onResolveCCBCCControlSelector(Ref * pTarget, const char* pSelectorName);
	virtual bool onAssignCCBMemberVariable(cocos2d::Ref * pTarget, const char * pMemberVariableName, cocos2d::Node * node);
	//virtual bool init();

	Level7TestLayer();
	virtual ~Level7TestLayer();

 	void setInvGameObjectTouchListener();
 	void setGameObjectTouchListener();

	void gameInvObject1FuncCallback();
	void gameInvObjToGameObj();

	void onEnter();
    void initPhysics();
	void reset(cocos2d::Ref* sender);
	void update(float dt);
	void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);

	void addTarget();
	void spriteMoveFinished(cocos2d::Node* sender);
protected:
	cocos2d::Sprite * mInvObject1;

	cocos2d::Sprite * mPol;
	cocos2d::Sprite * mBorderBottom;
	cocos2d::Sprite * mWall;
	cocos2d::Sprite * mBorderTop;
	cocos2d::Sprite * mPotolok;
private:
    cocos2d::Texture2D* _spriteTexture; // weak ref
#if CC_ENABLE_CHIPMUNK_INTEGRATION    
    cocos2d::extension::PhysicsDebugNode* _debugLayer; // weak ref
#endif
    cpSpace* _space; // strong ref
    cpShape* _walls[4];
};
#endif