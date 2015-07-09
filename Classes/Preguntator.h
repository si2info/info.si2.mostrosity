#ifndef __PREGUNTATOR_SCENE_H__
#define __PREGUNTATOR_SCENE_H__

#include "cocos2d.h"
#include "CPreguntasPreguntator.h"

class Preguntator : public cocos2d::Layer
{
	

public:
    
    ~Preguntator();
    void cleanMemory();
    
    // Juego ya iniciado
    bool running;
    
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
    void initReloj();
    void initProfesor();
    void initBocadillo();
    void initTextoCentral();
    void initBtAjustes();
    void selectorAjustes(Ref *pSender);
    void cambiarTextoDialogo(std::string texto);
    void modificarTXTDialogo();
    void vaciarTXTDialogo();
    void rellamarTXTDialogo();
    __Array *textosProfesor;

    void initCuadroJuego();
    void initCuadroInicial();
    void initPlataformas();
    cocos2d::__Array *aPlataformas;
    
    std::string textoProximoBocadillo;
    
    //escuchadores
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event);

    //elementos interfaz
    cocos2d::Menu* menu;
    cocos2d::CCLabelTTF* reloj;
    cocos2d::MenuItemImage* botonAtras;
    cocos2d::Layer* cuadroJuego;
    cocos2d::Sprite* bocadillo;
    cocos2d::CCLabelTTF* cuadroDialogo;
    cocos2d::Sprite* sCuadroPregunta;
    cocos2d::CCLabelTTF* lbCuadroPregunta;
    cocos2d::LayerColor* capaFondoCuadroInicial;
    cocos2d::LayerColor* capaTextoCuadroInicial;
    cocos2d::CCLabelTTF* lbCuadroInicial;
    MenuItemImage* btAjustes;
    
    //profesor
    float anchoProfesor = 0.0;
    float altoProfesor = 0.0;
    
    float altoBarba = 0;
    float altoBigote = 0;
    float altoCejas = 0;
    float altoOjos = 0;
    
    cocos2d::Sprite* profesor;
    cocos2d::Sprite *profBarba;
    cocos2d::Sprite *profBigote;
    cocos2d::Sprite *profCejas;
    cocos2d::Sprite *profOjos;
    void ProfesorLeyendoHablando();
    void ProfesorFalloRespuesta();
    void ProfesorAciertaRespuesta();
    void ProfesorNuevaPregunta();
    
    //dialogoComenzar
    cocos2d::LayerColor* dial1_bg;
    cocos2d::Menu* dial1_menu;
    cocos2d::MenuItem* dial1_Imenu1;
    cocos2d::MenuItem* dial1_Imenu2;
    cocos2d::CCLabelTTF* dial1_titulo;
    cocos2d::CCLabelTTF* dial1_Imenu1_text;
    cocos2d::CCLabelTTF* dial1_Imenu2_text;
    void dial1_Imenu2_resp1(Ref* sender);
    void dial1_Imenu2_resp2(Ref* sender);
    
    
    //respuestas
    cocos2d::__Array *respuestasMostruos;
    
    //resposivo
    float escalaPropiaBocadillo = 0.0;
    float escalaPropiaPlataformas = 0.0;
    
    //cuadroJuego
    float altoIndividalCuadroJuego = 0.0;
    float anchoIndividualCuadroJuego = 0.0;
    
    //medidas
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;
    float relacion = 0.0;
    float escala = 0.0;
    float escalaAncha = 0.0;
    float escalaAlta = 0.0;
    float anchoLateral = 0.0;
    float anchoNoLateral = 0.0;
    float anchoLateralCE = 0.0;
    float anchoNoLateralCE = 0.0;
    
    // implement the "static create()" method manually
    CREATE_FUNC(Preguntator);
    
    bool isPlayNarracion = false;
    
    //LOGICA
    int letraReloj = 100;
    int espacioSuperiorBtAtras = 50;
    int espacioBordesCuadro = 25;
    int proximaPregunta = 0;
    int tiempoRestante = 0;
    int tiempoOriginal = 0;
    int aciertos = 0;
    int maxAciertos = 5;
    bool escuchadores = true;
    bool escuchadoresPregunta = false;
    bool juegoTerminado = false;
    
    void mostrarDialogoComenzar();
    void ocultarDialogoComenzar();
    void crearDialogoComenzar();
    void comenzarReloj();
    void aumentarReloj(float dt);
    
        //aciertos
        void actualizarAciertos();
        cocos2d::Sprite *sAciertos;
        cocos2d::CCLabelTTF* txAciertos;
    
        //juegoTerminado
        void JuegoTerminado();
    
        //preguntas
        cocos2d::__Array *preguntas;
        cocos2d::__Array *PreguntasRealizadas;

        cocos2d::__String* obtenerRespuesta(int iNRespuesta);
        void initPreguntas();
        void iniciarSiguientePregunta();
        void mostrarPregunta();
        void reproducirPregunta();
        void activarEscuchadorPregunta();
        void modificarLabelPregunta();
        int aleatorioPreguntaProxima();
    
        //mostros
        int ultimoMostroBueno = -1;
        void initMostros();
        void quitarMostros();
        void mostrosRespuestaFeelback(cocos2d::Sprite *target,bool respuesta);
    
    
        //TRAS JSON
        CPreguntasPreguntator *gPreguntas;
        int nPreguntas;
        LayerColor *marcoRespuestas;
    
    
        //narraciones
        cocos2d::Sequence *narracion;
        int narracionActual = 0;
        void saltarAnimacion();
        void comenzarNarracion();
        void narracion1();
        void narracion2();
        void narracion3();
        void narracion4();
        
        //toques de pantalla
        bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event * event);
        void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event * event);
        void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event * event);
    
};

#endif // __PREGUNTATOR_SCENE_H__
