//
//  LineContainer.cpp
//  Yuloow
//
//  Created by luyifan on 13-11-22.
//
//

#include "LineContainer.h"
LineContainer::LineContainer()
{
    _screenSize = CCDirector::sharedDirector()->getWinSize() ;
    _energyLineX = _screenSize.width * 0.99 ;
    _energyHeight = _screenSize.height * 0.6 ;
    glLineWidth( 8.0* CC_CONTENT_SCALE_FACTOR() ) ;
    this->reset ( ) ;
}

LineContainer * LineContainer::create()
{
    LineContainer * node = new LineContainer() ;
    if ( node )
    {
        node->autorelease();
        return node ;
    }
    CC_SAFE_DELETE(node);
    return NULL ;
}

void LineContainer::reset()
{
    _energy = 1.0 ;
    _energyDecrement = 0.04f ;
    
}

void LineContainer::update(float dt)
{
    _energy -= _energyDecrement*dt ;
    if ( _energy < 0 )
        _energy = 0 ;
}
void LineContainer::addEnergy(float value )
{
    _energy += value ;
    if( _energy > 1 )
        _energy = 1 ;
    
}

void LineContainer::setEnergyDecrement(float value)
{
    _energyDecrement += value ;
    //
    if ( _energyDecrement > 0.07 ) _energyDecrement = 0.07 ;
}

void LineContainer::draw()
{
    //draw energy bar
    ccDrawColor4F(0.0, 0.0, 0.0, 1.0);
    glLineWidth( _screenSize.width * 0.005 );
    ccDrawLine( ccp( _energyLineX ,  _screenSize.height * 0.3 ) ,
               
                ccp( _energyLineX ,  _screenSize.height * 0.9 ) ) ;
    if ( _energy > 0.2 )
        ccDrawColor4F(1.0, 0.5, 0.0, 1.0 ) ;
    else
        ccDrawColor4F(1.0, 0.0, 0.0, 1.0 ) ;
    ccDrawLine( ccp ( _energyLineX , _screenSize.height * 0.3 ) ,
               ccp ( _energyLineX , _screenSize.height * 0.3 + _energy * _energyHeight ));

}
