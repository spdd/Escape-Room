#ifndef _MainGameLayer_h
#define _MainGameLayer_h

#define COCOS2D_DEBUG 1

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "cocosbuilder/CocosBuilder.h"

class MainGameLayer : 
	public cocos2d::Layer,
    public cocosbuilder::CCBSelectorResolver,
    public cocosbuilder::NodeLoaderListener
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(MainGameLayer, create);

	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(Ref * pTarget, const char* pSelectorName);
	virtual cocos2d::extension::Control::Handler onResolveCCBCCControlSelector(Ref * pTarget, const char* pSelectorName);
	virtual void onNodeLoaded(cocos2d::Node * node, cocosbuilder::NodeLoader * nodeLoader);
	void tappedPlayButton(Ref * pTarget, cocos2d::extension::Control::EventType pControlEventType);
	void onMenuItemAClicked(cocos2d::Ref * sender);
	MainGameLayer();
	virtual ~MainGameLayer();

	virtual bool init();
	virtual void onEnterTransitionDidFinish();
};

#endif