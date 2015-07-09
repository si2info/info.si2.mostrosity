#ifndef __AJUSTES_SCENE_H__
#define __AJUSTES_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class Ajustes : public Layer
{
    
    
public:
    
    ~Ajustes();
    void cleanMemory();
    
    static Scene* createScene();
    virtual bool init();
    virtual void onEnterTransitionDidFinish();
    virtual void onExitTransitionDidStart();
    
    //metodos
    void irAtras(Ref* pSender);
    void obtenerMedidas();
    void initFondoTemp();
    void initBotonAtras();
    void initEscuchadores();
    void initBtCreditos();
    void initBtPaginaWeb();
    void initBtLicencia();
    
    void initTitulo();
    void initAjustesIdioma();
    
    
    //musica
    Sprite *barraMusica;
    Sprite *barraEfectos;
    Sprite *btMusica;
    Sprite *btEfectos;
    bool tocaBtMusica = false;
    bool tocaBtEfecto = false;
    void initAjustesMusica();
    void initAjustesEfectos();
    void cambiarSonido(float positionX,bool fondo);
    void cambiarEfectos(float positionX);
    void situarBarrasSonido();
    
    //flag para diferenciar cuando llega de un sitio o otro
    //
    static int desdeEscena;
    static const int desdeMenu = 0;
    static const int desdeAjustes = 6;
    static const int desdeMiMostro = 5;
    static const int desdePreguntator = 1;
    static const int desdeDimeketekito = 2;
    static const int desdeArmame = 3;
    static const int desdeAkuerdate = 4;
    
    //escuchadores
    void onKeyReleased(EventKeyboard::KeyCode keyCode, Event * event);
    bool onTouchBegan(Touch *touch, Event * event);
    void onTouchMoved(Touch *touch, Event * event);
    void onTouchEnded(Touch *touch, Event * event);
    
    //elementos
    Sprite* fondoTemp;
    LayerGradient* cuadroJuego;
    MenuItemImage* botonAtras;
    CCLabelTTF* tituloEscena;
    CCLabelTTF* tituloMusica;
    CCLabelTTF* tituloEfectos;
    
    //idioma
    CCLabelTTF* tituloIdioma;
    Sprite *selector;
    Sprite *idioma1;
    Sprite *idioma2;
    Sprite *idioma3;
    void situarIdioma();
    void guardarIdioma(int idioma);
    void cambiarIdioma(Sprite *idioma,int nIdioma);
    void refrescarIdioma();
    //opcional fiel a diseño
    void initBotonesIdioma();
    void posBotonIdioma(Ref * boton);
    MenuItemImage *btEspanol;
    MenuItemImage *btIngles;
    CCLabelTTF *txEspanol;
    CCLabelTTF *txIngles;
    bool btCircularesIdioma = false;
    
    
    //medidas
    Size visibleSize;
    float anchoCE = 0.0;
    float altoCE = 0.0;
    
    Vec2 origin;
    float relacion = 0.0;
    float escala = 0.0;
    float escalaAncha = 0.0;
    float escalaAlta = 0.0;
    float anchoLateralCE = 0.0;
    float anchoNoLateralCE = 0.0;
    float altoIndividalCuadroJuego = 0.0;
    float anchoIndividualCuadroJuego = 0.0;
    
    int letraReloj = 100;
    int espacioSuperiorBtAtras = 30;
    int espacioBordesCuadro = 25;
    
    //logica
    bool escuchadores = true;
    bool comprobarToque(Touch *touch,Sprite *target);
    
    MenuItemImage *btCreditos;
    MenuItemImage *btPaginaWeb;
    MenuItemImage *btLicencia;
    Menu *menuCreditos;
    void irCreditos();
    void irPaginaWeb();
    void irWebLicencia();
    
    //activar debug o quitar
    Sprite *btDesarrollo;
    void initBtDesarrollo();
    void toogleDesarrollo();
    Sprite *btReinicio;
    void initBtReinicio();
    void toogleReinicio();
    
    CREATE_FUNC(Ajustes);
};

#endif
