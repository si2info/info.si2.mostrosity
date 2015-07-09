#ifndef __SPLASH_SCENE_H__
#define __SPLASH_SCENE_H__

#include "cocos2d.h"
#include "HelloWorldScene.h"

class Splash : public cocos2d::Layer
{
    float relacion = 0.0;
    float escala = 0.0;
    float escalaAncha = 0.0;
    float escalaAlta = 0.0;
    
    
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    HelloWorld* helloworld;
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    // a selector callback
    void irAMenu();
    void fijarFondo();
    void cargarAnimacionLogo();
    void modificarCargando();
    void fijarPublicidad();

    cocos2d::Size visibleSize;
    
    cocos2d::SpriteBatchNode *ssLogo;
    cocos2d::Sprite* sLogo;
    cocos2d::Animation* aniLogo;
    
    cocos2d::RepeatForever* secuenciaCarga;
    int nContenidoActual = 0;
    cocos2d::Array *recursos;
    void cargarContenidos();
    void iniciarCarga();
    
    
    cocos2d::CCLabelTTF* label;
    // implement the "static create()" method manually
    CREATE_FUNC(Splash);
};

#endif // __SPLASH_SCENE_H__