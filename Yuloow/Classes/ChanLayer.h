//
//  ChanLayer.h
//  Yuloow
//
//  Created by luyifan on 13-11-17.
//
//

#ifndef __Yuloow__ChanLayer__
#define __Yuloow__ChanLayer__
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "GameConfig.h"
#include "LineContainer.h"
#include "Yuloow.h"
using namespace CocosDenshion ;
USING_NS_CC;

typedef enum chanState
{
    kChanPlaying ,
    kChanColdPlaying ,
    kChanHeatPlaying ,
    kChanPausing ,
    kChanGameOver
}ChanState;
enum
{
    kSpriteStrawberry ,
    kSpriteOrange ,
    kSpriteApple ,
    kSpriteWatermelon ,
    kSpriteGrape ,
    kSpriteBanana ,
    kSpriteHeatBanana ,
    kSpriteColdBanana ,
    
    kSpriteBomb ,
    kSpritePill ,
    
    kSpriteChocolate ,
    kSpriteRocket ,
    kSpriteTimemachine,
    
    kSpriteHalo ,
    kSpritePause ,
    kSpriteChocolateMove ,
    kSpriteRocketMove,
    kSpriteTimemachineMove
};
enum
{
    kGameOverScore ,
    kGameOverMenuRestart ,
    kGameOverMenuQuit
};

class ChanLayer : public CCLayer
{
    ChanState _state ;
    ChanState _oldstate ;
    CCSize _screenSize ;
    
    //the score in the game
    int _score ;
    //the timelimit in the game
    float _time ;
    //the numbers functional tools
    //int _chocolateNum ;
    int _rocketNum ;
    int _timemachineNum;
    
    //pool of falling thing
    
    CCArray * _strawberryPool ;
    int _strawberryIndex ;
    CCArray * _orangePool ;
    int _orangeIndex ;
    CCArray * _applePool ;
    int _appleIndex ;
    CCArray * _watermelonPool ;
    int _watermelonIndex ;
    CCArray * _grapePool ;
    int _grapeIndex ;
    CCArray * _bananaPool ;
    int _bananaIndex ;
    CCArray * _heatBananaPool ;
    int _heatBananaIndex ;
    CCArray * _coldBananaPool ;
    int _coldBananaIndex ;
    //CCArray * _bombPool ;
    //int _bombIndex ;
    //CCArray * _pillPool ;
    //int _pillIndex ;
    //CCArray * _chocolatePool ;
    //int _chocolateIndex ;
    CCArray * _rocketPool ;
    int _rocketIndex ;
    CCArray * _timemachinePool;
    int  _timemachineIndex;
    //CCArray * _haloPool ;
    //int _haloIndex ;
    
    CCArray * _fallingObjects ;
    
    //cloud in the background
    CCArray * _clouds ;
    //the line to show remaining time
    LineContainer * _lineContainer ;
    //to show the remaining time
    CCLabelBMFont *_timeDisplay;
    //to show the score
    CCLabelBMFont * _scoreDisplay ;
    //to show the chocolate num
    //CCLabelBMFont * _chocolateDisplay ;
    //to show the chocolate Sprite
    //to show the rocket Sprite
    //to show the rocket num
    CCLabelBMFont * _rocketDisplay ;
    //to show the rocket Sprite
    //to show the timemachine num
    CCLabelBMFont * _timemachineDisplay;
    
    
    //the button to pause the game
    CCSprite * _pauseBtn ;
    //the particle of boom
    //CCParticleSystem * _boom ;
    //CCParticleSystem * _boom2 ;
    //the particle of rocket jet
    //CCParticleSystem * _jet ;
    
    
    //the star of game
    Yuloow * _yuloow ;
    
    //the batchNode to store picture
    CCSpriteBatchNode * _gameBatchNode ;
    
    
    //Actions
    CCAction * _rotateAction ;
    //CCAction * _haloBiggerAction ;
    //CCAction * _haloFadeOutAction ;
    
    //Show Pause Screen
    CCSprite * _gamePauseScreen ;
    CCMenu * _pauseMenuOff ;
    
    //Show GameOver Screen
    CCSprite * _gameOverScreen ;
    //TimeInterval of falling things  and speed
    //Special State Interval and Timer
    float _coldPlayingTimer ;
    float _heatPlayingTimer ;
    //Rocket and Chocolate and Timemachine for move
    
    //CCSprite * _moveChocolate ;
    CCSprite * _moveRocket ;
    CCSprite * _moveTimemachine ;
    
    //eating food
    float _bananaSpeed ;
    float _heatBananaSpeed ;
    float _coldBananaSpeed ;
    float _appleSpeed ;
    float _grapeSpeed ;
    float _orangeSpeed ;
    float _watermelonSpeed ;
    float _strawberrySpeed ;
    
    //time to add difficulty
    float _difficultyInterval ;
    float _difficultyTimer ;
    //time of fruit interval
    //time of fruit timer
    int _fruitInterval ;
    float _fruitCurrentInterval ;
    float _fruitTimer ;
    int _specialIntervalTimes ;
    int _specialCurrentTimes ;
    //time of danger interval
    //time of danger timer
    int _dangerInterval ;
    float _dangerCurrentInterval ;
    float _dangerTimer ;
    int _eachCountOfDanger ;
    //time of function interval
    //time of function timer
    int _functionInterval ;
    float _functionCurrentInterval ;
    float _functionTimer ;
    
    
    //TimeInterval of danger things
    float _bombInterval ;
    float _bombTimer ;
    float _bombSpeed ;
    float _pillInterval ;
    float _pillTimer ;
    float _pillSpeed ;
    //TimeInterval of functional tools
    //float _chocolateInterval ;
    //float _chocolateTimer ;
    //float _chocolateSpeed ;
    float _rocketInterval ;
    float _rocketTimer ;
    float _rocketSpeed ;
    float _timemachineInterVal ;
    float _timemachineTimer ;
    float _timemachineSpeed ;
    //Set to store all pause action sprite
    CCSet * _pausedTargets ;
    
    //food below this height will loss
    float _minHeight ;
    void createGameScreen( ) ;
    void createPools ( ) ;
    //void createParticles ( ) ;
    void createActions ( ) ;
    void resetGame ( ) ;
    
    //add one thing from pool into screen
    //eating food
    void resetBanana( void ) ;
    void resetHeatBanana ( void ) ;
    void resetColdBanana ( void ) ;
    void resetApple ( void ) ;
    void resetOrange ( void ) ;
    void resetWatermelon ( void ) ;
    void resetGrape ( void ) ;
    void resetStrawberry ( void ) ;
    //danger things
    //void resetBomb ( void ) ;
    //void resetPill ( void ) ;
    //function toos
    //void resetChocolate ( void ) ;
    void resetRocket ( void ) ;
    void resetTimemachine(void) ;
     //pick actions to the falling object
    void pickActions ( CCSprite * pSender , float fallingSpeed ) ;
    
    //to increase difficulty
    //void increaseDifficulty ( void ) ;
    //void haloBiggerDone ( CCNode * pSender ) ;
    void fallingObjectDone ( CCNode * pSender ) ;
    
    //resume to Play State
    void resumeChanPlaying ( void ) ;
    //update three kind of thing by times
    void updateEating ( float dt  );
    void updateHeatEating ( float dt  );
    
    //void updateDanger ( float dt  ) ;
    void updateFunction ( float dt ) ;
    
    //change state to heat playing or cold playing
    void changeToHeatPlaying ( ) ;
    void changeToColdPlaying ( ) ;
    //game is over
    void killYuloow ( ) ;
    //game is pause
    void stopChanGame ( ) ;
    //go back to MenuLayer
    void quitGame ( ) ;
    //continue a new jieji Play
    void restartGame ( ) ;
    //continue this game
    void resumeGame ( ) ;
    //_yuloow coming back
    void comingFinish ( ) ;
    
     
    //bool for _chocolateMove
    //bool _isChooseChocolate ;
    //bool for _rocketMove
    bool _isChooseRocket ;
    //bool for _timemachineMove;
    bool _isChooseTimemachine ;
    
    //chocolatePosition
    //CCPoint _chocolatePosition ;
    //rocketPosition
    CCPoint _rocketPosition ;
    //timemachinePosition
    CCPoint _timemachinePosition ;
    
    //chocolate Come back
    //CCAction * _chocolateComeBack ;
    //rocket Come back
    CCAction * _rocketComeBack ;
    //timemachine Come back
    CCAction * _timemachineComeBack;
    
    //Fly with bomb
    //Yuloow Height
    float _yuloowHeight ;
    
public:
    ~ChanLayer ();
    ChanLayer();
    CCScene * oldScene ;
    static CCScene * scene ( );
    
    virtual bool init();
    
    void update ( float dt );
    
    
    CREATE_FUNC( ChanLayer );
    virtual void ccTouchesEnded (CCSet* pTouches, CCEvent* event);
    virtual void ccTouchesBegan (CCSet* pTouches, CCEvent* event);
    virtual void ccTouchesMoved (CCSet* pTouches, CCEvent* event);
};

#include <iostream>

#endif /* defined(__Yuloow__ChanLayer__) */
