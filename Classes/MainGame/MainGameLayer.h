#ifndef _MainGameLayer_h
#define _MainGameLayer_h

#define COCOS2D_DEBUG 1

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "cocosbuilder/CocosBuilder.h"

class MainGameLayer : 
	public cocos2d::Layer,
	public cocosbuilder::CCBMemberVariableAssigner,
    public cocosbuilder::CCBSelectorResolver,
	public cocosbuilder::NodeLoaderListener
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(MainGameLayer, create);

	bool isOpenDoor;
	int levelNumber;

	void openScene(const char * pCCBFileName, const char * nodeName = NULL, cocosbuilder::NodeLoader * nodeLoader = NULL);
	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(Ref * pTarget, const char* pSelectorName);
	virtual cocos2d::extension::Control::Handler onResolveCCBCCControlSelector(Ref * pTarget, const char* pSelectorName);
	virtual bool onAssignCCBMemberVariable(cocos2d::Ref * pTarget, const char * pMemberVariableName, cocos2d::Node * node);
	virtual void onNodeLoaded(cocos2d::Node * node, cocosbuilder::NodeLoader * nodeLoader);
    //virtual bool onAssignCCBCustomProperty(Ref* pTarget, const char* pMemberVariableName, const cocos2d::Value& pCCBValue);
	void tappedPlayButton(Ref * pTarget, cocos2d::extension::Control::EventType pControlEventType);
	void onMenuItemAClicked(cocos2d::Ref * sender);
	MainGameLayer();
	virtual ~MainGameLayer();

	//void onTouchesEnded(const std::vector<Touch*>& touches, Event* event);
    //virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	//virtual void onEnter() override;

	//virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
    //virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event);
    //virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);
    //virtual void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *event);

	virtual bool init();
	virtual void onEnterTransitionDidFinish();

private:
	// callback function pointer for inventar click logic
	typedef void (*InventarCallbackFunc)();
	InventarCallbackFunc inventar1CBFunc;
	InventarCallbackFunc inventar2CBFunc;
	InventarCallbackFunc inventar3CBFunc;
	InventarCallbackFunc inventar4CBFunc;
	InventarCallbackFunc inventar5CBFunc;

	void setInventar1CallBackFunction(InventarCallbackFunc func);
	void setInventar2CallBackFunction(InventarCallbackFunc func);
	void setInventar3CallBackFunction(InventarCallbackFunc func);
	void setInventar4CallBackFunction(InventarCallbackFunc func);
	void setInventar5CallBackFunction(InventarCallbackFunc func);

	cocos2d::Sprite * mDoor;
	cocos2d::Sprite * mInvItem1;
    cocos2d::Sprite * mInvItem2;
	cocos2d::Sprite * mInvItem3;
    cocos2d::Sprite * mInvItem4;
    cocos2d::Sprite * mInvItem5;

	void setDoorTouchListener();
	void setInventarItemsTouchListener();
};

#endif