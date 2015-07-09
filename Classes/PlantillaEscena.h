#ifndef __PLANTILLAESCENA_SCENE_H__
#define __PLANTILLAESCENA_SCENE_H__

#include "cocos2d.h"

using namespace cocos2d;

class PlantillaEscena : public cocos2d::Layer
{
    
    
public:
   
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    virtual void onEnterTransitionDidFinish();
    // a selector callback
    
    
    CREATE_FUNC(PlantillaEscena);
};

#endif
