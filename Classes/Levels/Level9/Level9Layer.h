#ifndef __Level9Layer__
#define __Level9Layer__

#include "../../MainGame/MainGameLayer.h"

class Level9Layer : public MainGameLayer
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(Level9Layer, create);
	virtual void onNodeLoaded(cocos2d::Node * node, cocosbuilder::NodeLoader * nodeLoader);
	virtual bool onAssignCCBMemberVariable(cocos2d::Ref * pTarget, const char * pMemberVariableName, cocos2d::Node * node);
	//virtual bool init();

	Level9Layer();
	virtual ~Level9Layer();

 	void setInvGameObjectTouchListener();
 	void setGameObjectTouchListener();

	void gameInvObject1FuncCallback();
	void gameInvObjToGameObj();

protected:
	cocos2d::Sprite * mInvObject1;

	bool runBackMove;
	float rotateCount1;
	float rotateCount2;
	float rotateCount3;
	float rotateCount4;
	cocos2d::Sprite * mBackButton;
	cocos2d::Sprite * mBack1;
	cocos2d::Sprite * mBack2;
	cocos2d::Sprite * mBack3;
	cocos2d::Sprite * mBack4;
};
#endif