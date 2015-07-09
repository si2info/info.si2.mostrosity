#include "HelloWorldScene.h"
#include "Preguntator.h"
#include "Akuerdate.h"
#include "Armame.h"
#include "Dimeketekito.h"
#include "Configuracion.h"
#include "Ajustes.h"
#include "MiMostro.h"
#include "Mosterland.h"
#include "Acerca.h"
#include "LanguageManager.h"
#include "SimpleAudioEngine.h"

#include "../cocos2d/cocos/network/HttpClient.h"
#include "../cocos2d/extensions/GUI/CCControlExtension/CCControlExtensions.h"
#include "../cocos2d/cocos/editor-support/spine/Json.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "JniLink.h"
#endif


USING_NS_CC;

Scene* HelloWorld::createScene()
{

    auto scene = Scene::create();

    auto layer = HelloWorld::create();
    scene->addChild(layer);
    return scene;
}


bool HelloWorld::init()
{
    
    oldLanguage = Configuracion::idioma;
    
    this->setKeypadEnabled(true);
    if ( !Layer::init() )
    {
        return false;
    }

    
    if(Configuracion::desarrollo)
        CCLOG("INIT HELLOWORLD");
    
    if(!cargado){
        if(Configuracion::desarrollo)
            CCLOG("VUELVO A CARGAR");
        iniciarCargas();
    }
    if(cargado)
        iniciarEscena();
    
    log("IDDEVIDE %s",Configuracion::getIDDEVICE());

    return true;
}
void HelloWorld::iniciarCargas(){
    
    if(Configuracion::desarrollo)
        CCLOG("EMPIEZO CARGAS");

    this->cargado = true;
    if(Configuracion::desarrollo)
        CCLOG("ACABO CARGAS");
    
    visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    //empiezo a colocar
    relacion = visibleSize.width/visibleSize.height;
    escalaAncha = visibleSize.width/2560;
    escalaAlta = visibleSize.height/1600;
    
    //cargarBotonesMenus
    cargarBotonesMenu();
    
    //fijarfondo
    fijarFondo();

}

void HelloWorld::onEnterTransitionDidFinish(){
    
    getIdMiMostro();
    cargarMusica();
    salir = false;
    CCTextureCache::getInstance()->getCachedTextureInfo();
    
    if (oldLanguage != Configuracion::idioma) {
        oldLanguage = Configuracion::idioma;
        
        eliminarTextosBotones();
        cargarTextos();
        
    }
    

}

void HelloWorld::onExitTransitionDidStart() {
    
    cleanMemory();
    
}

HelloWorld::~HelloWorld() {
    
    cleanMemory();
    
}

void HelloWorld::cleanMemory() {
    
    CCDirector::sharedDirector()->purgeCachedData();
    
    CCTextureCache::sharedTextureCache()->removeUnusedTextures();
    CCTextureCache::sharedTextureCache()->removeAllTextures();
    CCTextureCache::purgeSharedTextureCache();
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames();
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFrames();
    CCSpriteFrameCache::purgeSharedSpriteFrameCache();
    
    SpriteFrameCache::getInstance()->removeUnusedSpriteFrames();
    
}

void HelloWorld::iniciarEscena(){
    if(cargado&&!empezado){
        empezado = true;
        
        //menu textos de los botones
        cargarTextos();
        
        
        //cargo musica
        cargarMusica();
        
        if(Configuracion::desarrollo)
            CCLOG("EMPIEZAN ANIMACIONES");
        //animacionesMURCIELAGO
        cargarAnimacionMurcielago();
        cargarAnimacionAkuerdate();
        cargarAnimacionArmame();
        cargarAnimacionDimeketekito();
        cargarAnimacionPreguntator();
        
        cargarAnimacionConfiguracion();
        cargarAnimacionMimostro();
        cargarAnimacionMosterland();
        
        
        
        //acelerometro
        //Device::setAccelerometerEnabled(true);
        auto listener = EventListenerAcceleration::create(CC_CALLBACK_2(HelloWorld::OnAcceleration,this));
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);
        
        //activo los tocuh de pantalla
        auto listener1 = EventListenerTouchOneByOne::create();
        listener1->setSwallowTouches(true);
        listener1->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
        listener1->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
        listener1->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);
        
        
        if(Configuracion::desarrollo)
            desplazarMurcielago();
    }
    
}

void HelloWorld::cargarBotonesMenu(){
    
    menu_botonera_preguntator = Sprite::create("menu_botonera_preguntator.png");
    menu_botonera_armame = Sprite::create("menu_botonera_armame.png");
    menu_botonera_dimeketekito = Sprite::create("menu_botonera_dimeketekito.png");
    menu_botonera_akuerdate = Sprite::create("menu_botonera_akuerdate.png");
    menu_bttop_config = Sprite::create("menu_bttop_config.png");
    menu_bttop_mimostro = Sprite::create("menu_bttop_mimostro.png");
    menu_bttop_mosterlan = Sprite::create("menu_bttop_mosterlan.png");
    menu_bttop_murcielago = Sprite::create("menu_bttop_murcielago.png");
    menu_bttop_logo = Sprite::create("menu_bttop_logo.png");
    
    if(relacion<1.5){
        
        //cargo la escala diviendo el ancho de la pantalla entre el ancho del diseño pasado por SI2
        escala = escalaAncha;
        
        if(Configuracion::desarrollo)
            CCLOG("escala %f",escala);
        
        //cargo la escala
        
        //cargo botones de juegos
        
        
        //---------------------preguntator-------------//
        menu_botonera_preguntator->setScaleX(escala);
        menu_botonera_preguntator->setScaleY(escala);
        menu_botonera_preguntator->setAnchorPoint(Vec2(0, 1));
        
        //_______________MARGEN________________________//
        margen4botones = (visibleSize.width)-((menu_botonera_preguntator->getContentSize().width*escala)*2);
        //if(Configuracion::desarrollo)
        //log("pantalla %f margen %f boton %f",visibleSize.width,margen4botones,menu_botonera_preguntator->getContentSize().width*escala);
        //_______________MARGEN________________________//
        
        menu_botonera_preguntator->setPosition(
                                               ((visibleSize.width/2)-(menu_botonera_preguntator->getContentSize().width*escala))-((margen4botones/3)/2),
                                               (menu_botonera_preguntator->getContentSize().height*escala)+(margen4botones/4)
                                               );
        
        //---------------------preguntator-------------//
        
        //---------------------armame-------------//
        menu_botonera_armame->setScaleX(escala);
        menu_botonera_armame->setScaleY(escala);
        menu_botonera_armame->setAnchorPoint(Vec2(0, 1));
        menu_botonera_armame->setPosition(
                                          (visibleSize.width/2)+((margen4botones/3)/2),
                                          menu_botonera_preguntator->getPosition().y
                                          );
        //---------------------armame-------------//
        
        //---------------------dimeketekito-------------//
        menu_botonera_dimeketekito->setScaleX(escala);
        menu_botonera_dimeketekito->setScaleY(escala);
        menu_botonera_dimeketekito->setAnchorPoint(Vec2(0, 1));
        menu_botonera_dimeketekito->setPosition(
                                                menu_botonera_preguntator->getPosition().x,
                                                menu_botonera_preguntator->getPosition().y+(menu_botonera_dimeketekito->getContentSize().height*escala)+(margen4botones/4)
                                                );
        //this->addChild(menu_botonera_dimeketekito);
        //---------------------dimeketekito-------------//
        
        //---------------------akuerdate-------------//
        menu_botonera_akuerdate->setScaleX(escala);
        menu_botonera_akuerdate->setScaleY(escala);
        menu_botonera_akuerdate->setAnchorPoint(Vec2(0, 1));
        menu_botonera_akuerdate->setPosition(
                                             menu_botonera_armame->getPosition().x,
                                             menu_botonera_dimeketekito->getPosition().y
                                             );
        //---------------------akuerdate-------------//
        //cargo botones de juegos
        
        
        //menu superior
        //---------------------logo-------------//
        menu_bttop_logo->setScaleX(escala);
        menu_bttop_logo->setScaleY(escala);
        menu_bttop_logo->setAnchorPoint(Vec2(0, 1));
        menu_bttop_logo->setPosition(
                                     menu_botonera_preguntator->getPosition().x,
                                     (visibleSize.height-(margen4botones/5))
                                     );
        //---------------------logo-------------//
        //---------------------murcielago-------------//
        menu_bttop_murcielago->setScaleX(escala);
        menu_bttop_murcielago->setScaleY(escala);
        menu_bttop_murcielago->setAnchorPoint(Vec2(0, 1));
        menu_bttop_murcielago->setPosition(
                                           (menu_bttop_logo->getPosition().x)+(menu_bttop_logo->getContentSize().width*escala)+(margen4botones/5),
                                           (visibleSize.height-(margen4botones/5)+((menu_bttop_murcielago->getContentSize().height*escala)*0.60))
                                           );
        //---------------------murcielago-------------//
        //---------------------mimostro-------------//
        menu_bttop_mimostro->setScaleX(escala);
        menu_bttop_mimostro->setScaleY(escala);
        menu_bttop_mimostro->setAnchorPoint(Vec2(0, 1));
        menu_bttop_mimostro->setPosition(
                                         (menu_botonera_akuerdate->getPosition().x+menu_botonera_akuerdate->getContentSize().width*escala)-(menu_bttop_mimostro->getContentSize().width*escala),
                                         menu_bttop_logo->getPosition().y
                                         );
        //---------------------mimostro-------------//
        
        
        //---------------------mosterlan-------------//
        menu_bttop_mosterlan->setScaleX(escala);
        menu_bttop_mosterlan->setScaleY(escala);
        menu_bttop_mosterlan->setAnchorPoint(Vec2(0, 1));
        menu_bttop_mosterlan->setPosition(
                                          menu_bttop_mimostro->getPosition().x-(margen4botones/5)-(menu_bttop_mosterlan->getContentSize().width*escala),
                                          menu_bttop_logo->getPosition().y
                                          );
        //---------------------mosterlan-------------//
        
        //---------------------CONFIGURACION-------------//
        menu_bttop_config->setScaleX(escala);
        menu_bttop_config->setScaleY(escala);
        menu_bttop_config->setAnchorPoint(Vec2(0, 1));
        menu_bttop_config->setPosition(
                                       menu_bttop_mosterlan->getPosition().x-(margen4botones/5)-(menu_bttop_config->getContentSize().width*escala),
                                       menu_bttop_logo->getPosition().y
                                       );
        //---------------------CONFIGURACION-------------//
        
        
        
        
        
        
        
        
    }else{
        //cargo la escala
        escala = escalaAlta;
        if(Configuracion::desarrollo)
            CCLOG("escala %f",escala);
        //cargo la escala
        
        //cargo botones de juegos
        
        //---------------------preguntator-------------//
        menu_botonera_preguntator->setScaleX(escala);
        menu_botonera_preguntator->setScaleY(escala);
        menu_botonera_preguntator->setAnchorPoint(Vec2(0, 1));
        
        //_______________MARGEN________________________//
        margen4botones = 100*escala;
        //_______________MARGEN________________________//
        
        float Xpreguntator = ((visibleSize.width/2)-(menu_botonera_preguntator->getContentSize().width*escala))-(margen4botones/2);
        float yPreguntator =(menu_botonera_preguntator->getContentSize().height*escala)+(margen4botones/4);
        menu_botonera_preguntator->setPosition(Xpreguntator,yPreguntator);
        //---------------------preguntator-------------//
        
        //---------------------armame-------------//                                             );
        menu_botonera_armame->setScaleX(escala);
        menu_botonera_armame->setScaleY(escala);
        menu_botonera_armame->setAnchorPoint(Vec2(0, 1));
        menu_botonera_armame->setPosition(
                                          (visibleSize.width/2)+(margen4botones/2),
                                          menu_botonera_preguntator->getPosition().y
                                          );
        //---------------------armame-------------//
        
        //---------------------dimeketekito-------------//                                                 );
        menu_botonera_dimeketekito->setScaleX(escala);
        menu_botonera_dimeketekito->setScaleY(escala);
        menu_botonera_dimeketekito->setAnchorPoint(Vec2(0, 1));
        menu_botonera_dimeketekito->setPosition(
                                                menu_botonera_preguntator->getPosition().x,
                                                (menu_botonera_dimeketekito->getContentSize().height*escala*2)+(margen4botones)
                                                );
        //---------------------dimeketekito-------------//
        //---------------------akuerdate-------------//
        menu_botonera_akuerdate->setScaleX(escala);
        menu_botonera_akuerdate->setScaleY(escala);
        menu_botonera_akuerdate->setAnchorPoint(Vec2(0, 1));
        menu_botonera_akuerdate->setPosition(
                                             menu_botonera_armame->getPosition().x,
                                             menu_botonera_dimeketekito->getPosition().y
                                             );

        //---------------------akuerdate-------------//
        //menu superior
        //---------------------logo-------------//
        menu_bttop_logo->setScaleX(escala);
        menu_bttop_logo->setScaleY(escala);
        menu_bttop_logo->setAnchorPoint(Vec2(0, 1));
        menu_bttop_logo->setPosition(
                                     (menu_botonera_preguntator->getPosition().x),
                                     (visibleSize.height-(margen4botones/5))
                                     );
        //---------------------logo-------------//
        //---------------------murcielago-------------//
        menu_bttop_murcielago->setScaleX(escala);
        menu_bttop_murcielago->setScaleY(escala);
        menu_bttop_murcielago->setAnchorPoint(Vec2(0, 1));
        menu_bttop_murcielago->setPosition(
                                           (menu_bttop_logo->getPosition().x)+(menu_bttop_logo->getContentSize().width*escala)+(margen4botones/2),
                                           (visibleSize.height)+((menu_bttop_murcielago->getContentSize().height*escala)*0.4)
                                           );
        //---------------------murcielago-------------//
        
        //---------------------mimostro-------------//                                           );
        menu_bttop_mimostro->setScaleX(escala);
        menu_bttop_mimostro->setScaleY(escala);
        menu_bttop_mimostro->setAnchorPoint(Vec2(0, 1));
        menu_bttop_mimostro->setPosition(
                                         (menu_botonera_akuerdate->getPosition().x+menu_botonera_akuerdate->getContentSize().width*escala)-(menu_bttop_mimostro->getContentSize().width*escala),
                                         menu_bttop_logo->getPosition().y
                                         );
        //---------------------mimostro-------------//
        
        
        
        //---------------------mosterlan-------------//
        menu_bttop_mosterlan->setScaleX(escala);
        menu_bttop_mosterlan->setScaleY(escala);
        menu_bttop_mosterlan->setAnchorPoint(Vec2(0, 1));
        menu_bttop_mosterlan->setPosition(
                                          (menu_bttop_mimostro->getPosition().x-(menu_bttop_mosterlan->getContentSize().width*escala)-(margen4botones/2)),
                                          menu_bttop_logo->getPosition().y
                                          );
        //---------------------mosterlan-------------//
        
        //---------------------CONFIGURACION-------------//
        menu_bttop_config->setScaleX(escala);
        menu_bttop_config->setScaleY(escala);
        menu_bttop_config->setAnchorPoint(Vec2(0, 1));
        menu_bttop_config->setPosition(
                                       (menu_bttop_mosterlan->getPosition().x-(menu_bttop_config->getContentSize().width*escala)-(margen4botones/2)),
                                       menu_bttop_logo->getPosition().y
                                       );
        //---------------------CONFIGURACION-------------//
    }
    //MENUS PARA QUE TENGAN ANIMACION
    if(Configuracion::desarrollo)
        CCLOG("EMPIEZAN MENUS");
    /*auto menu1 = Menu::create();
    menu1->setPosition(Vec2::ZERO);
    this->addChild(menu1);*/
    
    menu_botonera_preguntator->setLocalZOrder(2);
    menu_botonera_akuerdate->setLocalZOrder(2);
    menu_botonera_dimeketekito->setLocalZOrder(2);
    menu_botonera_armame->setLocalZOrder(2);
    menu_bttop_murcielago->setLocalZOrder(2);
    menu_bttop_config->setLocalZOrder(2);
    menu_bttop_logo->setLocalZOrder(2);
    menu_bttop_mimostro->setLocalZOrder(2);
    menu_bttop_mosterlan->setLocalZOrder(2);
    
    this->addChild(menu_botonera_preguntator);
    this->addChild(menu_botonera_akuerdate);
    this->addChild(menu_botonera_dimeketekito);
    this->addChild(menu_botonera_armame);
    this->addChild(menu_bttop_murcielago);
    this->addChild(menu_bttop_config);
    this->addChild(menu_bttop_logo);
    this->addChild(menu_bttop_mimostro);
    this->addChild(menu_bttop_mosterlan);
        
    __Array *aBt1 = Array::create(menu_botonera_preguntator,Sprite::create("menu_botonera_preguntator_down.png"), NULL);
    __Array *aBt2 = Array::create(menu_botonera_akuerdate,Sprite::create("menu_botonera_akuerdate_down.png"), NULL);
    __Array *aBt3 = Array::create(menu_botonera_dimeketekito,Sprite::create("menu_botonera_dimeketekito_down.png"), NULL);
    __Array *aBt4 = Array::create(menu_botonera_armame,Sprite::create("menu_botonera_armame_down.png"), NULL);
    __Array *aBt5 = Array::create(menu_bttop_murcielago,Sprite::create("menu_bttop_murcielago.png"), NULL);
    __Array *aBt6 = Array::create(menu_bttop_config,Sprite::create("menu_bttop_config_down.png"), NULL);
    __Array *aBt7 = Array::create(menu_bttop_logo,Sprite::create("menu_bttop_logo.png"), NULL);
    __Array *aBt8 = Array::create(menu_bttop_mimostro,Sprite::create("menu_bttop_mimostro_down.png"), NULL);
    __Array *aBt9 = Array::create(menu_bttop_mosterlan,Sprite::create("menu_bttop_mosterlan_down.png"), NULL);
    
    botones = __Array::create(aBt1,aBt2,aBt3,aBt4,aBt5,aBt6,aBt7,aBt8,aBt9, NULL);
    botones->retain();
    
    
    for (int i=0;i<botones->count(); i++) {
        
        __Array *botonActual = dynamic_cast<__Array*>(botones->getObjectAtIndex(i));
        Sprite *spriteActual = dynamic_cast<Sprite*>(botonActual->getObjectAtIndex(0));
        Sprite *spriteActualDown = dynamic_cast<Sprite*>(botonActual->getObjectAtIndex(1));
        
        spriteActualDown->setScale(escala);
        spriteActualDown->setVisible(false);
        this->addChild(spriteActualDown);
        
        float x = spriteActual->getPositionX();
        float y = spriteActual->getPositionY();
        
        spriteActualDown->setAnchorPoint(spriteActual->getAnchorPoint());
        spriteActualDown->setPositionX(x);
        spriteActualDown->setPositionY(y);
    }
    
}


void HelloWorld::cargarMusica(){
    //pongo musica
    if(!Configuracion::desarrollo){
        if(!CocosDenshion::SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying()){
            CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("fondojardinmonstruos.mp3", true);
        }
    }

}

void HelloWorld::cargarTextos(){

    //_____textos cuadros
    
    label = CCLabelTTF::create(LanguageManager::getInstance()->getString("textoBotonesJuegos"), "HVD_Comic_Serif_Pro.ttf", 50*escala,CCSizeMake(516*escala, 70*escala), TextHAlignment::CENTER);
    label->setVerticalAlignment(TextVAlignment::CENTER);
    label->setAnchorPoint(Vec2(0, 1));
    label->setPosition(
                       menu_botonera_dimeketekito->getPosition().x+(470*escala),
                       menu_botonera_dimeketekito->getPosition().y-(menu_botonera_dimeketekito->getContentSize().height*escala)+(100*escala)
                       );
    label->setLocalZOrder(4);
    this->addChild(label);
    
    label2 = CCLabelTTF::create(LanguageManager::getInstance()->getString("textoBotonesJuegos"), "HVD_Comic_Serif_Pro.ttf", 50*escala,CCSizeMake(516*escala, 200*escala), TextHAlignment::CENTER);
    label2->setVerticalAlignment(TextVAlignment::TOP);
    label2->setAnchorPoint(Vec2(0, 1));
    label2->setPosition(
                        menu_botonera_akuerdate->getPosition().x+(470*escala),
                        menu_botonera_akuerdate->getPosition().y-(menu_botonera_akuerdate->getContentSize().height*escala)+(100*escala)
                        );
    label2->setLocalZOrder(4);
    this->addChild(label2);
    
    label3 = CCLabelTTF::create(LanguageManager::getInstance()->getString("textoBotonesJuegos"), "HVD_Comic_Serif_Pro.ttf", 50*escala,CCSizeMake(516*escala, 70*escala), TextHAlignment::CENTER);
    label3->setVerticalAlignment(TextVAlignment::CENTER);
    label3->setAnchorPoint(Vec2(0, 1));
    label3->setPosition(
                        menu_botonera_armame->getPosition().x+(470*escala),
                        menu_botonera_armame->getPosition().y-(menu_botonera_armame->getContentSize().height*escala)+(100*escala)
                        );
    label3->setLocalZOrder(4);
    this->addChild(label3);
    
    label4 = CCLabelTTF::create(LanguageManager::getInstance()->getString("textoBotonesJuegos"), "HVD_Comic_Serif_Pro.ttf", 50*escala,CCSizeMake(516*escala, 70*escala), TextHAlignment::CENTER);
    label4->setVerticalAlignment(TextVAlignment::CENTER);
    label4->setAnchorPoint(Vec2(0, 1));
    label4->setPosition(
                        menu_botonera_preguntator->getPosition().x+(470*escala),
                        menu_botonera_preguntator->getPosition().y-(menu_botonera_preguntator->getContentSize().height*escala)+(100*escala)
                        );
    label4->setLocalZOrder(4);
    this->addChild(label4);

}

void HelloWorld::eliminarTextosBotones() {
    
    this->removeChild(label);
    this->removeChild(label2);
    this->removeChild(label3);
    this->removeChild(label4);
    
}

void HelloWorld::loadingCallBack( cocos2d::CCObject* tex ){
}

void HelloWorld::OnAcceleration(cocos2d::Acceleration *acc, cocos2d::Event *event){
    if(Configuracion::desarrollo)
        CCLOG("z:%f x:%f y:%f", acc->z,acc->x,acc->y);
}

void HelloWorld::cargarAnimacionMurcielago(){
    
    SpriteFrameCache* frameCache = SpriteFrameCache::sharedSpriteFrameCache();
    frameCache->addSpriteFramesWithFile("pruebaAnimacionMurcielago.plist");
    
    ssMurcielago = SpriteBatchNode::create("pruebaAnimacionMurcielago.png");
    this->addChild(ssMurcielago);
    
    for(int i=1;i<=2;i++){
        __String* archivo = CCString::createWithFormat("frame%d_murcielago.png",i);
        SpriteFrame* frame = SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(archivo->getCString());
        murcielagoFrames.pushBack(frame);
    }
    __String* archivo = CCString::createWithFormat("frame%d_murcielago.png",1);
    SpriteFrame* frame = SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(archivo->getCString());
    murcielagoFrames.pushBack(frame);
    
    sMurcielgo = CCSprite::createWithSpriteFrameName("frame1_murcielago.png");
    sMurcielgo->setAnchorPoint(Vec2(0, 1));
    sMurcielgo->setPosition(
        menu_bttop_murcielago->getPositionX(),
        menu_bttop_murcielago->getPositionY()
    );
    sMurcielgo->setLocalZOrder(0);
    sMurcielgo->setScale(escala,escala);
    ssMurcielago->addChild(sMurcielgo,10);
    
    menu_bttop_murcielago->setVisible(false);
    
    
    this->schedule(schedule_selector(HelloWorld::activarAnimacionMurcielago),tiempoBatidaNormal);
    
}

void HelloWorld::activarAnimacionMurcielago(float dt){
    int dtVerdadero = (int)dt;//esto es porque a veces si tu le asignas 10 llega 10,001 o cosas asi
    int veces = 1;
    if(dtVerdadero== tiempoBatidaNormal){
        veces = aleatorioVecesAnimacionMurcielago();
        
        if(nBatidasActual==nBatidaAlasParaMovimiento){
            nBatidasActual= 0;
            desplazarMurcielago();
        }else{
            nBatidasActual++;
        }
    }
    
    if(Configuracion::desarrollo)
        CCLOG("veces %i",veces);
    
    switch (veces) {
        case 1:
            aniMurcielago = Animation::createWithSpriteFrames(murcielagoFrames,0.1f);
            accMurcielago = Sequence::create(Animate::create(aniMurcielago),NULL);
            break;
        case 2:
            aniMurcielago = Animation::createWithSpriteFrames(murcielagoFrames,0.1f);
            accMurcielago = Sequence::create(Animate::create(aniMurcielago),Animate::create(aniMurcielago),NULL);
            break;
        case 3:
            aniMurcielago = Animation::createWithSpriteFrames(murcielagoFrames,0.1f);
            accMurcielago = Sequence::create(Animate::create(aniMurcielago),Animate::create(aniMurcielago),Animate::create(aniMurcielago),NULL);
            break;
            
        default:
            break;
    }
    
    accMurcielago->retain();
    
    if(sMurcielgo->numberOfRunningActions()==0 || dtVerdadero!= tiempoBatidaNormal){
        if(!Configuracion::desarrollo){
            CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sonidoMurcielago.mp3");
        }
        sMurcielgo->runAction(accMurcielago);
    }
    else{
        sMurcielgo->stopAction(accMurcielago);
    }
    
    
}

void HelloWorld::desplazarMurcielago(){
    if(!escuchadorMurcielago){
        return;
    }else{
        escuchadorMurcielago = false;
    }
    comenzarBatidaAlas();
    float velocidad = 2;
    float tiempoMaximoAnimacion = 2;
    int animacion = Configuracion::aleatorioEnteros(1,3);//posibilidades de animacion
    while(animacion == ultimaAnimacionMurcielago){
        animacion = Configuracion::aleatorioEnteros(1,3);
    }
    ultimaAnimacionMurcielago = animacion;
    
    if(Configuracion::desarrollo){
        log("__________________________________________________________________");
        log("animacion para murcielago: %i",animacion);
        log("__________________________________________________________________");
    }
    
    //acontinuacion se listan las tres animaciones disponibles para el murcielago
    if(animacion==1){
        MoveTo *hastaArmame = MoveTo::create(velocidad/2, menu_botonera_armame->getPosition());
        RotateTo * giro180 = RotateTo::create(velocidad/2,-180);
        MoveTo *hastaOriginal = MoveTo::create(velocidad/2, sMurcielgo->getPosition());
        RotateTo * giro0 = RotateTo::create(velocidad/2, 0);
        
        sMurcielgo->runAction(Sequence::create(hastaArmame,hastaOriginal ,NULL));
        sMurcielgo->runAction(Sequence::create(giro180,giro0 ,NULL));
        tiempoMaximoAnimacion = velocidad*1.5;
        
    }else if(animacion==2){
        Vec2 fin = menu_bttop_mimostro->getPosition();
        fin.y = fin.y - ((menu_bttop_mimostro->getContentSize().height*menu_bttop_mimostro->getScale())*2);
        fin.x = fin.x + ((menu_bttop_mimostro->getContentSize().width*menu_bttop_mimostro->getScale())/**2*/);
        
        Vec2 fin2 = menu_bttop_logo->getPosition();
        fin2.y = fin2.y + ((menu_bttop_logo->getContentSize().height*menu_bttop_logo->getScale())*2);
        fin2.x = fin2.x - ((menu_bttop_logo->getContentSize().width*menu_bttop_logo->getScale())*2);
        
        
        MoveTo *hastaMiMostro = MoveTo::create(velocidad, fin);
        MoveTo *hastaLogo = MoveTo::create(velocidad, fin2);
        MoveTo *hastaOriginal = MoveTo::create(velocidad/4, sMurcielgo->getPosition());
        
        RotateTo * giro90 = RotateTo::create(velocidad/4,-60);
        RotateTo * giro180 = RotateTo::create(velocidad/4,-180);
        RotateTo * giro270 = RotateTo::create(velocidad/4,-240);
        RotateTo * giro360 = RotateTo::create(velocidad/4, -360);
        RotateTo * giro0 = RotateTo::create(0, 0);
        
        
        
        
        sMurcielgo->runAction(Sequence::create(hastaMiMostro,DelayTime::create(velocidad*2),hastaLogo,hastaOriginal ,NULL));
        sMurcielgo->runAction(Sequence::create(giro90,DelayTime::create(velocidad/4*2),giro180,DelayTime::create(velocidad*2),giro270,DelayTime::create(velocidad/4*2),giro360,giro0,NULL));
        tiempoMaximoAnimacion = velocidad * 5;
    }else if(animacion==3){
        Vec2 fin1 = visibleSize;
        fin1.y = (visibleSize.height/2)*-1;
        fin1.x = 0;
        
        MoveTo *hastaFin1 = MoveTo::create(velocidad, fin1);
        RotateTo * giro180 = RotateTo::create(velocidad/4,-180);
        MoveTo *hastaOriginal = MoveTo::create(velocidad, sMurcielgo->getPosition());
        RotateTo * giro0 = RotateTo::create(velocidad/4, 0);
        
        sMurcielgo->runAction(Sequence::create(hastaFin1,hastaOriginal ,NULL));
        sMurcielgo->runAction(Sequence::create(DelayTime::create(velocidad),giro180,DelayTime::create(velocidad),giro0 ,NULL));
        tiempoMaximoAnimacion = velocidad * 3;
    }
    
    //termino de batir alas
    CallFunc *runCallback = CallFunc::create(CC_CALLBACK_0(HelloWorld::terminarBatidaAlas, this));
    runAction(Sequence::create(DelayTime::create(tiempoMaximoAnimacion),runCallback,NULL));
}

void HelloWorld::comenzarBatidaAlas(){
    this->schedule(schedule_selector(HelloWorld::activarAnimacionMurcielago),0.5);
}

void HelloWorld::terminarBatidaAlas(){
    escuchadorMurcielago = true;
    this->schedule(schedule_selector(HelloWorld::activarAnimacionMurcielago),tiempoBatidaNormal);
}

void HelloWorld::cargarAnimacionAkuerdate(){
    
    SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();
    frameCache->addSpriteFramesWithFile("akuerdateAnimacion.plist");
    
    ssAkuerdate = SpriteBatchNode::create("akuerdateImagenAnimacion.png");
    ssAkuerdate->setLocalZOrder(10);
    this->addChild(ssAkuerdate);
    
    Vector<SpriteFrame*>  akuerdateFrames(4);
    char str[100] = {0};
    
    for(int i=1;i<=4;i++){
        sprintf(str, "akuerdate_frame%d.png", i);
        SpriteFrame* frame = frameCache->getSpriteFrameByName( str );
        akuerdateFrames.pushBack(frame);
    }
    
    sAkuerdate = CCSprite::createWithSpriteFrameName("akuerdate_frame1.png");
    sAkuerdate->setAnchorPoint(Vec2(0, 1));
    sAkuerdate->setPosition(
                            menu_botonera_akuerdate->getPositionX()+(70*escala),
                            menu_botonera_akuerdate->getPositionY()-(70*escala)
                            );
    sAkuerdate->setScale(escala,escala);
    
    
    aniAkuerdate = CCAnimation::createWithSpriteFrames(akuerdateFrames,0.2f);
    accAkuerdate = CCAnimate::create(aniAkuerdate);
    
    
    
    Animate *animacionFrame = Animate::create(aniAkuerdate);
    CallFunc *runCallback = CallFunc::create(CC_CALLBACK_0(HelloWorld::updateAnimacionAkuerdate, this));
    accAkuerdate = RepeatForever::create(Sequence::create(animacionFrame,runCallback, NULL));
    ssAkuerdate->addChild(sAkuerdate);
    accAkuerdate->retain();
}

void HelloWorld::updateAnimacionAkuerdate(){
    CCLOG("UPDATE ANIMACION AKUERDATE");
    if(menu_botonera_akuerdate->isVisible())
        sAkuerdate->stopAllActions();
}

void HelloWorld::cargarAnimacionArmame(){
    
    SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();
    frameCache->addSpriteFramesWithFile("armameAnimacion.plist");
    
    ssArmame = SpriteBatchNode::create("armameImagenAnimacion.png");
    ssArmame->setLocalZOrder(10);
    this->addChild(ssArmame);
    
    Vector<SpriteFrame*>  ArmameFrames(4);
    char str[100] = {0};
    
    for(int i=1;i<=4;i++){
        sprintf(str, "armame_frame%d.png", i);
        SpriteFrame* frame = frameCache->getSpriteFrameByName( str );
        ArmameFrames.pushBack(frame);
    }
    
    sArmame = CCSprite::createWithSpriteFrameName("armame_frame1.png");
    sArmame->setAnchorPoint(Vec2(0, 1));
    sArmame->setPosition(
                            menu_botonera_armame->getPositionX()+(70*escala),
                            menu_botonera_armame->getPositionY()+(0*escala)
                            );
    sArmame->setScale(escala,escala);
    
    
    aniArmame = CCAnimation::createWithSpriteFrames(ArmameFrames,0.2f);
    Animate *animacionFrame = Animate::create(aniArmame);
    CallFunc *runCallback = CallFunc::create(CC_CALLBACK_0(HelloWorld::updateAnimacionArmame, this));
    accArmame = RepeatForever::create(Sequence::create(animacionFrame,runCallback, NULL));
    ssArmame->addChild(sArmame);
    
    accArmame->retain();
    
}

void HelloWorld::updateAnimacionArmame(){
    CCLOG("UPDATE ANIMACION ARMAME");
    if(menu_botonera_armame->isVisible())
        sArmame->stopAllActions();
}

void HelloWorld::cargarAnimacionDimeketekito(){
    
    SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();
    frameCache->addSpriteFramesWithFile("dimeketekitoAnimacion.plist");
    
    ssDimeketekito = SpriteBatchNode::create("dimeketekitoImagenAnimacion.png");
    ssDimeketekito->setLocalZOrder(10);
    this->addChild(ssDimeketekito);
    
    Vector<SpriteFrame*>  DimeketekitoFrames(4);
    char str[100] = {0};
    
    for(int i=1;i<=4;i++){
        sprintf(str, "dimeketekito_frame%d.png", i);
        SpriteFrame* frame = frameCache->getSpriteFrameByName( str );
        DimeketekitoFrames.pushBack(frame);
    }
    
    sDimeketekito = CCSprite::createWithSpriteFrameName("dimeketekito_frame1.png");
    sDimeketekito->setAnchorPoint(Vec2(0, 1));
    sDimeketekito->setPosition(
                         menu_botonera_dimeketekito->getPositionX()+(70*escala),
                         menu_botonera_dimeketekito->getPositionY()-(70*escala)
                         );
    sDimeketekito->setScale(escala,escala);
    
    
    aniDimeketekito = CCAnimation::createWithSpriteFrames(DimeketekitoFrames,0.2f);
    Animate *animacionFrame = Animate::create(aniDimeketekito);
    CallFunc *runCallback = CallFunc::create(CC_CALLBACK_0(HelloWorld::updateAnimacionDimeketekito, this));
    accDimeketekito = RepeatForever::create(Sequence::create(animacionFrame,runCallback, NULL));
    ssDimeketekito->addChild(sDimeketekito);
    
    accDimeketekito->retain();
    
}

void HelloWorld::updateAnimacionDimeketekito(){
    CCLOG("UPDATE ANIMACION DIMEKETEKITO");
    if(menu_botonera_dimeketekito->isVisible())
        sDimeketekito->stopAllActions();
}




void HelloWorld::cargarAnimacionPreguntator(){
    
    SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();
    frameCache->addSpriteFramesWithFile("preguntatorAnimacion.plist");
    
    ssPreguntator = SpriteBatchNode::create("preguntatorImagenAnimacion.png");
    ssPreguntator->setLocalZOrder(10);
    this->addChild(ssPreguntator);
    
    Vector<SpriteFrame*>  PreguntatorFrames(5);
    char str[100] = {0};
    
    for(int i=1;i<=5;i++){
        sprintf(str, "preguntator_frame%d.png", i);
        SpriteFrame* frame = frameCache->getSpriteFrameByName( str );
        PreguntatorFrames.pushBack(frame);
    }
    
    sPreguntator = CCSprite::createWithSpriteFrameName("preguntator_frame1.png");
    sPreguntator->setAnchorPoint(Vec2(0, 1));
    sPreguntator->setPosition(
        menu_botonera_preguntator->getPositionX()+(50*escala),
        menu_botonera_preguntator->getPositionY()-(40*escala)
    );
    sPreguntator->setScale(escala,escala);
    
    
    aniPreguntator = CCAnimation::createWithSpriteFrames(PreguntatorFrames,0.2f);
    Animate *animacionFrame = Animate::create(aniPreguntator);
    CallFunc *runCallback = CallFunc::create(CC_CALLBACK_0(HelloWorld::updateAnimacionPreguntator, this));
    accPreguntator = RepeatForever::create(Sequence::create(animacionFrame,runCallback, NULL));
    ssPreguntator->addChild(sPreguntator);
    
    
    accPreguntator->retain();
}

void HelloWorld::updateAnimacionPreguntator(){
    CCLOG("UPDATE ANIMACION PREGUNTATOR");
    if(menu_botonera_preguntator->isVisible())
        sPreguntator->stopAllActions();
}


void HelloWorld::cargarAnimacionConfiguracion(){
    
    SpriteFrameCache* frameCache = SpriteFrameCache::sharedSpriteFrameCache();
    frameCache->addSpriteFramesWithFile("configuracionAnimacion.plist");
    
    ssConfiguracion = SpriteBatchNode::create("configuracionImagenAnimacion.png");
    ssConfiguracion->setLocalZOrder(10);
    this->addChild(ssConfiguracion);
    
    Vector<SpriteFrame*>  ConfiguracionFrames(3);
    for(int i=1;i<=3;i++){
        __String* archivo = __String::createWithFormat("configuracion_frame%d.png",i);
        SpriteFrame* frame = SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(archivo->getCString());
        ConfiguracionFrames.pushBack(frame);
    }
    
    sConfiguracion = CCSprite::createWithSpriteFrameName("configuracion_frame1.png");
    sConfiguracion->setAnchorPoint(Vec2(0, 1));
    sConfiguracion->setPosition(
                         menu_bttop_config->getPositionX()+(0*escala),
                         menu_bttop_config->getPositionY()-(0*escala)
                         );
    sConfiguracion->setScale(escala,escala);
    
    
    aniConfiguracion = CCAnimation::createWithSpriteFrames(ConfiguracionFrames,0.2f);
    Animate *animacionFrame = Animate::create(aniConfiguracion);
    CallFunc *runCallback = CallFunc::create(CC_CALLBACK_0(HelloWorld::updateAnimacionConfiguracion, this));
    accConfiguracion = RepeatForever::create(Sequence::create(animacionFrame,runCallback, NULL));
    ssConfiguracion->addChild(sConfiguracion);
    accConfiguracion->retain();
}

void HelloWorld::updateAnimacionConfiguracion(){
    CCLOG("UPDATE ANIMACION CONFIGURACION");
    if(menu_bttop_config->isVisible())
        sConfiguracion->stopAllActions();
}




void HelloWorld::cargarAnimacionMimostro(){
    
    SpriteFrameCache* frameCache = SpriteFrameCache::sharedSpriteFrameCache();
    frameCache->addSpriteFramesWithFile("mimostroAnimacion.plist");
    
    ssMimostro = SpriteBatchNode::create("mimostroImagenAnimacion.png");
    ssMimostro->setLocalZOrder(10);
    this->addChild(ssMimostro);
    
    Vector<SpriteFrame*>  MimostroFrames(2);
    for(int i=1;i<=2;i++){
        CCString* archivo = CCString::createWithFormat("mimostro_frame%d.png",i);
        SpriteFrame* frame = SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(archivo->getCString());
        MimostroFrames.pushBack(frame);
    }
    
    sMimostro = CCSprite::createWithSpriteFrameName("mimostro_frame1.png");
    sMimostro->setAnchorPoint(Vec2(0, 1));
    sMimostro->setPosition(
                                menu_bttop_mimostro->getPositionX()+((menu_bttop_mimostro->getContentSize().width/4)*escala),
                                menu_bttop_mimostro->getPositionY()-(20*escala)
                                );
    sMimostro->setScale(escala,escala);
    
    
    aniMimostro = CCAnimation::createWithSpriteFrames(MimostroFrames,0.2f);
    accMimostro = CCAnimate::create(aniMimostro);
    ssMimostro->addChild(sMimostro);
    
    accMimostro->retain();
}

void HelloWorld::cargarAnimacionMosterland(){
    
    SpriteFrameCache* frameCache = SpriteFrameCache::sharedSpriteFrameCache();
    frameCache->addSpriteFramesWithFile("mosterlandAnimacion.plist");

    ssMosterland = SpriteBatchNode::create("mosterlandImagenAnimacion.png");
    ssMosterland->setLocalZOrder(10);
    this->addChild(ssMosterland);

    Vector<SpriteFrame*>  MosterlandFrames(4);
    for(int i=1;i<=4;i++){
        __String* archivo = CCString::createWithFormat("mosterland_frame%d.png",i);
        SpriteFrame* frame = SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(archivo->getCString());
        MosterlandFrames.pushBack(frame);
    }
    
    sMosterland = CCSprite::createWithSpriteFrameName("mosterland_frame1.png");
    sMosterland->setAnchorPoint(Vec2(0, 1));
    sMosterland->setPosition(
                           menu_bttop_mosterlan->getPositionX()+(0*escala),
                           menu_bttop_mosterlan->getPositionY()-(0*escala)
                           );
    sMosterland->setScale(escala,escala);
    
    
    aniMosterland = CCAnimation::createWithSpriteFrames(MosterlandFrames,0.1f);
    Animate *animacionFrames = Animate::create(aniMosterland);
    CallFunc *runCallback = CallFunc::create(CC_CALLBACK_0(HelloWorld::finAnimacionMosterland, this));
    accMosterland = Sequence::create(animacionFrames,runCallback,NULL);
    
    //ocultar al terminar
    ssMosterland->setVisible(false);
    
    ssMosterland->addChild(sMosterland);
    
    accMosterland->retain();
}






//AKUERDATE
void HelloWorld::activarAnimacionAkuerdate(float dt){
    if(sAkuerdate->numberOfRunningActions()==0){
        sAkuerdate->runAction(accAkuerdate);
    }
}

//ARMAME
void HelloWorld::activarAnimacionArmame(float dt){
    if(sArmame->numberOfRunningActions()==0){
        sArmame->runAction(accArmame);
    }
}

//DIMEKETEKITO
void HelloWorld::activarAnimacionDimeketekito(float dt){
    if(sDimeketekito->numberOfRunningActions()==0){
        sDimeketekito->runAction(accDimeketekito);
    }
}

//PREGUNTATOR
void HelloWorld::activarAnimacionPreguntator(float dt){
    if(sPreguntator->numberOfRunningActions()==0){
        sPreguntator->runAction(accPreguntator);
    }
}



//CONFIGURACION
void HelloWorld::activarAnimacionConfiguracion(float dt){
    if(sConfiguracion->numberOfRunningActions()==0){
        sConfiguracion->runAction(accConfiguracion);
    }
}

//MIMOSTRO
void HelloWorld::activarAnimacionMimostro(float dt){
    if(sMimostro->numberOfRunningActions()==0){
        sMimostro->runAction(accMimostro);
    }
}

//MOSTERLAND
void HelloWorld::activarAnimacionMosterland(float dt){
    if(sMosterland->numberOfRunningActions()==0){
        ssMosterland->setVisible(true);
        sMosterland->runAction(accMosterland);
    }
}

void HelloWorld::finAnimacionMosterland(){
    ssMosterland->setVisible(false);
    if(MostrarMosterlandFinAnimacion){
        menu_bttop_mosterlan->setVisible(true);
        MostrarMosterlandFinAnimacion = false;
    }
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::irJuego(Ref* pSender){

}

void HelloWorld::fijarFondo(){
    auto fondo = Sprite::create("menu_bg_i.png");
    if(escalaAncha>escalaAlta){
        fondo->setScaleX(escalaAncha);
        fondo->setScaleY(escalaAncha);
    }else{
        fondo->setScaleX(escalaAlta);
        fondo->setScaleY(escalaAlta);
    }
    fondo->setAnchorPoint(Vec2(1, 0));
    fondo->setPosition(visibleSize.width/2, 0);
    fondo->setZOrder(-1);
    this->addChild(fondo);
    
    auto fondo_u = Sprite::create("menu_bg_d.png");
    if(escalaAncha>escalaAlta){
        fondo_u->setScaleX(escalaAncha);
        fondo_u->setScaleY(escalaAncha);
    }else{
        fondo_u->setScaleX(escalaAlta);
        fondo_u->setScaleY(escalaAlta);
    }
    fondo_u->setAnchorPoint(Vec2(0, 0));
    fondo_u->setPosition(visibleSize.width/2, 0);
    fondo_u->setZOrder(-1);
    this->addChild(fondo_u);
    
}

void HelloWorld::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event){
    if(keyCode == cocos2d::EventKeyboard::KeyCode::KEY_ESCAPE){
        if(!salir){
            capaSalir = LayerColor::create(ccc4(0, 0, 0, 120));
            capaSalir->setContentSize(Size(visibleSize.width, visibleSize.height));
            capaSalir->setPosition(
                (visibleSize.width/2)-(capaSalir->getContentSize().width/2),
                (visibleSize.height/2)-(capaSalir->getContentSize().height/2)
            );
            capaSalir->setVisible(true);
            addChild(capaSalir,999);
            
            labelCapaSalir = Label::create(LanguageManager::getInstance()->getString("VENT_SALIR"), "HVD_Comic_Serif_Pro.ttf", 80*escala,CCSizeMake(visibleSize.width, visibleSize.height), TextHAlignment::CENTER);
            labelCapaSalir->setColor(ccc3(255,255,255));
            labelCapaSalir->setVerticalAlignment(TextVAlignment::CENTER);
            labelCapaSalir->setAnchorPoint(Vec2(0, 0));
            labelCapaSalir->setPosition(0,0);
            capaSalir->addChild(labelCapaSalir,1000);
            salir = true;
            
            CallFunc *runCallback = CallFunc::create(CC_CALLBACK_0(HelloWorld::quitarCapaSalir, this));
            this->runAction(Sequence::create(DelayTime::create(1.0), runCallback, NULL));
            
            
        }else{
            Director::getInstance()->end();
        }
    }else if (keyCode == EventKeyboard::KeyCode::KEY_HOME){
        if(Configuracion::desarrollo)
            CCLOG("You pressed home button");
        // pause the game
    }else{
        MessageBox("TECLA PULSADA","TECLA");
    }
    
    
}




bool HelloWorld::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
    comprobarPulsado(touch,1);
    
    if(Configuracion::desarrollo)
        log("BEGAN %f %f",touch->getLocation().x,touch->getLocation().y);
    
    comprobarToques(1, touch);
    
    return  true;
}
void HelloWorld::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event)
{
    comprobarPulsado(touch,2);
    
    if(Configuracion::desarrollo)
        log("MOVED %f %f ",touch->getLocation().x,touch->getLocation().y);
    comprobarToques(1, touch);
}
void HelloWorld::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
{
    comprobarPulsado(touch,3);
    
    if(Configuracion::desarrollo)
        log("ENDED %f %f ",touch->getLocation().x,touch->getLocation().y);
    
    
    comprobarToques(2, touch);
    
    
    /*CCFiniteTimeAction* actionMove = CCMoveBy::create((float)0.3,ccp(xOriginal-mySprite->getPosition().x,yOriginal-mySprite->getPosition().y));
     mySprite->runAction( CCSequence::create(actionMove,NULL) );
     */
}

/*
 * lanzado de animaciones y entrado en juego
 */
void HelloWorld::comprobarToques(int modo, cocos2d::Touch *touch){
    //modo 1 no entra en el juego MODO 2 entra
    
    //PREGUNTATOR
    if(comprobarToque(touch,menu_botonera_preguntator)){
        if(Configuracion::desarrollo)
            CCLOG("PREGUNTATOR");
        HelloWorld::activarAnimacionPreguntator(0.0);
        
        if(modo==2){
            if(!salir){
                salir = true;
                CallFunc *runCallback = CallFunc::create(CC_CALLBACK_0(HelloWorld::irEscenaPreguntator, this));
                this->runAction(Sequence::create(DelayTime::create(0.7),runCallback,NULL));
            }
        }
    }else if(comprobarToque(touch,menu_botonera_armame)){
        if(Configuracion::desarrollo)
            CCLOG("ARMAME");
        HelloWorld::activarAnimacionArmame(0.0);
        
        if(modo==2){
            if(!salir){
                salir = true;
                CallFunc *runCallback = CallFunc::create(CC_CALLBACK_0(HelloWorld::irEscenaArmame, this));
                this->runAction(Sequence::create(DelayTime::create(0.7),runCallback,NULL));
            }
        }
    }else if(comprobarToque(touch,menu_botonera_akuerdate)){
        if(Configuracion::desarrollo)
            CCLOG("AKUERDATE");
        HelloWorld::activarAnimacionAkuerdate(0.0);
        
        if(modo==2){
            if(!salir){
                salir = true;
                CallFunc *runCallback = CallFunc::create(CC_CALLBACK_0(HelloWorld::irEscenaAkuerdate, this));
                this->runAction(Sequence::create(DelayTime::create(0.7),runCallback,NULL));
            }
        }
    }else if(comprobarToque(touch,menu_botonera_dimeketekito)){
        if(Configuracion::desarrollo)
            CCLOG("DIMEKETEKITO");
        HelloWorld::activarAnimacionDimeketekito(0.0);
        
        if(modo==2){
            if(!salir){
                salir = true;
                CallFunc *runCallback = CallFunc::create(CC_CALLBACK_0(HelloWorld::irEscenaDimeketekito, this));
                this->runAction(Sequence::create(DelayTime::create(0.7),runCallback,NULL));
            }
        }
    }else if(comprobarToque(touch,menu_bttop_config)){
        if(Configuracion::desarrollo)
            CCLOG("CONFIGURACION");
        HelloWorld::activarAnimacionConfiguracion(0.0);
        
        if(modo==2){
            if(!salir){
                salir = true;
                CallFunc *runCallback = CallFunc::create(CC_CALLBACK_0(HelloWorld::irEscenaAjustes, this));
                this->runAction(Sequence::create(DelayTime::create(0.7),runCallback,NULL));
            }
        }
    }else if(comprobarToque(touch,menu_bttop_mimostro)){
        if(Configuracion::desarrollo)
            CCLOG("MIMOSTRO");
        HelloWorld::activarAnimacionMimostro(0.0);
        
        if(modo==2){
            if(!salir){
                salir = true;
                CallFunc *runCallback = CallFunc::create(CC_CALLBACK_0(HelloWorld::irEscenaMiMostro, this));
                this->runAction(Sequence::create(DelayTime::create(0.7),runCallback,NULL));
            }
        }
    }else if(comprobarToque(touch,menu_bttop_mosterlan)){
        if(Configuracion::desarrollo)
            CCLOG("MOSTERLAND");
        HelloWorld::activarAnimacionMosterland(0.0);
        
        if(modo==2){
            if(!salir){
                salir = true;
                CallFunc *runCallback = CallFunc::create(CC_CALLBACK_0(HelloWorld::irEscenaMosterland, this));
                this->runAction(Sequence::create(DelayTime::create(0.7),runCallback,NULL));
            }
        }
    }else if(comprobarToque(touch,menu_bttop_logo)){
        if(Configuracion::desarrollo)
            CCLOG("LOGO");
        
        
        if(modo==2){
            if(!salir){
                salir = true;
                CallFunc *runCallback = CallFunc::create(CC_CALLBACK_0(HelloWorld::irEscenaAcerca, this));
                this->runAction(Sequence::create(DelayTime::create(0.0),runCallback,NULL));
            }
        }
    }else if(comprobarToque(touch,menu_bttop_murcielago)){
        desplazarMurcielago();
    }else{
        
    }

    
    if(!Configuracion::desarrollo&&salir){
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("tambores_3.mp3");
    }

}


/*
 *  lanzado de animaciones y entrado en juego
 */
void HelloWorld::comprobarPulsado(cocos2d::Touch *touch,int modo){

    
    
    for (int i=0;i<botones->count(); i++) {
        
        __Array *botonActual = dynamic_cast<__Array*>(botones->getObjectAtIndex(i));
        Sprite *spriteActual = dynamic_cast<Sprite*>(botonActual->getObjectAtIndex(0));
        Sprite *spriteActualDown = dynamic_cast<Sprite*>(botonActual->getObjectAtIndex(1));
        
        bool toque = comprobarToque(touch, spriteActual);
        switch (modo) {
            case 1:
                //began
                if(toque){
                    if(spriteActual->isVisible()){
                        spriteActualDown->setVisible(true);
                        spriteActual->setVisible(false);
                    }
                }
                break;
            case 2:
                //moved
                if(toque){
                    if(spriteActual->isVisible()){
                        spriteActualDown->setVisible(true);
                        spriteActual->setVisible(false);
                    }
                }else{
                    if(spriteActualDown->isVisible()){
                        spriteActualDown->setVisible(false);
                        if(spriteActual->_ID==menu_bttop_mosterlan->_ID){
                            //excepcion de mostrarlan que la animacio no se hace en un elemento aparte sino el boton entero es animado y no va independiente la base del boton con el elemento animado como ocurre en los demas.
                            MostrarMosterlandFinAnimacion = true;
                        }else{
                            spriteActual->setVisible(true);
                        }
                    }
                }
                break;
            case 3:
                //ended

                if(spriteActualDown->isVisible()){
                    spriteActualDown->setVisible(false);
                    spriteActual->setVisible(true);
                }
                break;
        }
        
    }

}






void HelloWorld::fuera(Ref* pSender)
{
    exit(0);
}

void HelloWorld::quitarCapaSalir(){
    CCFadeOut *fade = CCFadeOut::create(0.5f);
    CCFadeOut *fade1 = CCFadeOut::create(0.5f);
    capaSalir->runAction(fade1);
    labelCapaSalir->runAction(fade);
    
    CallFunc *runCallback = CallFunc::create(CC_CALLBACK_0(HelloWorld::quitarCapaSalir, this));
    this->runAction(Sequence::create(DelayTime::create(0.7),HelloWorld::salir=false, NULL));
    
}



//ESCENAS NAVEGACION
void HelloWorld::irEscenaPreguntator(){
    CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
    
//    auto director = Director::getInstance();
//    director->setAnimationInterval(1.0 / 60);
//    auto scene = Preguntator::createScene();
//    auto transition = TransitionFade::create(1.0f, scene);
//    director->replaceScene(transition);
    
    auto director = Director::getInstance();
    auto scene = Preguntator::createScene();
    director->pushScene(scene);
    
}

void HelloWorld::irEscenaAkuerdate(){
    CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
    
//    auto director = Director::getInstance();
//    director->setAnimationInterval(1.0 / 60);
//    auto scene = Akuerdate::createScene();
//    auto transition = TransitionFade::create(1.0f, scene);
//    director->replaceScene(transition);
    
    auto director = Director::getInstance();
    auto scene = Akuerdate::createScene();
    director->pushScene(scene);
    
}
void HelloWorld::irEscenaArmame(){
    CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
    
//    auto director = Director::getInstance();
//    director->setAnimationInterval(1.0 / 60);
//    auto scene = Armame::createScene();
//    auto transition = TransitionFade::create(1.0f, scene);
//    director->replaceScene(transition);
    
    auto director = Director::getInstance();
    auto scene = Armame::createScene();
    director->pushScene(scene);
    
}
void HelloWorld::irEscenaDimeketekito(){
    CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
    
//    auto director = Director::getInstance();
//    director->setAnimationInterval(1.0 / 60);
//    auto scene = Dimeketekito::createScene();
//    auto transition = TransitionFade::create(1.0f, scene);
//    director->replaceScene(scene);
    
    auto director = Director::getInstance();
    auto scene = Dimeketekito::createScene();
    director->pushScene(scene);
    
}

void HelloWorld::irEscenaAjustes(){
    Ajustes::desdeEscena = Ajustes::desdeMenu;
    
//    auto director = Director::getInstance();
//    director->setAnimationInterval(1.0 / 60);
//    auto scene = Ajustes::createScene();
//    auto transition = TransitionFade::create(1.0f, scene);
//    director->replaceScene(transition);
    
    auto director = Director::getInstance();
    auto scene = Ajustes::createScene();
    director->pushScene(scene);
    
}

void HelloWorld::irEscenaMiMostro(){
    CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
    
//    auto director = Director::getInstance();
//    director->setAnimationInterval(1.0 / 60);
//    auto scene = MiMostro::createScene();
//    auto transition = TransitionFade::create(1.0f, scene);
//    director->replaceScene(transition);
    
    auto director = Director::getInstance();
    auto scene = MiMostro::createScene();
    director->pushScene(scene);
    
}

void HelloWorld::irEscenaMosterland(){
    CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
    
//    auto director = Director::getInstance();
//    director->setAnimationInterval(1.0 / 60);
//    auto scene = Mosterland::createScene();
//    auto transition = TransitionFade::create(1.0f, scene);
//    director->replaceScene(transition);
    
    auto director = Director::getInstance();
    auto scene = Mosterland::createScene();
    director->pushScene(scene);
    
}

void HelloWorld::irEscenaAcerca(){
    CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
    
//    Acerca::desdeEscena = Acerca::desdeMenu;
//    auto director = Director::getInstance();
//    director->setAnimationInterval(1.0 / 60);
//    auto scene = Acerca::createScene();
//    auto transition = TransitionFade::create(1.0f, scene);
//    director->replaceScene(transition);
    
    auto director = Director::getInstance();
    auto scene = Acerca::createScene();
    director->pushScene(scene);
    
}


int HelloWorld::aleatorioVecesAnimacionMurcielago(){
  
    int max = 3;
    int min = 1;
    srand(time(0));
    
    int randNum = rand()%(max-min + 1) + min;
    randNum = rand()%(max-min + 1) + min;
    while(antAleatorio == randNum){
        randNum = rand()%(max-min + 1) + min;
        if(Configuracion::desarrollo)
            CCLOG("%i",randNum);
    }
    
    antAleatorio = randNum;
    return randNum;
}

bool HelloWorld::comprobarToque(Touch *touch,Node *sprite){
    
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

void HelloWorld::getIdMiMostro() {
    
    const char* idDevice = Configuracion::getIDDEVICE();
    __String *url = __String::createWithFormat("http://mostrosity.com/SI2-API/idMostro.php?dispositivo=%s",idDevice);
    
    network::HttpRequest *request = new network::HttpRequest();
    request->setUrl(url->getCString());
    request->setRequestType(network::HttpRequest::Type::GET);
    request->setResponseCallback([this](network::HttpClient *sender, network::HttpResponse *response) {
        
        std::vector<char>* respuesta = response->getResponseData();
        
        if(respuesta->size()!=0){
            
            Configuracion *config = new Configuracion();
            Json *jsonRespuesta = Json_create(config->charTochar(respuesta));
            
            int error = jsonRespuesta->child->valueInt;
            
            if (error == 0) {

                __String *miId = __String::create(jsonRespuesta->child->next->valueString);
                std::string myIdString = miId->getCString();
                Configuracion::idMiMostro = myIdString;
                
                CCLOG("error: 0");
                CCLOG("%s", Configuracion::idMiMostro.c_str());
            } /*else {
                CCLOG("error: 1");
                __String *error = __String::create(jsonRespuesta->child->next->valueString);
                std::string errorMessage = error->getCString();
                CCLOG("%s", errorMessage.c_str());
            }*/
            
        }
        
    });
    
    network::HttpClient::getInstance()->send(request);

}
