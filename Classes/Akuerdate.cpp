#include "Akuerdate.h"
#include "HelloWorldScene.h"
#include "Configuracion.h"
#include "Ajustes.h"
#include "CGestorRecursos.h"
#include "LanguageManager.h"
#include "SimpleAudioEngine.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "JniLink.h"
#endif


USING_NS_CC;

Scene* Akuerdate::createScene()
{
    
    auto scene = Scene::create();
    
    auto layer = Akuerdate::create();
    scene->addChild(layer);
    return scene;
}


bool Akuerdate::init()
{
    
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
    listener1->onTouchBegan = CC_CALLBACK_2(Akuerdate::onTouchBegan, this);
    listener1->onTouchMoved = CC_CALLBACK_2(Akuerdate::onTouchMoved, this);
    listener1->onTouchEnded = CC_CALLBACK_2(Akuerdate::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);
    

    initConfiguracion();
    initPanelElementos();
    initPanelPalabras();
    
    return true;
}

void Akuerdate::onEnterTransitionDidFinish(){
    if(Configuracion::desarrollo)
        CCLOG("ENTRA EN ESCENA Armame");
    
    if (!running) {
        initMusica();
        
        if(Configuracion::desarrollo){
            //comenzarNarracion();
            //mostrarDialogoComenzar();
            escuchadores = true;
            comenzarJuego();
            //        JuegoTerminado();
        }else {
            comenzarNarracion();
        }
        
        running = true;
        
    }
    
    CCTextureCache::getInstance()->getCachedTextureInfo();
    
}

void Akuerdate::onExitTransitionDidStart() {
    
    cleanMemory();
    
}

Akuerdate::~Akuerdate() {
    
    cleanMemory();
    
}

void Akuerdate::cleanMemory() {
    
    CCDirector::sharedDirector()->purgeCachedData();
    
    CCTextureCache::sharedTextureCache()->removeUnusedTextures();
    CCTextureCache::sharedTextureCache()->removeAllTextures();
    CCTextureCache::purgeSharedTextureCache();
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames();
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFrames();
    CCSpriteFrameCache::purgeSharedSpriteFrameCache();
    
    SpriteFrameCache::getInstance()->removeUnusedSpriteFrames();
    
}

void Akuerdate::comenzarNarracion(){
    
    lbCuadroInicial->setVisible(true);
    capaFondoCuadroInicial->setVisible(true);
    capaTextoCuadroInicial->setVisible(true);
    
    if(!isPlayNarracion){
        isPlayNarracion = true;
        narracionActual = 0;
        saltarAnimacion();
    }
}
void Akuerdate::saltarAnimacion(){
    stopAction(narracion);
    CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
    CallFunc *runCallback1 = CallFunc::create(CC_CALLBACK_0(Akuerdate::narracion1, this));
    CallFunc *runCallback2 = CallFunc::create(CC_CALLBACK_0(Akuerdate::narracion2, this));
    CallFunc *runCallback3 = CallFunc::create(CC_CALLBACK_0(Akuerdate::narracion3, this));
    CallFunc *runCallback4 = CallFunc::create(CC_CALLBACK_0(Akuerdate::narracion4, this));
    CallFunc *runCallback5 = CallFunc::create(CC_CALLBACK_0(Akuerdate::mostrarDialogoComenzar, this));
    if(narracionActual==0){
        narracion = Sequence::create(runCallback1,DelayTime::create(3),runCallback2,DelayTime::create(4.4),runCallback3,DelayTime::create(1),runCallback4,DelayTime::create(2.8),runCallback5,NULL);
    }else if(narracionActual==1){
        narracion = Sequence::create(runCallback2,DelayTime::create(4.4),runCallback3,DelayTime::create(1),runCallback4,DelayTime::create(2.8),runCallback5,NULL);
    }else if(narracionActual==2){
        narracion = Sequence::create(runCallback3,DelayTime::create(1),runCallback4,DelayTime::create(2.8),runCallback5,NULL);
    }else if(narracionActual==3){
        narracion = Sequence::create(runCallback4,DelayTime::create(2.8),runCallback5,NULL);
    }else if(narracionActual==4){
        narracion = Sequence::create(runCallback5,NULL);
    }
    runAction(narracion);
}

void Akuerdate::narracion1(){
    narracionActual = 1;
    CallFunc *leer = CallFunc::create(CC_CALLBACK_0(Akuerdate::ProfesorLeyendoHablando, this));
    Sequence *leyendo = Sequence::create(leer,NULL);
    this->runAction(leyendo);
    
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("akuerdate_intro_1.mp3");
    lbCuadroInicial->setString(LanguageManager::getInstance()->getString("AKUERDATE_NAR_01"));
}
void Akuerdate::narracion2(){
    narracionActual = 2;
    CallFunc *leer = CallFunc::create(CC_CALLBACK_0(Akuerdate::ProfesorLeyendoHablando, this));
    Sequence *leyendo = Sequence::create(leer,DelayTime::create(1.6),leer,DelayTime::create(1.6),leer,NULL);
    this->runAction(leyendo);
    
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("akuerdate_intro_2.mp3");
    lbCuadroInicial->setString(LanguageManager::getInstance()->getString("AKUERDATE_NAR_02"));
}
void Akuerdate::narracion3(){
    narracionActual = 3;
    CallFunc *leer = CallFunc::create(CC_CALLBACK_0(Akuerdate::ProfesorLeyendoHablando, this));
    Sequence *leyendo = Sequence::create(leer,DelayTime::create(1.6),leer,DelayTime::create(1.6),leer,DelayTime::create(1.6),leer,NULL);
    this->runAction(leyendo);
    
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("akuerdate_intro_3.mp3");
    lbCuadroInicial->setString(LanguageManager::getInstance()->getString("AKUERDATE_NAR_03"));
}
void Akuerdate::narracion4(){
    narracionActual = 4;
    CallFunc *leer = CallFunc::create(CC_CALLBACK_0(Akuerdate::ProfesorLeyendoHablando, this));
    Sequence *leyendo = Sequence::create(leer,NULL);
    this->runAction(leyendo);
    
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("akuerdate_intro_4.mp3");
    lbCuadroInicial->setString(LanguageManager::getInstance()->getString("AKUERDATE_NAR_04"));
}


void Akuerdate::obtenerMedidas(){
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
    
    margenPanelPalabrasInternoCE = margenPanelPalabrasInterno * escala;
    
    tamLetraCE = tamLetra * escala;
    
}

void Akuerdate::irAtras(Ref* pSender)
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
void Akuerdate::initFondo(){
    //33% de alto para cada una
    float altoIndividal = visibleSize.height/3;
    
    Layer* fondo = LayerColor::create(Color4B(26,79,121,255),visibleSize.width,visibleSize.height);
    fondo->setAnchorPoint(Vec2(1, 0.5));
    fondo->setPosition(0,0);
    fondo->setZOrder(-1);
    this->addChild(fondo);
    
    
    Sprite* bg = Sprite::create("preguntator_bg.png");
    //calculo su 33%
    float escala1 = altoIndividal/bg->getContentSize().height;
    
    bg->setScale(escala1);
    bg->setAnchorPoint(Vec2(0, 0));
    bg->setPosition(0,0);
    bg->setZOrder(4);
    this->addChild(bg);
    
    
    Sprite* interrogaciones = Sprite::create("preguntator_interrogaciones.png");
    //calculo su 33%
    float escala2 = altoIndividal/interrogaciones->getContentSize().height;
    
    interrogaciones->setScale(escala2);
    interrogaciones->setAnchorPoint(Vec2(0.5, 0.5));
    interrogaciones->setPosition(anchoLateralCE/2,visibleSize.height/2);
    interrogaciones->setZOrder(7);
    this->addChild(interrogaciones);
    
}

void Akuerdate::initReloj(){
    reloj = CCLabelTTF::create("00:00", "HVD_Comic_Serif_Pro.ttf", letraReloj*escala,CCSizeMake(anchoLateralCE, (letraReloj+20)*escala), TextHAlignment::CENTER);
    reloj->setColor(Color3B(216,254,51));
    reloj->setVerticalAlignment(TextVAlignment::TOP);
    reloj->setAnchorPoint(Vec2(0, 1));
    reloj->setPosition(0,btAtras->getPositionY()-(btAtras->getContentSize().height*escala));
    reloj->setZOrder(9);
    this->addChild(reloj, 1);
}

void Akuerdate::initMusica(){
    //pongo musica
    if(!Configuracion::desarrollo){
        if(CocosDenshion::SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying()){
            
        }else{
            CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("sintonia_akuerdate.mp3", true);
        }
    }
}

void Akuerdate::initBtAtras(){
    btAtras = MenuItemImage::create("preguntator_bt_atras.png","preguntator_bt_atras_down.png",CC_CALLBACK_1(Akuerdate::irAtras, this));
    
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

void Akuerdate::initBtAjustes(){
    btAjustes = MenuItemImage::create("mostrosity_mimostro_bt_ajustes.png","mostrosity_mimostro_bt_ajustes_down.png",CC_CALLBACK_1(Akuerdate::selectorAjustes, this));
    btAjustes->setScale(escala);
    btAjustes->setAnchorPoint(Vec2(1,1));
    btAjustes->setPosition(visibleSize.width-(espacioBordesCuadroCE*2),btAtras->getPositionY());
    btAjustes->retain();
    menu->addChild(btAjustes);
}

void Akuerdate::selectorAjustes(Ref *pSender){
    CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    
    if(Configuracion::desarrollo)
        CCLOG("Selector ajustes");
    
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    
//    Ajustes::desdeEscena = Ajustes::desdeAkuerdate;
//    auto scene = Ajustes::createScene();
//    auto transicion = TransitionFade::create(0.3f, scene);
//    Director::getInstance()->replaceScene(transicion);
    
    auto scene = Ajustes::createScene();
    Director::getInstance()->pushScene(scene);
    
}

void Akuerdate::initCuadroInicial(){
    
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


void Akuerdate::initBocadillo(){
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
void Akuerdate::initProfesor(){
    
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

void Akuerdate::ProfesorLeyendoHablando(){
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

void Akuerdate::ProfesorFalloRespuesta(){
    
    MoveTo *cejasAbajo = MoveTo::create(0.2, Vec2((anchoProfesor/2)-15,altoCejas-25));
    if(profCejas->getNumberOfRunningActions()==0){
        profCejas->runAction(cejasAbajo);
    }
    
}

void Akuerdate::ProfesorAciertaRespuesta(){
    RotateBy *Giro = RotateBy::create(0.4, 360);
    if(profBigote->getNumberOfRunningActions()==0){
        profBigote->runAction(Giro);
    }
    
    MoveTo *ojosArriba = MoveTo::create(0.4, Vec2(anchoProfesor/2,altoOjos+20));
    if(profOjos->getNumberOfRunningActions()==0){
        profOjos->runAction(ojosArriba);
    }
}

void Akuerdate::ProfesorNuevaPregunta(){
    MoveTo *cejasOrigen = MoveTo::create(0.4, Vec2((anchoProfesor/2),altoCejas));
    if(profCejas->getNumberOfRunningActions()==0){
        profCejas->runAction(Sequence::create(DelayTime::create(1),cejasOrigen,NULL));
    }
    
    MoveTo *ojosNormal = MoveTo::create(0.4, Vec2(anchoProfesor/2,altoOjos));
    if(profOjos->getNumberOfRunningActions()==0){
        profOjos->runAction(ojosNormal);
    }
}

void Akuerdate::initCuadroJuego(){
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
    /*Sprite *cuadroTemporal = Sprite::create("mostrosity_Armame_cuadro_temp.png");
     cuadroTemporal->setScaleX(escalaAncha);
     cuadroTemporal->setScaleY(escalaAlta);
     cuadroTemporal->setAnchorPoint(Vec2::ZERO);
     cuadroTemporal->setPosition(cuadroJuego->getPosition());
     cuadroTemporal->setZOrder(6);
     this->addChild(cuadroTemporal);*/
}


void Akuerdate::initTextoCentral(){
    float bordesBocadillos = 40*escalaPropiaBocadillo;
    cuadroDialogo = CCLabelTTF::create("", "HVD_Comic_Serif_Pro.ttf", (bocadillo->getContentSize().height*escalaPropiaBocadillo)/7,CCSizeMake((bocadillo->getContentSize().width*escalaPropiaBocadillo)-(bordesBocadillos*2), (bocadillo->getContentSize().height*escalaPropiaBocadillo)-(bordesBocadillos*3)), TextHAlignment::CENTER);
    cuadroDialogo->setColor(Color3B(0,0,0));
    cuadroDialogo->setVerticalAlignment(TextVAlignment::CENTER);
    cuadroDialogo->setAnchorPoint(Vec2(0.5,0.5));
    cuadroDialogo->setPosition(bocadillo->getPositionX(),bocadillo->getPositionY()+((bocadillo->getContentSize().height*escalaPropiaBocadillo)/2)+(bordesBocadillos*0.5));
    cuadroDialogo->setZOrder(10);
    this->addChild(cuadroDialogo);
    
}

void Akuerdate::cambiarTextoDialogo(std::string texto){
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
            CallFunc *runCallback1 = CallFunc::create(CC_CALLBACK_0(Akuerdate::modificarTXTDialogo, this));
            CallFunc *runCallback2 = CallFunc::create(CC_CALLBACK_0(Akuerdate::vaciarTXTDialogo, this));
            CallFunc *runCallback3 = CallFunc::create(CC_CALLBACK_0(Akuerdate::rellamarTXTDialogo, this));
            
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
void Akuerdate::modificarTXTDialogo(){
    this->cuadroDialogo->setString(textoProximoBocadillo);
    cuadroDialogo->runAction(FadeIn::create(0.3));
}
void Akuerdate::vaciarTXTDialogo(){
    this->cuadroDialogo->setString("");
    bocadillo->setVisible(false);
}

void Akuerdate::rellamarTXTDialogo(){
    cambiarTextoDialogo("");
}



void Akuerdate::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event){
    irAtras(NULL);
}

void Akuerdate::mostrarDialogoComenzar(){
    lbCuadroInicial->setVisible(false);
    isPlayNarracion = false;
    if(dial1_bg==NULL){
        crearDialogoComenzar();
    }
    dial1_bg->setVisible(true);
}
void Akuerdate::ocultarDialogoComenzar(){
    
    if(dial1_bg==NULL){
        crearDialogoComenzar();
    }
    dial1_bg->setVisible(false);
}

void Akuerdate::crearDialogoComenzar(){
    dial1_bg = LayerColor::create(Color4B(0,0,0,0), visibleSize.width-(anchoLateralCE*escala*0.7*2), 700*escala);
    dial1_bg->setPosition((visibleSize.width-dial1_bg->getContentSize().width)/2,visibleSize.height/2-(700*escala/2));
    dial1_bg->setZOrder(16);
    this->addChild(dial1_bg);
    
    dial1_Imenu1 = MenuItemImage::create("preguntator_dial_bt1.png","preguntator_dial_bt1_down.png",CC_CALLBACK_1(Akuerdate::dial1_Imenu2_resp1, this));
    dial1_Imenu1->setScale(escala);
    dial1_Imenu1->setAnchorPoint(Vec2(1, 1));
    dial1_Imenu1->setPosition(dial1_bg->getContentSize().width/2,dial1_bg->getContentSize().height/2);
    
    dial1_Imenu2 = MenuItemImage::create("preguntator_dial_bt2.png","preguntator_dial_bt2_down.png",CC_CALLBACK_1(Akuerdate::dial1_Imenu2_resp2, this));
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

void Akuerdate::dial1_Imenu2_resp1(Ref* sender){
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("tambores_3.mp3");
    ocultarDialogoComenzar();
    comenzarNarracion();
}

void Akuerdate::dial1_Imenu2_resp2(Ref* sender){
    CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("tambores_3.mp3");
    lbCuadroInicial->setVisible(false);
    capaFondoCuadroInicial->setVisible(false);
    capaTextoCuadroInicial->setVisible(false);
    
    ocultarDialogoComenzar();
    comenzarReloj();
    comenzarJuego();
    escuchadores = true;
}

void Akuerdate::comenzarReloj(){
    
    this->schedule(schedule_selector(Akuerdate::aumentarReloj),1.0);
    
}
void Akuerdate::aumentarReloj(float dt){
    if(tiempoRestante<0||juegoTerminado){
        unschedule(schedule_selector(Akuerdate::aumentarReloj));
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

void Akuerdate::initConfiguracion(){
    
    gProfesion = new CProfesionAkuerdate();
    gProfesion->retain();
    int nPanel = Configuracion::aleatorioEnteros(0, gProfesion->ObtenerNumeroProfesiones()-1);
    gProfesion->cargarProfesion(nPanel);
    
    if (Configuracion::idioma == 1) { // Español
        sNombreProfesion = __String::create(gProfesion->sNombreProfesion->getCString());
        log("nProfesion %i profesion %s",nPanel,gProfesion->sNombreProfesion->getCString());
    } else { // Inglés
        sNombreProfesion = __String::create(gProfesion->sNombreProfesionEN->getCString());
        log("nProfesion %i profesion %s",nPanel,gProfesion->sNombreProfesionEN->getCString());
    }
    
    sNombreProfesion->retain();
    
    aElementosProfesion = gProfesion->obtenerElementosProfesion();
    aElementosProfesion->retain();
    
    nAciertos = aElementosProfesion->count();
}

void Akuerdate::initPanelElementos(){
    
    panelElementos = gProfesion->obtenerImgFondo();
    escalaPanel = cuadroJuego->getContentSize().width/panelElementos->getContentSize().width;
    panelElementos->setScaleX(escalaPanel);
    panelElementos->setScaleY(escalaAlta);
    panelElementos->setAnchorPoint(Vec2(0,1));
    panelElementos->setPosition(cuadroJuego->getPositionX(),visibleSize.height-espacioBordesCuadroCE);
    panelElementos->setZOrder(6);
    addChild(panelElementos);
    
}

void Akuerdate::initPanelPalabras(){
    panelPalabras = Sprite::create("panelPalabras.png");
    panelPalabras->setScaleX(escalaPanel);
    panelPalabras->setScaleY(escalaAlta);
    panelPalabras->setAnchorPoint(Vec2(1,0.5));
    panelPalabras->setPosition(cuadroJuego->getPositionX()+cuadroJuego->getContentSize().width,cuadroJuego->getPositionY()+(cuadroJuego->getContentSize().height/2));
    panelPalabras->setZOrder(6);
    addChild(panelPalabras);
}

void Akuerdate::comenzarJuego(){
    desordenarElementos();
    pintoElementos();
    inicioELEMENTO();
}

void Akuerdate::desordenarElementos(){
    
    std::vector<int> orden (aElementosProfesion->count());
    for (int i=0; i<orden.size(); i++){
        orden.assign (i,-1);
    }
    bool terminado = false;
    do{
        int _numero = Configuracion::aleatorioEnteros(0, aElementosProfesion->count()-1);
        bool contenido = false;
        for (int i=0; i<orden.size(); i++){
            int nActual = orden.at(i);
            if(_numero == nActual){
                contenido = true;
            }
        }
        if(!contenido)
            orden.push_back(_numero);
        
        if(orden.size()>=aElementosProfesion->count())
            terminado = true;
    
    }while (!terminado);
    
    __Array *auxElementosProfesion = __Array::createWithCapacity(aElementosProfesion->count());
    for(int i=0;i<aElementosProfesion->count();i++){
        int numero =orden.at(i);
        log("N %i",numero);
        auxElementosProfesion->addObject(aElementosProfesion->getObjectAtIndex(numero));
    }
    aElementosProfesion = auxElementosProfesion;
    aElementosProfesion->retain();
    
}

void Akuerdate::inicioELEMENTO(){
    if (mostrados < cantidadActual) {
        escuchadorElementos = false;
        elementoActual ++;
        //cambiarTextoDialogo("¡Empezamos la secuencia!");
        log("inicioElemento");
        
        CallFunc *recorroElemento = CallFunc::create(CC_CALLBACK_0(Akuerdate::recorroElemento, this));
        CallFunc *pintoPalabra = CallFunc::create(CC_CALLBACK_0(Akuerdate::pintoPalabra, this));
        CallFunc *reproducirAudio = CallFunc::create(CC_CALLBACK_0(Akuerdate::reproducirAudio, this));
        CallFunc *finIteraccionPalabras = CallFunc::create(CC_CALLBACK_0(Akuerdate::finIteraccionPalabras, this));
        CallFunc *inicioELEMENTO = CallFunc::create(CC_CALLBACK_0(Akuerdate::inicioELEMENTO, this));
        
        Sequence *secuencia = Sequence::create(DelayTime::create(0.5),recorroElemento,pintoPalabra,reproducirAudio,DelayTime::create(0.75),finIteraccionPalabras,inicioELEMENTO, NULL);
        Sequence *secuenciaUltima = Sequence::create(DelayTime::create(0.5),recorroElemento,pintoPalabra,reproducirAudio,DelayTime::create(0.75),finIteraccionPalabras,NULL);
        
        if(elementoActual==cantidadActual-1){
            runAction(secuenciaUltima);
        }else
            runAction(secuencia);
        /*for(int i=0;i<cantidad;i++){
         int tag = pintoElemento(i);
         pintoPalabra(tag);
         reproducirAudio(tag);
         }*/
        mostrados++;
    }
}

void Akuerdate::pintoElementos(){
    
    for(int i=0;i<nAciertos;i++){
        Sprite * obj = dynamic_cast<Sprite*>(aElementosProfesion->getObjectAtIndex(i));
        obj->setPosition(gProfesion->obternerPosElementoProfesion(obj->getTag()));
        obj->setLocalZOrder(200);
        panelElementos->addChild(obj);
    }
    
    
    
}

void Akuerdate::recorroElemento(){

    if (elementoActual < aElementosProfesion->count()) {
        Sprite * obj = dynamic_cast<Sprite*>(aElementosProfesion->getObjectAtIndex(elementoActual));
        tagActual = obj->getTag();
    }
    
    
}

void Akuerdate::pintoPalabra(){
    
    LabelTTF *texto = CCLabelTTF::create(gProfesion->obtenerPalabraElemento(tagActual)->getCString(), "HVD_Comic_Serif_Pro.ttf",100,Size(panelPalabras->getContentSize().width-margenPanelPalabrasInterno,130), TextHAlignment::CENTER);
    texto->setColor(Color3B(228,70,106));
    texto->setVerticalAlignment(TextVAlignment::CENTER);
    texto->setAnchorPoint(Vec2(1,1));
    texto->setPosition(panelPalabras->getContentSize().width+margenPanelPalabrasInterno,panelPalabras->getContentSize().height-((panelPalabras->getChildrenCount()*(100+margenPanelPalabrasInterno))+(margenPanelPalabrasInterno*5)));
    //texto->setPosition(0,0);
    panelPalabras->addChild(texto);
    
}

void Akuerdate::finIteraccionPalabras(){
    //ES EL ULTIMO METODO DE CADA INTERACCION POR LO QUE HABILITO EL ESCUCHADOR SI ES LA ULTIMA PALABRA
    if(elementoActual==cantidadActual-1){
        cambiarTextoDialogo(LanguageManager::getInstance()->getString("AKUERDATE_TX_PROF_05"));
        borrarElementos();
        escuchadorElementos = true;
    }
}

void Akuerdate::reproducirAudio(){

    __String *srcAudio = gProfesion->obtenerAudioElemento(tagActual);
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(srcAudio->getCString());
}

void Akuerdate::borrarElementos(){
    panelPalabras->removeAllChildren();
    //panelElementos->removeAllChildren();
    
}
//DEBUG
void Akuerdate::initPintarPalabras(){
    for(int i=0;i<aElementosProfesion->count();i++){
        Sprite * obj = dynamic_cast<Sprite*>(aElementosProfesion->getObjectAtIndex(i));
        //obj->setPosition(visibleSize.width/2+(100*i),visibleSize.height/2);
        obj->setPosition(gProfesion->obternerPosElementoProfesion(i));
        obj->setLocalZOrder(200);
        panelElementos->addChild(obj);
    }
}

void Akuerdate::JuegoTerminado(){
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
    

    __String *txtConsegido = __String::createWithFormat("%s %s",LanguageManager::getInstance()->getString("JUEGO_TX_FINAL_EXITO_2").c_str(),sNombreProfesion->getCString());
    
    CCLabelTTF *txConseguido = CCLabelTTF::create(txtConsegido->getCString(), "HVD_Comic_Serif_Pro.ttf",120*escala,Size((visibleSize.width),(220*escala)*2), TextHAlignment::CENTER);
    txConseguido->setColor(Color3B(25,78,121));
    txConseguido->setVerticalAlignment(TextVAlignment::CENTER);
    txConseguido->setAnchorPoint(Vec2(0.5,1));
    txConseguido->setPosition(lyConseguido->getContentSize().width/2,visibleSize.height+(280*escala));
    lyConseguido->addChild(txConseguido);
    
    //animacion textoConsegido
    MoveTo *aniTxConseguido = MoveTo::create(0.3, Vec2(lyConseguido->getContentSize().width/2,(lyConseguido->getContentSize().height)));
    txConseguido->runAction(aniTxConseguido);
    
    Sprite *pizzarra = Sprite::create("pizzarra_final_tiempo.png");
    pizzarra->setScale(escalaAlta);
    pizzarra->setAnchorPoint(Vec2(0.5,1));
    pizzarra->setPosition(visibleSize.width,(lyConseguido->getContentSize().height)-(txConseguido->getContentSize().height));
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

bool Akuerdate::comprobarToqueElemento(cocos2d::Touch *toque){
    
    return true;

}


void Akuerdate::comprobarExitoElemento(cocos2d::Touch *toque){

    Sprite *spExito = dynamic_cast<Sprite*>(panelElementos->getChildren().at(aciertosPorInteraccion));//obtenerElementoPorNumero(aciertosPorInteraccion);
    if(Configuracion::comprobarToque(toque, spExito)){
        spExito->runAction(Sequence::create(ScaleTo::create(0.2, spExito->getScale()*1.1),ScaleTo::create(0.2, spExito->getScale()), NULL));
        aciertosPorInteraccion++;
        if(aciertosPorInteraccion==cantidadActual){
            elementoActual = -1;
            aciertosPorInteraccion = 0;
            mostrados = 0;
            cantidadActual ++;
            if(cantidadActual-1==nAciertos){
                JuegoTerminado();
            }else{
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("correcto.mp3");
                cambiarTextoDialogo(LanguageManager::getInstance()->getString("AKUERDATE_TX_PROF_01"));
                CallFunc *runCallback1 = CallFunc::create(CC_CALLBACK_0(Akuerdate::inicioELEMENTO, this));
                runAction(Sequence::create(DelayTime::create(1),runCallback1,NULL));
            }
        }else{
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("akuerdate_plop.mp3");
            //Aqui suena el sonido de cada elemento
            //CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sonido de elemento.");
            cambiarTextoDialogo(LanguageManager::getInstance()->getString("AKUERDATE_TX_PROF_02"));
        }
        
        

    }else{
        bool bTocadoElemento = false;
        for(int i=0;i<nAciertos;i++){
            Sprite * obj = dynamic_cast<Sprite*>(panelElementos->getChildren().at(i));
            if(Configuracion::comprobarToque(toque,obj)){
                obj->runAction(Sequence::create(ScaleTo::create(0.2, obj->getScale()*1.1),ScaleTo::create(0.2, obj->getScale()), NULL));
                bTocadoElemento = true;
            }
        }

        if(bTocadoElemento){
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("fallo.mp3");
            cambiarTextoDialogo(LanguageManager::getInstance()->getString("AKUERDATE_TX_PROF_03"));
            reiniciarElementos();
            mostrados = 0;

            inicioELEMENTO();
            
        }else{
            cambiarTextoDialogo(LanguageManager::getInstance()->getString("AKUERDATE_TX_PROF_04"));
        }
        
        
    }

}

void Akuerdate::falloToqueElemento(){
    
    escuchadores = true;
}

Sprite* Akuerdate::obtenerElementoPorNumero(int numero){
    for(int i=0;i<panelElementos->getChildrenCount();i++){
        Sprite *elementoActual = dynamic_cast<Sprite*>(panelElementos->getChildren().at(i));
        int nElemento = elementoActual->getTag();
        if(nElemento==numero){
            return elementoActual;
        }
    }
    return NULL;
}

void Akuerdate::reiniciarElementos(){
    borrarElementos();
    aciertos = 0;
    aciertosPorInteraccion = 0;
    cantidadActual = 1;
    elementoActual = -1;
}


bool Akuerdate::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
    
    if(Configuracion::desarrollo)
        log("BEGAN %f %f",touch->getLocation().x,touch->getLocation().y);
    
    if(juegoTerminado)
        irAtras(NULL);
    
    if(isPlayNarracion){
        if(Configuracion::comprobarToque(touch, capaTextoCuadroInicial)){
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
    
    if(!escuchadorElementos){
        if(Configuracion::comprobarToque(touch, cuadroJuego)){
            cambiarTextoDialogo(LanguageManager::getInstance()->getString("Aun_no"));
            return false;
        }else
            return false;
    }
    
    if(comprobarToqueElemento(touch)){
        comprobarExitoElemento(touch);
        CCLOG("IMPLEMENTAR SECUENCIA TOCADA DE MOSTRO");
        
        CCLOG("PARTE TOCADA DE MOSTRO");
    }else{
        CCLOG("NO TOCO PARTE MOSTRO");
    }
    
    
    
    return  true;
}
void Akuerdate::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event)
{
    if(!escuchadores){
        return;
    }
    
    if(Configuracion::desarrollo)
        log("MOVED %f %f ",touch->getLocation().x,touch->getLocation().y);
    
    
    
}
void Akuerdate::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
{
    if(!escuchadores){
        return;
    }
        
}
