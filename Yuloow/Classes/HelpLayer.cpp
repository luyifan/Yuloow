//
//  HelpLayer.cpp
//  Yuloow
//
//  Created by luyifan on 13-11-17.
//
//

#include "HelpLayer.h"
HelpLayer::HelpLayer()
{
    
}
HelpLayer::~HelpLayer()
{
    
}
CCScene * HelpLayer::scene()
{
    CCScene * scene = CCScene::create() ;
    HelpLayer * layer = HelpLayer::create();
    scene->addChild( layer ) ;
    return scene ;

    
}
bool HelpLayer::init()
{
    if ( !CCLayer::init())
        return false ;
    _screenSize = CCDirector::sharedDirector()->getWinSize();
    
    createGameScreen ( ) ;
    
    
    return true ;
}

void HelpLayer::update(float dt)
{
    
}

void HelpLayer::createGameScreen()
{
    CCSprite * bg = CCSprite::create("bg.png") ;
    bg->setPosition( ccp ( _screenSize.width * 0.5 , _screenSize.height * 0.5 )) ;
    this->addChild( bg ) ;
    CCSprite * rect ;
    rect = CCSprite::create ( "blank.png" ) ;
    rect->setTextureRect( CCRectMake( 0, 0, 512 , 512 ));
    rect->setPosition( ccp( _screenSize.width * 0.5 , _screenSize.height * 0.5 )) ;
    rect->setOpacity( 50 ) ;
    this->addChild( rect ) ;
    
    
}

