#ifndef __DIMEKETEKITO_SCENE_H__
#define __DIMEKETEKITO_SCENE_H__

#include "cocos2d.h"
#include "CGestorRecursos.h"

using namespace cocos2d;

class Dimeketekito : public cocos2d::Layer
{
    
    
public:
    
    ~Dimeketekito();
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
    
    void initMesaFondo();
    void initCuadroJuego();
    void initCuadroInicial();
    
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
    Sprite *mesaFondo;
    
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
    
    
    
    //botes
    float maxAltoContenidoBote = 200;
    int entidadExito = -1;
    bool cogidaParte = false;
    bool rozadoBote = false;
    Sprite *spCogido;
    Sprite *spCogidoClon;
    
    int aciertos = 0;
    int nBotes = 5;
    float margenBotes = 20;
    int altoCapaBotes = 300;
    LayerColor *capaBotes;
    __Array *aBotes;
    void initBotes();
    void asignarNBotes();
    void rellenarBotes();
    bool disponibleBoteXParte(int numero);
    bool comprobarToquePartesMostro(Touch *toque);
    void desplazarParteMostro(Touch *toque);
    void rozandoBote(Touch *toque);
    void stopAnimBotesGiro(bool forzar);
    void stopAnimBotesGiroShedule(float seg);
    void reproducirToqueBote();
    
    void comprobarExitoParteMostro(Touch *toque);
    int parteMostroFalsa = -1;
    Sprite* obtenerBotePorEntidad(int entidad);
    void falloDesplazamiento();
    void reinicioPartes();
    
    //MOSTRO
    CGestorRecursos *gRecursos = NULL;
    void initGestorRecursos();
    void initMostro();
    void initMostroPropiedades(CGestorRecursos::TIPOS tipo);
    void mostrarMostro();
    TintTo* obtenerTintatoAleatorio();
    TintTo *tintado;
    LayerColor *mostro;
    Sprite *mostro_cuerpo;
    Sprite *mostro_pies;
        Sprite *mostro_pie_izq;
        Sprite *mostro_pie_der;
    Sprite *mostro_ojos;
    Sprite *mostro_orejas;
        Sprite *mostro_oreja_izq;
        Sprite *mostro_oreja_der;
    Sprite *mostro_boca;
    Sprite *mostro_brazos;
        Sprite *mostro_brazo_izq;
        Sprite *mostro_brazo_der;
    Sprite *mostro_pelo;
    Sprite *mostro_alas;
    Sprite *mostro_accesorio;
    
    CRecurso* recursoMostro_pies;
    CRecurso* recursoMostro_ojos;
    CRecurso* recursoMostro_orejas;
    CRecurso* recursoMostro_boca;
    CRecurso* recursoMostro_brazos;
    CRecurso* recursoMostro_pelo;
    CRecurso* recursoMostro_alas;
    
    //resposivo
    float escalaPropiaBocadillo = 0.0;
    float escalaPropiaPlataformas = 0.0;
    
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
    
    
    //juegoTerminado
    void JuegoTerminado();
    
    
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

    CREATE_FUNC(Dimeketekito);
};

#endif
