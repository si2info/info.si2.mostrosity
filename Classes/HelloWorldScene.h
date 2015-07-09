#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Layer
{
    
    
    
public:
    
    ~HelloWorld();
    void cleanMemory();
    
    //booleana para evitar dos llamar a dos escenas
    bool salir = false;
    float relacion = 0.0;
    float escala = 0.0;
    float escalaAncha = 0.0;
    float escalaAlta = 0.0;
    //margen de 4 botones
    float margen4botones = 0.0;
    bool cargado = false;
    bool empezado = false;
    int antAleatorio = 0;
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    //botones de juegos
    cocos2d::Sprite* menu_botonera_akuerdate;
    cocos2d::Sprite* menu_botonera_armame;
    cocos2d::Sprite* menu_botonera_dimeketekito;
    cocos2d::Sprite* menu_botonera_preguntator;
    
    //botones superiores
    cocos2d::Sprite* menu_bttop_config;
    cocos2d::Sprite* menu_bttop_mimostro;
    cocos2d::Sprite* menu_bttop_mosterlan;
    cocos2d::Sprite* menu_bttop_murcielago;
    cocos2d::Sprite* menu_bttop_logo;
    
    //arrayBotones
    cocos2d::__Array* botones;
    cocos2d::__Array* botonesPulsados;
    cocos2d::__Array* sImagesPulsados;
    
    cocos2d::Sprite* sprite;
    cocos2d::Animate* animate;

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    virtual void onEnterTransitionDidFinish();
    virtual void onExitTransitionDidStart();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    void irJuego(cocos2d::Ref* pSender);
    void fijarFondo();
    
    void OnAcceleration(cocos2d::Acceleration *acc, cocos2d::Event *event);
    
    //TODO MURCIELAGO
    void cargarAnimacionMurcielago();
    void activarAnimacionMurcielago(float dt);
    cocos2d::SpriteBatchNode *ssMurcielago;
    cocos2d::Sprite* sMurcielgo;
    cocos2d::Animation* aniMurcielago;
    cocos2d::Action* accMurcielago;
    cocos2d::Vector<cocos2d::SpriteFrame*>  murcielagoFrames;
    
    //TODO AKUERDATEANIMACION
    void cargarAnimacionAkuerdate();
    void activarAnimacionAkuerdate(float dt);
    void updateAnimacionAkuerdate();
    cocos2d::SpriteBatchNode *ssAkuerdate;
    cocos2d::Sprite* sAkuerdate;
    cocos2d::Animation* aniAkuerdate;
    cocos2d::Action* accAkuerdate;
    
    //TODO ARMAMEANIMACION
    void cargarAnimacionArmame();
    void activarAnimacionArmame(float dt);
    void updateAnimacionArmame();
    cocos2d::SpriteBatchNode *ssArmame;
    cocos2d::Sprite* sArmame;
    cocos2d::Animation* aniArmame;
    cocos2d::Action* accArmame;
    
    
    //TODO DIMEKETEKITOANIMACION
    void cargarAnimacionDimeketekito();
    void activarAnimacionDimeketekito(float dt);
    void updateAnimacionDimeketekito();
    cocos2d::SpriteBatchNode *ssDimeketekito;
    cocos2d::Sprite* sDimeketekito;
    cocos2d::Animation* aniDimeketekito;
    cocos2d::Action* accDimeketekito;
    
    
    //TODO PREGUNTATORANIMACION
    void cargarAnimacionPreguntator();
    void activarAnimacionPreguntator(float dt);
    void updateAnimacionPreguntator();
    cocos2d::SpriteBatchNode *ssPreguntator;
    cocos2d::Sprite* sPreguntator;
    cocos2d::Animation* aniPreguntator;
    cocos2d::Action* accPreguntator;
    
    
    //TODO CONFIGURACION
    void cargarAnimacionConfiguracion();
    void activarAnimacionConfiguracion(float dt);
    void updateAnimacionConfiguracion();
    cocos2d::SpriteBatchNode *ssConfiguracion;
    cocos2d::Sprite* sConfiguracion;
    cocos2d::Animation* aniConfiguracion;
    cocos2d::Action* accConfiguracion;
    
    
    //TODO MIMOSTRO
    void cargarAnimacionMimostro();
    void activarAnimacionMimostro(float dt);
    cocos2d::SpriteBatchNode *ssMimostro;
    cocos2d::Sprite* sMimostro;
    cocos2d::Animation* aniMimostro;
    cocos2d::Action* accMimostro;
    
    //TODO MOSTERLAND
    void cargarAnimacionMosterland();
    void activarAnimacionMosterland(float dt);
    cocos2d::SpriteBatchNode *ssMosterland;
    cocos2d::Sprite* sMosterland;
    cocos2d::Animation* aniMosterland;
    cocos2d::Action* accMosterland;
    void finAnimacionMosterland();
    bool MostrarMosterlandFinAnimacion = false;
    
    
    //ESCENAS Y NAVEGACION
    void irEscenaPreguntator();
    void irEscenaArmame();
    void irEscenaAkuerdate();
    void irEscenaDimeketekito();
    void irEscenaAjustes();
    void irEscenaMiMostro();
    void irEscenaMosterland();
    void irEscenaAcerca();
    
    //GENERAL
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event);
    void fuera(cocos2d::Ref* pSender);
    void loadingCallBack(cocos2d::CCObject *obj);
    void cargarTextos();
    void cargarMusica();
    void cargarBotonesMenu();
    void iniciarEscena();
    void iniciarCargas();
    int aleatorioVecesAnimacionMurcielago();
    bool escuchadorMurcielago = true;
    void desplazarMurcielago();
    void batirAlasMurcielago();
    void comenzarBatidaAlas();
    void terminarBatidaAlas();
    int nBatidaAlasParaMovimiento = 2;//sin desarrollo seria 3 (por ejemplo)
    int nBatidasActual = 0;
    float tiempoBatidaNormal = 10;//normal 10 segundos
    int ultimaAnimacionMurcielago = 0;
    
    cocos2d::Size visibleSize;
    
    //toques de pantalla
    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event * event);
    void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event * event);
    void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event * event);
    bool comprobarToque(cocos2d::Touch *touch,cocos2d::Node *sprite);
    void comprobarToques(int modo,cocos2d::Touch *touch);
    void comprobarPulsado(cocos2d::Touch *touch,int modo);
    
    //capaSalir
    cocos2d::LayerColor* capaSalir;
    cocos2d::Label* labelCapaSalir;
    void quitarCapaSalir();
    
    // Cambio de idioma?
    int oldLanguage;
    void eliminarTextosBotones();
    
    void getIdMiMostro();
    
    // Textos botones de juego
    cocos2d::LabelTTF* label;
    cocos2d::CCLabelTTF* label2;
    cocos2d::CCLabelTTF* label3;
    cocos2d::CCLabelTTF* label4;
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
