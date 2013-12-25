//
//  MenuLayer.cpp
//  Yuloow
//
//  Created by luyifan on 13-11-17.
//
//

#include "MenuLayer.h"
#include "GameConfig.h"
//#include "JiejiLayer.h"
#include "ChanLayer.h" 
#include "HelpLayer.h"
#include "GameConfig.h"
#include "LoadingJieji.h"
#include "LoadingChan.h"
MenuLayer::MenuLayer()
{
    
}
MenuLayer::~MenuLayer()
{
    
}
CCScene * MenuLayer::scene()
{
    CCScene * scene = CCScene::create();
    MenuLayer * layer = MenuLayer::create();
    
    scene->addChild ( layer ) ;
    
    return scene ;
}

bool MenuLayer::init()
{
    if ( !CCLayer::init())
        return false;
    _screenSize = CCDirector::sharedDirector()->getWinSize();
    
    
    createScreen() ;
    
    setTouchEnabled( true );
    scheduleUpdate();
    SimpleAudioEngine::sharedEngine()->playBackgroundMusic(CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("background.mp3"), true);
    
    return true;
}


void MenuLayer::createScreen()
{
    
    CCSprite * bg = CCSprite::create("bg.png");
    bg->setPosition( ccp ( _screenSize.width*0.5 , _screenSize.height*0.5));
    this->addChild( bg , kBackground ) ;
    /*
    CCSprite * logo = CCSprite::create("logo.png");
    logo->setPosition( ccp ( logo->boundingBox().size.width * 0.5 , logo->boundingBox().size.height * 0.5 )) ;
    this->addChild( logo , kForeground ) ;
    */
    CCSprite * logo = CCSprite::create("logo.png");
    logo->setPosition( ccp ( _screenSize.width * 0.5 , _screenSize.height * 0.8 )) ;
    this->addChild( logo , kForeground ) ;
    
    //load Particle System
    /*
    _snow = CCParticleSystemQuad::create("snow.plist");
    _snow->setPosition( ccp ( _screenSize.width*0.5 , _screenSize.height)) ;
    this->addChild( _snow , kBackground ) ;
    */
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("sprite_sheet.plist");
    _layerBatchNode = CCSpriteBatchNode::create("sprite_sheet.png" , 50 );
    this->addChild( _layerBatchNode , kMiddleground ) ;
    
    
    
    
    
    CCSprite * menuItemOn ;
    CCSprite * menuItemOff ;
    
    
    menuItemOn = CCSprite::createWithSpriteFrameName("jieji_on.png");
    menuItemOff = CCSprite::createWithSpriteFrameName("jieji_off.png");
  
    
   
    CCMenuItemSprite * jiejiPlayItem = CCMenuItemSprite::create( menuItemOff ,
                                                                menuItemOn ,
                                                                this ,
                                                                menu_selector( MenuLayer::showJieji) );
    menuItemOn = CCSprite::createWithSpriteFrameName("chan_on.png");
    menuItemOff = CCSprite::createWithSpriteFrameName("chan_off.png");
    
    
    CCMenuItemSprite * chanPlayItem = CCMenuItemSprite::create( menuItemOff ,
                                                               menuItemOn ,
                                                               this,
                                                               menu_selector( MenuLayer::showChan ));
                                                               
    /*
    menuItemOn = CCSprite::createWithSpriteFrameName("help_on.png");
    menuItemOff = CCSprite::createWithSpriteFrameName("help_off.png");
    
    CCMenuItemSprite * helpItem = CCMenuItemSprite::create(
                                                           menuItemOff,
                                                           menuItemOn,
                                                           this,
                                                           menu_selector(MenuLayer::showHelp));
    */
    menuItemOn = CCSprite::createWithSpriteFrameName("quitgame_on.png");
    menuItemOff = CCSprite::createWithSpriteFrameName("quitgame_off.png");
    
    CCMenuItemSprite * quitItem = CCMenuItemSprite::create( menuItemOff ,
                                                           menuItemOn ,
                                                           this ,
                                                           menu_selector(MenuLayer::quitGame));
    _mainMenu = CCMenu::create( jiejiPlayItem , chanPlayItem , /*helpItem , */ quitItem ,NULL) ;
    _mainMenu->alignItemsVertically() ;
    _mainMenu->alignItemsVerticallyWithPadding(10);
    
    
    _mainMenu->setPosition( ccp ( _screenSize.width*0.5 , _screenSize.height*0.64 - logo->boundingBox().size.height )) ;
    this->addChild( _mainMenu , kForeground ) ;
    /*
    CCSprite * sprite = CCSprite::create("StopGameScreen.png") ;
    sprite->setPosition ( ccp( _screenSize.width * 0.5 , _screenSize.height * 0.5 )) ;
    this->addChild( sprite , kForeground ) ;
    CCLabelTTF * label = CCLabelTTF::create("Your Score","Marker Felt", sprite->boundingBox().size.height * 0.3 ) ;
    sprite->addChild( label , kForeground ) ;
    label->setAnchorPoint( ccp ( 0.5 , 0.5 )) ;
    label->setColor( ccc3 ( 0 , 0 , 0 )) ;
    label->setPosition( ccp( sprite->boundingBox().size.width * 0.5 , sprite->boundingBox().size.height - label->boundingBox().size.height * 0.6 ) );
    CCLabelTTF * scoreDisplay = CCLabelTTF::create("0","Marker Felt", sprite->boundingBox().size.height * 0.3 ) ;
    scoreDisplay->setAnchorPoint( ccp ( 0.5 , 0.5 )) ;
    scoreDisplay->setColor( ccc3 ( 255 , 0 , 0 )) ;
    scoreDisplay->setPosition( ccp ( sprite->boundingBox().size.width * 0.5 , sprite->boundingBox().size.height - label->boundingBox().size.height * 1.4 ));
    sprite->addChild( scoreDisplay ) ;
    menuItemOn = CCSprite::create("Quit.png");
    menuItemOff = CCSprite::create("Restart.png");
    CCMenuItemSprite * quitJieji = CCMenuItemSprite::create(
                                                           menuItemOff,
                                                           menuItemOn,
                                                           this,
                                                           menu_selector(MenuLayer::showHelp));
    menuItemOn = CCSprite::create("Restart.png");
    menuItemOff = CCSprite::create("Quit.png");
    
    CCMenuItemSprite * restartJieji = CCMenuItemSprite::create(
                                                           menuItemOff,
                                                           menuItemOn,
                                                           this,
                                                           menu_selector(MenuLayer::showHelp));
    CCMenu * _jiejiGameOver = CCMenu::create( quitJieji , restartJieji , NULL ) ;
    _jiejiGameOver->alignItemsHorizontally() ;
    _jiejiGameOver->alignItemsHorizontallyWithPadding( 30 ) ;
    sprite->addChild( _jiejiGameOver , kForeground ) ;
    _jiejiGameOver->setPosition( ccp ( sprite->boundingBox().size.width* 0.5 , restartJieji->boundingBox().size.height  )) ;
    */
    /*
    CCSprite * sprite = CCSprite::createWithSpriteFrameName("PauseJieji.png") ;
    sprite->setPosition ( ccp( _screenSize.width * 0.5 , _screenSize.height * 0.5 )) ;
    this->addChild( sprite , kBackground ) ;
    */
    /*
    CCMenuItemSprite * restartJieji = CCMenuItemSprite::create(
                                                           menuItemOff,
                                                           menuItemOn,
                                                           this,
                                                           menu_selector(MenuLayer::showHelp));
    CCMenu * _jiejiGameOver = CCMenu::create( quitJieji , restartJieji , NULL ) ;
    _jiejiGameOver->alignItemsHorizontally() ;
    _jiejiGameOver->alignItemsHorizontallyWithPadding( 30 ) ;
    sprite->addChild( _jiejiGameOver , kForeground ) ;
    _jiejiGameOver->setPosition( ccp ( sprite->boundingBox().size.width* 0.5 , restartJieji->boundingBox().size.height  )) ;
    */
    /*
    CCSprite * sprite = CCSprite::createWithSpriteFrameName("PauseJieji.png") ;
    sprite->setPosition ( ccp( _screenSize.width * 0.5 , _screenSize.height * 0.5 )) ;
    this->addChild( sprite , kBackground ) ;
    */
}

void MenuLayer::showJieji()
{
    
    SimpleAudioEngine::sharedEngine()->playEffect("button.wav");
    
    CCScene* newScene = CCTransitionMoveInR::create(0.2f, LoadingJieji::scene());
    CCDirector::sharedDirector()->replaceScene(newScene);

}
void MenuLayer::showHelp()
{
    SimpleAudioEngine::sharedEngine()->playEffect("button.wav");
    CCScene* newScene = CCTransitionMoveInR::create(0.2f, HelpLayer::scene());
    CCDirector::sharedDirector()->replaceScene(newScene);
}
void MenuLayer::showChan()
{
    SimpleAudioEngine::sharedEngine()->playEffect("button.wav");
    CCScene* newScene = CCTransitionMoveInR::create(0.2f, LoadingChan::scene());
    CCDirector::sharedDirector()->replaceScene(newScene);
    
}
void MenuLayer::quitGame(CCObject* pSender)
{
    SimpleAudioEngine::sharedEngine()->playEffect("button.wav");
    CCDirector::sharedDirector()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif

    
}
void MenuLayer::quitGame()
{
    
}