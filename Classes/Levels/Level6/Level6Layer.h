#ifndef __Level6Layer__
#define __Level6Layer__

#include "../../MainGame/MainGameLayer.h"

class Level6Layer : public MainGameLayer
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(Level6Layer, create);
	virtual void onNodeLoaded(cocos2d::Node * node, cocosbuilder::NodeLoader * nodeLoader);
	//virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(Ref * pTarget, const char* pSelectorName);
	//virtual cocos2d::extension::Control::Handler onResolveCCBCCControlSelector(Ref * pTarget, const char* pSelectorName);
	virtual bool onAssignCCBMemberVariable(cocos2d::Ref * pTarget, const char * pMemberVariableName, cocos2d::Node * node);
	//virtual bool init();

	void onAcceleration(cocos2d::Acceleration* acc, cocos2d::Event* event);
	virtual void onEnter() override;

	Level6Layer();
	virtual ~Level6Layer();

 	void setInvGameObjectTouchListener();
 	void setGameObjectTouchListener();

	void gameInvObject1FuncCallback();
	void gameInvObjToGameObj();

	void checkAnim(float dt);

protected:
	int vibroCount;
	void doorEffect();

	cocos2d::Sprite * mDoor2;
	cocos2d::Sprite * mInvObject1;
	cocos2d::NodeGrid* _gridNodeTarget;

	double _lastTime;
};
#endif