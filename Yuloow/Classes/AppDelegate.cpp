//
//  YuloowAppDelegate.cpp
//  Yuloow
//
//  Created by luyifan on 13-11-13.
//  Copyright __MyCompanyName__ 2013年. All rights reserved.
//

#include "AppDelegate.h"

#include "cocos2d.h"
#include "MenuLayer.h"
USING_NS_CC;

AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();
    
    pDirector->setOpenGLView(pEGLView);
    
    CCSize screenSize = pEGLView->getFrameSize();
    CCSize designSize = CCSize(2048, 1536);
    
    CCLOG(" cocos = %d" , (int)screenSize.height );
    CCEGLView::sharedOpenGLView()->setDesignResolutionSize( screenSize.width , screenSize.height ,kResolutionExactFit );

    pDirector->setContentScaleFactor(designSize.height/screenSize.height );
   
    SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic( CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("background.mp3"));
    SimpleAudioEngine::sharedEngine()->preloadEffect( CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("button.wav") );
    SimpleAudioEngine::sharedEngine()->preloadEffect( CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("EatingChocolate.wav"));
    SimpleAudioEngine::sharedEngine()->preloadEffect( CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("Explosion.wav"));
    SimpleAudioEngine::sharedEngine()->preloadEffect( CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("Fruit.wav")) ;
    SimpleAudioEngine::sharedEngine()->preloadEffect( CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("WearRocket.wav"));
    SimpleAudioEngine::sharedEngine()->preloadEffect( CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("Pill.wav"));
    SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.5f);
    SimpleAudioEngine::sharedEngine()->setEffectsVolume(0.6f);
    
    // turn on display FPS
    //pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this  
    pDirector->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    CCScene * pScene = MenuLayer::scene();
    // run
    pDirector->runWithScene( pScene );

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->pause();

    // if you use SimpleAudioEngine, it must be paused
     SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->resume();
    
    // if you use SimpleAudioEngine, it must resume here
     SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
