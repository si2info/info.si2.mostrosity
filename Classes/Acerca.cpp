#include "HelloWorldScene.h"
#include "Acerca.h"
#include "Ajustes.h"
#include "Configuracion.h"
#include "MiMostro.h"
#include "LanguageManager.h"
#include "SimpleAudioEngine.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "JniLink.h"
#endif


USING_NS_CC;

char * Acerca::paginaDocentic = "http://cmidocentic.com/";
char * Acerca::paginaCMI = "http://www.eulainmaculada.com/";
char * Acerca::paginaSI2 = "http://si2.info/";

/*default menu*/
int Acerca::desdeEscena = 0;

Scene* Acerca::createScene()
{

    auto scene = Scene::create();

    auto layer = Acerca::create();
    scene->addChild(layer);
    return scene;
}

bool Acerca::init()
{

    if ( !Layer::init() )
    {
        return false;
    }
    this->setKeypadEnabled(true);
    
    obtenerMedidas();
    initFondo();
    initBotonAtras();
    //initCuadroJuego();
    initPizzarra();
    initContenidoPizzarra();
    initBannerLateral();
    
    //activo los tocuh de pantalla
    auto listener1 = EventListenerTouchOneByOne::create();
    listener1->setSwallowTouches(true);
    listener1->onTouchBegan = CC_CALLBACK_2(Acerca::onTouchBegan, this);
    listener1->onTouchMoved = CC_CALLBACK_2(Acerca::onTouchMoved, this);
    listener1->onTouchEnded = CC_CALLBACK_2(Acerca::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);
    
    
    
    return true;
}

void Acerca::onEnterTransitionDidFinish(){
    if(Configuracion::desarrollo){
        CCLOG("ENTRA EN ESCENA ACERCA ");
        if(desdeMenu){
            CCLOG("DESDE MENU");
        }else{
            CCLOG("DESDE AJUSTES");
        }
    }
    initMusica();
    
    
    
}

void Acerca::onExitTransitionDidStart() {
    
    CCTextureCache::sharedTextureCache()->removeUnusedTextures();
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames();
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames();
    CCTextureCache::sharedTextureCache()->removeUnusedTextures();
    
    SpriteFrameCache::getInstance()->removeUnusedSpriteFrames();
    
}

void Acerca::obtenerMedidas(){
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
    
    espacioSuperiorBtAtrasCE = espacioSuperiorBtAtras*escala;
}

void Acerca::irAtras(Ref* pSender)
{
    if(Configuracion::desarrollo)
        CCLOG("atras");
    CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    
    Director::getInstance()->popScene();
    
//    if(desdeEscena==desdeMenu){
//        auto scene = HelloWorld::createScene();
//        auto transicion = TransitionFade::create(0.3f, scene);
//        Director::getInstance()->replaceScene(transicion);
//    }else if(desdeEscena==desdeAjustes){
//        auto scene = Ajustes::createScene();
//        auto transicion = TransitionFade::create(0.3f, scene);
//        Director::getInstance()->replaceScene(transicion);
//    }else if(desdeEscena==desdeMiMostro){
//        auto scene = MiMostro::createScene();
//        auto transicion = TransitionFade::create(0.3f, scene);
//        Director::getInstance()->replaceScene(transicion);
//    }
    
}
void Acerca::initFondo(){   
    
    LayerColor *capaFondo = LayerColor::create(Color4B(25,78,121,255), visibleSize.width, visibleSize.height);
    capaFondo->setPosition(0,0);
    this->addChild(capaFondo,-1);
    
    fondoTemp_i = Sprite::create("mostrosity_dientes_i.png");
    fondoTemp_i->setScale(escala);
    fondoTemp_i->setAnchorPoint(Vec2(0,0.5));
    fondoTemp_i->setPosition(visibleSize.width/2,visibleSize.height/2);
    this->addChild(fondoTemp_i);
    
    
    
    fondoTemp_d = Sprite::create("mostrosity_dientes_d.png");
    fondoTemp_d->setScale(escala);
    fondoTemp_d->setAnchorPoint(Vec2(1,0.5));
    fondoTemp_d->setPosition(visibleSize.width/2,visibleSize.height/2);
    this->addChild(fondoTemp_d);
    
    

    
}

void Acerca::initMusica(){
    //pongo musica
    if(!Configuracion::desarrollo){
        if(CocosDenshion::SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying()){
            
        }else{
            CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("MUSICA2.mp3", true);
        }
    }
}

void Acerca::initBotonAtras(){
    botonAtras = MenuItemImage::create("preguntator_bt_atras.png","preguntator_bt_atras_down.png",CC_CALLBACK_1(Acerca::irAtras, this));
    
    botonAtras->setScale(escala);
    botonAtras->setAnchorPoint(Vec2(0, 1));
    //calculo espacio sobrante
    float espacio = anchoLateral-(botonAtras->getContentSize().width*escala);
    
    botonAtras->setPosition(0+(espacio/2),visibleSize.height-(espacioSuperiorBtAtras*escala));
    
    menu = Menu::create(botonAtras, NULL);
    menu->setPosition(Vec2::ZERO);
    botonAtras->setZOrder(10);
    this->addChild(menu);
}

void Acerca::initCuadroJuego(){
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

void Acerca::initBannerLateral(){
    
    float anchoBannerLateral = visibleSize.width-(pizarra->getContentSize().width*escalaAlta)-(2*espacioSuperiorBtAtrasCE);
    //Prueba de hasta donde llega el banner
    /*LayerColor *capaPrueba  = LayerColor::create(Color4B(155,122,100,255), anchoBannerLateral, 200);
    capaPrueba->setPosition(0+espacioSuperiorBtAtrasCE, visibleSize.height/2);
    addChild(capaPrueba);*/
    
    
    //posicion de origen para la sucesion de elementos en vertical
    float posicionActual = (visibleSize.height/3)*2+(letraPizzara*escalaAncha) + (70*escalaAncha);
    
    LabelTTF *texto1 = LabelTTF::create(LanguageManager::getInstance()->getString("Creditos_texto1"), "HVD_Comic_Serif_Pro.ttf", letraPizzara*escalaAncha,Size(anchoBannerLateral, (letraPizzara+margenLetrasPizarra)*escalaAncha), TextHAlignment::CENTER);
    texto1->setColor(Color3B(255,255,255));
    texto1->setVerticalAlignment(TextVAlignment::TOP);
    texto1->setAnchorPoint(Vec2(0, 1));
    texto1->setPosition(0, posicionActual);
    this->addChild(texto1);
    
    posicionActual = posicionActual-texto1->getContentSize().height*escalaAncha - (70*escalaAncha)/*espacio entre elementos*/;

    logoDocen = Sprite::create("mostrosity_creditos_logoDocen.png");
    logoDocen->setAnchorPoint(Vec2(0,1));
    logoDocen->setScale(escalaAncha);
    int posLogo = ((anchoBannerLateral - logoDocen->boundingBox().size.width) / 2);
    logoDocen->setPosition(posLogo,posicionActual);
    this->addChild(logoDocen);
    
    posicionActual = posicionActual-logoDocen->getContentSize().height*escalaAncha - (100*escalaAncha)/*espacio entre elementos*/;
    
    LabelTTF *texto2 = LabelTTF::create(LanguageManager::getInstance()->getString("Creditos_texto2"), "HVD_Comic_Serif_Pro.ttf", letraPizzara*escalaAncha,Size(anchoBannerLateral, (letraPizzara+margenLetrasPizarra)*escalaAncha*4.5), TextHAlignment::CENTER);
    texto2->setColor(Color3B(255,255,255));
    texto2->setVerticalAlignment(TextVAlignment::TOP);
    texto2->setAnchorPoint(Vec2(0, 1));
    texto2->setPosition(0, posicionActual);
    this->addChild(texto2);
    
    posicionActual = posicionActual-texto2->getContentSize().height*escalaAncha + (45*escalaAncha)/*espacio entre elementos*/;
    
    logoInma = Sprite::create("mostrosity_creditos_logoInmaculada.png");
    logoInma->setAnchorPoint(Vec2(0,1));
    logoInma->setScale(escalaAncha);
    posLogo = ((anchoBannerLateral - logoInma->boundingBox().size.width) / 2);
    logoInma->setPosition(posLogo, posicionActual);
    this->addChild(logoInma);
    
    float anchoLogoInma = logoInma->getContentSize().width*escalaAncha;
    if(anchoLogoInma>anchoBannerLateral-espacioSuperiorBtAtrasCE){
        float escalaNueva = (anchoBannerLateral*escalaAncha)/anchoLogoInma;
        logoInma->setScale(escalaNueva);
    }
    
    posicionActual = posicionActual-logoInma->getContentSize().height*escalaAncha-(70*escalaAncha)/*espacio entre elementos*/;
    
    LabelTTF *texto3 = LabelTTF::create(LanguageManager::getInstance()->getString("Creditos_texto3"), "HVD_Comic_Serif_Pro.ttf", letraPizzara*escalaAncha,Size(anchoBannerLateral, (letraPizzara+margenLetrasPizarra)*escalaAncha*4.5), TextHAlignment::CENTER);
    texto3->setColor(Color3B(255,255,255));
    texto3->setVerticalAlignment(TextVAlignment::TOP);
    texto3->setAnchorPoint(Vec2(0, 1));
    texto3->setPosition(0, posicionActual);
    this->addChild(texto3);
    
    posicionActual = posicionActual-logoInma->getContentSize().height*escalaAncha-(110*escalaAncha)/*espacio entre elementos*/;
    
    logoSI2 = Sprite::create("mostrosity_creditos_logoSI2.png");
    logoSI2->setAnchorPoint(Vec2(0,0));
    logoSI2->setScale(escalaAncha * 1.5);
    posLogo = ((anchoBannerLateral - logoSI2->boundingBox().size.width) / 2);
    logoSI2->setPosition(posLogo, posicionActual);
    this->addChild(logoSI2);

}

void Acerca::initPizzarra(){
    
    pizarra = Sprite::create("mostrosity_creditos_pizzarra.png");
    pizarra->setScale(escalaAlta);
    pizarra->setAnchorPoint(Vec2(1,1));
    pizarra->setPosition(visibleSize.width-espacioSuperiorBtAtrasCE,visibleSize.height-espacioSuperiorBtAtrasCE);
    pizarra->retain();
    this->addChild(pizarra);
    
    //obtengo el marco de la pizzarra y le aplico unos bordes para no pisar el marco
    anchoPizarra = pizarra->getContentSize().width-250;
    altoPizarra = pizarra->getContentSize().height-250;
    
    //capa inferior que ha de ser mas grande que la ventana que permite ver el contenido
    scrollContainer = Layer::create();
    scrollContainer->setAnchorPoint(Vec2::ZERO);
    scrollContainer->setContentSize(Size(anchoPizarra,altoPizarra*altoContPizzaraEnPizzaras + (100*escalaAlta)));
    scrollContainer->setColor(Color3B(45,65,12));
    scrollContainer->retain();
    
    //este es el fondo seria opcional porque el contenido se podria meter en el scrollContainer pero es una ejemplo de que se le puede aplicar un fondo cualquiera. esta debe tener el mismo tamaño.
    contenedorPizarra = LayerColor::create(Color4B(0,53,0,255), scrollContainer->getContentSize().width, scrollContainer->getContentSize().height);
    contenedorPizarra->setAnchorPoint(Vec2::ZERO);
    contenedorPizarra->setPosition(0,0);
    contenedorPizarra->retain();
    scrollContainer->addChild(contenedorPizarra);
    
    
    //esta es la ventana que permite que se vea el contenido de la pizzara ocultando lo demas.
    scrollView = ScrollView::create(Size(anchoPizarra,altoPizarra), scrollContainer);
    scrollView->setPosition(125,125);
    scrollView->setDirection(ScrollView::Direction::VERTICAL);
    scrollView->setContentOffset(scrollView->minContainerOffset(), false);
    //scrollView->setContentOffsetInDuration(scrollView->minContainerOffset(),1);
    pizarra->addChild(scrollView);

    
}


void Acerca::initContenidoPizzarra(){
    
    float posicionActual = contenedorPizarra->getContentSize().height;
    
    //LOGO
    /*Sprite *mstLogo = Sprite::create("mostrosity_creditos_mst_logo.png");
    mstLogo->setAnchorPoint(Vec2(0,1));
    mstLogo->setPosition(0,posicionActual);
    contenedorPizarra->addChild(mstLogo);*/
    
    //LOGO ABSOLUTO
    Sprite *mstLogoAbs = Sprite::create("mostrosity_creditos_mst_logo.png");
    mstLogoAbs->setAnchorPoint(Vec2(0,0));
    mstLogoAbs->setPosition(100,altoPizarra-margenPizzaraBordes);
    pizarra->addChild(mstLogoAbs);
    
    //FLECHA
    Sprite *flecha1 = Sprite::create("mostrosity_creditos_flecha.png");
    flecha1->setAnchorPoint(Vec2(1,1));
    flecha1->setPosition(anchoPizarra,altoPizarra*(altoContPizzaraEnPizzaras));
    contenedorPizarra->addChild(flecha1);
    
    //FLECHA ABSOLUTA
    /*Sprite *flecha0 = Sprite::create("mostrosity_creditos_flecha.png");
    flecha0->setAnchorPoint(Vec2(0,0));
    flecha0->setPosition(anchoPizarra,margenPizzaraBordes);
    pizarra->addChild(flecha0);
     */
    
    LabelTTF *texto1 = LabelTTF::create(LanguageManager::getInstance()->getString("Creditos_pizarra_1"), "HVD_Comic_Serif_Pro.ttf", letraPizzara,Size(anchoPizarra, (letraPizzara+margenLetrasPizarra)*5.5), TextHAlignment::CENTER);
    texto1->setColor(Color3B(139,152,139));
    texto1->setVerticalAlignment(TextVAlignment::TOP);
    texto1->setAnchorPoint(Vec2(0.5, 1));
    texto1->setPosition(anchoPizarra/2,posicionActual);
    contenedorPizarra->addChild(texto1);
    
    
    posicionActual = posicionActual- texto1->getContentSize().height;
    
    LabelTTF *texto2 = LabelTTF::create(LanguageManager::getInstance()->getString("Creditos_pizarra_2"), "HVD_Comic_Serif_Pro.ttf", letraPizzara,Size(anchoPizarra, (letraPizzara+margenLetrasPizarra)*3), TextHAlignment::CENTER);
    texto2->setColor(Color3B(255,255,255));
    texto2->setVerticalAlignment(TextVAlignment::TOP);
    texto2->setAnchorPoint(Vec2(0.5, 1));
    texto2->setPosition(anchoPizarra/2,posicionActual);
    contenedorPizarra->addChild(texto2);
    
    
    posicionActual = posicionActual- texto2->getContentSize().height;
    
    LabelTTF *texto3 = LabelTTF::create(LanguageManager::getInstance()->getString("Creditos_pizarra_3"), "HVD_Comic_Serif_Pro.ttf", letraPizzara,Size(anchoPizarra, (letraPizzara+margenLetrasPizarra)*2), TextHAlignment::CENTER);
    texto3->setColor(Color3B(139,152,139));
    texto3->setVerticalAlignment(TextVAlignment::TOP);
    texto3->setAnchorPoint(Vec2(0.5, 1));
    texto3->setPosition(anchoPizarra/2,posicionActual);
    contenedorPizarra->addChild(texto3);
    
    
    posicionActual = posicionActual- texto3->getContentSize().height;
    
    LabelTTF *texto4 = LabelTTF::create(LanguageManager::getInstance()->getString("Creditos_pizarra_4"), "HVD_Comic_Serif_Pro.ttf", letraPizzara,Size(anchoPizarra, (letraPizzara+margenLetrasPizarra)*5), TextHAlignment::CENTER);
    texto4->setColor(Color3B(255,255,255));
    texto4->setVerticalAlignment(TextVAlignment::TOP);
    texto4->setAnchorPoint(Vec2(0.5, 1));
    texto4->setPosition(anchoPizarra/2,posicionActual);
    contenedorPizarra->addChild(texto4);
    
    posicionActual = posicionActual- texto4->getContentSize().height;
    
    LabelTTF *texto5 = LabelTTF::create(LanguageManager::getInstance()->getString("Creditos_pizarra_5"), "HVD_Comic_Serif_Pro.ttf", letraPizzara,Size(anchoPizarra, (letraPizzara+margenLetrasPizarra)*2), TextHAlignment::CENTER);
    texto5->setColor(Color3B(139,152,139));
    texto5->setVerticalAlignment(TextVAlignment::TOP);
    texto5->setAnchorPoint(Vec2(0.5, 1));
    texto5->setPosition(anchoPizarra/2,posicionActual);
    contenedorPizarra->addChild(texto5);
    
    
    posicionActual = posicionActual- texto5->getContentSize().height;
    
    LabelTTF *texto6 = LabelTTF::create(LanguageManager::getInstance()->getString("Creditos_pizarra_6"), "HVD_Comic_Serif_Pro.ttf", letraPizzara,Size(anchoPizarra, (letraPizzara+margenLetrasPizarra)*2), TextHAlignment::CENTER);
    texto6->setColor(Color3B(255,255,255));
    texto6->setVerticalAlignment(TextVAlignment::TOP);
    texto6->setAnchorPoint(Vec2(0.5, 1));
    texto6->setPosition(anchoPizarra/2,posicionActual);
    contenedorPizarra->addChild(texto6);
    
    posicionActual = posicionActual- texto6->getContentSize().height;
    
    LabelTTF *texto7 = LabelTTF::create(LanguageManager::getInstance()->getString("Creditos_pizarra_7"), "HVD_Comic_Serif_Pro.ttf", letraPizzara,Size(anchoPizarra, (letraPizzara+margenLetrasPizarra)*2), TextHAlignment::CENTER);
    texto7->setColor(Color3B(139,152,139));
    texto7->setVerticalAlignment(TextVAlignment::TOP);
    texto7->setAnchorPoint(Vec2(0.5, 1));
    texto7->setPosition(anchoPizarra/2,posicionActual);
    contenedorPizarra->addChild(texto7);
    
    
    posicionActual = posicionActual- texto7->getContentSize().height;
    
    LabelTTF *texto8 = LabelTTF::create(LanguageManager::getInstance()->getString("Creditos_pizarra_8"), "HVD_Comic_Serif_Pro.ttf", letraPizzara,Size(anchoPizarra, (letraPizzara+20)*2), TextHAlignment::CENTER);
    texto8->setColor(Color3B(255,255,255));
    texto8->setVerticalAlignment(TextVAlignment::TOP);
    texto8->setAnchorPoint(Vec2(0.5, 1));
    texto8->setPosition(anchoPizarra/2,posicionActual);
    contenedorPizarra->addChild(texto8);
    
    
    posicionActual = posicionActual- texto8->getContentSize().height;
    
    LabelTTF *texto9 = LabelTTF::create(LanguageManager::getInstance()->getString("Creditos_pizarra_9"), "HVD_Comic_Serif_Pro.ttf", letraPizzara,Size(anchoPizarra, (letraPizzara+margenLetrasPizarra)*2), TextHAlignment::CENTER);
    texto9->setColor(Color3B(139,152,139));
    texto9->setVerticalAlignment(TextVAlignment::TOP);
    texto9->setAnchorPoint(Vec2(0.5, 1));
    texto9->setPosition(anchoPizarra/2,posicionActual);
    contenedorPizarra->addChild(texto9);
    
    
    posicionActual = posicionActual- texto9->getContentSize().height;
    
    LabelTTF *texto10 = LabelTTF::create(LanguageManager::getInstance()->getString("Creditos_pizarra_10"), "HVD_Comic_Serif_Pro.ttf", letraPizzara,Size(anchoPizarra, (letraPizzara+20)*2), TextHAlignment::CENTER);
    texto10->setColor(Color3B(255,255,255));
    texto10->setVerticalAlignment(TextVAlignment::TOP);
    texto10->setAnchorPoint(Vec2(0.5, 1));
    texto10->setPosition(anchoPizarra/2,posicionActual);
    contenedorPizarra->addChild(texto10);
    
    
    posicionActual = posicionActual- texto10->getContentSize().height;
    
    LabelTTF *texto11 = LabelTTF::create(LanguageManager::getInstance()->getString("Creditos_pizarra_11"), "HVD_Comic_Serif_Pro.ttf", letraPizzara,Size(anchoPizarra, (letraPizzara+margenLetrasPizarra)*2), TextHAlignment::CENTER);
    texto11->setColor(Color3B(139,152,139));
    texto11->setVerticalAlignment(TextVAlignment::TOP);
    texto11->setAnchorPoint(Vec2(0.5, 1));
    texto11->setPosition(anchoPizarra/2,posicionActual);
    contenedorPizarra->addChild(texto11);
    
    
    posicionActual = posicionActual- texto11->getContentSize().height;
    
    LabelTTF *texto12 = LabelTTF::create(LanguageManager::getInstance()->getString("Creditos_pizarra_12"), "HVD_Comic_Serif_Pro.ttf", letraPizzara,Size(anchoPizarra, (letraPizzara+margenLetrasPizarra)*3), TextHAlignment::CENTER);
    texto12->setColor(Color3B(255,255,255));
    texto12->setVerticalAlignment(TextVAlignment::TOP);
    texto12->setAnchorPoint(Vec2(0.5, 1));
    texto12->setPosition(anchoPizarra/2,posicionActual);
    contenedorPizarra->addChild(texto12);
    
    posicionActual = posicionActual- texto12->getContentSize().height + (20*escalaAlta);
    
    LabelTTF *texto13 = LabelTTF::create(LanguageManager::getInstance()->getString("Creditos_pizarra_13"), "HVD_Comic_Serif_Pro.ttf", letraPizzara-10,Size(anchoPizarra, (letraPizzara+margenLetrasPizarra)*8), TextHAlignment::CENTER);
    texto13->setColor(Color3B(139,152,139));
    texto13->setVerticalAlignment(TextVAlignment::TOP);
    texto13->setAnchorPoint(Vec2(0.5, 1));
    texto13->setPosition(anchoPizarra/2,posicionActual);
    contenedorPizarra->addChild(texto13);
    
    posicionActual = posicionActual- texto13->getContentSize().height;
    
    //FLECHA
    Sprite *flecha2 = Sprite::create("mostrosity_creditos_flecha.png");
    flecha2->setAnchorPoint(Vec2(1,0));
    /*anterotacion flecha2->setPosition(anchoPizarra,posicionActual+(flecha2->getContentSize().height)); */
    flecha2->setPosition(anchoPizarra-(flecha2->getContentSize().width),posicionActual+(flecha2->getContentSize().height)*2);
    flecha2->setOpacity(0);
    flecha2->runAction(Sequence::create(RotateBy::create(0,180),FadeIn::create(0),NULL));
    /*anterotacion*/
    contenedorPizarra->addChild(flecha2);
    
}


void Acerca::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event){
	irAtras(NULL);
}

bool Acerca::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
    CCPoint location = touch->getLocationInView();
    location = CCDirector::sharedDirector()->convertToGL(location);
    
    if (logoDocen->boundingBox().containsPoint(location)) {
        Configuracion::callOpenURL(Acerca::paginaDocentic);
    }
    
    if (logoInma->boundingBox().containsPoint(location)) {
        Configuracion::callOpenURL(Acerca::paginaCMI);
    }
    
    if (logoSI2->boundingBox().containsPoint(location)) {
        Configuracion::callOpenURL(Acerca::paginaSI2);
    }
    
    if(!escuchadores){
        return false;
    }
    if(Configuracion::desarrollo)
        log("BEGAN %f %f",touch->getLocation().x,touch->getLocation().y);
    
    return  true;
}
void Acerca::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event)
{
    if(Configuracion::desarrollo)
        log("MOVED %f %f ",touch->getLocation().x,touch->getLocation().y);
    
}
void Acerca::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
{
    if(Configuracion::desarrollo)
        log("ENDED %f %f ",touch->getLocation().x,touch->getLocation().y);
    
    
    
}
