#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "Game.h"
#include "GameMenu.h"
#include "State.h"

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

    auto designSize = Size(640, 1136);
    if(!glview) {
        //glview = GLView::create("My Game");
        glview = GLView::createWithRect("My Game", Rect(0, 0, designSize.width, designSize.height));
        director->setOpenGLView(glview);
    }

    //auto screenSize = EGLView::getInstance()->getFrameSize();
    glview->setDesignResolutionSize(designSize.width, designSize.height, ResolutionPolicy::FIXED_WIDTH);
	
    // turn on display FPS
    director->setDisplayStats(true);

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    auto scene = Scene::create();

    scene->addChild(GameMenu::create());

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
