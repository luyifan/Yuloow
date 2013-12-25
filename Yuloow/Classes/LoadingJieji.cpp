//
//  LoadingJieji.cpp
//  Yuloow
//
//  Created by luyifan on 13-12-17.
//
//

#include "LoadingJieji.h"
#include "JiejiLayer.h"
#include "GameConfig.h"
LoadingJieji::LoadingJieji ( )
{
    
}
LoadingJieji::~LoadingJieji()
{
    
}
CCScene * LoadingJieji::scene()
{
    CCScene * scene = CCScene::create();
    LoadingJieji * layer = LoadingJieji::create() ;
    scene->addChild( layer ) ;
    return scene ;
}
bool LoadingJieji::init( )
{
    if ( !CCLayer::init() )
        return false ;
    _screenSize = CCDirector::sharedDirector()->getWinSize() ;
    createScreen(  ) ;
    return true ;
    
}
void LoadingJieji::createScreen()
{
    //need a logo
    //CCSprite * titleBg = CCSprite::create("loading_title.png");
    //titleBg->setPosition( ccp ( _screenSize.width * 0.5 , _screenSize.height * 0.5 )) ;
    //this->addChild( titleBg , 1 ) ;
    // background of loading
    CCSprite * logo = CCSprite::create("logo.png");
    logo->setPosition( ccp ( _screenSize.width * 0.5 , _screenSize.height * 0.6 )) ;
    logo->setScale( 1.2 ) ;
    this->addChild( logo , kForeground ) ;
    
    CCSprite * load1Background = CCSprite::create("loading_1_1.png");
    load1Background->setPosition(ccp ( _screenSize.width * 0.5 , _screenSize.height * 0.2 )) ;
    this->addChild( load1Background , 1 ) ;
    CCSprite * load2Background = CCSprite::create("loading_2_1.png");
    load2Background->setPosition(ccp ( _screenSize.width * 0.5 , _screenSize.height * 0.1 )) ;
    this->addChild( load2Background , 1 ) ;
    
    /// foreground of loading
    CCSprite * load1Foreground = CCSprite::create("loading_1_2.png");
    CCProgressTimer * timer1 = CCProgressTimer::create ( load1Foreground ) ;
    
    CCAction * timeAction1 = CCSequence::create( CCProgressTo::create( 3 , 100 ) , NULL ) ;
    
    timer1->setType(kCCProgressTimerTypeBar) ;
    timer1->setMidpoint( ccp ( 0 , 0 ) ) ;
    timer1->setBarChangeRate( ccp ( 1, 0 ) ) ;
    timer1->setPosition( ccp ( _screenSize.width * 0.5 , _screenSize.height * 0.2 )) ;
    timer1->runAction( timeAction1 ) ;
    this->addChild( timer1 , 2 ) ;
    
    CCSprite * load2Foregound = CCSprite::create("loading_2_2.png");
    CCProgressTimer * timer2 = CCProgressTimer::create( load2Foregound ) ;
    
    CCAction * timeAction2 = CCSequence::create ( CCProgressTo::create( 3 , 100 ) ,
                                                 CCCallFuncN::create ( this , callfuncN_selector( LoadingJieji::gameStart )) , NULL );
    
    timer2->setType(kCCProgressTimerTypeBar);
    timer2->setMidpoint( ccp ( 0 , 0 )) ;
    timer2->setBarChangeRate( ccp ( 1 , 0 )) ;
    timer2->setPosition( ccp ( _screenSize.width * 0.5 , _screenSize.height * 0.1 )) ;
    timer2->runAction( timeAction2 ) ;
    this->addChild( timer2 , 2 ) ;
    
}
void LoadingJieji::gameStart()
{
    CCScene* newScene = CCTransitionMoveInR::create(0.2f, JiejiLayer::scene() );
    CCDirector::sharedDirector()->replaceScene(newScene);

}