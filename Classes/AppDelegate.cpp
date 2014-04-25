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
		glview = GLView::createWithRect("Escape Room", Rect(0,0, 640, 960)); // for windows
		//glview = GLView::create("Escape Room");
        director->setOpenGLView(glview);
    }

	Size designSize = Size(320,480);
    Size resourceSize = Size(640,960);
	Size screenSize = glview->getFrameSize();
	
	std::vector<std::string> resDirOrders;
	std::vector<std::string> searchPaths;

	Platform platform = Application::getInstance()->getTargetPlatform();
	if (platform == Platform::OS_IPHONE || platform == Platform::OS_IPAD)
    {
		searchPaths = FileUtils::getInstance()->getSearchPaths();
		searchPaths.insert(searchPaths.begin(), "Published-iOS"); // Resources/Published-iOS
		FileUtils::getInstance()->setSearchPaths(searchPaths);
        if (screenSize.width > 768)
        {
            resourceSize = Size(1536, 2048);
            resDirOrders.push_back("resources-ipadhd");
        }
        else if (screenSize.width > 640)
        {
            resourceSize = Size(768, 1024);
            resDirOrders.push_back("resources-ipad");
        }else if (screenSize.width > 480)
        {
            resourceSize = Size(640, 960);
            resDirOrders.push_back("resources-iphonehd");
        }
        else
        {
            resDirOrders.push_back("resources-iphone");
        }
		FileUtils::getInstance()->setSearchResolutionsOrder(resDirOrders);
		
	}
	else if (platform == Platform::OS_ANDROID || platform == Platform::OS_WINDOWS)
	{
		searchPaths = FileUtils::getInstance()->getSearchPaths();
		searchPaths.insert(searchPaths.begin(), "Published-Android"); // Resources/Published-Android
		FileUtils::getInstance()->setSearchPaths(searchPaths);

		resourceSize = Size(640, 960);
		resDirOrders.push_back("resources-large");

		float kDeviceH = screenSize.height/screenSize.width;

		if (screenSize.width <= 640 && kDeviceH >= 2.0)
			resDirOrders.push_back("resources-wall-large");
		else if(screenSize.width <= 640)
			resDirOrders.push_back("resources-wall-medium");
		else
			resDirOrders.push_back("resources-wall-small");

		/*
		if (screenSize.height >= 960)
		{
			resourceSize = Size(640, 960);
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
		*/

		FileUtils::getInstance()->setSearchResolutionsOrder(resDirOrders);
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
