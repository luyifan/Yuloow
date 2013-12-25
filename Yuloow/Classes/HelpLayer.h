//
//  HelpLayer.h
//  Yuloow
//
//  Created by luyifan on 13-11-17.
//
//

#ifndef __Yuloow__HelpLayer__
#define __Yuloow__HelpLayer__
#include "cocos2d.h"

USING_NS_CC;

class HelpLayer : public CCLayer
{
    void createGameScreen ( void ) ;
public:
    CCSize _screenSize ;
    ~HelpLayer ();
    HelpLayer();
    
    static CCScene * scene ( );
    
    virtual bool init();
    
    void update ( float dt );
    
    
    CREATE_FUNC( HelpLayer );

    
};


#endif /* defined(__Yuloow__HelpLayer__) */
