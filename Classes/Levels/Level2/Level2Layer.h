#ifndef __Level2Layer__
#define __Level2Layer__

#include "../../MainGame/MainGameLayer.h"

class Level2Layer : public MainGameLayer
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(Level2Layer, create);
	virtual void onNodeLoaded(cocos2d::Node * node, cocosbuilder::NodeLoader * nodeLoader);
	//virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(Ref * pTarget, const char* pSelectorName);
	//virtual cocos2d::extension::Control::Handler onResolveCCBCCControlSelector(Ref * pTarget, const char* pSelectorName);
	virtual bool onAssignCCBMemberVariable(cocos2d::Ref * pTarget, const char * pMemberVariableName, cocos2d::Node * node);
	//virtual bool init();

	Level2Layer();
	virtual ~Level2Layer();

 	void setInvGameObjectTouchListener();
 	void setGameObjectTouchListener();

	void gameInvObject1FuncCallback();
	void gameInvObjToGameObj();

protected:
	cocos2d::Sprite * mInvObject1;
};
#endif