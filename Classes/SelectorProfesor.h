#ifndef __SELECTORPROFESOR_SCENE_H__
#define __SELECTORPROFESOR_SCENE_H__

#include "cocos2d.h"
#include "HelloWorldScene.h"

USING_NS_CC;

class SelectorProfesor : public cocos2d::Layer
{
    bool escuchadores = false;
    float relacion = 0.0;
    float escala = 0.0;
    float escalaAncha = 0.0;
    float escalaAlta = 0.0;
    float margen = 30;
    float margenCE = 30;
    
    
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    HelloWorld* helloworld;
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    virtual void onExitTransitionDidStart();
    // a selector callback
    void fijarFondo();
    void irAMenu();
    void initMusica();
    void initTitulo();
    void initParrafos();
    void initProfesores();
    void initPiesProfesores();
    void selectorGeneral(Ref *pSender);
    
    
    LabelTTF *titulo;
    LabelTTF *parrafoCentral;
    LabelTTF *pieProfesor1;
    LabelTTF *pieProfesor2;
    Menu *menu;
    MenuItem *btProfesor1;
    MenuItem *btProfesor2;
    Size visibleSize;

    // implement the "static create()" method manually
    CREATE_FUNC(SelectorProfesor);
};

#endif // __SPLASH_SCENE_H__
