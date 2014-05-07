#ifndef __Level3Layer__
#define __Level3Layer__

#include "../../MainGame/MainGameLayer.h"

class Level3Layer : public MainGameLayer
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(Level3Layer, create);
	virtual void onNodeLoaded(cocos2d::Node * node, cocosbuilder::NodeLoader * nodeLoader);
	virtual bool onAssignCCBMemberVariable(cocos2d::Ref * pTarget, const char * pMemberVariableName, cocos2d::Node * node);
	//virtual bool init();

	void onAcceleration(cocos2d::Acceleration* acc, cocos2d::Event* event);
	virtual void onEnter() override;

	Level3Layer();
	virtual ~Level3Layer();

 	void setInvGameObjectTouchListener();
 	void setGameObjectTouchListener();

	void gameInvObject1FuncCallback();
	void gameInvObjToGameObj();

protected:
	cocos2d::Sprite* _ball;
    double _lastTime;
	cocos2d::Sprite* mInvObject1;
};
#endif