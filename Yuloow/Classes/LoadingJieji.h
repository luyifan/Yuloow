//
//  LoadingJieji.h
//  Yuloow
//
//  Created by luyifan on 13-12-17.
//
//

#ifndef __Yuloow__LoadingJieji__
#define __Yuloow__LoadingJieji__
#include "cocos2d.h"
USING_NS_CC ;
class LoadingJieji : public CCLayer
{
private :
    CCSize _screenSize ;
    
public:
    LoadingJieji() ;
    ~LoadingJieji() ;
    
    virtual bool init ( ) ;
    
    CREATE_FUNC(LoadingJieji ) ;
    
    static CCScene * scene ( ) ;
    
    
private:
    void createScreen ( ) ;
    void gameStart ( ) ;
    
    
};
#endif /* defined(__Yuloow__LoadingJieji__) */
