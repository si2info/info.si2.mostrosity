#ifndef __MIMOSTRO_SCENE_H__
#define __MIMOSTRO_SCENE_H__

#include "cocos2d.h"
#include "CGestorRecursos.h"
#include "CRecurso.h"
#include "../extensions/cocos-ext.h"
#include "../cocos2d/cocos/network/HttpClient.h"


using namespace cocos2d;
using namespace network;
using namespace extension;


class MiMostro : public cocos2d::Layer, public EditBoxDelegate
{
    
    
public:
    
    ~MiMostro();
    void cleanMemory();
    
    static cocos2d::Scene* createScene();
    virtual bool init();
    virtual void onEnterTransitionDidFinish();
    virtual void onExitTransitionDidStart();
    void update(float dt);
    
    //metodos
    void irAtras(Ref* pSender);
    
    //compartir
    void initBtCompartir();
    void selectorCompartir();
    bool crearCaptura();
    void posCapturaMostro();
    LayerColor *capaLoadingCaptura;
    LabelTTF *capaLoadingCapturaTxt;
    void mostrarCapaLoadingCaptura();
    void eliminarCapaLoadingCaptura();
    void mostrarSelectorCompartir();
    void finAccionMenuCompartir(Ref* boton);
    Menu *menuCompartir;
    MenuItemImage *btMenuCompartirTwitter;
    MenuItemImage *btMenuCompartirFacebook;
    MenuItemImage *btMenuCompartirCerrar;

    //sincronizar
    void sincronizar();
    void sincronizado(HttpClient *sender, HttpResponse *response);
    
    // Nombre mi Mostro
    void showEditBox();
    void hideEditBox();
    EditBox *myName;
    
    void initMusica();
    void obtenerMedidas();
    void initFondoTemp();
    void initBotonAtras();
    void initTxtLateral();
    void initCuadroJuego();
    //contenido cuadro
    void selectorGeneral(Ref* pSender);
        //BOTONES
        MenuItemImage *btColor;
        MenuItemImage *btAjustes;
        MenuItemImage *btCompartir;
        void initBtColor();
        void initBtAjustes();
        void selectorColor();
        void cambiarColorBT(Ref* pSender);
        void cambiarColor(int nColor);
    
    
        int indiceSonidoLabel = 0;
        int indiceSonidoValue = 1;
        LabelTTF *uiLabelSonido;
    
        
        void initBtSonido();
        void selectorSonido();
        void cambiarSonidoBT(Ref* pSender);
        void cambiarSonido(int nColor,bool reproducir);
        __String *obtenerDatoSonido(int indice);
        MenuItemImage *btSonido;
    
        void selectorAjustes();
        //CAJAS
        void initCajas();
        void iniciarCajaXNumero(int nCaja);
        void iniciarCajaXRecurso(int nRecurso);
        __Array * aCapasPartesHor;
        __Array * aCapasPartesVer;
        void initCapasPartes();
        int comprobarToqueCajas(Touch * toque);
        Sprite* cjHori;
        Sprite* cjVert;
        std::string obtenerTextoCaja(bool Hori,int iNumero);
        Color3B obtenerColorTxtCaja(bool Hori,int iNumero);
            //CAJAS CONSTANTES
                //horizontales
                enum cajas
                {
                    nCajaOjos = 0,
                    nCajaDientes=1,
                    nCajaOrejas=2,
                    nCajaBrazos=3,
                    //verticales
                    nCajaAccesorios=4,
                    nCajaPelo=5,
                    nCajaAlas=6,
                    nCajaPatas = 7
                };

    
            //CAJAS SELECT & CHANGER
            void selectorRecurso();
            void cambiarRecursoBT(Ref* pSender);
            void cambiarRecurso(CGestorRecursos::TIPOS Tipo,int nELemento);
            int obtenerActualCodRecurso(CGestorRecursos::TIPOS Tipo);
            int guardarActualCodRecurso(CGestorRecursos::TIPOS Tipo,int codElemento);
            Sprite* obtenerPartePorTipo(CGestorRecursos::TIPOS Tipo);
    
    
    
    
        //MOSTRO
        int comprobarToquePartes(Touch * toque);
        void initMostro();
        void initMostroPropiedades(CGestorRecursos::TIPOS tipo);
        LayerColor *mostro;
        Sprite *mostro_cuerpo;
        Sprite *mostro_pies;
        Sprite *mostro_ojos;
        Sprite *mostro_orejas;
        Sprite *mostro_boca;
        Sprite *mostro_brazos;
        Sprite *mostro_pelo;
        Sprite *mostro_alas;
        Sprite *mostro_accesorio;
    
        //RECURSOS
        void initRecursos();
        __Array* recursosBloqueados = NULL;
        bool recursoBloqueado(CRecurso *recurso);
        CGestorRecursos *gRecursos = NULL;
        CTipoRecurso *ultimoTipoRecurso = NULL;
        __Array *tiposRecursos = NULL;
        CGestorRecursos::TIPOS TipoRecursoSelecionado;
    
    
    //Ventana Modal scroll
    void cerrarModal(cocos2d::Ref *pSender);
    void destrozarModal();
    void initModal(int tipo,__Array* elementos);
    void desplazarModal(int nElemento);
    int modalConMenu = 0;
    __Array *ultimoArrayPasado;
    
    float altoModal = 1000;
    float altoModalCE = 1000;
    Color3B verdeModal = Color3B(216,254,51);
    float tamLetraModalTitulo = 120;
    float tamLetraModalTituloCE = 120;
    float margenModal = 50;
    
    LayerColor *bgModal;
    LayerColor *modal;
    LabelTTF *modalTitulo;
    Sprite *spBtDesplizamiento;
    Sprite *spBarraBtDesplizamiento;
    void desplazarBtDesplizamiento(float xPos);
    bool moviendoScroll = false;
    
    LayerColor *fondoContenedor;
    ScrollView *scrollView;
    Layer *scrollContainer;
    float anchoBtDespCE = 0;
    float anchoContenedorScroll = 0;
    float anchoScrollView = 0;
    float altoContenedorScroll = 0;
    
    float anchoUltElementoCE = 0;
    float margenElementosCE = 0;
    void DesplazarIzquierda(Ref* pSender);
    void DesplazarDerecha(Ref* pSender);
    void UpdateScrollView(float dt);
    
    
    
    //elementos interfaz
    Menu* menu;
    Sprite* fondoTemp;
    MenuItemImage* botonAtras;
    Layer* cuadroJuego;
    Layer* cuadroJuegoInterior;
    
    //medidas
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;
    float espacioSuperiorBtAtras = 50;
    float espacioSuperiorBtAtrasCE = 50;
    float espacioBordesCuadro = 25;
    float espacioBordesCuadroCE = 25;
    float relacion = 0.0;
    float escala = 0.0;
    float escalaAncha = 0.0;
    float escalaAlta = 0.0;
    float escalaCajas = 0.0;
    float anchoLateralCE = 0.0;
    float anchoNoLateralCE = 0.0;
    float tamLetra = 60;
    float tamLetraCE = 60;
    float tamLetraMiMostro = 70;
    float margenLetras = 0;
    float margenLetrasCE = 0;
    //cuadroJuego
    float altoIndividalCuadroJuego = 0.0;
    float anchoIndividualCuadroJuego = 0.0;
    //cajas
    float margenEntreCajas = 15;
    float margenEntreCajasCE = 15;
    int opacidadCapasSeleccion = 0;
    /*
    float anchoCajaVertical = 360;
    float anchoCajaVerticalCE = 0;
    float altoCajaVertical = 1150;
    float altoCajaVerticalCE = 0;
    
    float anchoCajaHorizontal = 1380;
    float anchoCajaHorizontalCE = 0;
    float altoCajaHorizontal = 320;
    float altoCajaHorizontalCE = 0;
    */
    
    
    CREATE_FUNC(MiMostro);
    
    //escuchadores
        //toques de pantalla
        bool escuchadores = false;
        bool escuchadoresBtyCapas = false;
        void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event);
        bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event * event);
        void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event * event);
        void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event * event);
        //teclas
    
    //interfaz de delegado de editbox
    virtual void editBoxEditingDidBegin(EditBox* editBox);
    virtual void editBoxEditingDidEnd(EditBox* editBox);
    virtual void editBoxTextChanged(EditBox* editBox, const std::string& text);
    virtual void editBoxReturn(EditBox* editBox);
    
    // Cambio de idioma?
    int oldLanguage;
    LabelTTF *textSonido;
    void eliminarTextos();
    
    
};

#endif
