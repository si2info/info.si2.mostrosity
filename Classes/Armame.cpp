#include "Armame.h"
#include "CGestorRecursos.h"
#include "LanguageManager.h"
#include "SimpleAudioEngine.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "JniLink.h"
#endif


USING_NS_CC;

Scene* Armame::createScene()
{
    
    auto scene = Scene::create();
    
    auto layer = Armame::create();
    scene->addChild(layer);
    return scene;
}


bool Armame::init()
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
    listener1->onTouchBegan = CC_CALLBACK_2(Armame::onTouchBegan, this);
    listener1->onTouchMoved = CC_CALLBACK_2(Armame::onTouchMoved, this);
    listener1->onTouchEnded = CC_CALLBACK_2(Armame::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);
    
    return true;
}

void Armame::onEnterTransitionDidFinish(){
    if(Configuracion::desarrollo)
        CCLOG("ENTRA EN ESCENA Armame");
    
    if (!running) {
        initMusica();
        
        initCofiguracion();
        initPanelHuecos();
        initComplementosPanel();
        initHuecos();
        rellenarHuecos();
        
        if(Configuracion::desarrollo){
            //comenzarNarracion();
            comenzarNarracion();
        }else
            comenzarNarracion();
        
        running = true;
        
    }
    
    CCTextureCache::getInstance()->getCachedTextureInfo();
    
}

void Armame::onExitTransitionDidStart() {
    
    cleanMemory();
    
}

Armame::~Armame() {
    
    cleanMemory();
    
}

void Armame::cleanMemory() {
    
    CCDirector::sharedDirector()->purgeCachedData();
    
    CCTextureCache::sharedTextureCache()->removeUnusedTextures();
    CCTextureCache::sharedTextureCache()->removeAllTextures();
    CCTextureCache::purgeSharedTextureCache();
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames();
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFrames();
    CCSpriteFrameCache::purgeSharedSpriteFrameCache();
    
    SpriteFrameCache::getInstance()->removeUnusedSpriteFrames();
    
}

void Armame::comenzarNarracion(){
    
    lbCuadroInicial->setVisible(true);
    capaFondoCuadroInicial->setVisible(true);
    capaTextoCuadroInicial->setVisible(true);
    
    if(!isPlayNarracion){
        isPlayNarracion = true;
        narracionActual = 0;
        saltarAnimacion();
    }
}
void Armame::saltarAnimacion(){
    stopAction(narracion);
    CallFunc *runCallback1 = CallFunc::create(CC_CALLBACK_0(Armame::narracion1, this));
    CallFunc *runCallback2 = CallFunc::create(CC_CALLBACK_0(Armame::narracion2, this));
    CallFunc *runCallback3 = CallFunc::create(CC_CALLBACK_0(Armame::narracion3, this));
    CallFunc *runCallback4 = CallFunc::create(CC_CALLBACK_0(Armame::narracion4, this));
    CallFunc *runCallback5 = CallFunc::create(CC_CALLBACK_0(Armame::mostrarDialogoComenzar, this));
    if(narracionActual==0){
        narracion = Sequence::create(runCallback1,DelayTime::create(4),runCallback2,DelayTime::create(4.2),runCallback3,DelayTime::create(2.4),runCallback4,DelayTime::create(1.8),runCallback5,NULL);
    }else if(narracionActual==1){
        narracion = Sequence::create(runCallback2,DelayTime::create(4.2),runCallback3,DelayTime::create(2.4),runCallback4,DelayTime::create(1.8),runCallback5,NULL);
    }else if(narracionActual==2){
        narracion = Sequence::create(runCallback3,DelayTime::create(2.4),runCallback4,DelayTime::create(1.8),runCallback5,NULL);
    }else if(narracionActual==3){
        narracion = Sequence::create(runCallback4,DelayTime::create(1.8),runCallback5,NULL);
    }else if(narracionActual==4){
        narracion = Sequence::create(runCallback5,NULL);
    }
    runAction(narracion);
}

void Armame::narracion1(){
    narracionActual = 1;
    CallFunc *leer = CallFunc::create(CC_CALLBACK_0(Armame::ProfesorLeyendoHablando, this));
    Sequence *leyendo = Sequence::create(leer,NULL);
    this->runAction(leyendo);
    
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("armame_intro_1.mp3");
    
    lbCuadroInicial->setString(LanguageManager::getInstance()->getString("ARMAME_NAR_01"));
}
void Armame::narracion2(){
    narracionActual = 2;
    CallFunc *leer = CallFunc::create(CC_CALLBACK_0(Armame::ProfesorLeyendoHablando, this));
    Sequence *leyendo = Sequence::create(leer,DelayTime::create(1.6),leer,DelayTime::create(1.6),leer,NULL);
    this->runAction(leyendo);
    
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("armame_intro_2.mp3");
    lbCuadroInicial->setString(LanguageManager::getInstance()->getString("ARMAME_NAR_02"));
}
void Armame::narracion3(){
    narracionActual = 3;
    CallFunc *leer = CallFunc::create(CC_CALLBACK_0(Armame::ProfesorLeyendoHablando, this));
    Sequence *leyendo = Sequence::create(leer,DelayTime::create(1.6),leer,DelayTime::create(1.6),leer,DelayTime::create(1.6),leer,NULL);
    this->runAction(leyendo);
    
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("armame_intro_3.mp3");
    lbCuadroInicial->setString(LanguageManager::getInstance()->getString("ARMAME_NAR_03"));
}
void Armame::narracion4(){
    narracionActual = 4;
    CallFunc *leer = CallFunc::create(CC_CALLBACK_0(Armame::ProfesorLeyendoHablando, this));
    Sequence *leyendo = Sequence::create(leer,NULL);
    this->runAction(leyendo);
    
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("armame_intro_4.mp3");
    lbCuadroInicial->setString(LanguageManager::getInstance()->getString("ARMAME_NAR_04"));
}


void Armame::obtenerMedidas(){
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

void Armame::irAtras(Ref* pSender)
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
void Armame::initFondo(){
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

void Armame::initReloj(){
    reloj = CCLabelTTF::create("00:00", "HVD_Comic_Serif_Pro.ttf", letraReloj*escala,CCSizeMake(anchoLateralCE, (letraReloj+20)*escala), TextHAlignment::CENTER);
    reloj->setColor(Color3B(216,254,51));
    reloj->setVerticalAlignment(TextVAlignment::TOP);
    reloj->setAnchorPoint(Vec2(0, 1));
    reloj->setPosition(0,btAtras->getPositionY()-(btAtras->getContentSize().height*escala));
    reloj->setZOrder(9);
    this->addChild(reloj, 1);
}

void Armame::initMusica(){
    //pongo musica
    if(!Configuracion::desarrollo){
        if(CocosDenshion::SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying()){
            
        }else{
            CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("sintonia_armame.mp3", true);
        }
    }
}

void Armame::initBtAtras(){
    btAtras = MenuItemImage::create("preguntator_bt_atras.png","preguntator_bt_atras_down.png",CC_CALLBACK_1(Armame::irAtras, this));
    
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

void Armame::initBtAjustes(){
    btAjustes = MenuItemImage::create("mostrosity_mimostro_bt_ajustes.png","mostrosity_mimostro_bt_ajustes_down.png",CC_CALLBACK_1(Armame::selectorAjustes, this));
    btAjustes->setScale(escala);
    btAjustes->setAnchorPoint(Vec2(1,1));
    btAjustes->setPosition(visibleSize.width-(espacioBordesCuadroCE*2),btAtras->getPositionY());
    btAjustes->retain();
    menu->addChild(btAjustes);
}

void Armame::selectorAjustes(Ref *pSender){
    CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    
    if(Configuracion::desarrollo)
        CCLOG("Selector ajustes");
    
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    
//    Ajustes::desdeEscena = Ajustes::desdeArmame;
//    auto scene = Ajustes::createScene();
//    auto transicion = TransitionFade::create(0.3f, scene);
//    Director::getInstance()->replaceScene(transicion);
    
    auto scene = Ajustes::createScene();
    Director::getInstance()->pushScene(scene);
    
}

void Armame::initCuadroInicial(){
    
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


void Armame::initBocadillo(){
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

void Armame::initProfesor(){
    
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

void Armame::ProfesorLeyendoHablando(){
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

void Armame::ProfesorFalloRespuesta(){
    
    MoveTo *cejasAbajo = MoveTo::create(0.2, Vec2((anchoProfesor/2)-15,altoCejas-25));
    if(profCejas->getNumberOfRunningActions()==0){
        profCejas->runAction(cejasAbajo);
    }
    
}

void Armame::ProfesorAciertaRespuesta(){
    RotateBy *Giro = RotateBy::create(0.4, 360);
    if(profBigote->getNumberOfRunningActions()==0){
        profBigote->runAction(Giro);
    }
    
    MoveTo *ojosArriba = MoveTo::create(0.4, Vec2(anchoProfesor/2,altoOjos+20));
    if(profOjos->getNumberOfRunningActions()==0){
        profOjos->runAction(ojosArriba);
    }
}

void Armame::ProfesorNuevaPregunta(){
    MoveTo *cejasOrigen = MoveTo::create(0.4, Vec2((anchoProfesor/2),altoCejas));
    if(profCejas->getNumberOfRunningActions()==0){
        profCejas->runAction(Sequence::create(DelayTime::create(1),cejasOrigen,NULL));
    }
    
    MoveTo *ojosNormal = MoveTo::create(0.4, Vec2(anchoProfesor/2,altoOjos));
    if(profOjos->getNumberOfRunningActions()==0){
        profOjos->runAction(ojosNormal);
    }
}

void Armame::initCuadroJuego(){
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


void Armame::initTextoCentral(){
    float bordesBocadillos = 40*escalaPropiaBocadillo;
    cuadroDialogo = CCLabelTTF::create("", "HVD_Comic_Serif_Pro.ttf", (bocadillo->getContentSize().height*escalaPropiaBocadillo)/7,CCSizeMake((bocadillo->getContentSize().width*escalaPropiaBocadillo)-(bordesBocadillos*2), (bocadillo->getContentSize().height*escalaPropiaBocadillo)-(bordesBocadillos*3)), TextHAlignment::CENTER);
    cuadroDialogo->setColor(Color3B(0,0,0));
    cuadroDialogo->setVerticalAlignment(TextVAlignment::CENTER);
    cuadroDialogo->setAnchorPoint(Vec2(0.5,0.5));
    cuadroDialogo->setPosition(bocadillo->getPositionX(),bocadillo->getPositionY()+((bocadillo->getContentSize().height*escalaPropiaBocadillo)/2)+(bordesBocadillos*0.5));
    cuadroDialogo->setZOrder(10);
    this->addChild(cuadroDialogo);
    
}

void Armame::cambiarTextoDialogo(std::string texto){
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
            CallFunc *runCallback1 = CallFunc::create(CC_CALLBACK_0(Armame::modificarTXTDialogo, this));
            CallFunc *runCallback2 = CallFunc::create(CC_CALLBACK_0(Armame::vaciarTXTDialogo, this));
            CallFunc *runCallback3 = CallFunc::create(CC_CALLBACK_0(Armame::rellamarTXTDialogo, this));
            
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
void Armame::modificarTXTDialogo(){
    this->cuadroDialogo->setString(textoProximoBocadillo);
    cuadroDialogo->runAction(FadeIn::create(0.3));
}
void Armame::vaciarTXTDialogo(){
    this->cuadroDialogo->setString("");
    bocadillo->setVisible(false);
}

void Armame::rellamarTXTDialogo(){
    cambiarTextoDialogo("");
}


void Armame::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event){
    irAtras(NULL);
}

void Armame::mostrarDialogoComenzar(){
    lbCuadroInicial->setVisible(false);
    isPlayNarracion = false;
    if(dial1_bg==NULL){
        crearDialogoComenzar();
    }
    dial1_bg->setVisible(true);
}
void Armame::ocultarDialogoComenzar(){
    
    if(dial1_bg==NULL){
        crearDialogoComenzar();
    }
    dial1_bg->setVisible(false);
}

void Armame::crearDialogoComenzar(){
    dial1_bg = LayerColor::create(Color4B(0,0,0,0), visibleSize.width-(anchoLateralCE*escala*0.7*2), 700*escala);
    dial1_bg->setPosition((visibleSize.width-dial1_bg->getContentSize().width)/2,visibleSize.height/2-(700*escala/2));
    dial1_bg->setZOrder(16);
    this->addChild(dial1_bg);
    
    dial1_Imenu1 = MenuItemImage::create("preguntator_dial_bt1.png","preguntator_dial_bt1_down.png",CC_CALLBACK_1(Armame::dial1_Imenu2_resp1, this));
    dial1_Imenu1->setScale(escala);
    dial1_Imenu1->setAnchorPoint(Vec2(1, 1));
    dial1_Imenu1->setPosition(dial1_bg->getContentSize().width/2,dial1_bg->getContentSize().height/2);
    
    dial1_Imenu2 = MenuItemImage::create("preguntator_dial_bt2.png","preguntator_dial_bt2_down.png",CC_CALLBACK_1(Armame::dial1_Imenu2_resp2, this));
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

void Armame::dial1_Imenu2_resp1(Ref* sender){
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("tambores_3.mp3");
    ocultarDialogoComenzar();
    comenzarNarracion();
}

void Armame::dial1_Imenu2_resp2(Ref* sender){
    CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("tambores_3.mp3");
    lbCuadroInicial->setVisible(false);
    capaFondoCuadroInicial->setVisible(false);
    capaTextoCuadroInicial->setVisible(false);
    
    ocultarDialogoComenzar();
    comenzarReloj();
    escuchadores = true;
}

void Armame::comenzarReloj(){
    
    this->schedule(schedule_selector(Armame::aumentarReloj),1.0);
    
}
void Armame::aumentarReloj(float dt){
    if(tiempoRestante<0||juegoTerminado){
        unschedule(schedule_selector(Armame::aumentarReloj));
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

void Armame::initCofiguracion(){
    
    gPanel = new CPanelArmame();
    gPanel->retain();
    
    int nPanel = Configuracion::aleatorioEnteros(0, gPanel->ObtenerNumeroPaneles()-1);
    
    gPanel->cargarPanel(nPanel);
    panelHuecos = gPanel->obtenerImgPanel();
    escalaPanel = cuadroJuego->getContentSize().width/panelHuecos->getContentSize().width;
    
    aHuecos = gPanel->obtenerHuecos();
    aHuecos->retain();
}

void Armame::initPanelHuecos(){
    
    panelHuecos->setScaleX(escalaPanel);
    panelHuecos->setScaleY(escalaAlta);
    panelHuecos->setAnchorPoint(Vec2(0,1));
    panelHuecos->setPosition(cuadroJuego->getPositionX(),visibleSize.height-espacioBordesCuadroCE);
    panelHuecos->setZOrder(6);
    addChild(panelHuecos);
    
}
void Armame::initComplementosPanel(){
    
    __Array * aComplementos = gPanel->obtenerComplementos();
    
    for(int i=0;i<aComplementos->count();i++){
        Sprite *complementoActual = dynamic_cast<Sprite*>(aComplementos->getObjectAtIndex(i));
        Vec2 pos = gPanel->obternerMedidasComplemento(i);
        complementoActual->setAnchorPoint(Vec2(0.5,0));
        complementoActual->setPosition(pos);
        complementoActual->setLocalZOrder(gPanel->obtenerZIndexComplemento(i));
        //A LOS COMPLEMENTOS SE LES ASIGNA EL TAG -1
        complementoActual->setTag(-1);
        panelHuecos->addChild(complementoActual);
    }
    

}

void Armame::initHuecos(){
    
    
    
    capaHuecos = LayerColor::create(Color4B(89,54,00,255), cuadroJuego->getContentSize().width,cuadroJuego->getContentSize().height- (panelHuecos->getContentSize().height*panelHuecos->getScaleY())-(altoBordeCapaHuecos*escala));
    capaHuecos->setPosition(cuadroJuego->getPositionX(),espacioBordesCuadroCE);
    capaHuecos->setAnchorPoint(Vec2(0,0));
    capaHuecos->setLocalZOrder(10);
    addChild(capaHuecos);
    
    
    LayerColor *bordeCapaHuecos = LayerColor::create(Color4B(151,90,1,255), capaHuecos->getContentSize().width, altoBordeCapaHuecos*escala);
    bordeCapaHuecos->setPosition(capaHuecos->getPosition().x,capaHuecos->getPosition().y+capaHuecos->getContentSize().height);
    bordeCapaHuecos->setAnchorPoint(Vec2(0,1));
    bordeCapaHuecos->setLocalZOrder(11);
    addChild(bordeCapaHuecos);
    
    Sprite *tituloBorde = Sprite::create("mostrosity_armame_titulo_borde.png");
    tituloBorde->setScale(escala);
    tituloBorde->setAnchorPoint(Vec2(0.5,0.5));
    tituloBorde->setPosition(bordeCapaHuecos->getContentSize().width/2, bordeCapaHuecos->getContentSize().height/2);
    bordeCapaHuecos->addChild(tituloBorde);

    
    LabelTTF *txtTituloBorde = CCLabelTTF::create(LanguageManager::getInstance()->getString("ARMAME_TX_01"), "HVD_Comic_Serif_Pro.ttf",70,tituloBorde->getContentSize(), TextHAlignment::CENTER);
    txtTituloBorde->setColor(Color3B(255,255,255));
    txtTituloBorde->setVerticalAlignment(TextVAlignment::CENTER);
    txtTituloBorde->setAnchorPoint(Vec2(0, 0));
    txtTituloBorde->setPosition(0,0);
    tituloBorde->addChild(txtTituloBorde);
    
    float espacioPorHueco = capaHuecos->getContentSize().width/aHuecos->count();
    nAciertos = aHuecos->count();
    
    for (int i=0; i<aHuecos->count(); i++) {
        //SILUETAS ABAJO
        
        Sprite * hueco = dynamic_cast<Sprite*>(aHuecos->getObjectAtIndex(i));
        float escalaHuecos = escala;
        float escalaHuecosAlta = capaHuecos->getContentSize().height*escala/((hueco->getContentSize().height+margenHueco)*escala);
        float escalaHuecosAncha = espacioPorHueco/((hueco->getContentSize().width+margenHueco));
        if(escalaHuecosAlta>escalaHuecosAncha)
            escalaHuecos = escalaHuecosAncha;
        else
            escalaHuecos = escalaHuecosAlta;
        
        hueco->setScale(escalaHuecos);
        
        hueco->setPosition((espacioPorHueco*i)+(espacioPorHueco/2),capaHuecos->getContentSize().height/2);
        hueco->setOpacity(150);
        hueco->setTag(i);
        hueco->runAction(TintTo::create(0,0,0,0));
        capaHuecos->addChild(hueco);
        

    }
    siluetasPanel = __Array::createWithCapacity(aHuecos->count());
    siluetasPanel->retain();
    for (int i=0; i<aHuecos->count(); i++) {
        //SILUETAS EN PANEL
        aHuecos = gPanel->obtenerHuecos();
        aHuecos->retain();
        Sprite * hueco = dynamic_cast<Sprite*>(aHuecos->getObjectAtIndex(i));
        siluetasPanel->addObject(hueco);
        
        Vec2 pos = gPanel->obternerMedidasHueco(i);
        
        hueco->setScale(escalaPorAltitud(pos.y));
        hueco->setTag(i);
        hueco->setPosition(pos);
        hueco->runAction(TintTo::create(0,0,0,0));
        panelHuecos->addChild(hueco);
        
    }
    
}
void Armame::rellenarHuecos(){
    
    Vector<Node*> siluetasInf = capaHuecos->getChildren();
    
    for (int i=0;i<siluetasInf.size(); i++) {
        Sprite *siluetaInf = dynamic_cast<Sprite*>(siluetasInf.at(i));
        if(siluetaInf!=NULL){
            Sprite *silueta = Sprite::createWithTexture(siluetaInf->getTexture());
            silueta->setTag(siluetaInf->getTag());
            silueta->setAnchorPoint(siluetaInf->getAnchorPoint());
            silueta->setPosition(siluetaInf->getContentSize().width/2,siluetaInf->getContentSize().height/2);
            silueta->setLocalZOrder(gPanel->obtenerZIndexHueco(i));
            siluetaInf->addChild(silueta);
        }
    }
    
    
}

float Armame::escalaPorAltitud(float alto){

    float escalaMinima = 0.4;
    float escalaMaxima = 0.7;
    
    return escalaPorAltitud(alto,escalaMinima,escalaMaxima);
    
}

float Armame::escalaPorAltitud(float alto,float escalaMinima){
    
    float escalaMaxima = escala;
    
    return escalaPorAltitud(alto,escalaMinima,escalaMaxima);
    
}

float Armame::escalaPorAltitud(float alto,float escalaMinima, float escalaMaxima){
    //log("-______________________________________________");
    float altoMaximo = panelHuecos->getContentSize().height;
    //log("alto maximo %f",altoMaximo);
    //log("alto %f",alto);
    
    float porcentaje = (alto*100)/altoMaximo;
    //log("porcentaje %f",porcentaje);
    float porcentajeInv = 100-porcentaje;
    //log("porcentajeInv %f",porcentajeInv);
    
    
    float diferencia = escalaMaxima-escalaMinima;
    float escalaRetorno = ((diferencia/100)*porcentajeInv)+escalaMinima;
    
    //log("retorno %f",escalaRetorno);
    //log("______________________________________________");
    return escalaRetorno;
    
}

bool Armame::disponibleHuecoXRellenos(int numero){
    for(int i=0;i<aHuecos->count();i++){
        Sprite *huecoActual = dynamic_cast<Sprite*>(aHuecos->getObjectAtIndex(i));
        if(huecoActual->getTag()==numero){
            return false;
        }
    }
    return true;
    
}



void Armame::JuegoTerminado(){
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

bool Armame::comprobarToqueRellenoPanel(cocos2d::Touch *toque){
    
    /*Vector<Node*> siluetasInf = capaHuecos->getChildren();
    
    for (int i=0;i<siluetasInf.size(); i++) {
        Sprite *siluetaInf = dynamic_cast<Sprite*>(siluetasInf.at(i));
        if(siluetaInf!=NULL){
            auto target = siluetaInf;
            if(Configuracion::desarrollo)
                CCLOG("my sprite    x %f y %f",target->getPosition().x,target->getPosition().y);
            Point locationInNode = target->convertToNodeSpace(touch->getLocation());
            Size s = target->getContentSize();
            Rect rect = Rect(0, 0, s.width, s.height);
            if (rect.containsPoint(locationInNode))
            {
                CCLOG("SILUETA TOCADA");
                return true;
            }
            
        }
    }*/
    
    //inicializo con array para elegir el que tenga mas zIndex
    __Array *aSpCogidos = __Array::createWithCapacity(capaHuecos->getChildrenCount());
    int contador = 0;
    for (int i=0; i<capaHuecos->getChildrenCount(); i++) {
        Sprite *huecoSilueta = dynamic_cast<Sprite*>(capaHuecos->getChildren().at(i));
        Sprite *hueco = dynamic_cast<Sprite*>(huecoSilueta->getChildren().at(0));
        
        if(!aSpCogidos->containsObject(hueco)&&Configuracion::comprobarToque(toque,hueco)&&hueco->isVisible()){
            aSpCogidos->insertObject(hueco,contador);
            contador++;
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
        
        spCogidoClon = Sprite::createWithTexture(spCogido->getTexture());
        spCogidoClon->setScale(escala);
        spCogidoClon->setPosition(toque->getLocation());
        posOriginalCogido = toque->getLocation();
        spCogidoClon->setAnchorPoint(spCogido->getAnchorPoint());
        spCogidoClon->setLocalZOrder(50);
        spCogidoClon->setVisible(true);
        spCogidoClon->setTag(spCogido->getTag());
        addChild(spCogidoClon);
        cogidaRelleno = true;
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("dimeketekito_fiuu.mp3");
    }else{
        cogidaRelleno = false;
    }
    
    return cogidaRelleno;
}

void Armame::desplazarRellenoPanel(Touch *toque){
    
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

void Armame::reescalarHueco(cocos2d::Touch *toque){
    float altitud = panelHuecos->convertToNodeSpace(toque->getLocation()).y;
    log("altitud %f",altitud);
    //altitud = altitud-(capaHuecos->getContentSize().height*escala);
    //log("altitud2 %f",altitud);
    float escalaAplicada = escala*0.70;
    if(altitud>0){
        escalaAplicada = escalaPorAltitud(altitud,escala/100*35,escala*0.70);
    }
    
    
    log("escala obtenida %f",escalaAplicada);
    
    spCogidoClon->setScale(escalaAplicada);
    
    
}

void Armame::stopAnimHuecosGiro(bool forzar){
    
    for(int i=0;i<aHuecos->count();i++){
        Sprite *huecoActual = dynamic_cast<Sprite*>(aHuecos->getObjectAtIndex(i));
        
        if(huecoActual->getNumberOfRunningActions()!=0&&rozadoHueco == true){
            huecoActual->stopAllActions();
            huecoActual->runAction(RotateTo::create(0.1, 0,0));
            rozadoHueco = false;
        }
        
        if(forzar){
            huecoActual->stopAllActions();
            huecoActual->runAction(RotateTo::create(0.1, 0,0));
            rozadoHueco = false;
        }
    }
    
}

void Armame::stopAnimHuecosGiroShedule(float seg){
    if(!rozadoHueco)stopAnimHuecosGiro(true);
}

void Armame::comprobarExitoRellenoPanel(cocos2d::Touch *toque){
    
    if(cogidaRelleno){
        Sprite *huecoExito = obtenerHuecoPorEntidad(spCogidoClon->getTag());
        if(huecoExito!=NULL&&Configuracion::comprobarToque(toque,huecoExito)){
            CCLOG("EXITO !!!");
            spCogido->setVisible(false);
            
            huecoExito->runAction(TintTo::create(1, 255, 255, 255));
            
            spCogidoClon->runAction(FadeOut::create(0.5));
            
            aciertos++;
            if(aciertos==nAciertos)
                JuegoTerminado();
            else{
                __String *texto = __String::createWithFormat("%s %i",LanguageManager::getInstance()->getString("ARMAME_TX_PROF_01").c_str(),nAciertos-aciertos);
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("correcto.mp3");
                cambiarTextoDialogo(texto->getCString());
            }
        }else{
            bool tocadoHueco = false;
            
            for(int i=0;i<siluetasPanel->count();i++){
                Sprite *huecoActual = dynamic_cast<Sprite*>(siluetasPanel->getObjectAtIndex(i));
                if(Configuracion::comprobarToque(toque,huecoActual)){
                    tocadoHueco = true;
                }
            }
            
            if(tocadoHueco){
                reinicioRellenos();
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("fallo.mp3");
                cambiarTextoDialogo(LanguageManager::getInstance()->getString("ARMAME_TX_PROF_02"));
            }
            MoveTo *elatico = MoveTo::create(0.5,posOriginalCogido);
            CallFunc *runCallback1 = CallFunc::create(CC_CALLBACK_0(Armame::falloDesplazamiento, this));
            spCogidoClon->runAction(Sequence::create(elatico,runCallback1, NULL));
            spCogidoClon->runAction(ScaleTo::create(0.5, escala));
            escuchadores = false;
        }
        
    }
    
    rozadoHueco = false;
}

void Armame::falloDesplazamiento(){
    spCogido->setVisible(true);
    spCogidoClon->setVisible(false);
    escuchadores = true;
    
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("armame_plop2.mp3");
}

Sprite* Armame::obtenerHuecoPorEntidad(int entidad){
    for(int i=0;i<panelHuecos->getChildrenCount();i++){
        Sprite *huecoActual = dynamic_cast<Sprite*>(panelHuecos->getChildren().at(i));
        int entidadBote = huecoActual->getTag();
        if(entidadBote==entidad){
            return huecoActual;
        }
    }
    return NULL;
}

void Armame::reinicioRellenos(){
    Vector<Node *> partes = panelHuecos->getChildren();
    for (int i=0;i<partes.size() ; i++) {
        Node* parte = partes.at(i);
        if(parte!=spCogido)
            parte->setVisible(true);
        
    }
    
    for (int i=0;i<panelHuecos->getChildrenCount(); i++) {
        Sprite *huecoActual = dynamic_cast<Sprite*>(panelHuecos->getChildren().at(i));
        
        //A LOS COMPLEMENTOS SE LES ASIGNA EL TAG -1
        if(huecoActual->getTag()!=-1)
            huecoActual->runAction(TintTo::create(0,0,0,0));
    }
    
    for (int i=0; i<capaHuecos->getChildrenCount(); i++) {
        Sprite *huecoSilueta = dynamic_cast<Sprite*>(capaHuecos->getChildren().at(i));
        Sprite *hueco = dynamic_cast<Sprite*>(huecoSilueta->getChildren().at(0));
        
        if(hueco!=spCogido)
            hueco->setVisible(true);
    }
    aciertos = 0;
}


bool Armame::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
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
    
    
    if(comprobarToqueRellenoPanel(touch)){
        CCLOG("PARTE TOCADA DE MOSTRO");
    }else{
        CCLOG("NO TOCO PARTE MOSTRO");
    }
    
    
    
    return  true;
}
void Armame::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event)
{
    if(!escuchadores){
        return;
    }
    
    if(Configuracion::desarrollo)
        log("MOVED %f %f ",touch->getLocation().x,touch->getLocation().y);
    
    if(cogidaRelleno){
        desplazarRellenoPanel(touch);
        reescalarHueco(touch);
    }
    
}
void Armame::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
{
    if(!escuchadores){
        return;
    }
    
    if(Configuracion::desarrollo)
        log("ENDED %f %f ",touch->getLocation().x,touch->getLocation().y);
    
    
    if(cogidaRelleno)
        comprobarExitoRellenoPanel(touch);
}

