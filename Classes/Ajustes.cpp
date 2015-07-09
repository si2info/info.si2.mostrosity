
#include "Ajustes.h"
#include "HelloWorldScene.h"
#include "Configuracion.h"
#include "LanguageManager.h"
#include "Acerca.h"
#include "MiMostro.h"
#include "Preguntator.h"
#include "Dimeketekito.h"
#include "Armame.h"
#include "Akuerdate.h"
#include "SimpleAudioEngine.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "JniLink.h"
#include "JniHelper.h"
#endif


USING_NS_CC;
int Ajustes::desdeEscena = 0;
Scene* Ajustes::createScene()
{
    
    auto scene = Scene::create();
    
    auto layer = Ajustes::create();
    scene->addChild(layer);
    return scene;
}

bool Ajustes::init()
{
    
    if ( !Layer::init() )
    {
        return false;
    }
    this->setKeypadEnabled(true);

    obtenerMedidas();
    initFondoTemp();
    initBotonAtras();
    //initBtDesarrollo();
    //initBtReinicio();
    return true;
}

void Ajustes::onEnterTransitionDidFinish(){
    if(Configuracion::desarrollo)
        CCLOG("idioma %i",Configuracion::idioma);
    initTitulo();
    initAjustesIdioma();
    situarIdioma();
    
    //opcional fiel a diseño
    initBotonesIdioma();
    //lo ultimo
    initEscuchadores();
    
    initAjustesMusica();
    initAjustesEfectos();
    initBtCreditos();
    initBtPaginaWeb();
    initBtLicencia();
    situarBarrasSonido();
    
}

void Ajustes::onExitTransitionDidStart() {
    
    cleanMemory();
    
}

Ajustes::~Ajustes() {
    
    cleanMemory();
    
}

void Ajustes::cleanMemory() {
    
    CCDirector::sharedDirector()->purgeCachedData();
    
    CCTextureCache::sharedTextureCache()->removeUnusedTextures();
    CCTextureCache::sharedTextureCache()->removeAllTextures();
    CCTextureCache::purgeSharedTextureCache();
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames();
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFrames();
    CCSpriteFrameCache::purgeSharedSpriteFrameCache();
    
    SpriteFrameCache::getInstance()->removeUnusedSpriteFrames();
    
}

void Ajustes::initBtDesarrollo(){
    btDesarrollo = Sprite::create("logoSI2.png");
    btDesarrollo->setScale(escala);
    btDesarrollo->setAnchorPoint(Vec2(1,0));
    btDesarrollo->setPosition(visibleSize.width-(espacioBordesCuadro*escala*2),0+(espacioBordesCuadro*escala*2));
    btDesarrollo->setLocalZOrder(20);
    this->addChild(btDesarrollo);
}

void Ajustes::toogleDesarrollo(){
    if(Configuracion::desarrollo == false)
        Configuracion::desarrollo = true;
    else
        Configuracion::desarrollo = false;
}

void Ajustes::initBtReinicio(){
    btReinicio = Sprite::create("logoSI2ReiniciarDatos.png");
    btReinicio->setScale(escala);
    btReinicio->setAnchorPoint(Vec2(1,0));
    btReinicio->setPosition(visibleSize.width-(btDesarrollo->getContentSize().width*btDesarrollo->getScaleX())-(espacioBordesCuadro*escala*2),0+(espacioBordesCuadro*escala*2));
    btReinicio->setLocalZOrder(20);
    this->addChild(btReinicio);
}
void Ajustes::toogleReinicio(){
    Configuracion::reiniciarDatos();
    refrescarIdioma();
}

void Ajustes::obtenerMedidas(){
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    
    relacion = visibleSize.width/visibleSize.height;
    escalaAncha = visibleSize.width/2560;
    escalaAlta = visibleSize.height/1600;
    if(escalaAncha>escalaAlta){
        escala = escalaAncha;
    }else{
        escala = escalaAlta;
    }
    
    //no hay que aplicar escala al ser relativo al visibleSize
    anchoLateralCE = (visibleSize.width/100)*20;
    anchoNoLateralCE = ((visibleSize.width/100)*80);
    anchoCE = visibleSize.width;
    altoCE = visibleSize.height;
}

void Ajustes::initBotonAtras(){
    botonAtras = MenuItemImage::create("preguntator_bt_atras.png","preguntator_bt_atras_down.png",CC_CALLBACK_1(Ajustes::irAtras, this));
    
    botonAtras->setScale(escala);
    botonAtras->setAnchorPoint(Vec2(0, 1));
    //calculo espacio sobrante
    float espacio = anchoLateralCE-(botonAtras->getContentSize().width*escala);
    
    botonAtras->setPosition(0+(espacio/2),visibleSize.height-(espacioSuperiorBtAtras*escala));
    
    auto menu = Menu::create(botonAtras, NULL);
    menu->setPosition(Vec2::ZERO);
    botonAtras->setZOrder(10);
    this->addChild(menu, 1);
}

void Ajustes::initEscuchadores(){
    //activo los tocuh de pantalla
    auto listener1 = EventListenerTouchOneByOne::create();
    listener1->setSwallowTouches(true);
    listener1->onTouchBegan = CC_CALLBACK_2(Ajustes::onTouchBegan, this);
    listener1->onTouchMoved = CC_CALLBACK_2(Ajustes::onTouchMoved, this);
    listener1->onTouchEnded = CC_CALLBACK_2(Ajustes::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);
}

void Ajustes::initTitulo(){
    LayerColor *capaPosTitulo = LayerColor::create(Color4B(23, 70, 108, 210), cuadroJuego->getContentSize().width-(espacioBordesCuadro*escala*2), 200*escala);
    capaPosTitulo->setAnchorPoint(Vec2(0,1));
    capaPosTitulo->setPosition(anchoLateralCE+(espacioSuperiorBtAtras*escala),visibleSize.height-(200*escala)-(espacioSuperiorBtAtras*escala));
    capaPosTitulo->setZOrder(1);
    this->addChild(capaPosTitulo);
    

    tituloEscena = CCLabelTTF::create(LanguageManager::getInstance()->getString("AjustesLbTitulo"), "HVD_Comic_Serif_Pro.ttf", 130*escala,CCSizeMake(anchoNoLateralCE, capaPosTitulo->getContentSize().height), TextHAlignment::CENTER);
    tituloEscena->setColor(Color3B(216,254,51));
    tituloEscena->setVerticalAlignment(TextVAlignment::CENTER);
    tituloEscena->setAnchorPoint(Vec2(0, 0));
    tituloEscena->setPosition(anchoLateralCE,capaPosTitulo->getPositionY());
    tituloEscena->setZOrder(10);
    this->addChild(tituloEscena, 1);
    tituloEscena->retain();

}

void Ajustes::initBotonesIdioma(){
    std::string rutaImagenEs = "ajustes_bt_idiomas.png";
    std::string rutaImagenEn = "ajustes_bt_idiomas_disable.png";
    if(Configuracion::idioma ==2/*ingles*/){
        rutaImagenEs = "ajustes_bt_idiomas_disable.png";
        rutaImagenEn = "ajustes_bt_idiomas.png";
    }
    
    btEspanol = MenuItemImage::create(rutaImagenEs, rutaImagenEs, CC_CALLBACK_1(Ajustes::posBotonIdioma, this));
    btEspanol->setScale(escala);
    btEspanol->setAnchorPoint(Vec2(1,0.5));
    btEspanol->setPosition(idioma2->getPositionX()-(20*escala),idioma1->getPositionY());
    
    btIngles = MenuItemImage::create(rutaImagenEn, rutaImagenEn, CC_CALLBACK_1(Ajustes::posBotonIdioma, this));
    btIngles->setScale(escala);
    btIngles->setAnchorPoint(Vec2(0,0.5));
    btIngles->setPosition(idioma2->getPositionX()+(20*escala),idioma1->getPositionY());
    
    int altoBotonIdioma = btEspanol->getContentSize().height;
    int anchoBotonIdioma = btEspanol->getContentSize().width;
    
    txEspanol = CCLabelTTF::create(LanguageManager::getInstance()->getString("AjustesBtIdiomaEs"), "HVD_Comic_Serif_Pro.ttf", altoBotonIdioma-(60),CCSizeMake(anchoBotonIdioma,altoBotonIdioma), TextHAlignment::CENTER);
    txEspanol->setColor(Color3B(255,255,255));
    txEspanol->setVerticalAlignment(TextVAlignment::CENTER);
    txEspanol->setAnchorPoint(Vec2(0, 0));
    btEspanol->addChild(txEspanol);
    
    
    txIngles = CCLabelTTF::create(LanguageManager::getInstance()->getString("AjustesBtIdiomaEn"), "HVD_Comic_Serif_Pro.ttf", altoBotonIdioma-(60),CCSizeMake(anchoBotonIdioma,altoBotonIdioma), TextHAlignment::CENTER);
    txIngles->setColor(Color3B(255,255,255));
    txIngles->setVerticalAlignment(TextVAlignment::CENTER);
    txIngles->setAnchorPoint(Vec2(0, 0));
    btIngles->addChild(txIngles);
    
    
    
    Menu *menuIdiomas = Menu::create(btEspanol,btIngles, NULL);
    menuIdiomas->setPosition(Vec2::ZERO);
    menuIdiomas->setLocalZOrder(15);
    if(!btCircularesIdioma)
        this->addChild(menuIdiomas);
}

void Ajustes::posBotonIdioma(Ref* boton){
    bool cambio = false;
    if(boton == btEspanol&&Configuracion::idioma!=1){
        cambio = true;
    }else if(boton == btIngles&&Configuracion::idioma!=2){
        cambio = true;
    }
    
    
    if(cambio){
        refrescarIdioma();
        
        if(boton == btEspanol){
            CCLOG("ESCOGIDO EL ESPAÑOL");
            Sprite *imgNormal1 = dynamic_cast<Sprite*>(btEspanol->getNormalImage());
            imgNormal1->setTexture("ajustes_bt_idiomas.png");
            Sprite *imgUp1 = dynamic_cast<Sprite*>(btEspanol->getSelectedImage());
            imgUp1->setTexture("ajustes_bt_idiomas.png");
            
            Sprite *imgNormal2 = dynamic_cast<Sprite*>(btIngles->getNormalImage());
            imgNormal2->setTexture("ajustes_bt_idiomas_disable.png");
            Sprite *imgUp2 = dynamic_cast<Sprite*>(btIngles->getSelectedImage());
            imgUp2->setTexture("ajustes_bt_idiomas_disable.png");
            
            guardarIdioma(1);
        }else{
            CCLOG("ESCOGIDO EL INGLES");
            
            Sprite *imgNormal1 = dynamic_cast<Sprite*>(btEspanol->getNormalImage());
            imgNormal1->setTexture("ajustes_bt_idiomas_disable.png");
            Sprite *imgUp1 = dynamic_cast<Sprite*>(btEspanol->getSelectedImage());
            imgUp1->setTexture("ajustes_bt_idiomas_disable.png");
            
            Sprite *imgNormal2 = dynamic_cast<Sprite*>(btIngles->getNormalImage());
            imgNormal2->setTexture("ajustes_bt_idiomas.png");
            Sprite *imgUp2 = dynamic_cast<Sprite*>(btIngles->getSelectedImage());
            imgUp2->setTexture("ajustes_bt_idiomas.png");
            
            guardarIdioma(2);
        }
    }
}

void Ajustes::initAjustesIdioma(){
    tituloIdioma = CCLabelTTF::create(LanguageManager::getInstance()->getString("AjustesLbIdioma"), "HVD_Comic_Serif_Pro.ttf", 100*escala,Size(anchoNoLateralCE, 140*escala), TextHAlignment::CENTER);
    tituloIdioma->setColor(Color3B(23,70,108));
    tituloIdioma->setVerticalAlignment(TextVAlignment::CENTER);
    tituloIdioma->setAnchorPoint(Vec2(0, 0));
    tituloIdioma->setPosition(tituloEscena->getPositionX(),tituloEscena->getPositionY()-(tituloEscena->getContentSize().height*escala)-(50*escala));
    tituloIdioma->setZOrder(10);
    this->addChild(tituloIdioma, 1);
    tituloIdioma->retain();
    
    
    selector = Sprite::create("ajustes_selector_idioma.png");
    selector->setScale(escala);
    selector->setAnchorPoint(Vec2(0.5,0.5));
    selector->setZOrder(10);
    
    float altoSelectorCE = tituloIdioma->getContentSize().height*escala;
    
    Vec2 posIdioma1 = Vec2(anchoLateralCE+((anchoNoLateralCE/4)*1),tituloIdioma->getPositionY()-(altoSelectorCE)-(50*escala));
    Vec2 posIdioma2 = Vec2(anchoLateralCE+((anchoNoLateralCE/4)*2),tituloIdioma->getPositionY()-(altoSelectorCE)-(50*escala));
    Vec2 posIdioma3 = Vec2(anchoLateralCE+((anchoNoLateralCE/4)*3),tituloIdioma->getPositionY()-(altoSelectorCE)-(50*escala));
    
    
    idioma1 = Sprite::create("ajustes_idioma_1.png");
    idioma1->setScale(escala);
    idioma1->setAnchorPoint(Vec2(0.5,0.5));
    idioma1->setPosition(posIdioma1);
    idioma1->setZOrder(11);
    
    
    idioma2 = Sprite::create("ajustes_idioma_2.png");
    idioma2->setScale(escala);
    idioma2->setAnchorPoint(Vec2(0.5,0.5));
    idioma2->setPosition(posIdioma2);
    idioma2->setZOrder(11);
    
    
    idioma3 = Sprite::create("ajustes_idioma_3.png");
    idioma3->setScale(escala);
    idioma3->setAnchorPoint(Vec2(0.5,0.5));
    idioma3->setPosition(posIdioma3);
    idioma3->setZOrder(11);
    
    //agrego a la pantalla
    this->addChild(idioma1);
    this->addChild(idioma2);
    this->addChild(idioma3);
    this->addChild(selector);
    
    //aplico visibilidad segun constante
    idioma1->setVisible(btCircularesIdioma);
    idioma2->setVisible(btCircularesIdioma);
    idioma3->setVisible(btCircularesIdioma);
    selector->setVisible(btCircularesIdioma);
    
    switch (Configuracion::idioma) {
        case 1:
            selector->setPosition(posIdioma1);
            break;
        case 2:
            selector->setPosition(posIdioma2);
            break;
        case 3:
            selector->setPosition(posIdioma3);
            break;
            
        default:
            break;
    }
    
    
}

void Ajustes::cambiarIdioma(Sprite *sIdioma,int nIdioma){
    bool refrescar = true;
    if(nIdioma == Configuracion::idioma){
        refrescar = false;
    }
    
    MoveTo *movimiento = MoveTo::create(0.3, sIdioma->getPosition());
    CallFunc *runCallBack = CallFunc::create(CC_CALLBACK_0(Ajustes::refrescarIdioma, this));
    if(refrescar){
        selector->runAction(Sequence::create(movimiento,runCallBack,NULL));
    }else{
        selector->runAction(Sequence::create(movimiento,NULL));
    }
    
    guardarIdioma(nIdioma);
    
}

void Ajustes::refrescarIdioma(){
    LanguageManager::getInstance()->recompilar();
    
//    auto scene = Ajustes::createScene();
//    auto transicion = TransitionFade::create(0.5f, scene);
//    Director::getInstance()->replaceScene(transicion);
    
    Director::getInstance()->popScene();
    auto scene = Ajustes::createScene();
    Director::getInstance()->pushScene(scene);
    
}

void Ajustes::initBtCreditos(){
    btCreditos = MenuItemImage::create("ajustes_btCreditos.png", "ajustes_btCreditos_down.png", callfunc_selector(Ajustes::irCreditos));
    btCreditos->setScale(escalaAncha);
    btCreditos->setAnchorPoint(Vec2(0,0));
    btCreditos->setPosition(espacioSuperiorBtAtras*escala,visibleSize.height/2);
    
    menuCreditos = Menu::create(btCreditos, NULL);
    menuCreditos->setPosition(Vec2::ZERO);
    botonAtras->setZOrder(10);
    menuCreditos->retain();
    this->addChild(menuCreditos, 1);
    
    //btCreditosTexto
    CCLabelTTF *lbBtCreditos = CCLabelTTF::create(LanguageManager::getInstance()->getString("AjustesBtCreditos"), "HVD_Comic_Serif_Pro.ttf", 70,Size(btCreditos->getContentSize().width, 120), TextHAlignment::CENTER);
    lbBtCreditos->setColor(Color3B(255,255,255));
    lbBtCreditos->setVerticalAlignment(TextVAlignment::CENTER);
    lbBtCreditos->setAnchorPoint(Vec2(0.5,0));
    lbBtCreditos->setPosition(btCreditos->getContentSize().width/2,0);
    btCreditos->addChild(lbBtCreditos, 1);
    
}

void Ajustes::initBtPaginaWeb(){
    btPaginaWeb = MenuItemImage::create("ajustes_btPaginaWeb.png", "ajustes_btPaginaWeb_down.png", callfunc_selector(Ajustes::irPaginaWeb));
    btPaginaWeb->setScale(escalaAncha);
    btPaginaWeb->setAnchorPoint(Vec2(0,1));
    btPaginaWeb->setPosition(espacioSuperiorBtAtras*escala,visibleSize.height/2-(espacioSuperiorBtAtras*escalaAncha));
    
    if(menuCreditos == NULL){
        menuCreditos = Menu::create(btPaginaWeb, NULL);
        menuCreditos->setPosition(Vec2::ZERO);
        botonAtras->setZOrder(10);
        this->addChild(menuCreditos, 1);
    }else{
        menuCreditos->addChild(btPaginaWeb);
    }
    
    
    //btCreditosTexto
    CCLabelTTF *lbBtPaginaWeb = CCLabelTTF::create(LanguageManager::getInstance()->getString("AjustesBtPaginaWeb"), "HVD_Comic_Serif_Pro.ttf", 70,Size(btPaginaWeb->getContentSize().width, 120), TextHAlignment::CENTER);
    lbBtPaginaWeb->setColor(Color3B(255,255,255));
    lbBtPaginaWeb->setVerticalAlignment(TextVAlignment::CENTER);
    lbBtPaginaWeb->setAnchorPoint(Vec2(0,0));
    lbBtPaginaWeb->setPosition(0,0);
    btPaginaWeb->addChild(lbBtPaginaWeb);
    
}

void Ajustes::initBtLicencia(){
    
    btLicencia = MenuItemImage::create("ajustes_btPaginaWeb.png", "ajustes_btPaginaWeb_down.png", callfunc_selector(Ajustes::irWebLicencia));
    btLicencia->setScale(escalaAncha);
    btLicencia->setAnchorPoint(Vec2(0,1));
    btLicencia->setPosition(espacioSuperiorBtAtras*escala,visibleSize.height/4-(espacioSuperiorBtAtras*escalaAncha));
    
    if(menuCreditos == NULL){
        menuCreditos = Menu::create(btLicencia, NULL);
        menuCreditos->setPosition(Vec2::ZERO);
        botonAtras->setZOrder(10);
        this->addChild(menuCreditos, 1);
    }else{
        menuCreditos->addChild(btLicencia);
    }
    
    
    //btCreditosTexto
    CCLabelTTF *lbBtLicencia = CCLabelTTF::create(LanguageManager::getInstance()->getString("AjustesBtLicencia"), "HVD_Comic_Serif_Pro.ttf", 70,Size(btLicencia->getContentSize().width, 120), TextHAlignment::CENTER);
    lbBtLicencia->setColor(Color3B(255,255,255));
    lbBtLicencia->setVerticalAlignment(TextVAlignment::CENTER);
    lbBtLicencia->setAnchorPoint(Vec2(0,0));
    lbBtLicencia->setPosition(0,0);
    btLicencia->addChild(lbBtLicencia);
    
}

void Ajustes::irCreditos(){
    
//    Acerca::desdeEscena = Acerca::desdeAjustes;
//    auto scene = Acerca::createScene();
//    auto transicion = TransitionFade::create(0.3f, scene);
//    Director::getInstance()->replaceScene(transicion);
    
    auto scene = Acerca::createScene();
    Director::getInstance()->pushScene(scene);

}

void Ajustes::irPaginaWeb(){
    
    Configuracion::callOpenURL(Configuracion::paginaWeb);
    
}

void Ajustes::irWebLicencia() {
    
    Configuracion::callOpenURL(Configuracion::paginaLicencia);
    
}

void Ajustes::initAjustesMusica(){
    tituloMusica = CCLabelTTF::create(LanguageManager::getInstance()->getString("AjustesLbMusica"), "HVD_Comic_Serif_Pro.ttf", 100*escala,Size(anchoNoLateralCE, 120*escala), TextHAlignment::CENTER);
    tituloMusica->setColor(Color3B(23,70,108));
    tituloMusica->setVerticalAlignment(TextVAlignment::CENTER);
    tituloMusica->setAnchorPoint(Vec2(0, 1));
    tituloMusica->setPosition(tituloIdioma->getPositionX(),btEspanol->getPositionY()-(btEspanol->getContentSize().height*escala));
    tituloMusica->setZOrder(10);
    this->addChild(tituloMusica, 1);
    tituloMusica->retain();
    
    barraMusica = Sprite::create("ajustes_barra_sonido.png");
    barraMusica->setScale(escala);
    barraMusica->setAnchorPoint(Vec2(0.5,0.5));
    barraMusica->setPosition(anchoLateralCE+(anchoNoLateralCE/2),tituloMusica->getPositionY()-(tituloMusica->getContentSize().height)-(espacioSuperiorBtAtras*escala));
    barraMusica->setZOrder(10);
    this->addChild(barraMusica,1);
    barraMusica->retain();
    
    btMusica = Sprite::create("ajustes_bt_sonido.png");
    btMusica->setScale(escala);
    btMusica->setAnchorPoint(Vec2(0.5,0.5));
    btMusica->setPosition(anchoCE/2,barraMusica->getPositionY());
    btMusica->setZOrder(10);
    this->addChild(btMusica,1);
    btMusica->retain();
    
}

void Ajustes::initAjustesEfectos(){
    tituloEfectos = CCLabelTTF::create(LanguageManager::getInstance()->getString("AjustesLbEfectos"), "HVD_Comic_Serif_Pro.ttf", 100*escala,Size(anchoNoLateralCE, 120*escala), TextHAlignment::CENTER);
    tituloEfectos->setColor(Color3B(23,70,108));
    tituloEfectos->setVerticalAlignment(TextVAlignment::CENTER);
    tituloEfectos->setAnchorPoint(Vec2(0, 1));
    tituloEfectos->setPosition(tituloMusica->getPositionX(),tituloMusica->getPositionY()-(tituloMusica->getContentSize().height)-(barraMusica->getContentSize().height*escala)-(espacioSuperiorBtAtras*escala*2));
    tituloEfectos->setZOrder(10);
    this->addChild(tituloEfectos, 1);
    tituloEfectos->retain();
    
    barraEfectos = Sprite::create("ajustes_barra_sonido.png");
    barraEfectos->setScale(escala);
    barraEfectos->setAnchorPoint(Vec2(0.5,0.5));
    barraEfectos->setPosition(anchoLateralCE+(anchoNoLateralCE/2),tituloEfectos->getPositionY()-(tituloEfectos->getContentSize().height)-(espacioSuperiorBtAtras*escala));
    barraEfectos->setZOrder(10);
    this->addChild(barraEfectos,1);
    barraEfectos->retain();
    
    btEfectos = Sprite::create("ajustes_bt_sonido.png");
    btEfectos->setScale(escala);
    btEfectos->setAnchorPoint(Vec2(0.5,0.5));
    btEfectos->setPosition(anchoCE/2,barraEfectos->getPositionY());
    btEfectos->setZOrder(10);
    this->addChild(btEfectos,1);
    btEfectos->retain();
}

void Ajustes::cambiarSonido(float positionX,bool fondo){
    float min = 0.0;
    float max = 0.0;
    if(!fondo){
        min = barraEfectos->getPositionX()-((barraEfectos->getContentSize().width*escala)/2);
        max = barraEfectos->getPositionX()+((barraEfectos->getContentSize().width*escala)/2);
    }else{
        min = barraMusica->getPositionX()-((barraMusica->getContentSize().width*escala)/2);
        max = barraMusica->getPositionX()+((barraMusica->getContentSize().width*escala)/2);
    }
    float maxOriginal = max-min;
    float valorOriginal = positionX-min;
    float porcentaje = (floorf((100*valorOriginal)/maxOriginal))/100;
    
    UserDefault *preferencias = UserDefault::getInstance();
    if(positionX>min&&positionX<max){
        if(!fondo){
            btEfectos->setPositionX(positionX);
            Configuracion::volumenEfectos = porcentaje;
            CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(Configuracion::volumenEfectos);
            preferencias->setFloatForKey("volEfectos", porcentaje);
        }else{
            btMusica->setPositionX(positionX);
            Configuracion::volumenMusica = porcentaje;
            CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(Configuracion::volumenMusica);
            preferencias->setFloatForKey("volMusica", porcentaje);
        }
    }
}

void Ajustes::situarBarrasSonido(){
    float minE = barraEfectos->getPositionX()-((barraEfectos->getContentSize().width*escala)/2);
    float maxE = barraEfectos->getPositionX()+((barraEfectos->getContentSize().width*escala)/2);
    
    float valorOriginalE = Configuracion::volumenEfectos*100;
    float pixelXUnidadE = (maxE-minE)/100;
    float posicionFinalE = minE+(pixelXUnidadE*valorOriginalE);
    if(Configuracion::desarrollo)
        CCLOG("[AJUSTES->situarBarraSonido EFECTOS] min %f max %f posicionfinal %f porcentaje %f ",minE,maxE,posicionFinalE,valorOriginalE);
    btEfectos->setPositionX(posicionFinalE);
    
    
    float minM = barraMusica->getPositionX()-((barraMusica->getContentSize().width*escala)/2);
    float maxM = barraMusica->getPositionX()+((barraMusica->getContentSize().width*escala)/2);
    
    float valorOriginalM = Configuracion::volumenMusica*100;
    float pixelXUnidadM = (maxM-minM)/100;
    float posicionFinalM = minM+(pixelXUnidadM*valorOriginalM);
    
    if(Configuracion::desarrollo)
        CCLOG("[AJUSTES->situarBarraSonido MUSICA] min %f max %f posicionfinal %f porcentaje %f ",minM,maxM,posicionFinalM,valorOriginalM);
    btMusica->setPositionX(posicionFinalM);
    
    
}

void Ajustes::situarIdioma(){
    switch (Configuracion::idioma) {
        case 1:
            cambiarIdioma(idioma1,1);
            break;
        case 2:
            cambiarIdioma(idioma2,2);
            break;
        case 3:
            cambiarIdioma(idioma3,3);
            break;
    }
    
}

void Ajustes::guardarIdioma(int nIdioma){
    Configuracion::idioma = nIdioma;
    UserDefault *preferencias = UserDefault::getInstance();
    preferencias->setIntegerForKey("idioma", nIdioma);
    LanguageManager::getInstance()->recompilar();
}


void Ajustes::irAtras(Ref* pSender)
{
    if(Configuracion::desarrollo)
        CCLOG("atras");
    
    if(desdeEscena!=desdeMenu){
        CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
        CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    }
    
    Director::getInstance()->popScene();
    
//    if(desdeEscena==desdeAjustes){
//        
//        auto scene = Ajustes::createScene();
//        auto transicion = TransitionFade::create(0.3f, scene);
//        Director::getInstance()->replaceScene(transicion);
//        
//    }else if(desdeEscena==desdeMiMostro){
//        
//        auto scene = MiMostro::createScene();
//        auto transicion = TransitionFade::create(0.3f, scene);
//        Director::getInstance()->replaceScene(transicion);
//        
//    }else if(desdeEscena==desdePreguntator){
//        
//        auto scene = Preguntator::createScene();
//        auto transicion = TransitionFade::create(0.3f, scene);
//        Director::getInstance()->replaceScene(transicion);
//        
//    }else if(desdeEscena==desdeDimeketekito){
//        
//        auto scene = Dimeketekito::createScene();
//        auto transicion = TransitionFade::create(0.3f, scene);
//        Director::getInstance()->replaceScene(transicion);
//        
//    }else if(desdeEscena==desdeArmame){
//        
//        auto scene = Armame::createScene();
//        auto transicion = TransitionFade::create(0.3f, scene);
//        Director::getInstance()->replaceScene(transicion);
//        
//    }else if(desdeEscena==desdeAkuerdate){
//        
//        auto scene = Akuerdate::createScene();
//        auto transicion = TransitionFade::create(0.3f, scene);
//        Director::getInstance()->replaceScene(transicion);
//        
//    }else if(desdeEscena==desdeMenu){
//        
//        auto scene = HelloWorld::createScene();
//        auto transicion = TransitionFade::create(0.3f, scene);
//        Director::getInstance()->replaceScene(transicion);
//        
//    }else{
//        auto scene = HelloWorld::createScene();
//        auto transicion = TransitionFade::create(0.3f, scene);
//        Director::getInstance()->replaceScene(transicion);
//    }
    
}

void Ajustes::initFondoTemp(){
    
    LayerColor *capaFondo = LayerColor::create(Color4B(25,78,121,255), visibleSize.width, visibleSize.height);
    capaFondo->setPosition(0,0);
    this->addChild(capaFondo,-1);
    
    fondoTemp = Sprite::create("mostrosity_dientes_d.png");
    fondoTemp->setScale(escala);
    fondoTemp->setAnchorPoint(Vec2(0,0.5));
    fondoTemp->setPosition(visibleSize.width/2,visibleSize.height/2);
    this->addChild(fondoTemp);
    
    
    
    fondoTemp = Sprite::create("mostrosity_dientes_d.png");
    fondoTemp->setScale(escala);
    fondoTemp->setAnchorPoint(Vec2(1,0.5));
    fondoTemp->setPosition(visibleSize.width/2,visibleSize.height/2);
    this->addChild(fondoTemp);
    
    
    
    
    altoIndividalCuadroJuego = visibleSize.height-((espacioBordesCuadro*2*escala));
    anchoIndividualCuadroJuego = anchoNoLateralCE-(espacioBordesCuadro*2*escala);
    
    cuadroJuego = LayerGradient::create(Color4B(174,209,240,255),Color4B(174,209,240,255));
    cuadroJuego->setContentSize(Size(anchoIndividualCuadroJuego,altoIndividalCuadroJuego));
    cuadroJuego->setPosition(anchoLateralCE+(espacioBordesCuadro*escala),(espacioBordesCuadro*escala));
    cuadroJuego->setZOrder(1);
    this->addChild(cuadroJuego);
    
}

void Ajustes::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event){
    irAtras(NULL);
}

bool Ajustes::comprobarToque(cocos2d::Touch *touch,Sprite *sprite){
    
    auto target = sprite;
    Point locationInNode = target->convertToNodeSpace(touch->getLocation());
    Size s = target->getContentSize();
    Rect rect = Rect(0, 0, s.width, s.height);
    if (rect.containsPoint(locationInNode))
    {
        return true;
    }else{
        return false;
    }
}

bool Ajustes::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
    if(!escuchadores){
        return false;
    }
    if(Configuracion::desarrollo)
        log("BEGAN %f %f",touch->getLocation().x,touch->getLocation().y);
    
    
    if(btDesarrollo!=NULL&&comprobarToque(touch,btDesarrollo)){
        toogleDesarrollo();
    }
    if(btReinicio!=NULL&&comprobarToque(touch,btReinicio)){
        toogleReinicio();
    }
    
    bool  tocaIdioma = false;
    if(comprobarToque(touch, idioma1)){
        if(Configuracion::desarrollo)
            CCLOG("idioma 1");
        cambiarIdioma(idioma1,1);
        tocaIdioma = true;
    }else if(comprobarToque(touch, idioma2)){
        if(Configuracion::desarrollo)
            CCLOG("idioma 2");
        cambiarIdioma(idioma2,2);
        tocaIdioma = true;
    }else if(comprobarToque(touch, idioma3)){
        if(Configuracion::desarrollo)
            CCLOG("idioma 3");
        cambiarIdioma(idioma3,3);
        tocaIdioma = true;
    }
    
    bool tocaBtSonido = false;
    tocaBtMusica = false;
    tocaBtEfecto = false;
    if(!tocaIdioma){
        
        if(comprobarToque(touch, btMusica)){
            if(Configuracion::desarrollo)
                CCLOG("select musica");
            tocaBtSonido = true;
            tocaBtMusica = true;
        }else if(comprobarToque(touch, btEfectos)){
            if(Configuracion::desarrollo)
                CCLOG("select efectos");
            tocaBtSonido = true;
            tocaBtEfecto = true;
        }
    }
    
    
    
    return  true;
}
void Ajustes::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event)
{
    if(Configuracion::desarrollo)
        log("MOVED %f %f ",touch->getLocation().x,touch->getLocation().y);
    
    if(tocaBtMusica){
        cambiarSonido(touch->getLocation().x,true);
    }else if(tocaBtEfecto){
        cambiarSonido(touch->getLocation().x,false);
    }
    
}
void Ajustes::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
{
    if(Configuracion::desarrollo)
        log("ENDED %f %f ",touch->getLocation().x,touch->getLocation().y);
    
    
    
}
