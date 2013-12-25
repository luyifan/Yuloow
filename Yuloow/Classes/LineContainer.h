//
//  LineContainer.h
//  Yuloow
//
//  Created by luyifan on 13-11-22.
//
//

#ifndef __Yuloow__LineContainer__
#define __Yuloow__LineContainer__

#include "cocos2d.h"

USING_NS_CC ;
class LineContainer : public CCNode {
public:
    CC_SYNTHESIZE( float , _lineLength , LineLength );
    CC_SYNTHESIZE( float , _energy , Energy ) ;
    LineContainer ( ) ;
    static LineContainer * create() ;
    
    virtual void draw ( ) ;
    void update ( float dt ) ;
    void reset ( );
    void setEnergyDecrement ( float value ) ;
    void addEnergy ( float value ) ;
private:
    CCSize _screenSize ;
    float _energyHeight ;
    float _energyLineX ;
    float _energyDecrement ;
};

#endif /* defined(__Yuloow__LineContainer__) */
