#include "HelloWorldScene.h"
#include "Preguntator.h"
#include "Configuracion.h"
#include "CGestorRecursos.h"
#include "LanguageManager.h"
#include "SimpleAudioEngine.h"
#include "Ajustes.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "JniLink.h"
#endif


USING_NS_CC;

Scene* Preguntator::createScene()
{

    auto scene = Scene::create();

    auto layer = Preguntator::create();
    scene->addChild(layer);
    return scene;
}

bool Preguntator::init()
{

    if ( !Layer::init() )
    {
        return false;
    }
    this->setKeypadEnabled(true);
    
    obtenerMedidas();
    initFondo();
    initBotonAtras();
    initBtAjustes();
    //reloj va despues de bt_atras porque coge la referencia
    initReloj();
    initProfesor();
    initCuadroInicial();
    initBocadillo();
    initTextoCentral();
    initCuadroJuego();
    initPlataformas();
    initPreguntas();
    
    //activo los tocuh de pantalla
    auto listener1 = EventListenerTouchOneByOne::create();
    listener1->setSwallowTouches(true);
    listener1->onTouchBegan = CC_CALLBACK_2(Preguntator::onTouchBegan, this);
    listener1->onTouchMoved = CC_CALLBACK_2(Preguntator::onTouchMoved, this);
    listener1->onTouchEnded = CC_CALLBACK_2(Preguntator::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);
    
    
    
    return true;
}

void Preguntator::onEnterTransitionDidFinish(){
    if(Configuracion::desarrollo)
        CCLOG("ENTRA EN ESCENA");
    
    if (!running) {
        initMusica();
        
        if(Configuracion::desarrollo){
            comenzarNarracion();
        }else
            comenzarNarracion();
        
        running = true;
        
    }
    
    CCTextureCache::getInstance()->getCachedTextureInfo();
    
}

void Preguntator::onExitTransitionDidStart() {
    
    cleanMemory();
    
}

Preguntator::~Preguntator() {
    
    cleanMemory();
    
}

void Preguntator::cleanMemory() {
    
    CCDirector::sharedDirector()->purgeCachedData();
    
    CCTextureCache::sharedTextureCache()->removeUnusedTextures();
    CCTextureCache::sharedTextureCache()->removeAllTextures();
    CCTextureCache::purgeSharedTextureCache();
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames();
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFrames();
    CCSpriteFrameCache::purgeSharedSpriteFrameCache();
    
    SpriteFrameCache::getInstance()->removeUnusedSpriteFrames();
    
}

void Preguntator::comenzarNarracion(){
    
    lbCuadroInicial->setVisible(true);
    capaFondoCuadroInicial->setVisible(true);
    capaTextoCuadroInicial->setVisible(true);
    
    if(!isPlayNarracion){
        isPlayNarracion = true;
        narracionActual = 0;
        saltarAnimacion();
    }
}
void Preguntator::saltarAnimacion(){
    stopAction(narracion);
    CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
    CallFunc *runCallback1 = CallFunc::create(CC_CALLBACK_0(Preguntator::narracion1, this));
    CallFunc *runCallback2 = CallFunc::create(CC_CALLBACK_0(Preguntator::narracion2, this));
    CallFunc *runCallback3 = CallFunc::create(CC_CALLBACK_0(Preguntator::narracion3, this));
    CallFunc *runCallback4 = CallFunc::create(CC_CALLBACK_0(Preguntator::narracion4, this));
    CallFunc *runCallback5 = CallFunc::create(CC_CALLBACK_0(Preguntator::mostrarDialogoComenzar, this));
    if(narracionActual==0){
        narracion = Sequence::create(runCallback1,DelayTime::create(4),runCallback2,DelayTime::create(5.8),runCallback3,DelayTime::create(10),runCallback4,DelayTime::create(4.5),runCallback5,NULL);
    }else if(narracionActual==1){
        narracion = Sequence::create(runCallback2,DelayTime::create(5.8),runCallback3,DelayTime::create(10),runCallback4,DelayTime::create(4.5),runCallback5,NULL);
    }else if(narracionActual==2){
        narracion = Sequence::create(runCallback3,DelayTime::create(10),runCallback4,DelayTime::create(4.5),runCallback5,NULL);
    }else if(narracionActual==3){
        narracion = Sequence::create(runCallback4,DelayTime::create(4.5),runCallback5,NULL);
    }else if(narracionActual==4){
        narracion = Sequence::create(runCallback5,NULL);
    }
    runAction(narracion);
}

void Preguntator::narracion1(){
    narracionActual = 1;
    CallFunc *leer = CallFunc::create(CC_CALLBACK_0(Preguntator::ProfesorLeyendoHablando, this));
    Sequence *leyendo = Sequence::create(leer,NULL);
    this->runAction(leyendo);
    
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("preguntator_intro_1.mp3");
    lbCuadroInicial->setString(LanguageManager::getInstance()->getString("PREGUNTATOR_NAR_01"));
}
void Preguntator::narracion2(){
    narracionActual = 2;
    CallFunc *leer = CallFunc::create(CC_CALLBACK_0(Preguntator::ProfesorLeyendoHablando, this));
    Sequence *leyendo = Sequence::create(leer,DelayTime::create(1.6),leer,DelayTime::create(1.6),leer,DelayTime::create(1.6),leer,NULL);
    this->runAction(leyendo);
    
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("preguntator_intro_2.mp3");
    lbCuadroInicial->setString(LanguageManager::getInstance()->getString("PREGUNTATOR_NAR_02"));
}
void Preguntator::narracion3(){
    narracionActual = 3;
    CallFunc *leer = CallFunc::create(CC_CALLBACK_0(Preguntator::ProfesorLeyendoHablando, this));
    Sequence *leyendo = Sequence::create(leer,DelayTime::create(1.6),leer,DelayTime::create(1.6),leer,DelayTime::create(1.6),leer,NULL);
    this->runAction(leyendo);
    
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("preguntator_intro_3.mp3");
    lbCuadroInicial->setString(LanguageManager::getInstance()->getString("PREGUNTATOR_NAR_03"));
}
void Preguntator::narracion4(){
    narracionActual = 4;
    CallFunc *leer = CallFunc::create(CC_CALLBACK_0(Preguntator::ProfesorLeyendoHablando, this));
    Sequence *leyendo = Sequence::create(leer,NULL);
    this->runAction(leyendo);
    
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("preguntator_intro_4.mp3");
    lbCuadroInicial->setString(LanguageManager::getInstance()->getString("PREGUNTATOR_NAR_04"));
}

void Preguntator::obtenerMedidas(){
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
    
    anchoLateral = (visibleSize.width/100)*20;
    anchoNoLateral = ((visibleSize.width/100)*80);
    anchoLateralCE = (visibleSize.width/100)*20;
    anchoNoLateralCE = ((visibleSize.width/100)*80);
}

void Preguntator::irAtras(Ref* pSender){
    if(Configuracion::desarrollo)
        CCLOG("atras");
    CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    
//    auto scene = HelloWorld::createScene();
//    auto transicion = TransitionFade::create(0.3f, scene);
//    Director::getInstance()->replaceScene(transicion);
    
    Director::getInstance()->popScene();
    
}

void Preguntator::initFondo(){
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
    
    /*
    Sprite* bg = Sprite::create("preguntator_bg.png");
    //calculo su 33%
    float escala1 = altoIndividal/bg->getContentSize().height;
    
    bg->setScale(escala1);
    bg->setAnchorPoint(Vec2(0, 0));
    bg->setPosition(0,0);
    bg->setZOrder(4);
    this->addChild(bg);
    */
    
    Sprite* interrogaciones = Sprite::create("preguntator_interrogaciones.png");
    //calculo su 33%
    float escala2 = altoIndividal/interrogaciones->getContentSize().height;
    
    interrogaciones->setScale(escala2);
    interrogaciones->setAnchorPoint(Vec2(0.5, 0.5));
    interrogaciones->setPosition(anchoLateral/2,visibleSize.height/2);
    interrogaciones->setZOrder(7);
    this->addChild(interrogaciones);
    
}

void Preguntator::initReloj(){
    reloj = CCLabelTTF::create("00:00", "HVD_Comic_Serif_Pro.ttf", letraReloj*escala,CCSizeMake(anchoLateral, (letraReloj+20)*escala), TextHAlignment::CENTER);
    reloj->setColor(Color3B(216,254,51));
    reloj->setVerticalAlignment(TextVAlignment::TOP);
    reloj->setAnchorPoint(Vec2(0, 1));
    reloj->setPosition(0,botonAtras->getPositionY()-(botonAtras->getContentSize().height*escala));
    reloj->setZOrder(9);
    this->addChild(reloj, 1);
}

void Preguntator::initMusica(){
    //pongo musica
    if(!Configuracion::desarrollo){
        if(CocosDenshion::SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying()){
            
        }else{
            CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("sintonia_preguntator.mp3", true);
        }
    }
}

void Preguntator::initBotonAtras(){
    botonAtras = MenuItemImage::create("preguntator_bt_atras.png","preguntator_bt_atras_down.png",CC_CALLBACK_1(Preguntator::irAtras, this));
    
    botonAtras->setScale(escala);
    botonAtras->setAnchorPoint(Vec2(0, 1));
    //calculo espacio sobrante
    float espacio = anchoLateral-(botonAtras->getContentSize().width*escala);
    
    botonAtras->setPosition(0+(espacio/2),visibleSize.height-(espacioSuperiorBtAtras*escala));
    
    menu = Menu::create(botonAtras, NULL);
    menu->setPosition(Vec2::ZERO);
    menu->setZOrder(20);
    this->addChild(menu);
}

void Preguntator::initBtAjustes(){
    
    btAjustes = MenuItemImage::create("mostrosity_mimostro_bt_ajustes.png","mostrosity_mimostro_bt_ajustes_down.png",CC_CALLBACK_1(Preguntator::selectorAjustes, this));
    btAjustes->setScale(escala);
    btAjustes->setAnchorPoint(Vec2(1,1));
    btAjustes->setPosition(visibleSize.width-(espacioBordesCuadro*2),botonAtras->getPositionY());
    btAjustes->retain();
    menu->addChild(btAjustes);
    
}

void Preguntator::selectorAjustes(Ref *pSender){
    CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    
    if(Configuracion::desarrollo)
        CCLOG("Selector ajustes");
    
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    
//    Ajustes::desdeEscena = Ajustes::desdePreguntator;
//    auto scene = Ajustes::createScene();
//    auto transicion = TransitionFade::create(0.3f, scene);
//    Director::getInstance()->replaceScene(transicion);
    
    auto scene = Ajustes::createScene();
    Director::getInstance()->pushScene(scene);
    
}

void Preguntator::initCuadroInicial(){
    
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
    
    lbCuadroInicial = CCLabelTTF::create("", "HVD_Comic_Serif_Pro.ttf", 100*escala,CCSizeMake(visibleSize.width-(anchoLateral*0.7*2),700*escala), TextHAlignment::CENTER);
    //70% del lateral tanto por un lado como por el otro
    lbCuadroInicial->setColor(Color3B(228,70,106));
    lbCuadroInicial->setVerticalAlignment(TextVAlignment::CENTER);
    lbCuadroInicial->setAnchorPoint(Vec2(0.5,0.5));
    lbCuadroInicial->setPosition(visibleSize.width/2,visibleSize.height/2);
    lbCuadroInicial->setZOrder(14);
    lbCuadroInicial->setVisible(false);
    this->addChild(lbCuadroInicial);
    
    
}

void Preguntator::initBocadillo(){
    textosProfesor = __Array::create();
    textosProfesor->retain();
    bocadillo = Sprite::create("preguntator_cuadro.png");
    
    escalaPropiaBocadillo = anchoLateral/bocadillo->getContentSize().width;
    if(relacion<1.5)
        bocadillo->setScale(escalaPropiaBocadillo);
    else{
        escalaPropiaBocadillo = escala;
        bocadillo->setScale(escala);
    }
    bocadillo->setVisible(false);
    bocadillo->setScale(0);
    bocadillo->setAnchorPoint(Vec2(0.5,0));
    bocadillo->setPosition((anchoLateral/2)+((espacioBordesCuadro*escala)/2),profesor->getPositionY()+(profesor->getContentSize().height*escala));
    bocadillo->setZOrder(8);
    this->addChild(bocadillo);

}
void Preguntator::initProfesor(){
    
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

void Preguntator::ProfesorLeyendoHablando(){
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

void Preguntator::ProfesorFalloRespuesta(){
    
    MoveTo *cejasAbajo = MoveTo::create(0.2, Vec2((anchoProfesor/2)-15,altoCejas-25));
    if(profCejas->getNumberOfRunningActions()==0){
        profCejas->runAction(cejasAbajo);
    }
    
}

void Preguntator::ProfesorAciertaRespuesta(){
    RotateBy *Giro = RotateBy::create(0.4, 360);
    if(profBigote->getNumberOfRunningActions()==0){
        profBigote->runAction(Giro);
    }
    
    MoveTo *ojosArriba = MoveTo::create(0.4, Vec2(anchoProfesor/2,altoOjos+20));
    if(profOjos->getNumberOfRunningActions()==0){
        profOjos->runAction(ojosArriba);
    }
}

void Preguntator::ProfesorNuevaPregunta(){
    MoveTo *cejasOrigen = MoveTo::create(0.4, Vec2((anchoProfesor/2),altoCejas));
    if(profCejas->getNumberOfRunningActions()==0){
        profCejas->runAction(Sequence::create(DelayTime::create(1),cejasOrigen,NULL));
    }
    
    MoveTo *ojosNormal = MoveTo::create(0.4, Vec2(anchoProfesor/2,altoOjos));
    if(profOjos->getNumberOfRunningActions()==0){
        profOjos->runAction(ojosNormal);
    }
}

void Preguntator::initCuadroJuego(){
    altoIndividalCuadroJuego = visibleSize.height-((espacioBordesCuadro*2*escala));
    anchoIndividualCuadroJuego = anchoNoLateral-(espacioBordesCuadro*2*escala);
    
    cuadroJuego = LayerGradient::create(Color4B(136,185,230,255),Color4B(163,201,235,255));
    cuadroJuego->setContentSize(Size(anchoIndividualCuadroJuego,altoIndividalCuadroJuego));
    cuadroJuego->setPosition(anchoLateral+(espacioBordesCuadro*escala),(espacioBordesCuadro*escala));
    cuadroJuego->setZOrder(6);
    this->addChild(cuadroJuego);
    
    Layer* cuadroJuegoInterior = LayerColor::create(Color4B(52,135,210,255));
    cuadroJuegoInterior->setContentSize(Size(anchoIndividualCuadroJuego-((espacioBordesCuadro/2)*2*escala),altoIndividalCuadroJuego/2));
    cuadroJuegoInterior->setPosition(cuadroJuego->getPositionX()+((espacioBordesCuadro/2)*escala),cuadroJuego->getPositionY()+((espacioBordesCuadro/2)*escala));
    cuadroJuegoInterior->setZOrder(6);
    this->addChild(cuadroJuegoInterior);
    
}

void Preguntator::initPlataformas(){
    if(Configuracion::desarrollo)
        CCLOG("ENTRADO EN PLATAFORMAS");
    //25% de la zona de juego
    float anchoPorPlataforma = anchoNoLateral/4-(espacioBordesCuadro*escala);
    
    for(int i=1;i<5;i++){
        __String* archivo = __String::createWithFormat("preguntator_plataforma%d.png",i);
        Sprite* plataforma = Sprite::create(archivo->getCString());
        
        float AnchoActualPlataforma = (plataforma->getContentSize().width*escala);
        if(AnchoActualPlataforma>anchoPorPlataforma){
            
            escalaPropiaPlataformas =anchoPorPlataforma/plataforma->getContentSize().width;
            plataforma->setScale(escalaPropiaPlataformas);
            
            
        }else{
            plataforma->setScale(escala);
        }
        
        plataforma->setAnchorPoint(Vec2(0,0));
        
        if(escalaPropiaPlataformas>0){
            plataforma->setPosition(cuadroJuego->getPositionX()+(anchoPorPlataforma*(i-1))+(espacioBordesCuadro*escalaPropiaPlataformas),(espacioBordesCuadro*escala)+(espacioBordesCuadro/2*escala));
        }else{
            plataforma->setPosition(cuadroJuego->getPositionX()+(anchoPorPlataforma*(i-1))+(espacioBordesCuadro*escala)+(espacioBordesCuadro/2*escala),(espacioBordesCuadro*escala)+(espacioBordesCuadro/2*escala));
        }
        plataforma->setZOrder(7);
        this->addChild(plataforma);
        plataforma->retain();
        
        if(aPlataformas==NULL){
            aPlataformas = __Array::createWithCapacity(4);
            aPlataformas->retain();
        }
        aPlataformas->addObject(plataforma);
       
    }
}

void Preguntator::initTextoCentral(){
    float bordesBocadillos = 40*escalaPropiaBocadillo;
    cuadroDialogo = CCLabelTTF::create("", "HVD_Comic_Serif_Pro.ttf", (bocadillo->getContentSize().height*escalaPropiaBocadillo)/7,CCSizeMake((bocadillo->getContentSize().width*escalaPropiaBocadillo)-(bordesBocadillos*2), (bocadillo->getContentSize().height*escalaPropiaBocadillo)-(bordesBocadillos*3)), TextHAlignment::CENTER);
    cuadroDialogo->setColor(Color3B(0,0,0));
    cuadroDialogo->setVerticalAlignment(TextVAlignment::CENTER);
    cuadroDialogo->setAnchorPoint(Vec2(0.5,0.5));
    cuadroDialogo->setPosition(bocadillo->getPositionX(),bocadillo->getPositionY()+((bocadillo->getContentSize().height*escalaPropiaBocadillo)/2)+(bordesBocadillos*0.5));
    cuadroDialogo->setZOrder(10);
    this->addChild(cuadroDialogo);
    
}

void Preguntator::cambiarTextoDialogo(std::string texto){
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
            CallFunc *runCallback1 = CallFunc::create(CC_CALLBACK_0(Preguntator::modificarTXTDialogo, this));
            CallFunc *runCallback2 = CallFunc::create(CC_CALLBACK_0(Preguntator::vaciarTXTDialogo, this));
            CallFunc *runCallback3 = CallFunc::create(CC_CALLBACK_0(Preguntator::rellamarTXTDialogo, this));
            
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
void Preguntator::modificarTXTDialogo(){
    this->cuadroDialogo->setString(textoProximoBocadillo);
    cuadroDialogo->runAction(FadeIn::create(0.3));
}
void Preguntator::vaciarTXTDialogo(){
    this->cuadroDialogo->setString("");
    bocadillo->setVisible(false);
}

void Preguntator::rellamarTXTDialogo(){
    cambiarTextoDialogo("");
}

void Preguntator::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event){
	irAtras(NULL);
}

void Preguntator::initPreguntas(){

    preguntas = CCArray::createWithCapacity(20);
    preguntas->retain();
    
    gPreguntas = new CPreguntasPreguntator();
    gPreguntas->retain();
    
    nPreguntas = gPreguntas->ObtenerNumeroPreguntas();
    
    //inicializo las preguntas realizadas
    PreguntasRealizadas = __Array::createWithCapacity(5);
    PreguntasRealizadas->retain();
    
    //creo el layer de toque de preguntas
    marcoRespuestas = LayerColor::create(Color4B(0,0,0,0), cuadroJuego->getContentSize().width,cuadroJuego->getContentSize().height/1.5);
    marcoRespuestas->setPosition(cuadroJuego->getPosition());
    marcoRespuestas->setPositionY(cuadroJuego->getContentSize().height/4);
    marcoRespuestas->setLocalZOrder(100);
    addChild(marcoRespuestas);

}

__String* Preguntator::obtenerRespuesta(int iNRespuesta){
    
    return dynamic_cast<__String* >(gPreguntas->aRespuestas->getObjectAtIndex(iNRespuesta));
}


void Preguntator::mostrarDialogoComenzar(){
    lbCuadroInicial->setVisible(false);
    isPlayNarracion = false;
    if(dial1_bg==NULL){
        crearDialogoComenzar();
    }
    dial1_bg->setVisible(true);
}
void Preguntator::ocultarDialogoComenzar(){
    
    if(dial1_bg==NULL){
        crearDialogoComenzar();
    }
    dial1_bg->setVisible(false);
}

void Preguntator::crearDialogoComenzar(){
    dial1_bg = LayerColor::create(Color4B(0,0,0,0), visibleSize.width-(anchoLateral*escala*0.7*2), 700*escala);
    dial1_bg->setPosition((visibleSize.width-dial1_bg->getContentSize().width)/2,visibleSize.height/2-(700*escala/2));
    dial1_bg->setZOrder(16);
    this->addChild(dial1_bg);
    
    dial1_Imenu1 = MenuItemImage::create("preguntator_dial_bt1.png","preguntator_dial_bt1_down.png",CC_CALLBACK_1(Preguntator::dial1_Imenu2_resp1, this));
    dial1_Imenu1->setScale(escala);
    dial1_Imenu1->setAnchorPoint(Vec2(1, 1));
    dial1_Imenu1->setPosition(dial1_bg->getContentSize().width/2,dial1_bg->getContentSize().height/2);
    
    dial1_Imenu2 = MenuItemImage::create("preguntator_dial_bt2.png","preguntator_dial_bt2_down.png",CC_CALLBACK_1(Preguntator::dial1_Imenu2_resp2, this));
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

void Preguntator::dial1_Imenu2_resp1(Ref* sender){
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("tambores_3.mp3");
    ocultarDialogoComenzar();
    comenzarNarracion();
}

void Preguntator::dial1_Imenu2_resp2(Ref* sender){
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("tambores_3.mp3");
    lbCuadroInicial->setVisible(false);
    capaFondoCuadroInicial->setVisible(false);
    capaTextoCuadroInicial->setVisible(false);
    
    ocultarDialogoComenzar();
    comenzarReloj();
    iniciarSiguientePregunta();
}

void Preguntator::comenzarReloj(){
    
    this->schedule(schedule_selector(Preguntator::aumentarReloj),1.0);

}
void Preguntator::aumentarReloj(float dt){
    if(tiempoRestante<0||juegoTerminado){
        unschedule(schedule_selector(Preguntator::aumentarReloj));
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

void Preguntator::iniciarSiguientePregunta(){
    ProfesorNuevaPregunta();
    if(Configuracion::desarrollo)
        CCLOG("Aciertos %i",aciertos);
    float segundoQuitandoMostruos = 1;
    if(aciertos==0)
        segundoQuitandoMostruos = 0.7;
    
    if(aciertos<maxAciertos){
        proximaPregunta = aleatorioPreguntaProxima();
        gPreguntas->cargarPregunta(proximaPregunta);
        
        CallFunc *runCallback1 = CallFunc::create(CC_CALLBACK_0(Preguntator::quitarMostros, this));
        CallFunc *runCallback2 = CallFunc::create(CC_CALLBACK_0(Preguntator::initMostros, this));
        CallFunc *runCallback3 = CallFunc::create(CC_CALLBACK_0(Preguntator::mostrarPregunta, this));
        CallFunc *runCallback4 = CallFunc::create(CC_CALLBACK_0(Preguntator::reproducirPregunta, this));
        Sequence *seMostros = Sequence::create(runCallback1,DelayTime::create(segundoQuitandoMostruos),runCallback2,runCallback3,runCallback4, NULL);
        runAction(seMostros);
        
        PreguntasRealizadas->addObject(__Integer::create(proximaPregunta));
    }else{
        //JUEGO TERMINADO
        JuegoTerminado();
    }
    
    actualizarAciertos();
    
    if(isPlayNarracion)
        CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
}


void Preguntator::initMostros(){
    float escalaFinal = 0;
    float anchoPorPlataforma = anchoNoLateral/4-(espacioBordesCuadro*escala);
    log("relacion %f",relacion);
    /*if(relacion>1.5)
        anchoPorPlataforma = anchoPorPlataforma-(80*escala);
    else*/
        anchoPorPlataforma = anchoPorPlataforma-(80*escala);
    float altoPltaformas = 800*escala;
    
    if(respuestasMostruos==NULL){
        respuestasMostruos = CCArray::createWithCapacity(4);
        respuestasMostruos->retain();
    }
    
    for(int i=1;i<5;i++){
        __String* filename = obtenerRespuesta(i-1);
        Sprite* mostroRespuesta;
        
        if(respuestasMostruos->count()>i-1){
            if(respuestasMostruos->getObjectAtIndex(i-1)!=NULL){
                mostroRespuesta = (Sprite*)respuestasMostruos->getObjectAtIndex(i-1);
                mostroRespuesta->setTexture(filename->getCString());
            }
        }else{
            mostroRespuesta = Sprite::create(filename->getCString());
        }
        
        if(mostroRespuesta->getContentSize().width*escala>anchoPorPlataforma){
            log("escalado tam mostro %f espacio %f",mostroRespuesta->getContentSize().width*escala,anchoPorPlataforma);
            escalaPropiaPlataformas =anchoPorPlataforma/mostroRespuesta->getContentSize().width;
            mostroRespuesta->setScale(escalaPropiaPlataformas);
            escalaFinal = escalaPropiaPlataformas;
            log("escalado final %f",escalaFinal);
        }else{
            mostroRespuesta->setScale(escala);
            escalaFinal = escala;
        }
        
        mostroRespuesta->setAnchorPoint(Vec2(0.5,0));
        

        Sprite *plataforma = dynamic_cast<Sprite*>(aPlataformas->getObjectAtIndex(i-1));
        mostroRespuesta ->setPositionX(plataforma->getPositionX()+((plataforma->getContentSize().width*plataforma->getScale())/2)-(30*plataforma->getScale()));//se le añade lo ultimo porque las plataformas tienen las sombras para la derecha y por tanto el centro del sprite no es el centro de la plataforma donde se apollan los mostros.
        mostroRespuesta->setPositionY(plataforma->getPositionY()+plataforma->getContentSize().height*plataforma->getScale()-(50*plataforma->getScale()));
        if(i==2){
            mostroRespuesta->setPositionY(mostroRespuesta->getPositionY()-(20*plataforma->getScale()));
        }
        
        
        
        
        if(Configuracion::desarrollo)
            CCLOG("position x %f y %f",mostroRespuesta->getPositionX(),mostroRespuesta->getPositionY());
        
        mostroRespuesta->setZOrder(11);
        mostroRespuesta->setOpacity(255);
        //animacion de entrada de mostruo
            Vec2 posicionOriginal = mostroRespuesta->getPosition();
            //los sitio arriba para que caigan
            mostroRespuesta->setPositionY(visibleSize.height+(mostroRespuesta->getContentSize().height*escalaFinal));
            //animacion de caida
            MoveTo *caida = MoveTo::create(0.5,posicionOriginal);
        
        if(respuestasMostruos->getIndexOfObject(mostroRespuesta)<0){
            respuestasMostruos->insertObject(mostroRespuesta,i-1);
            this->addChild(mostroRespuesta);
        }
        
        mostroRespuesta->runAction(caida);
        escuchadores = true;
    }
    
}
void Preguntator::quitarMostros(){
    if(respuestasMostruos==NULL){
        respuestasMostruos = CCArray::createWithCapacity(4);
        respuestasMostruos->retain();
    }
    if(respuestasMostruos->count()>0){
        for(int i=1;i<5;i++){
            Sprite *plataforma = (Sprite*)respuestasMostruos->getObjectAtIndex(i-1);
            MoveTo *animacionSalidaMostro ;
            MoveTo *posicionOriginalMostro = MoveTo::create(0, plataforma->getPosition());
            if(ultimoMostroBueno!=-1&&ultimoMostroBueno==i-1&&aciertos>0){
                animacionSalidaMostro = MoveTo::create(0.7, Vec2(plataforma->getPositionX(),visibleSize.height));
            }else{
                animacionSalidaMostro = MoveTo::create(0.5, Vec2(plataforma->getPositionX(),0-(plataforma->getContentSize().height*escala)));
            }
            
            plataforma->runAction(Sequence::create(animacionSalidaMostro,FadeOut::create(0),posicionOriginalMostro, NULL));
        }
    }
}

void Preguntator::mostrosRespuestaFeelback(Sprite *target,bool respuesta){
    if(respuesta){
        aciertos++;
        escuchadores = false;
        
        cambiarTextoDialogo(LanguageManager::getInstance()->getString("PREGUNTATOR_TX_PROF_01"));
        
        ProfesorAciertaRespuesta();
        
        //animacionMostros
        MoveTo *movientoUp = MoveTo::create(0.1, Vec2(target->getPositionX(),target->getPositionY()+10));
        MoveTo *movientoDown = MoveTo::create(0.1, Vec2(target->getPositionX(),target->getPositionY()));
        CallFunc *runCallback1 = CallFunc::create(CC_CALLBACK_0(Preguntator::iniciarSiguientePregunta, this));
        Sequence *secuencia = Sequence::create(movientoUp,movientoDown,movientoUp,movientoDown,runCallback1, NULL);
        
        if(target->getNumberOfRunningActions()==0){
            target->runAction(secuencia);
            if(aciertos<maxAciertos)
                    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("correcto.mp3");
        }
    }else{
        tiempoRestante = tiempoOriginal;
        aciertos=0;
        
        cambiarTextoDialogo(LanguageManager::getInstance()->getString("PREGUNTATOR_TX_PROF_02"));
        
        ProfesorFalloRespuesta();
        
        //animacionMostros
        MoveTo *movientoLeft = MoveTo::create(0.1, Vec2(target->getPositionX()+10,target->getPositionY()));
        MoveTo *movientoRigth = MoveTo::create(0.2, Vec2(target->getPositionX()-10,target->getPositionY()));
        MoveTo *movientoOriginal = MoveTo::create(0.1, Vec2(target->getPositionX(),target->getPositionY()));
        CallFunc *runCallback1 = CallFunc::create(CC_CALLBACK_0(Preguntator::iniciarSiguientePregunta, this));
        Sequence *secuencia = Sequence::create(movientoLeft,movientoRigth,movientoOriginal,runCallback1, NULL);
        if(target->getNumberOfRunningActions()==0){
            target->runAction(secuencia);
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("fallo.mp3");
        }

    }
    
}


void Preguntator::mostrarPregunta(){
    if(sCuadroPregunta==NULL){
        
        sCuadroPregunta = Sprite::create("preguntator_cuadro_pregunta.png");
        sCuadroPregunta->setScale(escala);
        if(sCuadroPregunta->getContentSize().width*escala>altoIndividalCuadroJuego){
            sCuadroPregunta->setScale(escalaAncha);
        }
        sCuadroPregunta->setAnchorPoint(Vec2(0.5, 0));
        sCuadroPregunta->setPosition(cuadroJuego->getPositionX()+(cuadroJuego->getContentSize().width/2),espacioSuperiorBtAtras*escala);
        sCuadroPregunta->setZOrder(16);
        addChild(sCuadroPregunta);
        sCuadroPregunta->retain();
        
        __String *texto;
        
        if (Configuracion::idioma == 1) { // Español
            texto = gPreguntas->sPregunta;
        } else { // Inglés
            texto = gPreguntas->sPreguntaEN;
        }
        
        lbCuadroPregunta = CCLabelTTF::create(texto->getCString(), "HVD_Comic_Serif_Pro.ttf",(sCuadroPregunta->getContentSize().height*0.4)*escala,Size(sCuadroPregunta->getContentSize().width*0.9,sCuadroPregunta->getContentSize().height), TextHAlignment::CENTER);
        lbCuadroPregunta->setVerticalAlignment(cocos2d::TextVAlignment::CENTER);
        lbCuadroPregunta->setAnchorPoint(Vec2(0.5, 0.5));
        lbCuadroPregunta->setPosition(sCuadroPregunta->getContentSize().width/2,sCuadroPregunta->getContentSize().height/2);
        lbCuadroPregunta->setOpacity(0);
        sCuadroPregunta->addChild(lbCuadroPregunta);
        FadeIn *vanecimiento = FadeIn::create(0.5);
        lbCuadroPregunta->runAction(vanecimiento);
        
    }else{
        //primero hago la animacion y despues modifico el contenido de la pregunta
        FadeOut *desvanecimiento = FadeOut::create(0.5);
        CallFunc *runCallback1 = CallFunc::create(CC_CALLBACK_0(Preguntator::modificarLabelPregunta, this));
        FadeIn *vanecimiento = FadeIn::create(0.5);
        Sequence *secuencia = Sequence::create(desvanecimiento,runCallback1,vanecimiento, NULL);
        lbCuadroPregunta->runAction(secuencia);
    }
    
}

void Preguntator::reproducirPregunta(){
    //comentado hasta tener audios
    if (Configuracion::idioma == 1) { // Español
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(gPreguntas->sAudio->getCString());
    } else { // Inglés
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(gPreguntas->sAudioEN->getCString());
    }
    
    CallFunc *runCallback1 = CallFunc::create(CC_CALLBACK_0(Preguntator::activarEscuchadorPregunta, this));
    float tiempo = gPreguntas->fDuracion;
    Sequence *seq = Sequence::create(DelayTime::create(tiempo),runCallback1, NULL);
    runAction(seq);
}

void Preguntator::activarEscuchadorPregunta(){
    escuchadoresPregunta = true;
    if(PreguntasRealizadas->count()==1)
        cambiarTextoDialogo(LanguageManager::getInstance()->getString("PREGUNTATOR_TX_PROF_03"));
    else if(PreguntasRealizadas->count()==2)
        cambiarTextoDialogo(LanguageManager::getInstance()->getString("PREGUNTATOR_TX_PROF_04"));
    else
        cambiarTextoDialogo(LanguageManager::getInstance()->getString("PREGUNTATOR_TX_PROF_05"));
}

void Preguntator::modificarLabelPregunta(){

    __String *texto;
    
    if (Configuracion::idioma == 1) { // Español
        texto = gPreguntas->sPregunta;
    } else { // Inglés
        texto = gPreguntas->sPreguntaEN;
    }
    
    lbCuadroPregunta->setString(texto->getCString());
    
    sCuadroPregunta->setVisible(true);
    lbCuadroPregunta->setVisible(true);
}

int Preguntator::aleatorioPreguntaProxima(){
    int NREALIZADAS = PreguntasRealizadas->count();
    int NPREGUNTAS = nPreguntas;
    if(NREALIZADAS==NPREGUNTAS)
        PreguntasRealizadas->removeAllObjects();
    
    int preguntaRetorno = -1;
    while(preguntaRetorno==-1){
        int preguntaPlanteada = Configuracion::aleatorioEnteros(0, nPreguntas-1);
        bool encontrada = false;
        for(int i = 0;i<PreguntasRealizadas->count();i++){
            __Integer* preguntaRealizadaActual = (__Integer *)PreguntasRealizadas->getObjectAtIndex(i);
            if(preguntaPlanteada == preguntaRealizadaActual->getValue()){
                encontrada = true;
            }
        }
        
        if(!encontrada)
            preguntaRetorno = preguntaPlanteada;
    }
    
    
    return preguntaRetorno;
}

void Preguntator::actualizarAciertos(){
    if(Configuracion::desarrollo)
        CCLOG("actualizando acierto");
    if(sAciertos==NULL){
        sAciertos = Sprite::create("preguntator_aciertos.png");
        sAciertos->setScale(escala);
        sAciertos->setAnchorPoint(Vec2(0,1));
        
        //cuadroJuego al ser un layer no hay que aplicarle escala
        sAciertos->setPosition(cuadroJuego->getPositionX()+(espacioBordesCuadro*escala),cuadroJuego->getPositionY()+(cuadroJuego->getContentSize().height)-(espacioBordesCuadro*escala));
        
        //antes ponia 19 y los monstros pasaban por detras
        sAciertos->setLocalZOrder(7);
        addChild(sAciertos);
    }
    
    if(txAciertos==NULL){
        CCLabelTTF *txAciertosInf = CCLabelTTF::create(LanguageManager::getInstance()->getString("PREGUNTATOR_TX_01"), "HVD_Comic_Serif_Pro.ttf",40*escala,CCSizeMake(sAciertos->getContentSize().width*escala,60*escala), TextHAlignment::CENTER);
        txAciertosInf->setVerticalAlignment(TextVAlignment::CENTER);
        txAciertosInf->setColor(Color3B(216,254,51));
        txAciertosInf->setAnchorPoint(Vec2(0,1));
        txAciertosInf->setPosition(sAciertos->getPosition());
        txAciertosInf->setPositionY(txAciertosInf->getPositionY()-(180*escala));
        txAciertosInf->setLocalZOrder(10);
        addChild(txAciertosInf);
        
        txAciertos = CCLabelTTF::create("0", "HVD_Comic_Serif_Pro.ttf",150*escala,CCSizeMake(sAciertos->getContentSize().width*escala,180*escala), TextHAlignment::CENTER);
        txAciertos->setColor(Color3B(216,254,51));
        txAciertos->setVerticalAlignment(TextVAlignment::CENTER);
        txAciertos->setAnchorPoint(Vec2(0,1));
        txAciertos->setPosition(sAciertos->getPosition());
        txAciertos->setPositionY(txAciertos->getPositionY()+(20*escala));
        txAciertos->setLocalZOrder(8);
        addChild(txAciertos);
        txAciertos->retain();
        
    }
    
    txAciertos->setString(__String::createWithFormat("%i",aciertos)->getCString());
    
}

void Preguntator::JuegoTerminado(){
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
    
    
    
    //PRUEBAS
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

bool Preguntator::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event){
    if(Configuracion::desarrollo)
        log("BEGAN %f %f",touch->getLocation().x,touch->getLocation().y);

    if(juegoTerminado)
        irAtras(NULL);
    
    if(!escuchadores){
        return false;
    }
    
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
    
    if(!escuchadoresPregunta){
        return false;
    }
    //SI LE DIO A MOSTRUOS
    bool  tocaMostruo = false;
    if(respuestasMostruos!=NULL){
        
        if(!Configuracion::comprobarToque(touch,marcoRespuestas)){
            return false;
        }
        
        for(int i = 0;i<respuestasMostruos->count();i++){
            auto mostro = static_cast<Sprite*>(respuestasMostruos->getObjectAtIndex(i));
            auto plataforma = static_cast<Sprite*>(aPlataformas->getObjectAtIndex(i));
            if(Configuracion::comprobarToque(touch, mostro)){
                tocaMostruo = true;
                escuchadoresPregunta = false;
                int respuestaValida = gPreguntas->iRespuestaOK;
                ultimoMostroBueno = i;
                if(respuestaValida==i){
                    mostrosRespuestaFeelback(mostro, true);
                }else{
                    mostrosRespuestaFeelback(mostro,false);
                }
                return true;
            }else
            if(Configuracion::comprobarToque(touch, plataforma)){
                tocaMostruo = true;
                escuchadoresPregunta = false;
                int respuestaValida = gPreguntas->iRespuestaOK;
                ultimoMostroBueno = i;
                if(respuestaValida==i){
                    mostrosRespuestaFeelback(mostro, true);
                }else{
                    mostrosRespuestaFeelback(mostro,false);
                }
                return true;
            }
        }
        
    }
    
    
    //SI TOCA AL PROFESOR
    if(!tocaProfesor&&!tocaMostruo&&proximaPregunta>0){
        cambiarTextoDialogo(LanguageManager::getInstance()->getString("PREGUNTATOR_TX_PROF_06"));
    }
    
    
    return  true;
}
void Preguntator::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event){
    if(Configuracion::desarrollo)
        log("MOVED %f %f ",touch->getLocation().x,touch->getLocation().y);
    
}
void Preguntator::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event){
    if(Configuracion::desarrollo)
        log("ENDED %f %f ",touch->getLocation().x,touch->getLocation().y);
    
    
    
}