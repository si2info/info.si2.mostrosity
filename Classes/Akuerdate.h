#ifndef __AKUERDATE_SCENE_H__
#define __AKUERDATE_SCENE_H__

#include "cocos2d.h"
#include "CProfesionAkuerdate.h"

using namespace cocos2d;

class Akuerdate : public cocos2d::Layer
{
    
    
public:
    
    ~Akuerdate();
    void cleanMemory();
    
    // Juego ya iniciado
    bool running;
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static Scene* createScene();
    
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
    void initBtAtras();
    void initBtAjustes();
    void selectorAjustes(Ref *pSender);
    void initReloj();
    void initProfesor();
    void initBocadillo();
    void initTextoCentral();
    void cambiarTextoDialogo(std::string texto);
    void modificarTXTDialogo();
    void vaciarTXTDialogo();
    void rellamarTXTDialogo();
    __Array *textosProfesor;
    
    
    void initCuadroJuego();
    void initCuadroInicial();
    
    bool bocadilloAbierto = false;
    std::string textoProximoBocadillo;
    
    //escuchadores
    void onKeyReleased(EventKeyboard::KeyCode keyCode, Event * event);
    
    //elementos interfaz
    Menu* menu;
    LabelTTF* reloj;
    MenuItemImage* btAtras;
    MenuItemImage* btAjustes;
    Layer* cuadroJuego;
    Sprite* bocadillo;
    LabelTTF* cuadroDialogo;
    LayerColor* capaFondoCuadroInicial;
    LayerColor* capaTextoCuadroInicial;
    LabelTTF* lbCuadroInicial;
    
    //profesor
    float anchoProfesor = 0.0;
    float altoProfesor = 0.0;
    
    float altoBarba = 0;
    float altoBigote = 0;
    float altoCejas = 0;
    float altoOjos = 0;
    
    Sprite* profesor;
    Sprite *profBarba;
    Sprite *profBigote;
    Sprite *profCejas;
    Sprite *profOjos;
    void ProfesorLeyendoHablando();
    void ProfesorFalloRespuesta();
    void ProfesorAciertaRespuesta();
    void ProfesorNuevaPregunta();
    
    //dialogoComenzar
    LayerColor* dial1_bg;
    Menu* dial1_menu;
    MenuItem* dial1_Imenu1;
    MenuItem* dial1_Imenu2;
    LabelTTF* dial1_titulo;
    LabelTTF* dial1_Imenu1_text;
    LabelTTF* dial1_Imenu2_text;
    void dial1_Imenu2_resp1(Ref* sender);
    void dial1_Imenu2_resp2(Ref* sender);
    
    
    
    //PROFESIONES
    bool escuchadorElementos = false;
    int aciertos = 0;
    int nAciertos = 4;
    
    int aciertosPorInteraccion = 0;
    
    CProfesionAkuerdate *gProfesion;
    __String* sNombreProfesion;
    __Array *aElementosProfesion;
    
    
    void initConfiguracion();

    Sprite *panelElementos;
    void initPanelElementos();
    Sprite *panelPalabras;
    float margenPanelPalabrasInterno = 30;
    float margenPanelPalabrasInternoCE = 30;
    void initPanelPalabras();
    void desordenarElementos();
    
    //tramiento
    int tagActual = 0;//utilizado para obtener el txt y audio del sprite
    int elementoActual = -1;//elemento por el que voy en el recorrido
    int cantidadActual = 1;//numero de elementos en ese recorrido
    
    void inicioELEMENTO();
        //retorna el tag que es el asociativo con los demas.
    void pintoElementos();
    void recorroElemento();
    void pintoPalabra();
    void reproducirAudio();
    void finIteraccionPalabras();
    int velocidad = 0.8;//1 normal 0.5 doble mas rapido etc
    
    
    //debug
    void initPintarPalabras();
    
    void comenzarJuego();
    bool comprobarToqueElemento(Touch *toque);
    void comprobarExitoElemento(Touch *toque);
    Sprite* obtenerElementoPorNumero(int numero);
    void falloToqueElemento();
    void borrarElementos();
    void reiniciarElementos();
    void JuegoTerminado();
    
    //resposivo
    float escalaPropiaBocadillo = 0.0;
    float escalaPanel = 0.0;
    
    //cuadroJuego
    float altoIndividalCuadroJuego = 0.0;
    float anchoIndividualCuadroJuego = 0.0;
    
    
    
    //medidas
    Size visibleSize;
    Vec2 origin;
    float relacion = 0.0;
    float escala = 0.0;
    float escalaAncha = 0.0;
    float escalaAlta = 0.0;
    float anchoLateralCE = 0.0;
    float anchoNoLateralCE = 0.0;
    
    
    bool isPlayNarracion = false;
    
    //LOGICA
    float letraReloj = 100;
    float tamLetra = 100;
    float tamLetraCE = 100;
    float espacioSuperiorBtAtras = 50;
    float espacioSuperiorBtAtrasCE = 50;
    float espacioBordesCuadro = 25;
    float espacioBordesCuadroCE = 25;
    int proximaPregunta = 0;
    int tiempoRestante = 0;
    int tiempoOriginal = 0;
    bool escuchadores = false;
    bool juegoTerminado = false;
    
    void mostrarDialogoComenzar();
    void ocultarDialogoComenzar();
    void crearDialogoComenzar();
    void comenzarReloj();
    void aumentarReloj(float dt);
    
    

    
    
    //narraciones
    Sequence *narracion;
    int narracionActual = 0;
    void saltarAnimacion();
    void comenzarNarracion();
    void narracion1();
    void narracion2();
    void narracion3();
    void narracion4();
    
    //toques de pantalla
    bool onTouchBegan(Touch *touch, Event * event);
    void onTouchMoved(Touch *touch, Event * event);
    void onTouchEnded(Touch *touch, Event * event);
    
    int mostrados = 0;
    
    // implement the "static create()" method manually
    CREATE_FUNC(Akuerdate);
    
    
};

#endif
