#include "AppDelegate.h"
#include "MainMenu/MainMenuLoader.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
		glview = GLView::createWithRect("Escape Room", Rect(0,0,640,960)); // for windows
		//glview = GLView::create("Escape Room");
        director->setOpenGLView(glview);
    }

	Size designSize = CCSizeMake(640, 960);
    Size resourceSize = CCSizeMake(640, 960);
	Size screenSize = glview->getFrameSize();
	
	std::vector<std::string> resDirOrders;
	std::vector<std::string> searchPaths;

	TargetPlatform platform = Application::sharedApplication()->getTargetPlatform();
	if (platform == kTargetIphone || platform == kTargetIpad)
    {
		searchPaths = FileUtils::sharedFileUtils()->getSearchPaths();
		searchPaths.insert(searchPaths.begin(), "Published-iOS"); // Resources/Published-iOS
		FileUtils::sharedFileUtils()->setSearchPaths(searchPaths);
        if (screenSize.width > 768)
        {
            resourceSize = CCSizeMake(1536, 2048);
            resDirOrders.push_back("resources-ipadhd");
        }
        else if (screenSize.width > 640)
        {
            resourceSize = CCSizeMake(768, 1536);
            resDirOrders.push_back("resources-ipad");
        }else if (screenSize.width > 480)
        {
            resourceSize = CCSizeMake(640, 960);
            resDirOrders.push_back("resources-iphonehd");
        }
        else
        {
            resDirOrders.push_back("resources-iphone");
        }
		FileUtils::sharedFileUtils()->setSearchResolutionsOrder(resDirOrders);
		
	}
	else if (platform == kTargetAndroid || platform == kTargetWindows)
	{
		searchPaths = FileUtils::sharedFileUtils()->getSearchPaths();
		searchPaths.insert(searchPaths.begin(), "Published-Android"); // Resources/Published-Android
		FileUtils::sharedFileUtils()->setSearchPaths(searchPaths);
		if (screenSize.height > 960)
		{
			resourceSize = CCSizeMake(640, 960);
			resDirOrders.push_back("resources-large");
		}
		else if (screenSize.height > 480)
		{
			resourceSize = CCSizeMake(480, 720);
			resDirOrders.push_back("resources-medium");
		}
		else
		{
			resourceSize = CCSizeMake(320, 568);
			resDirOrders.push_back("resources-small");
		}

		FileUtils::sharedFileUtils()->setSearchResolutionsOrder(resDirOrders);
	}

	//FileUtils::sharedFileUtils()->setSearchResolutionsOrder(resDirOrders);
	
	director->setContentScaleFactor(resourceSize.width/designSize.width);
	glview->setDesignResolutionSize(designSize.width, designSize.height, ResolutionPolicy::FIXED_WIDTH);
    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    auto scene = MainMenuLoader::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
