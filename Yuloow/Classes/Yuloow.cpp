//
//  Yuloow.cpp
//  Yuloow
//
//  Created by luyifan on 13-12-3.
//
//

#include "Yuloow.h"
Yuloow::Yuloow ( void ):
_yuloowState( kNormal )
{
    
    _screenSize = CCDirector::sharedDirector()->getWinSize() ;
    _isComingBack = true ;
    this->reset ( ) ;
}
Yuloow::~Yuloow( void )
{
    
}
Yuloow * Yuloow::create (  )
{
    Yuloow * sprite = new Yuloow ( ) ;
    if ( sprite && sprite->initWithSpriteFrameName("Yuloow.png"));
    {
        sprite->autorelease() ;
        return sprite ;
    }
    CC_SAFE_DELETE( sprite ) ;
    return NULL ;
}
void Yuloow::update(float dt)
{
    
    if ( _yuloowState == kFly )
    {
        _yuloowFlyTimer += dt ;
    
        if ( _yuloowFlyTimer > _yuloowFlyInterval )
        {
            _isComingBack = false ;
            changeState( kNormal );
            this->runAction( CCSequence::create( CCSpawn::create( CCFadeIn::create ( 1 ) , CCMoveTo::create( 1 , ccp ( _screenSize.width * 0.5 , this->boundingBox().size.height * 0.5 )) , NULL ) ,CCCallFunc::create( this ,callfunc_selector (Yuloow::comingFinish)) , NULL ));
        }
    }
    else
    if ( _yuloowState == kNude )
    {
        _yuloowNudeTimer += dt ;
        if ( _yuloowNudeTimer > _yuloowNudeInterval )
            changeState( kNormal ) ;
    }
    else
    if ( _yuloowState == kScorch )
    {
        _yuloowScorchTimer += dt ;
        if ( _yuloowScorchTimer > _yuloowScorchInterval )
            changeState( kNormal ) ;
    }
    else
    if ( _yuloowState != kNormal && _yuloowState != kWearSkirt )
    {
        _yuloowChangeTimer += dt ;
        if ( _yuloowChangeTimer > _yuloowChangeInterval )
            changeState( kNormal ) ;
    }
   // CCPoint position = this->getPosition() ;
   // position.x += _vector.x * _speed * dt ;
   // position.y += _vector.y * _speed * dt ;
   // this->setPosition( position ) ;
   // collidedWithSides( ) ;
}
void Yuloow::reset ( void )
{
   // _speed = kNormalSpeed ;
   // _vector = ccp( 0 , 0 ) ;
    this->setPosition( ccp( _screenSize.width * 0.5 , this->boundingBox().size.height * 0.5 ) );
    _yuloowNudeInterval = kYuloowNudeInterval ;
    _yuloowScorchInterval = kYuloowScorchInterval ;
    _yuloowChangeInterval = kYuloowChangeColorInterval ;
    _yuloowScorchInterval = kYuloowScorchInterval ;
    _yuloowFlyInterval = kYuloowFlyInterval ;
}
/*bool Yuloow::collidedWithSides( void )
{
    bool isCollided = false ;
    float width = this->boundingBox().size.width * 0.5 ;
    float height = this->boundingBox().size.height * 0.5 ;
    if ( m_tPosition.x > _screenSize.width - width )
    {
        m_tPosition.x = _screenSize.width - width ;
        isCollided = true ;
        _vector.x =  - this->getVector().x ;
    }
    if ( m_tPosition.x < width )
    {
        m_tPosition.x = width ;
        isCollided = true ;
        _vector.x = - this->getVector().x ;
    }
    if ( m_tPosition.y > _screenSize.height - height )
    {
        m_tPosition.y = _screenSize.height - height ;
        isCollided = true ;
        _vector.y = - this->getVector().y ;
    }
    if ( m_tPosition.y < height )
    {
        m_tPosition.y = height ;
        isCollided = true ;
        _vector.y = - this->getVector().y ;
    }
    //if ( isCollided && _yuloowState != kFly )
     //   _vector.x = 0 ;
    return isCollided ;
}
 */
void Yuloow::comingFinish()
{
    _isComingBack = true ;
}
void Yuloow::changeState ( YuloowState state )
{
    YuloowState oldState = _yuloowState ;
    CCSpriteFrame * frame ;
    if ( oldState == state )
    {
        switch ( _yuloowState )
        {
            case kGrapeColor :
            case kOrangeColor:
            case kWatermelonColor:
            case kAppleColor:
            case kStrawberryColor:
                _yuloowChangeTimer = 0 ;
                break ;
            case kScorch:
                _yuloowScorchTimer = 0 ;
                break ;
            case kFly:
                _yuloowFlyTimer = 0 ;
                break ;
            case kNude:
                _yuloowNudeTimer = 0 ;
                break ;
            default:
                break;
                
        }
        return ;
    }
    if ( oldState == kFly )
    {
        if ( state != kScorch && state != kNormal && state != kNude )
       // this->setPosition( ccp ( _screenSize.width * 0.5 , _screenSize.height * 0.5 )) ;
        return ;
    }
    if (  oldState == kNude || oldState == kScorch || oldState == kWearSkirt )
    {
        if ( state == kAppleColor || state == kOrangeColor || state == kGrapeColor || state == kWatermelonColor || state == kStrawberryColor)
            return ;
        
    }
    _yuloowState = state ;
    
    switch ( _yuloowState )
    {
        case kNormal :  frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Yuloow.png") ; _speed = kNormalSpeed ; break ;
        case kGrapeColor :  frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("grapeYuloow.png"); _speed = kOtherColorSpeed ; _yuloowChangeTimer = 0 ; break ;
        case kOrangeColor : frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("orangeYuloow.png"); _speed = kOtherColorSpeed ; _yuloowChangeTimer = 0 ; break ;
        case kWatermelonColor: frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("watermelonYuloow.png"); _speed = kOtherColorSpeed ; _yuloowChangeTimer = 0 ; break ;
        case kAppleColor : frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName( "appleYuloow.png" );         _speed = kOtherColorSpeed ; _yuloowChangeTimer = 0 ; break ;
        case kStrawberryColor: frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("strawberryYuloow.png");  _speed = kOtherColorSpeed ; _yuloowChangeTimer = 0 ; break ;
        case kScorch: frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("scorchYuloow.png"); _speed = kScorchSpeed ; _yuloowScorchTimer = 0 ; break ;
        case kWearSkirt: frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("skirtYuloow.png");
            _speed = kNormalSpeed; break ;
        case kFly: frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("flyYuloow.png");
            _speed = kFlySpeed; _yuloowFlyTimer = 0 ; break ;
        case kNude: frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("nudeYuloow.png");
            _speed = kNudeSpeed ; _yuloowNudeTimer = 0 ; break ;
        
    }
    this->setDisplayFrame( frame ) ;
    if ( oldState == kFly )
    {
        this->setRotation( 0 ) ;
        //this->setPosition( ccp ( _screenSize.width * 0.5, this->boundingBox().size.height * 0.5 )) ;
    }
    else
    if ( _yuloowState == kFly )
    {
        //fly up
 //       _vector = ccp ( 0 , 1 ) ;
    }
}

YuloowState Yuloow::getYuloowState()
{
    return _yuloowState ;
}
void Yuloow::resetYuloowScorchTimer()
{
    _yuloowScorchTimer = 0 ;
}
float Yuloow::getYuloowSpeed ( )
{
    return _speed ;
}