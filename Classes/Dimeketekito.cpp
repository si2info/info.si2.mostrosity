#include "Dimeketekito.h"
#include "HelloWorldScene.h"
#include "Configuracion.h"
#include "Ajustes.h"
#include "LanguageManager.h"
#include "SimpleAudioEngine.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "JniLink.h"
#endif

USING_NS_CC;

SpriteFrameCache *cache;

Scene* Dimeketekito::createScene()
{
    
    auto scene = Scene::create();
    
    auto layer = Dimeketekito::create();
    scene->addChild(layer);
    return scene;
}


bool Dimeketekito::init()
{
    
    cache = SpriteFrameCache::getInstance();
    
    if ( !Layer::init() )
    {
        return false;
    }
    this->setKeypadEnabled(true);
    
    obtenerMedidas();
    initFondo();
    initBtAtras();
    initBtAjustes();
    //reloj va despues de bt_atras porque coge la referencia
    initReloj();
    initProfesor();
    initCuadroInicial();
    initBocadillo();
    initTextoCentral();
    initCuadroJuego();
    
    //activo los tocuh de pantalla
    auto listener1 = EventListenerTouchOneByOne::create();
    listener1->setSwallowTouches(true);
    listener1->onTouchBegan = CC_CALLBACK_2(Dimeketekito::onTouchBegan, this);
    listener1->onTouchMoved = CC_CALLBACK_2(Dimeketekito::onTouchMoved, this);
    listener1->onTouchEnded = CC_CALLBACK_2(Dimeketekito::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);
    
    return true;
}

void Dimeketekito::onEnterTransitionDidFinish(){
    if(Configuracion::desarrollo)
        CCLOG("ENTRA EN ESCENA Dimeketekito");
    
    if (!running) {
        initMusica();
        initMesaFondo();
        initGestorRecursos();
        initMostro();
        initBotes();
        rellenarBotes();
        
        if(Configuracion::desarrollo){
            //comenzarNarracion();
            //mostrarDialogoComenzar();
            dial1_Imenu2_resp2(NULL);
        }else{
            comenzarNarracion();
        }
        
        running = true;
        
    }
    
    
//    CCTextureCache::getInstance()->getCachedTextureInfo();
    cleanMemory();

}

void Dimeketekito::onExitTransitionDidStart() {
    
    cleanMemory();
    
}

Dimeketekito::~Dimeketekito() {
    
//    cleanMemory();
    
}

void Dimeketekito::cleanMemory() {
    
//    CCDirector::sharedDirector()->purgeCachedData();
//    
//    CCTextureCache::sharedTextureCache()->removeUnusedTextures();
//    CCTextureCache::sharedTextureCache()->removeAllTextures();
//    CCTextureCache::purgeSharedTextureCache();
//
//    CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames();
//    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFrames();
//    CCSpriteFrameCache::purgeSharedSpriteFrameCache();
    
    SpriteFrameCache::getInstance()->removeUnusedSpriteFrames();
    
}

void Dimeketekito::comenzarNarracion(){
    
    lbCuadroInicial->setVisible(true);
    capaFondoCuadroInicial->setVisible(true);
    capaTextoCuadroInicial->setVisible(true);
    
    if(!isPlayNarracion){
        isPlayNarracion = true;
        narracionActual = 0;
        saltarAnimacion();
    }
}
void Dimeketekito::saltarAnimacion(){
    stopAction(narracion);
    CallFunc *runCallback1 = CallFunc::create(CC_CALLBACK_0(Dimeketekito::narracion1, this));
    CallFunc *runCallback2 = CallFunc::create(CC_CALLBACK_0(Dimeketekito::narracion2, this));
    CallFunc *runCallback3 = CallFunc::create(CC_CALLBACK_0(Dimeketekito::narracion3, this));
    CallFunc *runCallback4 = CallFunc::create(CC_CALLBACK_0(Dimeketekito::narracion4, this));
    CallFunc *runCallback5 = CallFunc::create(CC_CALLBACK_0(Dimeketekito::mostrarDialogoComenzar, this));
    
    if(narracionActual==0){
        narracion = Sequence::create(runCallback1,DelayTime::create(3),runCallback2,DelayTime::create(6.6),runCallback3,DelayTime::create(3),runCallback4,DelayTime::create(2),runCallback5,NULL);
    }else if(narracionActual==1){
        narracion = Sequence::create(runCallback2,DelayTime::create(6.6),runCallback3,DelayTime::create(3),runCallback4,DelayTime::create(2),runCallback5,NULL);
    }else if(narracionActual==2){
        narracion = Sequence::create(runCallback3,DelayTime::create(3),runCallback4,DelayTime::create(2),runCallback5,NULL);
    }else if(narracionActual==3){
        narracion = Sequence::create(runCallback4,DelayTime::create(2),runCallback5,NULL);
    }else if(narracionActual==4){
        narracion = Sequence::create(runCallback5,NULL);
    }
    runAction(narracion);
}

void Dimeketekito::narracion1(){
    narracionActual = 1;
    CallFunc *leer = CallFunc::create(CC_CALLBACK_0(Dimeketekito::ProfesorLeyendoHablando, this));
    Sequence *leyendo = Sequence::create(leer,NULL);
    this->runAction(leyendo);
    
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("demeketekito_intro_1.mp3");
    lbCuadroInicial->setString(LanguageManager::getInstance()->getString("DIMEKETEKITO_NAR_01"));
}
void Dimeketekito::narracion2(){
    narracionActual = 2;
    CallFunc *leer = CallFunc::create(CC_CALLBACK_0(Dimeketekito::ProfesorLeyendoHablando, this));
    Sequence *leyendo = Sequence::create(leer,DelayTime::create(3.5),leer,DelayTime::create(3.5),leer,NULL);
    this->runAction(leyendo);
    
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("demeketekito_intro_2.mp3");
    lbCuadroInicial->setString(LanguageManager::getInstance()->getString("DIMEKETEKITO_NAR_02"));
}
void Dimeketekito::narracion3(){
    narracionActual = 3;
    CallFunc *leer = CallFunc::create(CC_CALLBACK_0(Dimeketekito::ProfesorLeyendoHablando, this));
    Sequence *leyendo = Sequence::create(leer,DelayTime::create(2.0),leer,DelayTime::create(2.0),leer,DelayTime::create(2.0),leer,NULL);
    this->runAction(leyendo);
    
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("demeketekito_intro_3.mp3");
    lbCuadroInicial->setString(LanguageManager::getInstance()->getString("DIMEKETEKITO_NAR_03"));
}
void Dimeketekito::narracion4(){
    narracionActual = 4;
    CallFunc *leer = CallFunc::create(CC_CALLBACK_0(Dimeketekito::ProfesorLeyendoHablando, this));
    Sequence *leyendo = Sequence::create(leer,NULL);
    this->runAction(leyendo);
    
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("demeketekito_intro_4.mp3");
    lbCuadroInicial->setString(LanguageManager::getInstance()->getString("DIMEKETEKITO_NAR_04"));
}

void Dimeketekito::obtenerMedidas(){
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
    
    anchoLateralCE = (visibleSize.width/100)*20;
    anchoNoLateralCE = ((visibleSize.width/100)*80);
    
    espacioBordesCuadroCE = espacioBordesCuadro*escala;
    espacioSuperiorBtAtrasCE = espacioSuperiorBtAtras*escala;
    
    tamLetraCE = tamLetra * escala;

}

void Dimeketekito::irAtras(Ref* pSender)
{
    if(Configuracion::desarrollo)
        CCLOG("atras");
    CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    
//    auto scene = HelloWorld::createScene();
//    auto transicion = TransitionFade::create(0.3f, scene);
//    Director::getInstance()->replaceScene(transicion);
    
    Director::getInstance()->popScene();

    
}
void Dimeketekito::initFondo(){
    //33% de alto para cada una
    float altoIndividal = visibleSize.height/3;
    
    Layer* fondo = LayerColor::create(Color4B(26,79,121,255),visibleSize.width,visibleSize.height);
    fondo->setAnchorPoint(Vec2(1, 0.5));
    fondo->setPosition(0,0);
    fondo->setZOrder(-1);
    this->addChild(fondo);
    
    
        Sprite *bg_i = Sprite::create("preguntator_bg_i.png");
        if(escalaAncha>escalaAlta){
            bg_i->setScaleX(escalaAncha);
            bg_i->setScaleY(escalaAncha);
        }else{
            bg_i->setScaleX(escalaAlta);
            bg_i->setScaleY(escalaAlta);
        }
        bg_i->setAnchorPoint(Vec2(1, 0));
        bg_i->setPosition(visibleSize.width/2, 0);
        bg_i->setZOrder(-1);
        this->addChild(bg_i);
        
        auto bg_d = Sprite::create("preguntator_bg_d.png");
        if(escalaAncha>escalaAlta){
            bg_d->setScaleX(escalaAncha);
            bg_d->setScaleY(escalaAncha);
        }else{
            bg_d->setScaleX(escalaAlta);
            bg_d->setScaleY(escalaAlta);
        }
        bg_d->setAnchorPoint(Vec2(0, 0));
        bg_d->setPosition(visibleSize.width/2, 0);
        bg_d->setZOrder(-1);
        this->addChild(bg_d);
        
    

    /*Sprite* bg = Sprite::create("preguntator_bg.png");
    //calculo su 33%
    float escala1 = altoIndividal/bg->getContentSize().height;
    
    bg->setScale(escala1);
    bg->setAnchorPoint(Vec2(0, 0));
    bg->setPosition(0,0);
    bg->setZOrder(4);
    this->addChild(bg);*/
    
    
    Sprite* interrogaciones = Sprite::create("preguntator_interrogaciones.png");
    //calculo su 33%
    float escala2 = altoIndividal/interrogaciones->getContentSize().height;
    
    interrogaciones->setScale(escala2);
    interrogaciones->setAnchorPoint(Vec2(0.5, 0.5));
    interrogaciones->setPosition(anchoLateralCE/2,visibleSize.height/2);
    interrogaciones->setZOrder(7);
    this->addChild(interrogaciones);
    
}

void Dimeketekito::initReloj(){
    reloj = CCLabelTTF::create("00:00", "HVD_Comic_Serif_Pro.ttf", letraReloj*escala,CCSizeMake(anchoLateralCE, (letraReloj+20)*escala), TextHAlignment::CENTER);
    reloj->setColor(Color3B(216,254,51));
    reloj->setVerticalAlignment(TextVAlignment::TOP);
    reloj->setAnchorPoint(Vec2(0, 1));
    reloj->setPosition(0,btAtras->getPositionY()-(btAtras->getContentSize().height*escala));
    reloj->setZOrder(9);
    this->addChild(reloj, 1);
}

void Dimeketekito::initMusica(){
    //pongo musica
    if(!Configuracion::desarrollo){
        if(CocosDenshion::SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying()){
            
        }else{
            CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("sintonia_dimeketekito.mp3", true);
        }
    }
}

void Dimeketekito::initBtAtras(){
    btAtras = MenuItemImage::create("preguntator_bt_atras.png","preguntator_bt_atras_down.png",CC_CALLBACK_1(Dimeketekito::irAtras, this));
    
    btAtras->setScale(escala);
    btAtras->setLocalZOrder(20);
    btAtras->setAnchorPoint(Vec2(0, 1));
    //calculo espacio sobrante
    float espacio = anchoLateralCE-(btAtras->getContentSize().width*escala);
    
    btAtras->setPosition(0+(espacio/2),visibleSize.height-(espacioSuperiorBtAtras*escala));
    
    menu = Menu::create(btAtras, NULL);
    menu->setPosition(Vec2::ZERO);
    menu->setLocalZOrder(20);
    this->addChild(menu);
}

void Dimeketekito::initBtAjustes(){
    btAjustes = MenuItemImage::create("mostrosity_mimostro_bt_ajustes.png","mostrosity_mimostro_bt_ajustes_down.png",CC_CALLBACK_1(Dimeketekito::selectorAjustes, this));
    btAjustes->setScale(escala);
    btAjustes->setAnchorPoint(Vec2(1,1));
    btAjustes->setPosition(visibleSize.width-(espacioBordesCuadroCE*2),btAtras->getPositionY());
    btAjustes->retain();
    menu->addChild(btAjustes);
}

void Dimeketekito::selectorAjustes(Ref *pSender){
    CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    
    if(Configuracion::desarrollo)
        CCLOG("Selector ajustes");
    
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    
//    Ajustes::desdeEscena = Ajustes::desdeDimeketekito;
//    auto scene = Ajustes::createScene();
//    auto transicion = TransitionFade::create(0.3f, scene);
//    Director::getInstance()->replaceScene(transicion);
    
    auto scene = Ajustes::createScene();
    Director::getInstance()->pushScene(scene);
    
}

void Dimeketekito::initCuadroInicial(){
    
    capaFondoCuadroInicial = LayerColor::create(Color4B(133,173,214,204), visibleSize.width, visibleSize.height);
    capaFondoCuadroInicial->setAnchorPoint(Vec2(0, 0));
    capaFondoCuadroInicial->setPosition(0,0);
    capaFondoCuadroInicial->setLocalZOrder(13);
    capaFondoCuadroInicial->setVisible(false);
    capaFondoCuadroInicial->retain();
    this->addChild(capaFondoCuadroInicial);
    
    capaTextoCuadroInicial = LayerColor::create(Color4B(212,238,247,150), visibleSize.width, 700*escala);
    capaTextoCuadroInicial->setPosition(0,visibleSize.height/2-(700*escala/2));
    capaTextoCuadroInicial->setLocalZOrder(13);
    capaTextoCuadroInicial->setVisible(false);
    capaTextoCuadroInicial->retain();
    this->addChild(capaTextoCuadroInicial);
    
    lbCuadroInicial = CCLabelTTF::create("", "HVD_Comic_Serif_Pro.ttf", 100*escala,CCSizeMake(visibleSize.width-(anchoLateralCE*0.7*2),700*escala), TextHAlignment::CENTER);
    //70% del lateral tanto por un lado como por el otro
    lbCuadroInicial->setColor(Color3B(228,70,106));
    lbCuadroInicial->setVerticalAlignment(TextVAlignment::CENTER);
    lbCuadroInicial->setAnchorPoint(Vec2(0.5,0.5));
    lbCuadroInicial->setPosition(visibleSize.width/2,visibleSize.height/2);
    lbCuadroInicial->setZOrder(14);
    lbCuadroInicial->setVisible(false);
    this->addChild(lbCuadroInicial);
    
    
}


void Dimeketekito::initBocadillo(){
    textosProfesor = __Array::create();
    textosProfesor->retain();
    bocadillo = Sprite::create("preguntator_cuadro.png");
    
    escalaPropiaBocadillo = anchoLateralCE/bocadillo->getContentSize().width;
    if(relacion<1.5)
        bocadillo->setScale(escalaPropiaBocadillo);
    else{
        escalaPropiaBocadillo = escala;
        bocadillo->setScale(escala);
    }
    bocadillo->setVisible(false);
    bocadillo->setScale(0);
    bocadillo->setAnchorPoint(Vec2(0.5,0));
    bocadillo->setPosition((anchoLateralCE/2)+((espacioBordesCuadro*escala)/2),profesor->getPositionY()+(profesor->getContentSize().height*escala));
    bocadillo->setZOrder(8);
    this->addChild(bocadillo);
    
}


void Dimeketekito::initProfesor(){
    
    profesor = Sprite::create(__String::createWithFormat("tutor_base_%i.png",Configuracion::profesor)->getCString());
    profesor->setScale(escala);
    profesor->setAnchorPoint(Vec2(0.5,0));
    profesor->setPosition(anchoLateralCE/2,((espacioBordesCuadro*escala)/2));
    profesor->setZOrder(15);
    this->addChild(profesor);
    
    altoProfesor = profesor->getContentSize().height;
    anchoProfesor = profesor->getContentSize().width;
    
    profBarba = Sprite::create(__String::createWithFormat("tutor_barva_%i.png",Configuracion::profesor)->getCString());
    profBarba->setAnchorPoint(Vec2(0.5,0.5));
    profesor->addChild(profBarba,1);
    
    profBigote = Sprite::create(__String::createWithFormat("tutor_bigote_%i.png",Configuracion::profesor)->getCString());
    profBigote->setAnchorPoint(Vec2(0.5,0.5));
    profesor->addChild(profBigote,2);
    
    profCejas = Sprite::create(__String::createWithFormat("tutor_cejas_%i.png",Configuracion::profesor)->getCString());
    profCejas->setAnchorPoint(Vec2(0.5,0.5));
    profesor->addChild(profCejas,2);
    
    profOjos = Sprite::create(__String::createWithFormat("tutor_ojos_%i.png",Configuracion::profesor)->getCString());
    profOjos->setAnchorPoint(Vec2(0.5,0.5));
    profesor->addChild(profOjos,1);
    
    profOjos->retain();
    profesor->retain();
    
    if(Configuracion::profesor==1){
        altoBarba = 285;
        altoBigote = 350;
        altoCejas = 470;
        altoOjos = 420;
    }else{
        altoBarba = 320;
        altoBigote = 380;
        altoCejas = 430;
        altoOjos = 430;
    }
    profBarba->setPosition(anchoProfesor/2,altoBarba);
    profBigote->setPosition(anchoProfesor/2,altoBigote);
    profCejas->setPosition(anchoProfesor/2,altoCejas);
    profOjos->setPosition(anchoProfesor/2,altoOjos);
    
}

void Dimeketekito::ProfesorLeyendoHablando(){
    //tiempoAnimacion 1,6segundos
    
    //parteOJOS
    MoveTo *ojosCentro = MoveTo::create(0.4, Vec2(anchoProfesor/2,altoOjos));
    MoveTo *ojosDerecha = MoveTo::create(0.8, Vec2((anchoProfesor/2)+10,altoOjos));
    MoveTo *ojosIzquierda = MoveTo::create(0.4, Vec2((anchoProfesor/2)-10,altoOjos));
    
    Sequence *profesorLeyendo = Sequence::create(ojosCentro,ojosIzquierda,ojosDerecha,ojosCentro, NULL);
    
    if(profOjos->getNumberOfRunningActions()==0)
        profOjos->runAction(profesorLeyendo);
    
    //parteBigotorro
    RotateTo *bigoteCentrado = RotateTo::create(0.2, 0);
    RotateTo *bigoteIzquierda = RotateTo::create(0.2, 15);
    RotateTo *bigoteDerecha = RotateTo::create(0.4, -15);
    MoveTo *bigoteArriba = MoveTo::create(0.2, Vec2(anchoProfesor/2,profBigote->getPositionY()+5));
    MoveTo *bigoteAbajo = MoveTo::create(0.2, Vec2(anchoProfesor/2,profBigote->getPositionY()-5));
    MoveTo *bigoteOrignal = MoveTo::create(0.2, Vec2(anchoProfesor/2,profBigote->getPositionY()));
    
    Sequence *profesorHablandoRotate = Sequence::create(bigoteIzquierda,bigoteDerecha,bigoteCentrado,bigoteIzquierda,bigoteDerecha,bigoteCentrado, NULL);
    Sequence *profesorHablandoMove = Sequence::create(bigoteOrignal,bigoteArriba,bigoteAbajo,bigoteOrignal,bigoteOrignal,bigoteArriba,bigoteAbajo,bigoteOrignal, NULL);
    
    if(profBigote->getNumberOfRunningActions()==0){
        profBigote->runAction(profesorHablandoRotate);
        profBigote->runAction(profesorHablandoMove);
    }
    
    
}

void Dimeketekito::ProfesorFalloRespuesta(){
    
    MoveTo *cejasAbajo = MoveTo::create(0.2, Vec2((anchoProfesor/2)-15,altoCejas-25));
    if(profCejas->getNumberOfRunningActions()==0){
        profCejas->runAction(cejasAbajo);
    }
    
}

void Dimeketekito::ProfesorAciertaRespuesta(){
    RotateBy *Giro = RotateBy::create(0.4, 360);
    if(profBigote->getNumberOfRunningActions()==0){
        profBigote->runAction(Giro);
    }
    
    MoveTo *ojosArriba = MoveTo::create(0.4, Vec2(anchoProfesor/2,altoOjos+20));
    if(profOjos->getNumberOfRunningActions()==0){
        profOjos->runAction(ojosArriba);
    }
}

void Dimeketekito::ProfesorNuevaPregunta(){
    MoveTo *cejasOrigen = MoveTo::create(0.4, Vec2((anchoProfesor/2),altoCejas));
    if(profCejas->getNumberOfRunningActions()==0){
        profCejas->runAction(Sequence::create(DelayTime::create(1),cejasOrigen,NULL));
    }
    
    MoveTo *ojosNormal = MoveTo::create(0.4, Vec2(anchoProfesor/2,altoOjos));
    if(profOjos->getNumberOfRunningActions()==0){
        profOjos->runAction(ojosNormal);
    }
}

void Dimeketekito::initCuadroJuego(){
    altoIndividalCuadroJuego = visibleSize.height-((espacioBordesCuadro*2*escala));
    anchoIndividualCuadroJuego = anchoNoLateralCE-(espacioBordesCuadro*2*escala);
    
    cuadroJuego = LayerGradient::create(Color4B(6,18,28,255),Color4B(6,18,28,255));
    cuadroJuego->setContentSize(Size(anchoIndividualCuadroJuego,altoIndividalCuadroJuego));
    cuadroJuego->setPosition(anchoLateralCE+(espacioBordesCuadro*escala),(espacioBordesCuadro*escala));
    cuadroJuego->setZOrder(6);
    this->addChild(cuadroJuego);
    
    /*Layer* cuadroJuegoInterior = LayerColor::create(Color4B(52,135,210,255));
    cuadroJuegoInterior->setContentSize(Size(anchoIndividualCuadroJuego-((espacioBordesCuadro/2)*2*escala),altoIndividalCuadroJuego/2));
    cuadroJuegoInterior->setPosition(cuadroJuego->getPositionX()+((espacioBordesCuadro/2)*escala),cuadroJuego->getPositionY()+((espacioBordesCuadro/2)*escala));
    cuadroJuegoInterior->setZOrder(6);
    //this->addChild(cuadroJuegoInterior);
    */
    
    
    //TEMPORAL
    /*Sprite *cuadroTemporal = Sprite::create("mostrosity_dimeketekito_cuadro_temp.png");
    cuadroTemporal->setScaleX(escalaAncha);
    cuadroTemporal->setScaleY(escalaAlta);
    cuadroTemporal->setAnchorPoint(Vec2::ZERO);
    cuadroTemporal->setPosition(cuadroJuego->getPosition());
    cuadroTemporal->setZOrder(6);
    this->addChild(cuadroTemporal);*/
}


void Dimeketekito::initTextoCentral(){
    float bordesBocadillos = 30*escalaPropiaBocadillo;
    cuadroDialogo = CCLabelTTF::create("", "HVD_Comic_Serif_Pro.ttf", (bocadillo->getContentSize().height*escalaPropiaBocadillo)/7, CCSizeMake((bocadillo->getContentSize().width*escalaPropiaBocadillo)-(bordesBocadillos*2), (bocadillo->getContentSize().height*escalaPropiaBocadillo)-(bordesBocadillos*3)), TextHAlignment::CENTER);
    cuadroDialogo->setColor(Color3B(0,0,0));
    cuadroDialogo->setVerticalAlignment(TextVAlignment::CENTER);
    cuadroDialogo->setAnchorPoint(Vec2(0.5,0.5));
    cuadroDialogo->setPosition(bocadillo->getPositionX(),bocadillo->getPositionY()+((bocadillo->getContentSize().height*escalaPropiaBocadillo)/2)+(bordesBocadillos*0.5));
    cuadroDialogo->setZOrder(10);
    this->addChild(cuadroDialogo);
    
}

void Dimeketekito::cambiarTextoDialogo(std::string texto){
    log("[_____cambiarTextoDialogo]txt %s",texto.c_str());
    
    bool bocadilloVisible = bocadillo->isVisible();
    int nAnimacionesBocadillo = bocadillo->getNumberOfRunningActions();
    if(texto!=""){
        textosProfesor->addObject(__String::create(texto));
    }
    
    if(!bocadilloVisible&&nAnimacionesBocadillo==0){
        
        if(textosProfesor->count()>0){
            log("[_____PRE]Textos profesor %zi",textosProfesor->count());
            __String *txt = dynamic_cast<__String*>(textosProfesor->getLastObject());
            textoProximoBocadillo = txt->getCString();
            textosProfesor->removeObject(txt);
            log("[_____POS]Textos profesor %zi",textosProfesor->count());
            
            bocadillo->setScale(0);
            bocadillo->setVisible(true);
            ScaleTo *escalado = ScaleTo::create(0.2, escalaPropiaBocadillo);
            ScaleTo *escaladoInverso = ScaleTo::create(0.2, 0);
            CallFunc *runCallback1 = CallFunc::create(CC_CALLBACK_0(Dimeketekito::modificarTXTDialogo, this));
            CallFunc *runCallback2 = CallFunc::create(CC_CALLBACK_0(Dimeketekito::vaciarTXTDialogo, this));
            CallFunc *runCallback3 = CallFunc::create(CC_CALLBACK_0(Dimeketekito::rellamarTXTDialogo, this));
            
            Sequence *secuencia = Sequence::create(escalado,runCallback1,DelayTime::create(1),runCallback2,escaladoInverso, NULL);
            this->runAction(Sequence::create(DelayTime::create(1.5),runCallback3, NULL));
            bocadillo->runAction(secuencia);
        }else{
            //vacio
            log("[_____cambiarTextoDialogo]No hay mas mensajes para el bocadillo");
        }
    }else{
        log("[_____cambiarTextoDialogo]no entra");
    }
}
void Dimeketekito::modificarTXTDialogo(){
    this->cuadroDialogo->setString(textoProximoBocadillo);
    cuadroDialogo->runAction(FadeIn::create(0.3));
}
void Dimeketekito::vaciarTXTDialogo(){
    this->cuadroDialogo->setString("");
    bocadillo->setVisible(false);
}

void Dimeketekito::rellamarTXTDialogo(){
    cambiarTextoDialogo("");
}



void Dimeketekito::initMesaFondo(){
    mesaFondo = Sprite::create("mostrosity_dimeketekito_mesaFondo.png");
    mesaFondo->setScale(escala);
    mesaFondo->setAnchorPoint(Vec2(0.5,1));
    mesaFondo->setPosition(cuadroJuego->getPositionX()+(cuadroJuego->getContentSize().width/2),visibleSize.height-(espacioSuperiorBtAtrasCE*2));
    mesaFondo->setZOrder(7);
    mesaFondo->retain();
    this->addChild(mesaFondo);
}


void Dimeketekito::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event){
    irAtras(NULL);
}

void Dimeketekito::mostrarDialogoComenzar(){
    lbCuadroInicial->setVisible(false);
    isPlayNarracion = false;
    if(dial1_bg==NULL){
        crearDialogoComenzar();
    }
    dial1_bg->setVisible(true);
}
void Dimeketekito::ocultarDialogoComenzar(){
    
    if(dial1_bg==NULL){
        crearDialogoComenzar();
    }
    dial1_bg->setVisible(false);
}

void Dimeketekito::crearDialogoComenzar(){
    dial1_bg = LayerColor::create(Color4B(0,0,0,0), visibleSize.width-(anchoLateralCE*escala*0.7*2), 700*escala);
    dial1_bg->setPosition((visibleSize.width-dial1_bg->getContentSize().width)/2,visibleSize.height/2-(700*escala/2));
    dial1_bg->setZOrder(16);
    this->addChild(dial1_bg);
    
    dial1_Imenu1 = MenuItemImage::create("preguntator_dial_bt1.png","preguntator_dial_bt1_down.png",CC_CALLBACK_1(Dimeketekito::dial1_Imenu2_resp1, this));
    dial1_Imenu1->setScale(escala);
    dial1_Imenu1->setAnchorPoint(Vec2(1, 1));
    dial1_Imenu1->setPosition(dial1_bg->getContentSize().width/2,dial1_bg->getContentSize().height/2);
    
    dial1_Imenu2 = MenuItemImage::create("preguntator_dial_bt2.png","preguntator_dial_bt2_down.png",CC_CALLBACK_1(Dimeketekito::dial1_Imenu2_resp2, this));
    dial1_Imenu2->setScale(escala);
    dial1_Imenu2->setAnchorPoint(Vec2(0, 1));
    dial1_Imenu2->setPosition(dial1_bg->getContentSize().width/2,dial1_bg->getContentSize().height/2);
    
    dial1_menu = Menu::create(dial1_Imenu1,dial1_Imenu2, NULL);
    dial1_menu->setPosition(Vec2::ZERO);
    dial1_bg->addChild(dial1_menu);
    
    dial1_titulo = CCLabelTTF::create(LanguageManager::getInstance()->getString("JUEGO_DIAL_TITULO"), "HVD_Comic_Serif_Pro.ttf",100*escala,CCSizeMake(dial1_bg->getContentSize().width, (dial1_bg->getContentSize().height/2)), TextHAlignment::CENTER);
    dial1_titulo->setColor(Color3B(228,70,106));
    dial1_titulo->setVerticalAlignment(TextVAlignment::CENTER);
    dial1_titulo->setAnchorPoint(Vec2(0.5, 0));
    dial1_titulo->setPosition(dial1_bg->getContentSize().width/2,dial1_bg->getContentSize().height/2);
    dial1_bg->addChild(dial1_titulo);
    
    dial1_Imenu1_text = CCLabelTTF::create(LanguageManager::getInstance()->getString("JUEGO_DIAL_BT_01"), "HVD_Comic_Serif_Pro.ttf",70,CCSizeMake((dial1_Imenu1->getContentSize().width-20),(dial1_Imenu1->getContentSize().height-20)), TextHAlignment::CENTER);
    dial1_Imenu1_text->setScale(escala);
    dial1_Imenu1_text->setColor(Color3B(255,255,255));
    dial1_Imenu1_text->setVerticalAlignment(TextVAlignment::CENTER);
    dial1_Imenu1_text->setAnchorPoint(Vec2(1, 1));
    dial1_Imenu1_text->setPosition(dial1_bg->getContentSize().width/2,dial1_bg->getContentSize().height/2);
    dial1_bg->addChild(dial1_Imenu1_text);
    
    
    dial1_Imenu2_text = CCLabelTTF::create(LanguageManager::getInstance()->getString("JUEGO_DIAL_BT_02"), "HVD_Comic_Serif_Pro.ttf",70,CCSizeMake((dial1_Imenu2->getContentSize().width-20),(dial1_Imenu2->getContentSize().height-20)), TextHAlignment::CENTER);
    dial1_Imenu2_text->setScale(escala);
    dial1_Imenu2_text->setColor(Color3B(255,255,255));
    dial1_Imenu2_text->setVerticalAlignment(TextVAlignment::CENTER);
    dial1_Imenu2_text->setAnchorPoint(Vec2(0, 1));
    dial1_Imenu2_text->setPosition(dial1_bg->getContentSize().width/2,dial1_bg->getContentSize().height/2);
    dial1_bg->addChild(dial1_Imenu2_text);
}

void Dimeketekito::dial1_Imenu2_resp1(Ref* sender){
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("tambores_3.mp3");
    ocultarDialogoComenzar();
    comenzarNarracion();
}

void Dimeketekito::dial1_Imenu2_resp2(Ref* sender){
    CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("tambores_3.mp3");
    lbCuadroInicial->setVisible(false);
    capaFondoCuadroInicial->setVisible(false);
    capaTextoCuadroInicial->setVisible(false);
    
    ocultarDialogoComenzar();
    comenzarReloj();
    escuchadores = true;
}

void Dimeketekito::comenzarReloj(){
    
    this->schedule(schedule_selector(Dimeketekito::aumentarReloj),1.0);
    
}
void Dimeketekito::aumentarReloj(float dt){
    if(tiempoRestante<0||juegoTerminado){
        unschedule(schedule_selector(Dimeketekito::aumentarReloj));
    }else{
        
        __String *sMinutos,*sSegundos,*texto;
        
        float fMinutos = tiempoRestante/60;
        if(fMinutos>=10)
            sMinutos = __String::createWithFormat("%i",(int)fMinutos);
        else
            sMinutos = __String::createWithFormat("0%i",(int)fMinutos);
        
        float fSegundos = tiempoRestante-(fMinutos*60);
        if(fSegundos>=10)
            sSegundos = __String::createWithFormat("%i",(int)fSegundos);
        else
            sSegundos = __String::createWithFormat("0%i",(int)fSegundos);
        
        texto = __String::createWithFormat("%s:%s",sMinutos->getCString(),sSegundos->getCString());
        
        
        reloj->setString(texto->getCString());
        tiempoRestante ++;
    }
}

void Dimeketekito::initBotes(){
    
    float escalaBotes = escala;
    
    capaBotes = LayerColor::create(Color4B(12,34,78,0), cuadroJuego->getContentSize().width, altoCapaBotes*escala);
    capaBotes->setPosition(cuadroJuego->getPositionX(), espacioSuperiorBtAtrasCE);
    capaBotes->setLocalZOrder(10);
    addChild(capaBotes);
    aBotes = __Array::createWithCapacity(nBotes);
    aBotes->retain();
    
    for (int i=0; i<nBotes; i++) {
        Sprite * bote = Sprite::create("mostrosity_dimeketekito_botePartes.png");
        bote->setAnchorPoint(Vec2(0.5,0));
        
        escalaBotes = capaBotes->getContentSize().height*escala/(bote->getContentSize().height*escala);
        bote->setScale(escalaBotes);
        
        float xMargenCE = ((capaBotes->getContentSize().width)-(bote->getContentSize().width*escalaBotes*nBotes)-(margenBotes*escala*(nBotes+1)))/6;
        
        float x = (bote->getContentSize().width*escalaBotes*i)+(xMargenCE*(i+1))+(margenBotes*escala*(i));
        
        bote->setPosition(x+((bote->getContentSize().width*escalaBotes)/2),0);
        capaBotes->addChild(bote);
        aBotes->insertObject(bote,i);
    }
}
void Dimeketekito::rellenarBotes(){
    asignarNBotes();
    
    for (int i=0;i<aBotes->count(); i++) {
        Sprite *boteActual = dynamic_cast<Sprite*>(aBotes->getObjectAtIndex(i));
        
        Sprite *spriteActual = NULL;
        if(boteActual->getTag()==Configuracion::rcsTipoOjos){
            spriteActual = mostro_ojos;
        } else if(boteActual->getTag()==Configuracion::rcsTipoDientes){
            spriteActual = mostro_boca;
        } else if(boteActual->getTag()==Configuracion::rcsTipoBrazo_izq){
            spriteActual = mostro_brazo_izq;
        } else if(boteActual->getTag()==Configuracion::rcsTipoBrazo_der){
            spriteActual = mostro_brazo_der;
        }else if(boteActual->getTag()==Configuracion::rcsTipoPies_izq){
            spriteActual = mostro_pie_izq;
        }else if(boteActual->getTag()==Configuracion::rcsTipoPies_der){
            spriteActual = mostro_pie_der;
        } else if(boteActual->getTag()==Configuracion::rcsTipoOreja_izq){
            spriteActual = mostro_oreja_izq;
        } else if(boteActual->getTag()==Configuracion::rcsTipoOreja_der){
            spriteActual = mostro_oreja_der;
        } else if(boteActual->getTag()==Configuracion::rcsTipoCuerpo){
            spriteActual = mostro_cuerpo;
        }/* else if(boteActual->getTag()==Configuracion::rcsTipoPelo){
            spriteActual = mostro_pelo;
        }*/
        
        //COMUN A TODOS
        Sprite *nuevo;
        if(spriteActual->getTag()<0){
            Rect rectIzq = {spriteActual->getContentSize().width, 0, spriteActual->getContentSize().width, spriteActual->getContentSize().height};
            nuevo = Sprite::createWithTexture(spriteActual->getTexture(), rectIzq);
        }else{
            Rect rectIzq = {0, 0, spriteActual->getContentSize().width, spriteActual->getContentSize().height};
            nuevo = Sprite::createWithTexture(spriteActual->getTexture(), rectIzq);
        }
        
        
        float escalaIntBoteAncha = (boteActual->getContentSize().width-30)/nuevo->getContentSize().width;
        float escalaIntBoteAlta = (maxAltoContenidoBote)/nuevo->getContentSize().height;
        float escalaIntBote = escalaIntBoteAncha;
        
        if(escalaIntBoteAncha>escalaIntBoteAlta){
            escalaIntBote = escalaIntBoteAlta;
        }
        
        nuevo->setScale(escalaIntBote);
        nuevo->setAnchorPoint(Vec2(0.5,0.4));
        nuevo->setPosition(boteActual->getContentSize().width/2, boteActual->getContentSize().width/2);
        nuevo->setOpacity(0);
        nuevo->runAction(Sequence::create(TintTo::create(0, 0, 0, 0),FadeIn::create(0.1),NULL));
        boteActual->addChild(nuevo);
        
        
    }
    this->schedule(schedule_selector(Dimeketekito::stopAnimBotesGiroShedule),1.0);
    
}

void Dimeketekito::asignarNBotes(){
    
    int sizePartes = (sizeof(Configuracion::partesDimeketekito)/sizeof(*Configuracion::partesDimeketekito));
    
    for(int i=0;i<aBotes->count();i++){
        Sprite *boteActual = dynamic_cast<Sprite*>(aBotes->getObjectAtIndex(i));
    
        int parteActual = Configuracion::partesDimeketekito[Configuracion::aleatorioEnteros(0, sizePartes-1)];
        while (!disponibleBoteXParte(parteActual)) {
            parteActual = Configuracion::partesDimeketekito[Configuracion::aleatorioEnteros(0, sizePartes-1)];
            
        }
        CCLOG("NUMERO TAG %i",parteActual);
        boteActual->setTag(parteActual);
    }
    
    //asigno la unica parte falsa
    int parteActual = Configuracion::partesDimeketekito[Configuracion::aleatorioEnteros(0, sizePartes-1)];
    while (!disponibleBoteXParte(parteActual)) {
        parteActual = Configuracion::partesDimeketekito[Configuracion::aleatorioEnteros(0, sizePartes-1)];
    }
    parteMostroFalsa = parteActual;

}

bool Dimeketekito::disponibleBoteXParte(int numero){
    for(int i=0;i<aBotes->count();i++){
        Sprite *boteActual = dynamic_cast<Sprite*>(aBotes->getObjectAtIndex(i));
        if(boteActual->getTag()==numero){
            return false;
        }
    }
    return true;
    
}
void Dimeketekito::initGestorRecursos(){
    gRecursos = new CGestorRecursos();
    gRecursos->retain();
    

    
    recursoMostro_pies = gRecursos->obtenerRecursoAleatorioNoVacio(CGestorRecursos::TIPOS::Pies);
    recursoMostro_ojos = gRecursos->obtenerRecursoAleatorioNoVacio(CGestorRecursos::TIPOS::Ojos);
    recursoMostro_orejas = gRecursos->obtenerRecursoAleatorioNoVacio(CGestorRecursos::TIPOS::Orejas);
    recursoMostro_boca = gRecursos->obtenerRecursoAleatorioNoVacio(CGestorRecursos::TIPOS::Dientes);
    recursoMostro_brazos = gRecursos->obtenerRecursoAleatorioNoVacio(CGestorRecursos::TIPOS::Brazos);
    //recursoMostro_pelo = gRecursos->obtenerRecursoAleatorioNoVacio(CGestorRecursos::TIPOS::Pelo);
    recursoMostro_alas = gRecursos->obtenerRecursoAleatorioNoVacio(CGestorRecursos::TIPOS::Alas);

}

void Dimeketekito::initMostro(){
    
    
    mostro = LayerColor::create(Color4B(255,255,250,0), 500, 500);
    mostro->setPosition(mesaFondo->getPositionX()-((mesaFondo->getContentSize().width*escala)/2)+((735*escala)/2),
                        mesaFondo->getPositionY()-(mesaFondo->getContentSize().height/3));
    mostro->setLocalZOrder(10);
    mostro->setVisible(true);
    addChild(mostro);
    
    mostro_cuerpo = Sprite::create("mostrosity_mimostro_mostro_cuerpo.png");
    mostro->addChild(mostro_cuerpo);
    
    
    mostro_pies = Sprite::create(recursoMostro_pies->uri->getCString());
    //mostro->addChild(mostro_pies);
    
    Rect rectIzq1 = {0, 0, mostro_pies->getContentSize().width/2, mostro_pies->getContentSize().height};
    mostro_pie_izq = Sprite::createWithTexture(mostro_pies->getTexture(), rectIzq1);
    mostro_pie_izq->setScale(escala);
    mostro_pie_izq->setAnchorPoint(Vec2(1,0.5));
    mostro_pie_izq->setPosition(0,-300*escala);
    mostro_pie_izq->setLocalZOrder(1);
    mostro_pie_izq->setTag(Configuracion::rcsTipoPies_izq);
    mostro->addChild(mostro_pie_izq);
    
    Rect rectDer1 = {mostro_pies->getContentSize().width/2, 0, mostro_pies->getContentSize().width/2, mostro_pies->getContentSize().height};
    mostro_pie_der = Sprite::createWithTexture(mostro_pies->getTexture(), rectDer1);
    mostro_pie_der->setScale(escala);
    mostro_pie_der->setAnchorPoint(Vec2(0,0.5));
    mostro_pie_der->setPosition(0,-300*escala);
    mostro_pie_der->setLocalZOrder(1);
    mostro_pie_der->setTag(Configuracion::rcsTipoPies_der);
    mostro->addChild(mostro_pie_der);
    
    
    mostro_brazos = Sprite::create(recursoMostro_brazos->uri->getCString());
    //mostro->addChild(mostro_brazos);
    
    Rect rectIzq2 = {0, 0, mostro_brazos->getContentSize().width/2, mostro_brazos->getContentSize().height};
    mostro_brazo_izq = Sprite::createWithTexture(mostro_brazos->getTexture(), rectIzq2);
    mostro_brazo_izq->setScale(escala);
    mostro_brazo_izq->setAnchorPoint(Vec2(1,0.5));
    mostro_brazo_izq->setPosition(0,0);
    mostro_brazo_izq->setLocalZOrder(1);
    mostro_brazo_izq->setTag(Configuracion::rcsTipoBrazo_izq);
    mostro->addChild(mostro_brazo_izq);
    
    Rect rectDer2 = {mostro_brazos->getContentSize().width/2, 0, mostro_brazos->getContentSize().width/2, mostro_brazos->getContentSize().height};
    mostro_brazo_der = Sprite::createWithTexture(mostro_brazos->getTexture(), rectDer2);
    mostro_brazo_der->setScale(escala);
    mostro_brazo_der->setAnchorPoint(Vec2(0,0.5));
    mostro_brazo_der->setPosition(0,0);
    mostro_brazo_der->setLocalZOrder(1);
    mostro_brazo_der->setTag(Configuracion::rcsTipoBrazo_der);
    mostro->addChild(mostro_brazo_der);
    
    
    mostro_ojos = Sprite::create(recursoMostro_ojos->uri->getCString());
    mostro->addChild(mostro_ojos);
    
    
    mostro_boca = Sprite::create(recursoMostro_boca->uri->getCString());
    mostro->addChild(mostro_boca);
    
    mostro_orejas = Sprite::create(recursoMostro_orejas->uri->getCString());
    //mostro->addChild(mostro_orejas);
    
    Rect rectIzq3 = {0, 0, mostro_orejas->getContentSize().width/2, mostro_orejas->getContentSize().height};
    mostro_oreja_izq = Sprite::createWithTexture(mostro_orejas->getTexture(), rectIzq3);
    mostro_oreja_izq->setScale(escala);
    mostro_oreja_izq->setAnchorPoint(Vec2(1,0.5));
    mostro_oreja_izq->setPosition(0,370*escala);
    mostro_oreja_izq->setLocalZOrder(1);
    mostro_oreja_izq->setTag(Configuracion::rcsTipoOreja_izq);
    mostro->addChild(mostro_oreja_izq);
    
    Rect rectDer3 = {mostro_orejas->getContentSize().width/2, 0, mostro_orejas->getContentSize().width/2, mostro_orejas->getContentSize().height};
    mostro_oreja_der = Sprite::createWithTexture(mostro_orejas->getTexture(), rectDer3);
    mostro_oreja_der->setScale(escala);
    mostro_oreja_der->setAnchorPoint(Vec2(0,0.5));
    mostro_oreja_der->setPosition(0,370*escala);
    mostro_oreja_der->setLocalZOrder(1);
    mostro_oreja_der->setTag(Configuracion::rcsTipoOreja_der);
    mostro->addChild(mostro_oreja_der);

    /*mostro_alas = Sprite::create("dime_orejas.png");
     mostro->addChild(mostro_alas);*/
    
    
    //mostro_pelo = Sprite::create(recursoMostro_pelo->uri->getCString());
    //mostro->addChild(mostro_pelo);
    
    
    /*mostro_accesorio =Sprite::create("dime_orejas.png");
     mostro->addChild(mostro_accesorio);*/
    
    
    //cargo propiedades y ajusto altura mostro
    mostro->setPositionY(mesaFondo->getPositionY()/1.5);
    initMostroPropiedades(CGestorRecursos::TIPOS::Indefinido);
    
    
    
    CallFunc *runCallback1 = CallFunc::create(CC_CALLBACK_0(Dimeketekito::mostrarMostro, this));
    
    tintado = obtenerTintatoAleatorio();
    for(int i=0;i<mostro->getChildrenCount();i++){
        Node *actual = mostro->getChildren().at(i);
        if(actual!=mostro_boca&&actual!=mostro_ojos){
            actual->runAction(tintado->clone());
        }
    }
    Sequence *seq = Sequence::create(DelayTime::create(0.1),runCallback1, NULL);
    runAction(seq);
    
}

void Dimeketekito::initMostroPropiedades(CGestorRecursos::TIPOS tipo){
    
    if(tipo==-1||tipo==CGestorRecursos::TIPOS::Cuerpo){
        mostro_cuerpo->setScale(escala);
        mostro_cuerpo->setAnchorPoint(Vec2(0.5,0.5));
        mostro_cuerpo->setPosition(0,0);
        mostro_cuerpo->setLocalZOrder(3);
        mostro_cuerpo->setTag(Configuracion::rcsTipoCuerpo);
    }
    
    if(tipo==-1||tipo==CGestorRecursos::TIPOS::Pies){
        mostro_pies->setScale(escala);
        mostro_pies->setAnchorPoint(Vec2(0.5,0.5));
        mostro_pies->setPosition(0,-300*escala);
        mostro_pies->setLocalZOrder(1);
        mostro_pies->setTag(Configuracion::rcsTipoPies);
        mostro_pies->setRotation(0);
    }
    /*
    if(tipo==-1||tipo==CGestorRecursos::TIPOS::Alas){
        mostro_alas->setScale(escala);
        mostro_alas->setAnchorPoint(Vec2(0.5,0.5));
        mostro_alas->setPosition(0,200*escala);
        mostro_alas->setLocalZOrder(1);
        mostro_alas->setTag(Configuracion::rcsTipoAlas);
        mostro_alas->setRotation(0);
    }*/
    
    if(tipo==-1||tipo==CGestorRecursos::TIPOS::Brazos){
        mostro_brazos->setScale(escala);
        mostro_brazos->setAnchorPoint(Vec2(0.5,0.5));
        mostro_brazos->setPosition(0,0);
        mostro_brazos->setLocalZOrder(1);
        mostro_brazos->setTag(Configuracion::rcsTipoBrazos);
        mostro_brazos->setRotation(0);
    }
    
    if(tipo==-1||tipo==CGestorRecursos::TIPOS::Ojos){
        mostro_ojos->setScale(escala);
        mostro_ojos->setAnchorPoint(Vec2(0.5,0.5));
        mostro_ojos->setPosition(0,150*escala);
        mostro_ojos->setLocalZOrder(6);
        mostro_ojos->setTag(Configuracion::rcsTipoOjos);
        mostro_ojos->setRotation(0);
    }
    
    if(tipo==-1||tipo==CGestorRecursos::TIPOS::Dientes){
        mostro_boca->setScale(escala);
        mostro_boca->setAnchorPoint(Vec2(0.5,0.5));
        mostro_boca->setPosition(0,-150*escala);
        mostro_boca->setLocalZOrder(6);
        mostro_boca->setTag(Configuracion::rcsTipoDientes);
        mostro_boca->setRotation(0);
    }
    
    /*if(tipo==-1||tipo==CGestorRecursos::TIPOS::Pelo){
        mostro_pelo->setScale(escala);
        mostro_pelo->setAnchorPoint(Vec2(0.5,0.5));
        mostro_pelo->setPosition(0,270*escala);
        mostro_pelo->setLocalZOrder(6);
        mostro_pelo->setTag(Configuracion::rcsTipoPelo);
        mostro_pelo->setRotation(0);
    }*/
    
    if(tipo==-1||tipo==CGestorRecursos::TIPOS::Orejas){
        mostro_orejas->setScale(escala);
        mostro_orejas->setAnchorPoint(Vec2(0.5,0.5));
        mostro_orejas->setPosition(0,370*escala);
        mostro_orejas->setLocalZOrder(2);
        mostro_orejas->setTag(Configuracion::rcsTipoOrejas);
        mostro_orejas->setRotation(0);
    }
    /*
    if(tipo==-1||tipo==CGestorRecursos::TIPOS::Accesorio){
        mostro_accesorio->setScale(escala);
        mostro_accesorio->setAnchorPoint(Vec2(0.5,0.5));
        mostro_accesorio->setPosition(0,0);
        mostro_accesorio->setLocalZOrder(7);
        mostro_accesorio->setTag(Configuracion::rcsTipoAccesorio);
        mostro_accesorio->setRotation(0);
    }*/
    
}


void Dimeketekito::mostrarMostro(){
    mostro->setVisible(true);
}

TintTo* Dimeketekito::obtenerTintatoAleatorio(){
    int colorAleatorio = Configuracion::aleatorioEnteros(1, gRecursos->nColores-1);
    Color3B * color = gRecursos->obtenerColorSeleccion(colorAleatorio);
    
    
    tintado = TintTo::create(0,color->r,color->g,color->b);
    tintado->retain();
    return tintado;
}

void Dimeketekito::JuegoTerminado(){
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("ganar.mp3");
    escuchadores = false;
    juegoTerminado = true;
    
    LayerColor *lyConseguido = LayerColor::create(Color4B(124,180,224,200));
    lyConseguido->setPosition(cuadroJuego->getPosition());
    lyConseguido->setContentSize(cuadroJuego->getContentSize());
    lyConseguido->setLocalZOrder(20);
    addChild(lyConseguido);
    
    Sprite *foco = Sprite::create("preguntator_focoLuz.png");
    foco->setScaleX(escalaAlta);
    foco->setScaleY(0);
    foco->setScaleZ(escalaAlta);
    
    foco->setAnchorPoint(Vec2(0.5,1));
    foco->setPosition(lyConseguido->getContentSize().width/2,lyConseguido->getContentSize().height);
    lyConseguido->addChild(foco);
    //animacion foco
    ScaleTo *aniFoco = ScaleTo::create(0.7, escalaAlta);
    foco->runAction(aniFoco);
    
    CCLabelTTF *txConseguido = CCLabelTTF::create(LanguageManager::getInstance()->getString("JUEGO_TX_FINAL_EXITO"), "HVD_Comic_Serif_Pro.ttf",120*escala,CCSizeMake((lyConseguido->getContentSize().width),(220*escala)), TextHAlignment::CENTER);
    txConseguido->setColor(Color3B(25,78,121));
    txConseguido->setVerticalAlignment(TextVAlignment::CENTER);
    txConseguido->setAnchorPoint(Vec2(0.5,1));
    txConseguido->setPosition(lyConseguido->getContentSize().width/2,visibleSize.height+(220*escala));
    lyConseguido->addChild(txConseguido);
    
    //animacion textoConsegido
    MoveTo *aniTxConseguido = MoveTo::create(0.3, Vec2(lyConseguido->getContentSize().width/2,(lyConseguido->getContentSize().height)));
    txConseguido->runAction(aniTxConseguido);
    
    Sprite *pizzarra = Sprite::create("pizzarra_final_tiempo.png");
    pizzarra->setScale(escalaAlta);
    pizzarra->setAnchorPoint(Vec2(0.5,1));
    pizzarra->setPosition(visibleSize.width,(lyConseguido->getContentSize().height)-(txConseguido->getContentSize().height)-(120*escala));
    lyConseguido->addChild(pizzarra);
    
    CCLabelTTF *nAciertosPizarra = CCLabelTTF::create(reloj->getString(), "HVD_Comic_Serif_Pro.ttf",200,pizzarra->getContentSize(), TextHAlignment::CENTER);
    nAciertosPizarra->setColor(Color3B(255,255,255));
    nAciertosPizarra->setVerticalAlignment(TextVAlignment::CENTER);
    nAciertosPizarra->setAnchorPoint(Vec2(0,0));
    nAciertosPizarra->setPosition(0,0);
    pizzarra->addChild(nAciertosPizarra);
    
    //animacion pizzara
    MoveTo *aniPizzarra = MoveTo::create(0.3, Vec2(lyConseguido->getContentSize().width/2,pizzarra->getPositionY()));
    pizzarra->runAction(aniPizzarra);
    
    
    CGestorRecursos *gRecursos = new CGestorRecursos();
    CRecurso *recursoAleatorio = gRecursos->obtenerRecursoBloqueadoAleatorio();
    
    if(recursoAleatorio!=NULL){
        gRecursos->quitarRecursoBloqueado(recursoAleatorio);
        
        Sprite *txPremio = Sprite::create("preguntator_finjuego_texto_inferior.png");
        txPremio->setScale(escalaAlta);
        txPremio->setAnchorPoint(Vec2(0.5,0));
        txPremio->setPosition(foco->getPositionX(),foco->getPositionY()-(foco->getContentSize().height*escalaAlta));
        txPremio->setOpacity(0);
        lyConseguido->addChild(txPremio);
        
        //animacion txPremio
        Sequence *aniPremio1 = Sequence::create(DelayTime::create(0.7),FadeIn::create(1),NULL);
        txPremio->runAction(aniPremio1);
        
        
        Sprite *premio = Sprite::create(recursoAleatorio->uri->getCString());
        float escalaPremio = ((pizzarra->getContentSize().height*pizzarra->getScale())/2)/premio->getContentSize().height;
        float escalaPremioAncha = ((pizzarra->getContentSize().width*pizzarra->getScale()))/premio->getContentSize().width;
        if(escalaPremioAncha<escalaPremio)
            escalaPremio = escalaPremioAncha;
        premio->setScale(escalaPremio);
        premio->setAnchorPoint(Vec2(0.5,0));
        premio->setPosition(txPremio->getPositionX(),txPremio->getPositionY()+(20*escalaPremio)+(txPremio->getContentSize().height*txPremio->getScaleY()));
        premio->setOpacity(0);
        //nuevo
        if(recursoAleatorio->tipoRecurso->getValue()!=Configuracion::rcsTipoOjos&&recursoAleatorio->tipoRecurso->getValue()!=Configuracion::rcsTipoAccesorio&&recursoAleatorio->tipoRecurso->getValue()!=Configuracion::rcsTipoDientes&&recursoAleatorio->tipoRecurso->getValue()!=Configuracion::rcsTipoColor)
            premio->runAction(TintTo::create(0,0,0,0));
        lyConseguido->addChild(premio);
        
        string textoTraducido1 = LanguageManager::getInstance()->getString("kitDe");
        string keyTexto2 = __String::createWithFormat("tipoRecurso%i",recursoAleatorio->tipoRecurso->getValue())->getCString();
        string textoTraducido2 = LanguageManager::getInstance()->getString(keyTexto2);
        string textoFinal = __String::createWithFormat("%s %s",textoTraducido1.c_str(),textoTraducido2.c_str())->getCString();
        
        CCLabelTTF *nAciertosPizarra = CCLabelTTF::create(textoFinal, "HVD_Comic_Serif_Pro.ttf",60,Size(lyConseguido->getContentSize().width,txPremio->getContentSize().height), TextHAlignment::CENTER);
        nAciertosPizarra->setColor(Color3B(229,57,57));
        nAciertosPizarra->setVerticalAlignment(TextVAlignment::BOTTOM);
        nAciertosPizarra->setAnchorPoint(Vec2(0.5,0));
        nAciertosPizarra->setPosition(txPremio->getContentSize().width/2,80);
        nAciertosPizarra->setOpacity(0);
        txPremio->addChild(nAciertosPizarra);
        Sequence *aniNAciertosPizarra = Sequence::create(DelayTime::create(0.7),FadeIn::create(1),NULL);
        nAciertosPizarra->runAction(aniNAciertosPizarra);
        //nuevo
        
        
        Sequence *aniPremio = Sequence::create(DelayTime::create(0.7),FadeIn::create(1),NULL);
        premio->runAction(aniPremio);
        
        //efecto flotando
        RotateTo *rotarIzq = RotateTo::create(1, 10);
        RotateTo *rotarDer = RotateTo::create(1, -10);
        
        Sequence *total1 = Sequence::create(rotarIzq,rotarDer, NULL);
        Sequence *total2 = Sequence::create(rotarDer->clone(),rotarIzq->clone(), NULL);
        RepeatForever *repeticion1 = RepeatForever::create(total1);
        RepeatForever *repeticion2 = RepeatForever::create(total2);
        
        premio->runAction(repeticion1);
        
    }
    
    
    
}

bool Dimeketekito::comprobarToquePartesMostro(cocos2d::Touch *toque){
    //inicializo con array para elegir el que tenga mas zIndex
    __Array *aSpCogidos = __Array::createWithCapacity(mostro->getChildrenCount());
    int contador = 0;
    for (int i=0; i<mostro->getChildrenCount(); i++) {
        Sprite *parteActualMostro = dynamic_cast<Sprite*>(mostro->getChildren().at(i));
        if(!aSpCogidos->containsObject(parteActualMostro)&&Configuracion::comprobarToque(toque,parteActualMostro)&&parteActualMostro->isVisible()){
            if(parteActualMostro!=mostro_cuerpo){
                Sprite  *boteAsociado = obtenerBotePorEntidad(parteActualMostro->getTag());
                aSpCogidos->insertObject(parteActualMostro,contador);
                //volvemos a poner todas las partes cuando antes solo habia una falsa
                /*if(boteAsociado!=NULL || parteActualMostro->getTag()==parteMostroFalsa){
                    aSpCogidos->insertObject(parteActualMostro,contador);
                }else{
                    log("parte que no tiene bote ni es la falsa");
                }*/
                contador++;
            }else{
                log("Cuerpo");
            }
            
        }
    }
    
    int parteMaxCercana = -1;
    int zMasAlto = -99;
    for(int i=0;i<aSpCogidos->count();i++){
        Sprite *parteActualMostro = dynamic_cast<Sprite*>(aSpCogidos->getObjectAtIndex(i));
        if(zMasAlto<parteActualMostro->getLocalZOrder()){
            zMasAlto =parteActualMostro->getLocalZOrder();
            parteMaxCercana = i;
        }
    }
    
    
    if(parteMaxCercana != -1){
        this->removeChild(spCogidoClon);
        
        spCogido = dynamic_cast<Sprite*>(aSpCogidos->getObjectAtIndex(parteMaxCercana));
        
        spCogido->setVisible(false);
        
        Vec2 posicion = mostro->getPosition();
        posicion.x += spCogido->getPositionX();
        posicion.y += spCogido->getPositionY();
        
        if(spCogido->getTag()<0){
            Rect rectIzq = {spCogido->getContentSize().width, 0, spCogido->getContentSize().width, spCogido->getContentSize().height};
            spCogidoClon = Sprite::createWithTexture(spCogido->getTexture(), rectIzq);
        }else{
            Rect rectIzq = {0, 0, spCogido->getContentSize().width, spCogido->getContentSize().height};
            spCogidoClon = Sprite::createWithTexture(spCogido->getTexture(), rectIzq);
        }
        
        spCogidoClon->setScale(escala);
        spCogidoClon->setPosition(toque->getLocation());
        spCogidoClon->setAnchorPoint(Vec2(0.5,0.5));
        spCogidoClon->setLocalZOrder(50);
        spCogidoClon->setVisible(true);
        spCogidoClon->setTag(spCogido->getTag());
        if(spCogido!=mostro_boca&&spCogido!=mostro_ojos){
            spCogidoClon->runAction(tintado->clone());
        }
        addChild(spCogidoClon);
        cogidaParte = true;
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("dimeketekito_plop.mp3");
    }else{
        cogidaParte = false;
    }
    
    return cogidaParte;
}

void Dimeketekito::desplazarParteMostro(Touch *toque){
    
    if(!spCogidoClon->isVisible()){
        spCogidoClon->setVisible(true);
    }
    
    spCogidoClon->setPosition(toque->getLocation());
    
    Size s = spCogidoClon->getContentSize();
    log("tamano %f %f",s.width*escala,s.height*escala);
    
    //spCogidoClon->setPosition(toque->getLocation().x+((s.width*escala*-1)/2),toque->getLocation().y+((s.width*escala*-1)/2));
    
    //mostro->removeChild(spCogido);
    //spCogido->setVisible(false);
}

void Dimeketekito::rozandoBote(cocos2d::Touch *toque){
    bool dentro = false;
    for(int i=0;i<aBotes->count();i++){
        Sprite *boteActual = dynamic_cast<Sprite*>(aBotes->getObjectAtIndex(i));
        if(Configuracion::comprobarToque(toque,boteActual)){
            dentro = true;
            
            RotateTo *rotarIzq = RotateTo::create(0.1, 7,7);
            RotateTo *rotarDer = RotateTo::create(0.2, -7,-7);
            RotateTo *rotarNor = RotateTo::create(0.1, 0,0);
            CallFunc *runCallback1 = CallFunc::create(CC_CALLBACK_0(Dimeketekito::reproducirToqueBote, this));
            
            Sequence *movimiento = Sequence::create(rotarIzq,rotarDer,runCallback1,rotarNor, NULL);
            if(boteActual->getNumberOfRunningActions()==0){
                boteActual->runAction(RepeatForever::create(Sequence::create(movimiento,NULL)));
                rozadoBote = true;
            }
            
        }
    }
    
    if(!dentro&&rozadoBote){
        Dimeketekito::stopAnimBotesGiro(false);
    }
}
void Dimeketekito::reproducirToqueBote(){

    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("dimeketekito_clinclinclin.mp3");
    
}

void Dimeketekito::stopAnimBotesGiro(bool forzar){

    for(int i=0;i<aBotes->count();i++){
        Sprite *boteActual = dynamic_cast<Sprite*>(aBotes->getObjectAtIndex(i));
        
        if(boteActual->getNumberOfRunningActions()!=0&&rozadoBote == true){
            boteActual->stopAllActions();
            boteActual->runAction(RotateTo::create(0.1, 0,0));
            rozadoBote = false;
        }
        
        if(forzar){
            boteActual->stopAllActions();
            boteActual->runAction(RotateTo::create(0.1, 0,0));
            rozadoBote = false;
        }
    }
    
}

void Dimeketekito::stopAnimBotesGiroShedule(float seg){
    if(!rozadoBote)stopAnimBotesGiro(true);
}

void Dimeketekito::comprobarExitoParteMostro(cocos2d::Touch *toque){
    
    if(cogidaParte){
        Sprite *boteExito = obtenerBotePorEntidad(spCogidoClon->getTag());
        if(boteExito!=NULL&&Configuracion::comprobarToque(toque,boteExito)){
            CCLOG("EXITO !!!");
            spCogido->setVisible(false);
            Vector<Node*> hijos = boteExito->getChildren();
            if(spCogido!=mostro_boca&&spCogido!=mostro_ojos){
                hijos.at(0)->runAction(tintado->clone());
            }else{
                hijos.at(0)->runAction(TintTo::create(0,255,255,255));
            }
            spCogidoClon->runAction(FadeOut::create(0.5));
            
            aciertos++;
            if(aciertos==nBotes)
                JuegoTerminado();
            else{
                CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("dimeketekito_plop2.mp3");
                __String *texto = __String::createWithFormat("%s %i",LanguageManager::getInstance()->getString("DIMEKETEKITO_TX_PROF_01").c_str(),nBotes-aciertos);
                cambiarTextoDialogo(texto->getCString());
            }
        }else{
            //pregunto si a dado en algun bote
            bool tocadoBote = false;
            for(int i=0;i<aBotes->count();i++){
                Sprite *boteActual = dynamic_cast<Sprite*>(aBotes->getObjectAtIndex(i));
                if(Configuracion::comprobarToque(toque,boteActual)){
                    tocadoBote = true;
                }
            }
            Vec2 posicion = mostro->getPosition();
            //posicion.x -= (spCogido->getAnchorPoint().x-spCogidoClon->getAnchorPoint().x)*(spCogido->getContentSize().width*escala);
            //posicion.y -= (spCogido->getAnchorPoint().y-spCogidoClon->getAnchorPoint().y)*(spCogido->getContentSize().height*escala);
            float quitoX = spCogido->getPositionX();
            float quitoY = spCogido->getPositionY();
            posicion.x -= quitoX;
            posicion.y += quitoY;
            
            //spCogidoClon->setLocalZOrder(mostro->getLocalZOrder()-1);
            if(tocadoBote){
                reinicioPartes();
                cambiarTextoDialogo(LanguageManager::getInstance()->getString("DIMEKETEKITO_TX_PROF_02"));
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("fallo.mp3");
            }else{
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("dimeketekito_fiuu.mp3");
                cambiarTextoDialogo(LanguageManager::getInstance()->getString("DIMEKETEKITO_TX_PROF_03"));
            }
            
            
            MoveTo *elatico = MoveTo::create(0.5,posicion);
            ScaleTo *esc0 = ScaleTo::create(0.2,spCogido->getScale()/1.5);
            ScaleTo *esc1 = ScaleTo::create(0.3,spCogido->getScale());
            CallFunc *runCallback1 = CallFunc::create(CC_CALLBACK_0(Dimeketekito::falloDesplazamiento, this));
            spCogidoClon->runAction(Sequence::create(esc0,esc1, NULL));
            spCogidoClon->runAction(Sequence::create(elatico,runCallback1, NULL));
            escuchadores = false;
            
            
        }
        
    }
    
    rozadoBote = false;
}

void Dimeketekito::falloDesplazamiento(){
    spCogido->setVisible(true);
    spCogidoClon->setVisible(false);
    escuchadores = true;
}

Sprite* Dimeketekito::obtenerBotePorEntidad(int entidad){
    for(int i=0;i<aBotes->count();i++){
        Sprite *boteActual = dynamic_cast<Sprite*>(aBotes->getObjectAtIndex(i));
        int entidadBote = boteActual->getTag();
        if(entidadBote==entidad){
            return boteActual;
        }
    }
    return NULL;
}

void Dimeketekito::reinicioPartes(){
    Vector<Node *> partes = mostro->getChildren();
    for (int i=0;i<partes.size() ; i++) {
        Node* parte = partes.at(i);
        if(parte!=spCogido)
            parte->setVisible(true);
        
    }
    
    for (int i=0;i<aBotes->count(); i++) {
        Sprite *boteActual = dynamic_cast<Sprite*>(aBotes->getObjectAtIndex(i));
        Node* contenidoBote = boteActual->getChildren().at(0);
        contenidoBote->runAction(TintTo::create(0,0,0,0));
    }
    aciertos = 0;
}


bool Dimeketekito::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
    
    if(Configuracion::desarrollo)
        log("BEGAN %f %f",touch->getLocation().x,touch->getLocation().y);
    
    if(juegoTerminado)
        irAtras(NULL);
    
    if(isPlayNarracion){
        if(Configuracion::comprobarToque(touch, capaTextoCuadroInicial)){
            CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
            saltarAnimacion();
        }
    }
    
    //SI LE DIO AL PROFESOR
    bool  tocaProfesor = false;
    auto target = profesor;
    Point locationInNode = target->convertToNodeSpace(touch->getLocation());
    Size s = profesor->getContentSize();
    Rect rect = Rect(0, 0, s.width, s.height);
    if (rect.containsPoint(locationInNode))
    {
        tocaProfesor = true;
        if(isPlayNarracion || textosProfesor->count()>0 || cuadroDialogo->getString()!=""){
            cambiarTextoDialogo(LanguageManager::getInstance()->getString("PROFESOR_MENJ_01"));
            if(isPlayNarracion){
                mostrarDialogoComenzar();
                stopAction(narracion);
                isPlayNarracion = false;
                CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
            }
        }else{
            cambiarTextoDialogo(LanguageManager::getInstance()->getString("PROFESOR_MENJ_02"));
        }
    }
    
    if(!escuchadores){
        return false;
    }
    
    
    if(comprobarToquePartesMostro(touch)){
        CCLOG("PARTE TOCADA DE MOSTRO");
    }else{
        CCLOG("NO TOCO PARTE MOSTRO");
    }
    
    /*
     spCogido = parteActualMostro;
     spCogido->setVisible(false);
     
     */
    
    //SI LE DIO A MOSTRUOS
    /*bool  tocaBote = false;
    if(aBotes!=NULL){
        for(int i = 0;i<aBotes->count();i++){
            auto target = static_cast<Sprite*>(aBotes->getObjectAtIndex(i));
            //if(Configuracion::desarrollo)
            //CCLOG("my sprite    x %f y %f",obj->getPosition().x,obj->getPosition().y);
            Point locationInNode = target->convertToNodeSpace(touch->getLocation());
            Size s = target->getContentSize();
            Rect rect = Rect(0, 0, s.width, s.height);
            if (rect.containsPoint(locationInNode))
            {
                return true;
            }
        }
    }
    
    
    //SI TOCA AL PROFESOR
    if(!tocaProfesor&&!tocaBote&&proximaPregunta>0){
        cambiarTextoDialogo("¡Afina tu punteria!");
    }
    */
    
    return  true;
}
void Dimeketekito::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event)
{
    if(!escuchadores){
        return;
    }
    
    if(Configuracion::desarrollo)
        log("MOVED %f %f ",touch->getLocation().x,touch->getLocation().y);
    
    if(cogidaParte){
        desplazarParteMostro(touch);
        rozandoBote(touch);
    }
    
}
void Dimeketekito::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
{
    if(!escuchadores){
        return;
    }
    
    if(Configuracion::desarrollo)
        log("ENDED %f %f ",touch->getLocation().x,touch->getLocation().y);
    
    
    if(cogidaParte)
        comprobarExitoParteMostro(touch);
}

