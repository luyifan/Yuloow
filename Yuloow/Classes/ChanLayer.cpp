//
//  ChanLayer.cpp
//  Yuloow
//
//  Created by luyifan on 13-11-17.
//
//

#include "ChanLayer.h"
#include "MenuLayer.h"
ChanLayer::ChanLayer()
{
    
}
ChanLayer::~ChanLayer()
{
    
}
CCScene * ChanLayer::scene()
{
    CCScene * scene = CCScene::create() ;
    ChanLayer * layer = ChanLayer::create() ;
    scene->addChild( layer ) ;
    return scene ;
    
    
}

bool ChanLayer::init()
{
    if ( !CCLayer::init())
        return false ;
    srand(time(NULL));
    _state = kChanPlaying ;
    
    _screenSize = CCDirector::sharedDirector()->getWinSize();
    createGameScreen ( ) ;
    createPools ( ) ;
    //createParticles() ;
    createActions ( ) ;
    resetGame ( ) ;
    //create array to store all falling object
    _fallingObjects = CCArray::createWithCapacity( 50 ) ;
    _fallingObjects->retain() ;
    setTouchEnabled( true ) ;
    
    this->schedule(schedule_selector(ChanLayer::update));
    //SimpleAudioEngine::sharedEngine()->playBackgroundMusic("background.mp3", true ) ;
    
    return true ;
}

void ChanLayer::update( float dt )
{
    //the game is stop
    if ( _state == kChanGameOver || _state == kChanPausing )
        return ;
    int count ;
    //for debug
    //  _lineContainer->setEnergy(1.0);
    if ( _yuloow->getComingBack() == false )
        return ;
    CCSprite * sprite ;
    //_lineContainer->update( dt ) ;
    _yuloow->update ( dt );
    if ( _state != kChanColdPlaying )
        _time-= dt ;
    if ( _state == kChanPlaying || _state == kChanColdPlaying )
    {
        updateEating( dt ) ;
        //updateDanger( dt ) ;
        updateFunction( dt ) ;
    }
    if ( _state == kChanHeatPlaying )
    {
        updateHeatEating( dt ) ;
        _heatPlayingTimer += dt ;
        if ( _heatPlayingTimer > HEATPLAYINTERVAL )
            this->resumeChanPlaying ( ) ;
    }
    if ( _state == kChanColdPlaying )
    {
        _coldPlayingTimer += dt ;
        if ( _coldPlayingTimer > COLDPLAYINTERVAl )
            this->resumeChanPlaying() ;
    }
    //move clouds
    count = _clouds->count() ;
    for ( int i = count - 1 ; i >= 0  ; i -- )
    {
        sprite = ( CCSprite * ) _clouds->objectAtIndex( i ) ;
        sprite->setPositionX (  sprite->getPositionX() + dt * 20 ) ;
        if ( sprite->getPositionX() > _screenSize.width + sprite->boundingBox().size.width * 0.5 )
            sprite->setPositionX( - sprite->boundingBox().size.width * 0.5 ) ;
    }

    //check falling object
    count = _fallingObjects->count() ;
    //should from end to start
    float len ;
    bool ok ;
    float x1 , x2 , y1 , y2 ;
    for ( int i = count - 1 ; i >= 0 ; i -- )
    {
        ok = false ;
        sprite = ( CCSprite * ) _fallingObjects->objectAtIndex( i ) ;
        len = sqrt(  pow( sprite->boundingBox().size.width * 0.5 , 2 ) + pow ( sprite->boundingBox().size.height * 0.5 , 2 ) ) ;
        x1 = sprite->getPositionX() - len ;
        x2 = sprite->getPositionX() + len;
        y1 = sprite->getPositionY() - len ;
        y2 = sprite->getPositionY() + len ;
        if ( y2 <= _minHeight /*&& sprite->getTag() != kSpriteBomb*/ )
            continue ;
        if ( sprite->isVisible() == false )
            continue ;
        
        if (  _yuloow->boundingBox().containsPoint(ccp ( x1 , y1 )) ||
            _yuloow->boundingBox().containsPoint(ccp ( x1 , y2 )) ||
            _yuloow->boundingBox().containsPoint(ccp ( x2 , y1 )) ||
            _yuloow->boundingBox().containsPoint(ccp ( x2 , y2 )))
        {
            //overlap
            sprite->stopAllActions() ;
            //add action will be bette
            sprite->setVisible( false ) ;
            //eating food
            ////play music
            if ( sprite->getTag() == kSpriteBanana )
            {
                SimpleAudioEngine::sharedEngine()->playEffect("Fruit.wav");
                
                _score += GradeOfBanana ;
                //_lineContainer->addEnergy( EnergyOfBanana );
            }
            else
                if ( sprite->getTag() == kSpriteHeatBanana )
                {
                    //need to be filled
                    SimpleAudioEngine::sharedEngine()->playEffect("SpecialBanana.wav");
                    
                    _score += GradeOfHeatBanana ;
                    //_lineContainer->addEnergy( EnergyOfHeatBanana );
                    if ( _state == kChanColdPlaying || _state == kChanHeatPlaying )
                        resumeChanPlaying();
                    this->changeToHeatPlaying() ;
                    //break because the _falling for is broken
                    break ;
                }
                else
                    if ( sprite->getTag() == kSpriteColdBanana )
                    {
                        //need to be filled
                        SimpleAudioEngine::sharedEngine()->playEffect("SpecialBanana.wav");
                        
                        _score += GradeOfColdBanana ;
                        //_lineContainer->addEnergy( EnergyOfColdBanana );
                        if ( _state == kChanHeatPlaying || _state == kChanColdPlaying )
                            resumeChanPlaying() ;
                        this->changeToColdPlaying ( ) ;
                    }
                    else
                        if ( sprite->getTag() == kSpriteApple )
                        {
                            SimpleAudioEngine::sharedEngine()->playEffect("Fruit.wav");
                            _score += GradeOfApple ;
                            //_lineContainer->addEnergy( EnergyOfOtherFruit ) ;
                            _yuloow->changeState( kAppleColor ) ;
                        }
                        else
                            if ( sprite->getTag() == kSpriteOrange )
                            {
                                SimpleAudioEngine::sharedEngine()->playEffect("Fruit.wav");
                                
                                _score += GradeOfOrange ;
                                //_lineContainer->addEnergy( EnergyOfOtherFruit ) ;
                                _yuloow->changeState( kOrangeColor ) ;
                            }
                            else
                                if ( sprite->getTag() == kSpriteStrawberry )
                                {
                                    SimpleAudioEngine::sharedEngine()->playEffect("Fruit.wav");
                                    
                                    _score += GradeOfStrawberry ;
                                    //_lineContainer->addEnergy( EnergyOfOtherFruit ) ;
                                    _yuloow->changeState( kStrawberryColor ) ;
                                }
                                else
                                    if ( sprite->getTag() == kSpriteWatermelon )
                                    {
                                        SimpleAudioEngine::sharedEngine()->playEffect("Fruit.wav");
                                        
                                        _score += GradeOfWatermelon ;
                                        //_lineContainer->addEnergy( EnergyOfOtherFruit ) ;
                                        _yuloow->changeState( kWatermelonColor ) ;
                                    }
                                    else
                                        if ( sprite->getTag() == kSpriteGrape )
                                        {
                                            SimpleAudioEngine::sharedEngine()->playEffect("Fruit.wav");
                                            
                                            _score += GradeOfGrape ;
                                            //_lineContainer->addEnergy( EnergyOfOtherFruit ) ;
                                            _yuloow->changeState( kGrapeColor ) ;
                                        }
            //
                                        /*else
                                            
                                            //danger thing
                                            if ( sprite->getTag() == kSpritePill )
                                            {
                                                SimpleAudioEngine::sharedEngine()->playEffect("Pill.wav");
                                                
                                                _yuloow->changeState( kNude ) ;
                                            }
                                            else
                                                if ( sprite->getTag() == kSpriteBomb )
                                                {
                                                    SimpleAudioEngine::sharedEngine()->playEffect("Explosion.wav");
                                                    
                                                    _boom->setPosition ( sprite->getPosition() ) ;
                                                    _boom->resetSystem() ;
                                                    CCSprite * halo = ( CCSprite * ) _haloPool->objectAtIndex( _haloIndex ) ;
                                                    _haloIndex ++ ;
                                                    if ( _haloIndex == BOMB_NUM ) _haloIndex = 0 ;
                                                    halo->setPosition( sprite->getPosition() ) ;
                                                    halo->setVisible( true ) ;
                                                    halo->runAction( ( CCAction * ) _haloBiggerAction->copy()->autorelease() ) ;
                                                    halo->runAction( ( CCAction * ) _haloFadeOutAction->copy()->autorelease() ) ;
                                                    if ( _yuloow->getYuloowState() == kFly )
                                                    {
                                                        _boom2->setPosition ( sprite->getPosition() ) ;
                                                        _boom2->resetSystem() ;
                                                        _yuloow->setComingBack( false ) ;
                                                        _yuloow->runAction( CCSequence::create( CCSpawn::create( CCFadeIn::create ( 1 ) , CCMoveTo::create( 1, ccp ( _screenSize.width * 0.5 , _yuloowHeight)) , NULL ) ,
                                                                                               CCCallFunc::create( this ,callfunc_selector (JiejiLayer::comingFinish)) , NULL ));
                                                        
                                                    }
                                                    
                                                    _yuloow->changeState( kScorch ) ;
                                                    
                                                    float energy = _lineContainer->getEnergy() - BOMB_LOSS/2 ;
                                                    if ( energy < 0 )
                                                        energy = 0 ;
                                                    _lineContainer->setEnergy( energy ) ;
                                                    if ( energy == 0 )
                                                    {
                                                        ////show Game Over Screen
                                                        _lineContainer->update( dt ) ;
                                                        
                                                        killYuloow();
                                                        return ;
                                                    }
                                                    
                                                }*/
            //functional tools
                                                else
                                                    if ( sprite->getTag() == kSpriteTimemachine )
                                                    {
                                                        SimpleAudioEngine::sharedEngine()->playEffect("Fruit.wav");
                                                        
                                                        _timemachineNum ++ ;
                                                        //_score += GradeOfChocolate ;
                                                        //_time += TimeofTimemachine;
                                                    }
                                                    else
                                                        if ( sprite->getTag() == kSpriteRocket )
                                                        {
                                                            SimpleAudioEngine::sharedEngine()->playEffect("Fruit.wav");
                                                            _rocketNum ++ ;
                                                            _score += GradeOfRocket ;
                                                        }
            _fallingObjects->removeObjectAtIndex( i ) ;
            
        }
    }
    
    
    //show records
    char szValue [ 10 ] = { 0 } ;
    sprintf( szValue , "%i" , _score ) ;
    _scoreDisplay->setString( szValue ) ;
    sprintf( szValue , "%i" , (int) _time ) ;
    _timeDisplay->setString( szValue ) ;

    sprintf( szValue , "%i" , _timemachineNum ) ;
    _timemachineDisplay->setString ( szValue ) ;
    sprintf( szValue , "%i" , _rocketNum ) ;
    _rocketDisplay->setString( szValue ) ;
    
    if ( _time < 0 )
    {
        _state = kChanGameOver ;
        ////show ChanGame Screen
        killYuloow ( ) ;
    }

}

void ChanLayer::createGameScreen()
{
    CCSprite * bg = CCSprite::create("bg.png") ;
    bg->setPosition( ccp ( _screenSize.width * 0.5 , _screenSize.height * 0.5 )) ;
    this->addChild( bg ) ;
    
    
    _gameBatchNode = CCSpriteBatchNode::create("sprite_sheet.png");
    this->addChild( _gameBatchNode , kForeground );
    
    
    
    CCSprite * sprite ;
    for ( int i = 0 ; i < 2 ; i ++ )
    {
        sprite = CCSprite::createWithSpriteFrameName( "city_dark.png" ) ;
        
        _minHeight = sprite->boundingBox().size.height ;
        sprite->setPosition ( ccp( _screenSize.width *( 0.25 + i * 0.5 ) , _minHeight * 0.5 )) ;
        _gameBatchNode->addChild( sprite , kForeground ) ;
        sprite = CCSprite::createWithSpriteFrameName( "city_light.png"  ) ;
        sprite->setPosition( ccp ( _screenSize.width *( 0.25 + i * 0.5 ) , sprite->boundingBox().size.height * 0.9f )) ;
        
        _gameBatchNode->addChild( sprite , kBackground ) ;
    }
    for ( int i = 0 ; i < 3 ; i ++ )
    {
        sprite = CCSprite::createWithSpriteFrameName( "trees.png" ) ;
        sprite->setPosition( ccp( _screenSize.width * ( 0.2f + i * 0.3 ) , sprite->boundingBox().size.height * 0.5 ) ) ;
        _gameBatchNode->addChild( sprite , kForeground ) ;
        
    }
    
    CCSprite * cloud ;
    _clouds = CCArray::createWithCapacity( 4 ) ;
    _clouds->retain() ;
    float cloud_y ;
    for ( int i = 0 ; i < 4 ; i ++ )
    {
        cloud_y = i % 2 == 0 ? _screenSize.height * 0.4f : _screenSize.height * 0.5f ;
        cloud = CCSprite::createWithSpriteFrameName ( "cloud.png" ) ;
        cloud->setPosition( ccp ( _screenSize.width * 0.1f  + i * _screenSize.width * 0.3f , cloud_y ));
        _gameBatchNode->addChild( cloud , kBackground ) ;
        _clouds->addObject( cloud ) ;
    }
    
    CCSprite * scoreLabel = CCSprite::createWithSpriteFrameName("label_score.png");
    scoreLabel->setPosition( ccp ( _screenSize.width * 0.8 , _screenSize.height * 0.95 )) ;
    _gameBatchNode->addChild( scoreLabel , kBackground ) ;
    
    _scoreDisplay = CCLabelBMFont::create( "0" , "font.fnt" , _screenSize.width * 0.1f , kCCTextAlignmentLeft ) ;
    _scoreDisplay->setAnchorPoint( ccp ( 0 , 0.5 )) ;
    _scoreDisplay->setPosition(ccp( _screenSize.width * 0.85 , _screenSize.height * 0.95 )) ;
    this->addChild( _scoreDisplay , kBackground ) ;
    
    CCSprite * timeLabel = CCSprite::createWithSpriteFrameName("label_time.png");
    timeLabel->setPosition( ccp ( _screenSize.width * 0.2 , _screenSize.height * 0.95 )) ;
    _gameBatchNode->addChild( timeLabel , kBackground ) ;
    
    _timeDisplay = CCLabelBMFont::create( "60" , "font.fnt" , _screenSize.width * 0.1f , kCCTextAlignmentLeft ) ;
    _timeDisplay->setAnchorPoint( ccp ( 0 , 0.5 )) ;
    _timeDisplay->setPosition(ccp( _screenSize.width * 0.25 , _screenSize.height * 0.95 )) ;
    this->addChild( _timeDisplay , kBackground ) ;
    
    sprite = CCSprite::createWithSpriteFrameName("clock.png" ) ;
    sprite->setPosition( ccp ( sprite->boundingBox().size.height * 0.55 , _screenSize.height * 0.8 )) ;
    _gameBatchNode->addChild( sprite , kForeground ) ;
    
    _moveTimemachine = CCSprite::createWithSpriteFrameName("clock.png" ) ;
    _moveTimemachine->setOpacity( 125 ) ;
    _timemachinePosition = ccp ( _moveTimemachine->boundingBox().size.height * 0.55 , _screenSize.height * 0.8) ;
    _moveTimemachine->setPosition( _timemachinePosition ) ;
    _gameBatchNode->addChild( _moveTimemachine , kBigForeground ,kSpriteTimemachineMove) ;
    _timemachineDisplay = CCLabelBMFont::create( "0" , "font.fnt" , _screenSize.width * 0.04 , kCCTextAlignmentLeft ) ;
    _timemachineDisplay->setAnchorPoint( ccp ( 0 , 0.5 )) ;
    _timemachineDisplay->setRotation( 90 ) ;
    _timemachineDisplay->setPosition( ccp ( _moveTimemachine->boundingBox().size.height* 0.5 , _screenSize.height * 0.79 -_moveTimemachine->boundingBox().size.height/2));
    this->addChild( _timemachineDisplay , kForeground ) ;
    
    sprite = CCSprite::createWithSpriteFrameName("rocket.png" ) ;
    sprite->setPosition( ccp ( _moveTimemachine->boundingBox().size.height * 0.55 , _screenSize.height * 0.5 )) ;
    _gameBatchNode->addChild( sprite , kForeground ) ;
    
    _moveRocket = CCSprite::createWithSpriteFrameName("rocket.png" ) ;
    _moveRocket->setOpacity( 125 ) ;
    _rocketPosition = ccp ( _moveTimemachine->boundingBox().size.height * 0.55 , _screenSize.height * 0.5) ;
    _moveRocket->setPosition( _rocketPosition ) ;
    _gameBatchNode->addChild( _moveRocket , kBigForeground , kSpriteRocketMove ) ;
    _rocketDisplay = CCLabelBMFont::create( "0" , "font.fnt" , _screenSize.width * 0.04 , kCCTextAlignmentLeft ) ;
    _rocketDisplay->setAnchorPoint( ccp ( 0 , 0.5 )) ;
    _rocketDisplay->setRotation( 90 ) ;
    _rocketDisplay->setPosition( ccp ( _moveTimemachine->boundingBox().size.height* 0.5 , _screenSize.height * 0.49 -_moveRocket->boundingBox().size.height/2));
    this->addChild( _rocketDisplay , kForeground ) ;
    
    
    _pauseBtn = CCSprite::createWithSpriteFrameName("btn_pause_off.png");
    _pauseBtn->setPosition( ccp ( _screenSize.width  - 5 -  _pauseBtn->boundingBox().size.width * 0.5 , _screenSize.height * 0.98  - _pauseBtn->boundingBox().size.height * 0.5 )) ;
    _gameBatchNode->addChild ( _pauseBtn , kBackground , kSpritePause ) ;
    
    /*_lineContainer = LineContainer::create() ;
    this->addChild( _lineContainer , kForeground ) ;*/
    
    //_gameOverScreen = CCSprite::create ( "blank.png" ) ;
    //_gameOverScreen->setTextureRect( CCRectMake( 0 , 0 , 700 , 456));
    _gameOverScreen = CCSprite::createWithSpriteFrameName("StopGameScreen.png");
    _gameOverScreen->setPosition ( ccp( _screenSize.width * 0.5 , _screenSize.height * 0.5 )) ;
    //_gameOverScreen->setOpacity( 50 ) ;
    CCLabelTTF * label = CCLabelTTF::create("Your Score","Marker Felt", _gameOverScreen->boundingBox().size.height * 0.3 ) ;
    _gameOverScreen->addChild( label , kForeground ) ;
    label->setAnchorPoint( ccp ( 0.5 , 0.5 )) ;
    label->setColor( ccc3 ( 0 , 0 , 0 )) ;
    label->setPosition( ccp( _gameOverScreen->boundingBox().size.width * 0.45
    , _gameOverScreen->boundingBox().size.height - label->boundingBox().size.height * 0.6 ) );
    label = CCLabelTTF::create("0","Marker Felt", _gameOverScreen->boundingBox().size.height * 0.3 ) ;
    label->setAnchorPoint( ccp ( 0.5 , 0.5 )) ;
    label->setColor( ccc3 ( 255 , 0 , 0 )) ;
    label->setPosition( ccp ( _gameOverScreen->boundingBox().size.width * 0.5 , _gameOverScreen->boundingBox().size.height - label->boundingBox().size.height * 1.4 ));
    _gameOverScreen->addChild( label , kForeground , kGameOverScore ) ;
    
    CCMenu * chanGameOver = CCMenu::create(  NULL ) ;
    
    CCSprite * menuItemOn ;
    CCSprite * menuItemOff ;
    menuItemOn = CCSprite::createWithSpriteFrameName("Quit_on.png");
    menuItemOff = CCSprite::createWithSpriteFrameName("Quit_off.png");
    CCMenuItemSprite * menuitem = CCMenuItemSprite::create(
                                                           menuItemOff,
                                                           menuItemOn,
                                                           this,
                                                           menu_selector(ChanLayer::quitGame));
    chanGameOver->addChild( menuitem ) ;
    menuItemOn = CCSprite::createWithSpriteFrameName("Restart_on.png");
    menuItemOff = CCSprite::createWithSpriteFrameName("Restart_off.png");
    
    menuitem = CCMenuItemSprite::create(
                                        menuItemOff,
                                        menuItemOn,
                                        this,
                                        menu_selector(ChanLayer::restartGame));
    chanGameOver->addChild( menuitem ) ;
    chanGameOver->alignItemsHorizontally() ;
    chanGameOver->alignItemsHorizontallyWithPadding( 30 ) ;
    _gameOverScreen->addChild( chanGameOver , kForeground  ) ;
    chanGameOver->setPosition( ccp ( _gameOverScreen->boundingBox().size.width* 0.5 , menuitem->boundingBox().size.height  )) ;
    _gameOverScreen->setVisible( false ) ;
    this->addChild( _gameOverScreen , kForeground ) ;
    
    //_gamePauseScreen = CCSprite::create ( "blank.png" ) ;
    //_gamePauseScreen->setTextureRect( CCRectMake( 0 , 0 , 500 , 800 ));
    //_gamePauseScreen->setAnchorPoint( ccp ( 0.5 , 0.5 )) ;
    _gamePauseScreen = CCSprite::createWithSpriteFrameName("PauseJieji.png");
    _gamePauseScreen->setPosition( ccp ( _screenSize.width * 0.5 , _screenSize.height * 0.5 )) ;
    
   // _gamePauseScreen->setOpacity( 50 ) ;
    _pauseMenuOff = CCMenu::create( NULL ) ;
    //CCMenu * _pauseMenuOn = CCMenu::create( NULL ) ;
    menuItemOn = CCSprite::createWithSpriteFrameName("resumeGame_on.png");
    menuItemOff = CCSprite::createWithSpriteFrameName("resumeGame_off.png");
    menuitem = CCMenuItemSprite::create(
                                        menuItemOff,
                                        menuItemOn,
                                        this,
                                        menu_selector(ChanLayer::resumeGame));
    _pauseMenuOff->addChild( menuitem  ) ;
    menuItemOn = CCSprite::createWithSpriteFrameName("quitgame_on.png");
    menuItemOff = CCSprite::createWithSpriteFrameName("quitgame_off.png");
    
    menuitem = CCMenuItemSprite::create(
                                        menuItemOff,
                                        menuItemOn,
                                        this,
                                        menu_selector(ChanLayer::quitGame));
    _pauseMenuOff->addChild( menuitem ) ;
    
   
    _pauseMenuOff->alignItemsVertically() ;
    _pauseMenuOff->alignItemsVerticallyWithPadding( 20 ) ;
    _pauseMenuOff->setAnchorPoint( ccp ( 0.5 , 0 )) ;
    _pauseMenuOff->setPosition( ccp ( _screenSize.width * 0.5 , _screenSize.height * 0.5 )) ;
    this->addChild( _gamePauseScreen ,kForeground ) ;
    this->addChild( _pauseMenuOff , kForeground) ;
    _gamePauseScreen->setVisible( false ) ;
    _pauseMenuOff->setVisible( false ) ;
    _yuloow = Yuloow::create() ;
    _gameBatchNode->addChild( _yuloow , kForeground ) ;
}

void ChanLayer::createPools ( )
{
    CCSprite * sprite ;
    //eating food Pools
    _bananaPool = CCArray::createWithCapacity( BANANA_NUM ) ;
    _bananaPool->retain ( ) ;
    _bananaIndex = 0 ;
    for ( int i = 0 ; i < BANANA_NUM ; i ++ )
    {
        sprite = CCSprite::createWithSpriteFrameName("banana.png");
        sprite->setVisible ( false ) ;
        _gameBatchNode->addChild( sprite , kMiddleground , kSpriteBanana );
        _bananaPool->addObject( sprite ) ;
        
    }
    
    _heatBananaPool = CCArray::createWithCapacity( HEATBANANA_NUM ) ;
    _heatBananaPool->retain ( ) ;
    _heatBananaIndex = 0 ;
    for ( int i = 0 ; i < HEATBANANA_NUM ; i ++ )
    {
        sprite = CCSprite::createWithSpriteFrameName("heatBanana.png" ) ;
        sprite->setVisible( false ) ;
        _gameBatchNode->addChild( sprite , kMiddleground , kSpriteHeatBanana ) ;
        _heatBananaPool->addObject( sprite ) ;
    }
    
    _coldBananaPool = CCArray::createWithCapacity( COLDBANANA_NUM ) ;
    _coldBananaPool->retain() ;
    _coldBananaIndex = 0 ;
    for ( int i = 0 ; i < COLDBANANA_NUM ; i ++ )
    {
        sprite = CCSprite::createWithSpriteFrameName( "coldBanana.png" ) ;
        sprite->setVisible( false ) ;
        _gameBatchNode->addChild( sprite , kMiddleground , kSpriteColdBanana ) ;
        _coldBananaPool->addObject( sprite ) ;
    }
    
    _orangePool = CCArray::createWithCapacity( ORANGE_NUM ) ;
    _orangePool->retain( ) ;
    _orangeIndex = 0 ;
    for ( int i = 0 ; i < ORANGE_NUM ; i ++ )
    {
        sprite = CCSprite::createWithSpriteFrameName("orange.png") ;
        sprite->setVisible( false ) ;
        _gameBatchNode->addChild( sprite , kMiddleground , kSpriteOrange ) ;
        _orangePool->addObject( sprite ) ;
    }
    
    _grapePool = CCArray::createWithCapacity( GRAPE_NUM ) ;
    _grapePool->retain ( ) ;
    _grapeIndex = 0 ;
    for ( int i = 0 ; i < GRAPE_NUM ; i ++ )
    {
        sprite = CCSprite::createWithSpriteFrameName("grape.png");
        sprite->setVisible( false ) ;
        _gameBatchNode->addChild( sprite , kMiddleground , kSpriteGrape ) ;
        _grapePool->addObject( sprite ) ;
    }
    
    _strawberryPool = CCArray::createWithCapacity( STRAWBERRY_NUM ) ;
    _strawberryPool->retain() ;
    _strawberryIndex = 0 ;
    for ( int i = 0 ; i < STRAWBERRY_NUM ; i ++ )
    {
        sprite = CCSprite::createWithSpriteFrameName("strawberry.png") ;
        sprite->setVisible( false ) ;
        _gameBatchNode->addChild( sprite , kMiddleground , kSpriteStrawberry ) ;
        _strawberryPool->addObject( sprite ) ;
    }
    
    _applePool = CCArray::createWithCapacity( APPLE_NUM ) ;
    _applePool->retain ( ) ;
    _appleIndex = 0 ;
    for ( int i = 0 ; i < APPLE_NUM ; i ++ )
    {
        sprite = CCSprite::createWithSpriteFrameName("apple.png");
        sprite->setVisible( false ) ;
        _gameBatchNode->addChild( sprite , kMiddleground , kSpriteApple ) ;
        _applePool->addObject( sprite ) ;
    }
    
    _watermelonPool = CCArray::createWithCapacity( WATERMELON_NUM ) ;
    _watermelonPool->retain( ) ;
    _watermelonIndex = 0 ;
    for ( int i = 0 ; i < WATERMELON_NUM ; i ++ )
    {
        sprite = CCSprite::createWithSpriteFrameName("watermelon.png");
        sprite->setVisible( false );
        _gameBatchNode->addChild( sprite , kMiddleground , kSpriteWatermelon ) ;
        _watermelonPool->addObject( sprite ) ;
    }

    
    // functional tools
    /*_chocolatePool = CCArray::createWithCapacity( CHOCOLATE_NUM ) ;
    _chocolatePool->retain() ;
    _chocolateIndex = 0 ;
    
    for ( int i = 0 ; i < CHOCOLATE_NUM ; i ++ )
    {
        sprite = CCSprite::createWithSpriteFrameName("chocolate.png");
        sprite->setVisible( false ) ;
        _gameBatchNode->addChild( sprite , kMiddleground , kSpriteChocolate ) ;
        _chocolatePool->addObject( sprite ) ;
    }*/
    
    
    _rocketPool = CCArray::createWithCapacity( ROCKET_NUM ) ;
    _rocketPool->retain ( ) ;
    _rocketIndex = 0 ;
    for ( int i = 0 ; i < ROCKET_NUM ; i ++ )
    {
        sprite = CCSprite::createWithSpriteFrameName("rocket.png") ;
        sprite->setVisible( false ) ;
        _gameBatchNode->addChild( sprite , kMiddleground , kSpriteRocket ) ;
        _rocketPool->addObject( sprite ) ;
    }
    
    _timemachinePool = CCArray::createWithCapacity( TIMEMACHINE_NUM ) ;
    _timemachinePool->retain ( ) ;
    _timemachineIndex = 0 ;
    for ( int i = 0 ; i < TIMEMACHINE_NUM ; i ++ )
    {
        //need to be filled
        sprite = CCSprite::createWithSpriteFrameName("clock.png") ;
        sprite->setVisible( false ) ;
        _gameBatchNode->addChild( sprite , kMiddleground , kSpriteTimemachine ) ;
        _timemachinePool->addObject( sprite ) ;
    }
}

void ChanLayer::createActions()
{
    //rotate of falling things
    CCActionInterval * rotate = CCRotateBy::create ( 0.5 , -90 ) ;
    _rotateAction = CCRepeatForever::create ( rotate ) ;
    _rotateAction->retain ( ) ;
    //rocket come back
    _rocketComeBack = CCMoveTo::create ( 0.5 , _rocketPosition ) ;
    _rocketComeBack->retain() ;
    //timemachineComeBack
    _timemachineComeBack =CCMoveTo::create(0.5, _timemachinePosition);
    _timemachineComeBack->retain();
    
}

void ChanLayer::resetGame()
{
    //
    _time = 60;
    //
    _score  = 0 ;
    //reset chocolate num
    //_chocolateNum = 0 ;
    //reset rocket num
    _rocketNum = 0 ;
    //reset timemachine num
    _timemachineNum = 0 ;
    //energy is full
    //_lineContainer->setEnergy( 1 ) ;
    /*
    //reset difficulty
    _difficultyInterval = 30 ;
    _difficultyTimer = 0 ;*/
    //reset speed
    _bananaSpeed = BANANAFALLINGSPEED ;
    _appleSpeed = OTHERFRUITFALLINGSPEED ;
    _orangeSpeed = OTHERFRUITFALLINGSPEED ;
    _grapeSpeed = OTHERFRUITFALLINGSPEED ;
    _watermelonSpeed = OTHERFRUITFALLINGSPEED ;
    _strawberrySpeed = OTHERFRUITFALLINGSPEED ;
    _rocketSpeed = ROCKETFALLINGSPEED ;
    //_chocolateSpeed = CHOCOLATEFALLINGSPEED ;
    _timemachineSpeed = TIMEMACHINESEPEED;
    
    //heatSpeed
    //coldSpeed
    _heatBananaSpeed = SPECIALBANANAFALLINGSPEED ;
    _coldBananaSpeed = SPECIALBANANAFALLINGSPEED ;
    //_bombSpeed = BOMBFALLINGSPEED ;
    //_pillSpeed = PILLFALLINGSPEED ;
    //reset fruit and danger and function tools
    //reset fruit
    _fruitInterval = FallingFruitInterval ;
    _fruitCurrentInterval = (rand( )% (_fruitInterval) + _fruitInterval)/10.0;
    _fruitTimer = _fruitCurrentInterval * 0.99 ;
    _specialIntervalTimes = ChanSpecialIntervalTimes ;
    _specialCurrentTimes = _specialIntervalTimes/2;
    /*
    //reset danger
    _dangerInterval = FallingDangerInterval ;
    _dangerCurrentInterval = (rand()%( _dangerInterval ) + _dangerInterval)/10.0 ;
    _dangerTimer = 0 ;
    _eachCountOfDanger = DANGER_EACH_TIME ;*/
    
    //reset function
    _functionInterval = FallingFunctionInterval ;
    _functionCurrentInterval = (rand()%( _functionInterval ) + _functionInterval)/10.0 ;
    _functionTimer = _functionCurrentInterval * 0.8 ;
    
    //bool initilize
    //_isChooseChocolate = false ;
    _isChooseRocket = false ;
    _isChooseTimemachine = false ;
    _yuloow->setPosition( ccp( _screenSize.width * 0.5 , _yuloow->boundingBox().size.height *0.5 )) ;
    _yuloowHeight = _yuloow->boundingBox().size.height * 0.5 ;
    _yuloow->setVisible( true ) ;
    _yuloow->reset() ;
    
    char szValue [ 10 ] = { 0 } ;
    sprintf( szValue , "%i" , _score ) ;
    _scoreDisplay->setString( szValue ) ;
    sprintf( szValue , "%i" , (int)_time) ;
    _timeDisplay->setString( szValue ) ;
    //sprintf( szValue , "%i" , _chocolateNum ) ;
    //_chocolateDisplay->setString ( szValue ) ;
    sprintf( szValue , "%i" , _rocketNum ) ;
    _rocketDisplay->setString( szValue ) ;
    sprintf( szValue , "%i" , _timemachineNum ) ;
    _timemachineDisplay->setString( szValue ) ;
    //_lineContainer->reset() ;
}

void ChanLayer::fallingObjectDone( CCNode * pSender )
{
    _fallingObjects->removeObject( pSender );
    pSender->stopAllActions() ;
    pSender->setRotation( 0 ) ;
    //check what the falling thing is
    /*
     if ( pSender->getTag() == kSpriteBomb )
     {
     _boom->setPosition ( pSender->getPosition() ) ;
     _boom->resetSystem() ;
     CCSprite * halo = ( CCSprite * ) _haloPool->objectAtIndex( _haloIndex ) ;
     _haloIndex ++ ;
     if ( _haloIndex == BOMB_NUM ) _haloIndex = 0 ;
     halo->setPosition( pSender->getPosition() ) ;
     halo->setVisible( true ) ;
     halo->runAction( ( CCAction * ) _haloBiggerAction->copy()->autorelease() ) ;
     halo->runAction( ( CCAction * ) _haloFadeOutAction->copy()->autorelease() ) ;
     pSender->setVisible( false ) ;
     //bomb sound
     }
     else*/
    //{
        //other sound
        pSender->setVisible( false ) ;
    //}
}

//eating food
void ChanLayer::resetBanana()
{
    if ( _fallingObjects->count() >= 50 ) return ;
    CCSprite * banana = ( CCSprite * ) _bananaPool->objectAtIndex( _bananaIndex ) ;
    _bananaIndex ++ ;
    if ( _bananaIndex == BANANA_NUM ) _bananaIndex = 0 ;
    //pick start and target position for new banana
    this->pickActions( banana , _bananaSpeed ) ;
}

void ChanLayer::resetHeatBanana()
{
    if ( _fallingObjects->count() >= 50 ) return ;
    CCSprite * heatBanana = ( CCSprite * ) _heatBananaPool->objectAtIndex( _heatBananaIndex ) ;
    _heatBananaIndex ++ ;
    if ( _heatBananaIndex == HEATBANANA_NUM ) _heatBananaIndex = 0 ;
    this->pickActions ( heatBanana , _heatBananaSpeed ) ;
}

void ChanLayer::resetColdBanana()
{
    if ( _fallingObjects->count() >= 50 ) return ;
    CCSprite * coldBanana = ( CCSprite * ) _coldBananaPool->objectAtIndex( _coldBananaIndex ) ;
    _coldBananaIndex ++ ;
    if ( _coldBananaIndex == COLDBANANA_NUM ) _coldBananaIndex = 0 ;
    this->pickActions( coldBanana, _coldBananaSpeed ) ;
}
void ChanLayer::resetApple()
{
    if ( _fallingObjects->count() >= 50 ) return ;
    CCSprite * apple = ( CCSprite * ) _applePool->objectAtIndex( _appleIndex ) ;
    _appleIndex ++ ;
    if ( _appleIndex == APPLE_NUM ) _appleIndex = 0 ;
    this->pickActions( apple , _appleSpeed );
}

void ChanLayer::resetOrange()
{
    if ( _fallingObjects->count() >= 50 ) return ;
    CCSprite * orange = ( CCSprite * ) _orangePool->objectAtIndex( _orangeIndex ) ;
    _orangeIndex ++ ;
    if ( _orangeIndex == ORANGE_NUM ) _orangeIndex = 0 ;
    this->pickActions( orange, _orangeSpeed ) ;
}

void ChanLayer::resetGrape()
{
    if ( _fallingObjects->count() >= 50 ) return ;
    CCSprite * grape = ( CCSprite * ) _grapePool->objectAtIndex( _grapeIndex ) ;
    _grapeIndex ++ ;
    if ( _grapeIndex == GRAPE_NUM ) _grapeIndex = 0 ;
    this->pickActions( grape, _grapeSpeed ) ;
}
void ChanLayer::resetWatermelon()
{
    if ( _fallingObjects->count() >= 50 ) return ;
    CCSprite * watermelon = ( CCSprite * ) _watermelonPool->objectAtIndex( _watermelonIndex ) ;
    _watermelonIndex ++ ;
    if ( _watermelonIndex == WATERMELON_NUM ) _watermelonIndex = 0 ;
    this->pickActions( watermelon, _watermelonSpeed) ;
}
void ChanLayer::resetStrawberry()
{
    if ( _fallingObjects->count() >= 50 ) return ;
    CCSprite * strawberry = ( CCSprite * ) _strawberryPool->objectAtIndex( _strawberryIndex ) ;
    _strawberryIndex  ++ ;
    if ( _strawberryIndex == STRAWBERRY_NUM ) _strawberryIndex = 0 ;
    this->pickActions( strawberry , _strawberrySpeed ) ;
}

//functional things
/*void ChanLayer::resetChocolate()
{
    if ( _fallingObjects->count( ) >= 50 ) return ;
    CCSprite * chocolate = ( CCSprite * ) _chocolatePool->objectAtIndex( _chocolateIndex ) ;
    _chocolateIndex ++ ;
    if ( _chocolateIndex == CHOCOLATE_NUM ) _chocolateIndex = 0 ;
    this->pickActions( chocolate, _chocolateSpeed );
}*/

void ChanLayer::resetRocket()
{
    if ( _fallingObjects->count() >= 50 ) return ;
    CCSprite * rocket = ( CCSprite * ) _rocketPool->objectAtIndex( _rocketIndex ) ;
    _rocketIndex ++ ;
    if ( _rocketIndex == ROCKET_NUM ) _rocketIndex = 0 ;
    this->pickActions( rocket, _rocketSpeed ) ;
}

void ChanLayer::resetTimemachine()
{
    if ( _fallingObjects->count() >= 50 ) return ;
    CCSprite * timemachine = ( CCSprite * ) _timemachinePool->objectAtIndex( _timemachineIndex ) ;
    _timemachineIndex ++ ;
    if ( _timemachineIndex == TIMEMACHINE_NUM ) _timemachineIndex = 0 ;
    this->pickActions( timemachine, _timemachineSpeed ) ;
}

void ChanLayer::pickActions(CCSprite * pSender , float fallingSpeed )
{
    int __x = rand()%( int ) ( _screenSize.width * 0.8f ) + _screenSize.width * 0.1f ;
    int __target_x = rand()% ( int )( _screenSize.width * 0.8f ) + _screenSize.width * 0.1f ;
    int __start_y  = rand()% ( int )( _screenSize.height * 0.5f ) + _screenSize.height + pSender->boundingBox().size.height  ;
    pSender->stopAllActions() ;
    pSender->setPosition( ccp ( __x , __start_y )) ;
    //create Actions for banana
    CCFiniteTimeAction * sequence = CCSequence::create ( CCMoveTo::create ( fallingSpeed*1.0/ _screenSize.height * __start_y  , ccp ( __target_x , pSender->boundingBox().size.height * 0.5 ) ) , CCCallFuncN::create ( this , callfuncN_selector( ChanLayer::fallingObjectDone )), NULL );
    pSender->setVisible( true ) ;
    pSender->runAction(( CCAction *) _rotateAction->copy()->autorelease() ) ;
    pSender->runAction( sequence ) ;
    _fallingObjects->addObject( pSender ) ;
    
}

void ChanLayer::updateEating ( float dt )
{
    //eating food
    ////
    int count ;
    int num ;
    _fruitTimer += dt ;
    if ( _fruitTimer  > _fruitCurrentInterval )
    {
        _fruitTimer = 0 ;
        _fruitCurrentInterval =( rand()% _fruitInterval + _fruitInterval )/10.0 ;
        count = rand() % 3 + 3 ;
        for ( int i = 0 ; i < count ; i ++ )
        {
            num = rand() & 7 ;
            switch ( num ) {
                case 0:
                    this->resetOrange() ;
                    break ;
                case 1:
                    this->resetGrape() ;
                    break ;
                case 2:
                    this->resetApple() ;
                    break;
                case 3:
                    this->resetWatermelon();
                    break;
                case 4:
                    this->resetStrawberry();
                    break;
                default:
                    this->resetBanana() ;
                    break;
            }
        }
        _specialCurrentTimes ++ ;
        if ( _specialCurrentTimes  == _specialIntervalTimes )
        {
            _specialCurrentTimes = 0 ;
            count = rand() & 1 ;
            if ( count == 0 )
                this->resetColdBanana() ;
            else
                this->resetHeatBanana() ;
        }
        
    }
}

void ChanLayer::updateHeatEating ( float dt )
{
    //eating food
    ////
    int count ;
    int num ;
    _fruitTimer += dt ;
    if ( _fruitTimer  > _fruitCurrentInterval )
    {
        _fruitTimer = 0 ;
        _fruitCurrentInterval =( rand()% _fruitInterval )/10.0 ;
        count = rand() % 3 + 6 ;
        for ( int i = 0 ; i < count ; i ++ )
        {
            num = rand() & 7 ;
            switch ( num ) {
                case 0:
                    this->resetOrange() ;
                    break ;
                case 1:
                    this->resetGrape() ;
                    break ;
                case 2:
                    this->resetApple() ;
                    break;
                case 3:
                    this->resetWatermelon();
                    break;
                case 4:
                    this->resetStrawberry();
                    break;
                default:
                    this->resetBanana() ;
                    break;
            }
        }
               
    }
}


void ChanLayer::updateFunction ( float dt )
{
    //functional tools
    int count ;
    int num ;
    _functionTimer += dt ;
    if ( _functionTimer > _functionCurrentInterval  )
    {
        _functionTimer = 0 ;
        ////can add difficult in here
        //_functionInterval
        _functionCurrentInterval = ( rand() % _functionInterval + _functionInterval )/10.0 ;
        count = rand()% 1 + 2 ;
        for ( int i = 0 ; i < count ; i ++ )
        {
            num = rand() & 7  ;
            if ( num < 4 )
                this->resetRocket() ;
            else
                this->resetTimemachine() ;
        }
        
    }
}

void ChanLayer::resumeChanPlaying()
{
    if ( _state == kChanHeatPlaying )
    {
        //resume speed to JiejiPlaying
        /*
        _bananaSpeed *= 2 ;
        _orangeSpeed *= 2 ;
        _grapeSpeed *= 2 ;
        _strawberrySpeed *= 2 ;
        _watermelonSpeed *= 2 ;
        _appleSpeed *= 2 ;
        */
        //resume interval to JiejiPlaying
        _fruitInterval *= 2 ;
    }
    else
        if ( _state == kChanColdPlaying )
        {
            //resume speed
            //eating
            _bananaSpeed /= 1.5 ;
            _orangeSpeed /= 1.5 ;
            _appleSpeed /= 1.5 ;
            _grapeSpeed /= 1.5 ;
            _watermelonSpeed /= 1.5 ;
            _strawberrySpeed /= 1.5 ;
            //danger
            //_bombSpeed /= 2 ;
            //_pillSpeed /= 2 ;
            //function tools
            _rocketSpeed /= 1.5 ;
            _timemachineSpeed /= 1.5 ;
            //resume interval
            //eating
            _fruitInterval *=2 ;
            //function tools
            _functionInterval *= 2 ;
        }
    _state = kChanPlaying ;
    
}
void ChanLayer::changeToHeatPlaying()
{
    //play music
    int count ;
    //add new eating food
    //change eating food falling interval and speed
    count = rand()% 5 + 4;
    for ( int i = 0 ; i < count ; i ++ )
        resetBanana() ;
    count = rand()% 2 +  2 ;
    for ( int i = 0 ; i < count ; i ++ )
    {
        resetOrange() ;
        resetApple() ;
    }
    count = rand()% 2 + 1 ;
    for ( int i = 0 ; i < count ; i ++ )
    {
        resetWatermelon() ;
        resetGrape() ;
    }
    count = rand ( )% 2 + 1 ;
    for ( int i = 0 ; i <count ; i ++ )
        resetStrawberry() ;
    //increase speed and reduce interval
    /*
    _bananaSpeed /= 2 ;
    _orangeSpeed /= 2 ;
    _appleSpeed /= 2 ;
    _watermelonSpeed /= 2 ;
    _strawberrySpeed /= 2 ;
    _grapeSpeed /= 2 ;
     */
    _fruitInterval /= 2 ;
    // start heatPlaying
    _heatPlayingTimer = 0 ;
    //change Game State HeatPlaying
    _state = kChanHeatPlaying ;
    
}
void ChanLayer::changeToColdPlaying()
{
    //decrease speed
    //eating
    _bananaSpeed *= 1.5 ;
    _orangeSpeed *= 1.5 ;
    _appleSpeed *= 1.5 ;
    _grapeSpeed *= 1.5 ;
    _watermelonSpeed *= 1.5 ;
    _strawberrySpeed *= 1.5 ;
    //danger
    //_bombSpeed *= 2 ;
    //_pillSpeed *= 2 ;
    //function tools
    _rocketSpeed *= 1.5 ;
    _timemachineSpeed *= 1.5 ;
    //decrease interval
    //eating
    _fruitInterval /= 2 ;
    //function tools
    _functionInterval /= 2 ;
    //start ColdPlaying
    _coldPlayingTimer = 0 ;
    //change Game State
    _state = kChanColdPlaying ;
    
}

void ChanLayer::killYuloow()
{
    int count ;
    CCSprite * sprite ;
    ////play music here
    //game is over , so kill all actions and display game over screen
    _state = kChanGameOver ;
    count = _fallingObjects->count() ;
    
    for ( int i = count - 1 ; i >= 0 ; i --  )
    {
        sprite = ( CCSprite * ) _fallingObjects->objectAtIndex( i ) ;
        sprite->stopAllActions() ;
        sprite->setVisible( false ) ;
    }
    _fallingObjects->removeAllObjects() ;
    _yuloow->setVisible( false ) ;
    char szValue [ 10 ] = { 0 } ;
    sprintf( szValue , "%i" , _score ) ;
    CCLabelTTF * label =( CCLabelTTF *) _gameOverScreen->getChildByTag( kGameOverScore ) ;
    label->setString( szValue ) ;
    _moveTimemachine->runAction( _timemachineComeBack ) ;
    _moveRocket->runAction( _rocketComeBack ) ;
    
    _gameOverScreen->setVisible( true ) ;
    
}
void ChanLayer::stopChanGame()
{
    //game is stop , so stop all action and display game stop menu
    SimpleAudioEngine::sharedEngine()->playEffect("button.wav");
    
    _oldstate = _state ;
    _state = kChanPausing ;
    _pausedTargets = CCDirector::sharedDirector()->getActionManager()->pauseAllRunningActions() ;
    _pausedTargets->retain ( ) ;
    //CCDirector::sharedDirector()->getActionManager()->resumeTargets(_pausedTargets ) ;
    _gamePauseScreen->setVisible( true ) ;
    _pauseMenuOff->setVisible( true ) ;
    _pauseBtn->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("btn_pause_on.png"));
    
}


void ChanLayer::quitGame()
{
    SimpleAudioEngine::sharedEngine()->playEffect("button.wav");
    CCScene* newScene = CCTransitionMoveInR::create(0.2f, MenuLayer::scene());
    CCDirector::sharedDirector()->replaceScene(newScene);
    
}
void ChanLayer::restartGame()
{
    SimpleAudioEngine::sharedEngine()->playEffect("button.wav");
    
    this->resetGame() ;
    _yuloow->changeState( kNormal ) ;
    _gameOverScreen->setVisible( false ) ;
    _state = kChanPlaying ;
    
}
void ChanLayer::resumeGame()
{
    SimpleAudioEngine::sharedEngine()->playEffect("button.wav");
    
    _gamePauseScreen->setVisible( false ) ;
    _pauseMenuOff->setVisible( false ) ;
    _pauseBtn->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("btn_pause_off.png"));
    _state = _oldstate ;
    CCDirector::sharedDirector()->getActionManager()->resumeTargets(_pausedTargets ) ;
    
}
void ChanLayer::comingFinish()
{
    _yuloow->stopAllActions() ;
    _yuloow->setPosition( ccp ( _screenSize.width * 0.5 , _yuloow->boundingBox().size.height * 0.5 ) );
    _yuloow->setComingBack( true ) ;
}

//deal with touch
void ChanLayer::ccTouchesBegan(CCSet *pTouches, CCEvent *event )
{
    CCTouch * touch ;
    CCPoint tap ;
    CCSprite * sprite  ;
    bool choose = false ;
    float durationTime ;
    float dx , dy ;
    if ( _state != kChanPausing && _state != kChanGameOver )
    {
        touch = (CCTouch *)pTouches->anyObject();
        if ( touch )
        {
            tap = touch->getLocation() ;
            //check the position is on using timemachine
            sprite = ( CCSprite * ) _gameBatchNode->getChildByTag( kSpriteTimemachineMove ) ;
            if ( _timemachineNum != 0 &&  sprite->boundingBox().containsPoint( tap ) )
            {
                _isChooseTimemachine = true ;
                sprite->setPosition( tap ) ;
                choose = true ;
            }
            //check the positoon is on using rocket
            sprite = ( CCSprite * ) _gameBatchNode->getChildByTag( kSpriteRocketMove ) ;
            if ( _rocketNum != 0 && sprite->boundingBox().containsPoint( tap ) )
            {
                _isChooseRocket = true ;
                sprite->setPosition( tap ) ;
                choose = true ;
            }
            
            if ( !_isChooseTimemachine && !_isChooseRocket )
            {
                if ( _yuloow->getComingBack() )
                {
                    _yuloow->stopAllActions() ;
                    
                    if ( _yuloow->getYuloowState() != kFly )
                    {
                        durationTime = _yuloow->getYuloowSpeed() * fabs( tap.x - _yuloow->getPositionX() )/_screenSize.width;
                        
                        _yuloow->runAction( CCMoveTo::create( durationTime , ccp ( tap.x , _yuloow->getPositionY() ) ) );
                    }
                    else
                    {
                        dx = tap.x - _yuloow->getPositionX() ;
                        dy = tap.y - _yuloow->getPositionY() ;
                        durationTime = _yuloow->getYuloowSpeed() * ( fabs ( dx ) + fabs ( dy ) )/ _screenSize.width;
                        _yuloow->setRotation( CC_RADIANS_TO_DEGREES(atan2( dx , dy)) ) ;
                        _yuloow->runAction( CCMoveTo::create ( durationTime , tap ));
                    }
                }
            }
            
        }
    }
}


void ChanLayer::ccTouchesMoved(CCSet *pTouches, CCEvent *event )
{
    CCTouch * touch ;
    CCPoint tap ;
    CCSprite * sprite ;
    float durationTime ;
    float dx , dy ;
    if ( _state != kChanPausing && _state != kChanGameOver )
    {
        touch = ( CCTouch * )pTouches->anyObject() ;
        if ( touch )
        {
            tap = touch->getLocation() ;
            //check on move chocolate , and move chocolate
            if ( _isChooseTimemachine )
            {
                sprite = ( CCSprite * ) _gameBatchNode->getChildByTag( kSpriteTimemachineMove ) ;
                sprite->setPosition( tap ) ;
            }
            else
                //check on move rocket , and move rocket
                if ( _isChooseRocket )
                {
                    sprite = ( CCSprite * ) _gameBatchNode->getChildByTag( kSpriteRocketMove ) ;
                    sprite->setPosition( tap ) ;
                }
                else
                    if( _yuloow->getComingBack ( )  )
                    {
                        _yuloow->stopAllActions() ;
                        
                        if ( _yuloow->getYuloowState() != kFly )
                        {
                            
                            durationTime = _yuloow->getYuloowSpeed() * fabs( tap.x - _yuloow->getPositionX() )/_screenSize.width ;
                            _yuloow->runAction( CCMoveTo::create ( durationTime ,ccp( tap.x , _yuloow->getPositionY() )) ) ;
                            
                        }
                        else
                        {
                            dx = tap.x - _yuloow->getPositionX() ;
                            dy = tap.y - _yuloow->getPositionY() ;
                            durationTime = _yuloow->getYuloowSpeed() * ( fabs ( dx ) + fabs ( dy ) ) /_screenSize.width ;
                            _yuloow->setRotation( CC_RADIANS_TO_DEGREES(atan2( dx , dy)) ) ;
                            _yuloow->runAction( CCMoveTo::create ( durationTime , tap ));
                            
                        }
                    }
            
        }
        
    }
}

void ChanLayer::ccTouchesEnded(CCSet *pTouches, CCEvent *event )
{
    CCTouch * touch ;
    CCPoint tap ;
    CCSprite * sprite ;
    float x1 , x2 , y1 , y2 ;
    if ( _state != kChanPausing && _state != kChanGameOver )
    {
        
        touch = (CCTouch *)pTouches->anyObject();
        if ( touch )
        {
            tap = touch->getLocation() ;
            //check if touch leave on Pause
            sprite = ( CCSprite * )_gameBatchNode->getChildByTag( kSpritePause ) ;
            if ( sprite->boundingBox().containsPoint( tap ) )
            {
                this->stopChanGame() ;
                _gamePauseScreen->setVisible( true ) ;
                _pauseMenuOff->setVisible( true  ) ;
                
            }
            //check if finger leave timemachine
            if ( _isChooseTimemachine )
            {
                
                x1 = tap.x - sprite->boundingBox().size.width * 0.5 ;
                x2 = tap.x + sprite->boundingBox().size.width * 0.5 ;
                y1 = tap.y - sprite->boundingBox().size.height * 0.5 ;
                y2 = tap.y + sprite->boundingBox().size.height * 0.5 ;
                if ( _yuloow->boundingBox().containsPoint( ccp( x1 , y1 ) ) ||
                    _yuloow->boundingBox().containsPoint( ccp( x1 , y2 ) ) ||
                    _yuloow->boundingBox().containsPoint( ccp( x2 , y1 ) ) ||
                    _yuloow->boundingBox().containsPoint( ccp( x2 , y2 ) )
                    )
                {
                    SimpleAudioEngine::sharedEngine()->playEffect("EatingChocolate.wav");
                    
                    _timemachineNum -- ;
                    _time+=TimeofTimemachine;
                    //_lineContainer->setEnergy( 1.0 ) ;
                    
                    _moveTimemachine->setPosition( _timemachinePosition ) ;
                }
                else
                {
                    _moveTimemachine->runAction( ( CCAction * ) _timemachineComeBack->copy()->autorelease() ) ;
                    
                }
                _isChooseTimemachine = false ;
            }
            //check if finger leave rocket
            if ( _isChooseRocket )
            {
                x1 = tap.x - sprite->boundingBox().size.width * 0.5 ;
                x2 = tap.x + sprite->boundingBox().size.width * 0.5 ;
                y1 = tap.y - sprite->boundingBox().size.height * 0.5 ;
                y2 = tap.y + sprite->boundingBox().size.height * 0.5 ;
                if ( _yuloow->boundingBox().containsPoint( ccp( x1 , y1 ) ) ||
                    _yuloow->boundingBox().containsPoint( ccp( x1 , y2 ) ) ||
                    _yuloow->boundingBox().containsPoint( ccp( x2 , y1 ) ) ||
                    _yuloow->boundingBox().containsPoint( ccp( x2 , y2 ) )
                    )
                {
                    
                    SimpleAudioEngine::sharedEngine()->playEffect("WearRocket.wav");
                    
                    _rocketNum -- ;
                    _yuloow->changeState( kFly ) ;
                    _moveRocket->setPosition( _rocketPosition ) ;
                }
                else
                {
                    _moveRocket->runAction( ( CCAction * ) _rocketComeBack->copy()->autorelease() ) ;
                    
                }
                _isChooseRocket = false ;
                
            }
        }
    }
    
    
}
