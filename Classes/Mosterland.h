#ifndef __MOSTERLAND_SCENE_H__
#define __MOSTERLAND_SCENE_H__

#include "cocos2d.h"
#include "CMostro.h"


class Mosterland : public cocos2d::Layer
{
    
    
public:
    
    ~Mosterland();
    void cleanMemory();
    
    //constantes de numero array en mostros
    /*
     * 0 sprite 1 sonido
     * 2 animacion 3 nombre
     */
    static const int iSpriteMostro = 0;
    static const int iSonidoMostro = 1;
    static const int iAnimacionMostro = 2;
    static const int iNombreMostro = 3;
    
    static const int iSegundosEntreEntradas = 5;
    
    static cocos2d::Scene* createScene();
    virtual bool init();
    virtual void onEnterTransitionDidFinish();
    virtual void update(float dt);
    virtual void onExitTransitionDidStart();
    
    //metodos
    void irAtras(Ref* pSender);
    void compartir(Ref* pSender);
    void obtenerMedidas();
    void initMusicaFondo();
    void playMusicaFondo();
    void initFondoTemp();
    void initBotonAtras();
    void initEscuchadores();
    void initBtCompartir();
    void mostrarSelectorCompartir();
    
    int proximoMostro = 0;
    void cargarMostrosInternet();
    void initMostroPersonal();

    cocos2d::Node* iniciarMostroObj(CMostro *mostro);
    void iniciarAnimacionMostro();
    cocos2d::Sequence *dameAnimacion(int numero);
    cocos2d::Sprite *cargarSprite(std::string ruta,float escala,float anchorX,float anchorY,float despX,float despY,int zOrder,int opacidad);
    cocos2d::Node *miMostroBase1;
    cocos2d::__Array *mostros;
    cocos2d::__Array *mostrosObj;
    
    //escuchadores activos
    bool escuchadores = true;
    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event * event);
    void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event * event);
    void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event * event);
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event);
    bool comprobarToque(cocos2d::Touch *touch,cocos2d::Sprite *sprite);
    
    //elementos
    cocos2d::Sprite* fondoTemp_i;
    cocos2d::Sprite* fondoTemp_d;
    cocos2d::MenuItemImage* botonAtras;
    
    //medidas
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;
    float relacion = 0.0;
    float escala = 0.0;
    float escalaAncha = 0.0;
    float escalaAlta = 0.0;
    float anchoLateral = 0.0;
    float anchoNoLateral = 0.0;
    int letraReloj = 100;
    int espacioSuperiorBtAtras = 50;
    int espacioBordesCuadro = 25;
    
    // Compartir
    void finAccionMenuCompartir(Ref* boton);
    void eliminarCapaLoadingCaptura();
    LayerColor *capaLoadingCaptura;
    MenuItemImage* btCompartir;
    MenuItemImage *btMenuCompartirTwitter;
    MenuItemImage *btMenuCompartirFacebook;
    MenuItemImage *btMenuCompartirCerrar;
    
    //espacio entre el centro del mostro y el suelo
    int espacioEntreFondoMostros = 500;
    
    char* cancionFondo= "mosterland_audio_fondo.mp3";
    
    int getRandom(int end);
    
    CREATE_FUNC(Mosterland);
};

#endif
