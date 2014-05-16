#ifndef __Level7Layer__
#define __Level7Layer__

#include "../../MainGame/MainGameLayer.h"

class Level7Layer : public MainGameLayer
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(Level7Layer, create);
	virtual void onNodeLoaded(cocos2d::Node * node, cocosbuilder::NodeLoader * nodeLoader);
	//virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(Ref * pTarget, const char* pSelectorName);
	//virtual cocos2d::extension::Control::Handler onResolveCCBCCControlSelector(Ref * pTarget, const char* pSelectorName);
	virtual bool onAssignCCBMemberVariable(cocos2d::Ref * pTarget, const char * pMemberVariableName, cocos2d::Node * node);
	//virtual bool init();

	Level7Layer();
	virtual ~Level7Layer();

 	void setInvGameObjectTouchListener();
 	void setGameObjectTouchListener();

	void gameInvObject1FuncCallback();
	void gameInvObjToGameObj();

	void onEnter();
protected:
	cocos2d::Sprite * mInvObject1;

	cocos2d::Sprite * mShkaf;
};
#endif