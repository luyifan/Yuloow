//
//  Yuloow.h
//  Yuloow
//
//  Created by luyifan on 13-12-3.
//
//

#ifndef __Yuloow__Yuloow__
#define __Yuloow__Yuloow__
#include "cocos2d.h"
#include "GameConfig.h"
USING_NS_CC;

typedef enum yuloowState
{
    kNormal ,
    //other food
    kGrapeColor ,
    kAppleColor ,
    kStrawberryColor ,
    kWatermelonColor ,
    kOrangeColor ,
    
    //pill function
    kNude ,
    //rocket function
    kFly ,
    //energy become low
    kWearSkirt ,
    //bomb
    kScorch
}YuloowState;

class Yuloow : public CCSprite
{
private:
    CCSize _screenSize ;
    YuloowState _yuloowState ;
    //change color time and interval
    float _yuloowChangeTimer ;
    float _yuloowChangeInterval ;
    //nude time and interval
    float _yuloowNudeTimer ;
    float _yuloowNudeInterval ;
    //fly time and interval
    float _yuloowFlyTimer ;
    float _yuloowFlyInterval ;
    //bomb time and interval
    float _yuloowScorchTimer ;
    float _yuloowScorchInterval ;
    
    
public:
    CC_SYNTHESIZE( float , _isComingBack, ComingBack );
    CC_SYNTHESIZE( float , _speed , Speed);
    void changeState ( YuloowState state );
    void resetYuloowScorchTimer ( void ) ;
    Yuloow ( void ) ;
    ~Yuloow ( void ) ;
    static Yuloow * create ( ) ;
    
    void update ( float dt ) ;
    void reset ( void );
    YuloowState getYuloowState ( ) ;
    float getYuloowSpeed ( ) ;
    void  comingFinish ( ) ;
    //bool collidedWithSides ( void ) ;
    
};



#endif /* defined(__Yuloow__Yuloow__) */
