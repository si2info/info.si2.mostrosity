#include "PlantillaEscena.h"
#include "HelloWorldScene.h"
#include "Configuracion.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "JniLink.h"
#endif



USING_NS_CC;

Scene* PlantillaEscena::createScene()
{
    
    auto scene = Scene::create();
    
    auto layer = PlantillaEscena::create();
    scene->addChild(layer);
    return scene;
}

bool PlantillaEscena::init()
{
    
    if ( !Layer::init() )
    {
        return false;
    }
    this->setKeypadEnabled(true);
    
    return true;
}

void PlantillaEscena::onEnterTransitionDidFinish(){
    

    
}
