#ifndef __Level8Layer__
#define __Level8Layer__

#include "../../MainGame/MainGameLayer.h"

class Level8Layer : public MainGameLayer
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(Level8Layer, create);
	virtual void onNodeLoaded(cocos2d::Node * node, cocosbuilder::NodeLoader * nodeLoader);
	//virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(Ref * pTarget, const char* pSelectorName);
	//virtual cocos2d::extension::Control::Handler onResolveCCBCCControlSelector(Ref * pTarget, const char* pSelectorName);
	virtual bool onAssignCCBMemberVariable(cocos2d::Ref * pTarget, const char * pMemberVariableName, cocos2d::Node * node);
	//virtual bool init();

	Level8Layer();
	virtual ~Level8Layer();

 	void setInvGameObjectTouchListener();
 	void setGameObjectTouchListener();

	void gameInvObject1FuncCallback();
	void gameInvObjToGameObj();

protected:
	bool isSwitchOn;
	int switchOnCount;

	cocos2d::Sprite * mInvObject1;
	cocos2d::Sprite * mSwitch;
	cocos2d::Sprite * mPol;
};
#endif