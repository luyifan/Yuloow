//
//  LoadingChan.h
//  Yuloow
//
//  Created by luyifan on 13-12-22.
//
//

#ifndef __Yuloow__LoadingChan__
#define __Yuloow__LoadingChan__
#include "cocos2d.h"
USING_NS_CC ;
class LoadingChan : public CCLayer
{
    private :
    CCSize _screenSize ;
    
public:
    LoadingChan() ;
    ~LoadingChan() ;
    
    virtual bool init ( ) ;
    
    CREATE_FUNC(LoadingChan ) ;
    
    static CCScene * scene ( ) ;
    
    
private:
    void createScreen ( ) ;
    void gameStart ( ) ;
    
    
};
#endif /* defined(__Yuloow__LoadingChan__) */
