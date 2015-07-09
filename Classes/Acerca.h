#ifndef __ACERCA_SCENE_H__
#define __ACERCA_SCENE_H__

#include "cocos2d.h"
#include "../extensions/cocos-ext.h"

using namespace cocos2d;
using namespace extension;

class Acerca : public cocos2d::Layer
{
	

public:
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    virtual void onEnterTransitionDidFinish();
    virtual void onExitTransitionDidStart();
    // a selector callback
    
    //metodos de interfaz
    void irAtras(Ref* pSender);
    void obtenerMedidas();
    void initFondo();
    void initMusica();
    void initBotonAtras();
    void initCuadroJuego();
    
    // Banner lateral
    static char * paginaDocentic;
    static char * paginaCMI;
    static char * paginaSI2;
    Sprite *logoSI2;
    Sprite *logoInma;
    Sprite *logoDocen;
    
    //PIZZARRA
    void initPizzarra();
    void initBannerLateral();
    void initContenidoPizzarra();
    Sprite *pizarra;
    LayerColor *contenedorPizarra;
    ScrollView *scrollView;
    Layer *scrollContainer;
    
    //CONTENIDO PIZZARA
    float anchoPizarra = 0;
    float altoPizarra = 0;
    float altoContPizzaraEnPizzaras = 2.50;
    int letraPizzara = 60;
    int margenLetrasPizarra = 20;
    int margenPizzaraBordes = 150;
    
    
    //flag para diferenciar cuando llega de un sitio o otro
    //0 menu 1 ajustes 2 mimostro
    static int desdeEscena;
    static const int desdeMenu = 0;
    static const int desdeAjustes = 1;
    static const int desdeMiMostro = 2;
    
    //escuchadores
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event);

    //elementos interfaz
    cocos2d::Menu* menu;
    cocos2d::Sprite* fondoTemp_i;
    cocos2d::Sprite* fondoTemp_d;
    cocos2d::MenuItemImage* botonAtras;
    cocos2d::Layer* cuadroJuego;
    cocos2d::CCLabelTTF* cuadroDialogo;
    
    
    //respuestas
    cocos2d::__Array *respuestasMostruos;
    
    //cuadroJuego
    float altoIndividalCuadroJuego = 0.0;
    float anchoIndividualCuadroJuego = 0.0;
    
    //medidas
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;
    int espacioSuperiorBtAtras = 50;
    int espacioSuperiorBtAtrasCE = 0;
    int espacioBordesCuadro = 25;
    float relacion = 0.0;
    float escala = 0.0;
    float escalaAncha = 0.0;
    float escalaAlta = 0.0;
    float anchoLateral = 0.0;
    float anchoNoLateral = 0.0;
    
    // implement the "static create()" method manually
    CREATE_FUNC(Acerca);
    
         //toques de pantalla
        bool escuchadores = false;
        bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event * event);
        void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event * event);
        void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event * event);
};

#endif // __PREGUNTATOR_SCENE_H__
