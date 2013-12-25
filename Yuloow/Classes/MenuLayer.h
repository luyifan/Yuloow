//
//  MenuLayer.h
//  Yuloow
//
//  Created by luyifan on 13-11-17.
//
//

#ifndef __Yuloow__MenuLayer__
#define __Yuloow__MenuLayer__
#include "cocos2d.h"
#include "SimpleAudioEngine.h" 

USING_NS_CC ;
using namespace CocosDenshion ;

class MenuLayer : public CCLayer
{
private:
    CCSpriteBatchNode * _layerBatchNode ;
    CCMenu * _mainMenu ;
    
    //CCParticleSystem * _snow ;
    CCSize _screenSize ;
    
    
    
    void createScreen ( );

public:
    ~MenuLayer ();
    MenuLayer();
    
    static CCScene * scene ( );
    
    virtual bool init();
    
    
    
    CREATE_FUNC( MenuLayer );
    
    void showJieji ( ) ;
    void showChan ( ) ;
    void showHelp ( ) ;
    void quitGame ( CCObject * pSender ) ;
    void quitGame ( ) ;

    
    
    
};


#endif /* defined(__Yuloow__MenuLayer__) */
