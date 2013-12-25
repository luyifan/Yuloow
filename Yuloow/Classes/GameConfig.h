//
//  GameConfig.h
//  Yuloow
//
//  Created by luyifan on 13-11-17.
//
//

#ifndef __Yuloow__GameConfig__
#define __Yuloow__GameConfig__

enum {
    kBackground,
    kMiddleground,
    kForeground ,
    kBigForeground 
};

enum {
    kGameIntro,
    kGamePlay,
    kGameOver
};




enum {
    kSpriteBlock,
    kSpritePlayer,
    kSpriteSwitch,
    kSpritePlatform,
    kSpriteIgloo,
    kSpriteBtnOn,
    kSpriteBtnOff,
    kSpriteBtnPlay,
    kSpriteBtnPause,
    kSpriteBtnReset,
    kSpriteBtnStart,
    kSpriteBtnMenu,
    kSpriteBtnAgain
};




//define game notifications
//eating pool
#define BANANA_NUM 20
#define HEATBANANA_NUM 2
#define COLDBANANA_NUM 2
#define STRAWBERRY_NUM 10
#define WATERMELON_NUM 10
#define GRAPE_NUM 10
#define ORANGE_NUM 10
#define APPLE_NUM 10
//danger pool
#define BOMB_NUM 5
#define PILL_NUM 5
//functional tools
#define ROCKET_NUM 5
#define CHOCOLATE_NUM 5
#define TIMEMACHINE_NUM 5
//
#define HEATPLAYINTERVAL 10
#define COLDPLAYINTERVAl 20
//Yuloow Speed
//define total Time to move one screen
#define kNormalSpeed 3
#define kOtherColorSpeed  5
#define kNudeSpeed 20
#define kFlySpeed  2
#define kScorchSpeed 10
//Yuloow Change State Interval
#define kYuloowChangeColorInterval 5
#define kYuloowNudeInterval 20
#define kYuloowFlyInterval 20
#define kYuloowScorchInterval 5
//Grade
#define GradeOfBanana  5
#define GradeOfHeatBanana 10
#define GradeOfColdBanana 10
#define GradeOfApple  3
#define GradeOfOrange 3
#define GradeOfGrape  3
#define GradeOfWatermelon  3
#define GradeOfStrawberry  3
#define GradeOfChocolate 5
#define GradeOfRocket 5 
#define TimeofTimemachine 10
//define Falling speed
#define BANANAFALLINGSPEED 7
#define OTHERFRUITFALLINGSPEED 8
#define SPECIALBANANAFALLINGSPEED 6
#define ROCKETFALLINGSPEED 5
#define CHOCOLATEFALLINGSPEED 5
#define TIMEMACHINESEPEED 5
#define PILLFALLINGSPEED 5
#define BOMBFALLINGSPEED 5
//add Energy
#define EnergyOfBanana 0.1 
#define EnergyOfHeatBanana 0.1
#define EnergyOfColdBanana 0.1 
#define EnergyOfOtherFruit 0.05
//initilize interval of falling *10 of real speed
#define FallingFruitInterval 30
#define FallingDangerInterval 200
#define FallingFunctionInterval 200
//initilize interval times for special banana come
#define SpecialIntervalTimes 15
//define For chan
#define ChanSpecialIntervalTimes 10 
//loss energy when bomb
#define BOMB_LOSS 0.3
//one time produce danger things
#define DANGER_EACH_TIME 1 
//max danger one time
#define MAX_DANGER_NUM 10 
#endif /* defined(__Yuloow__GameConfig__) */
