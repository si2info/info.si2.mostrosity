#include "SelectorProfesor.h"
#include "HelloWorldScene.h"
#include "Preguntator.h"
#include "Configuracion.h"
#include "LanguageManager.h"
#include "SimpleAudioEngine.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "JniLink.h"
#endif


USING_NS_CC;

Scene* SelectorProfesor::createScene()
{
    
    auto scene = Scene::create();
    
    auto layer = SelectorProfesor::create();
    scene->addChild(layer);
    return scene;
}

bool SelectorProfesor::init()
{
    
    if ( !Layer::init() )
    {
        return false;
    }
    this->setKeypadEnabled(true);
    
    visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    relacion = visibleSize.width/visibleSize.height;
    escalaAncha = visibleSize.width/2560;
    escalaAlta = visibleSize.height/1600;
    if(escalaAncha>escalaAlta){
        escala = escalaAncha;
    }else{
        escala = escalaAlta;
    }
    margenCE = margen * escala;

    
    fijarFondo();
    initMusica();
    initTitulo();
    initParrafos();
    initPiesProfesores();
    initProfesores();
    
    
    return true;
}

void SelectorProfesor::onExitTransitionDidStart() {
    
    CCDirector::sharedDirector()->purgeCachedData();
    
    CCTextureCache::sharedTextureCache()->removeUnusedTextures();
    CCTextureCache::sharedTextureCache()->removeAllTextures();
    CCTextureCache::purgeSharedTextureCache();
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames();
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFrames();
    CCSpriteFrameCache::purgeSharedSpriteFrameCache();
    
    SpriteFrameCache::getInstance()->removeUnusedSpriteFrames();
    
}

void SelectorProfesor::fijarFondo(){
    LayerColor *capaFondo = LayerColor::create(Color4B(25,78,121,255), visibleSize.width, visibleSize.height);
    capaFondo->setPosition(0,0);
    this->addChild(capaFondo,-1);
    
    auto fondoTemp1 = Sprite::create("mostrosity_dientes_d.png");
    fondoTemp1->setScale(escala);
    fondoTemp1->setAnchorPoint(Vec2(0,0.5));
    fondoTemp1->setPosition(visibleSize.width/2,visibleSize.height/2);
    this->addChild(fondoTemp1);
    
    
    
    auto fondoTemp2 = Sprite::create("mostrosity_dientes_i.png");
    fondoTemp2->setScale(escala);
    fondoTemp2->setAnchorPoint(Vec2(1,0.5));
    fondoTemp2->setPosition(visibleSize.width/2,visibleSize.height/2);
    this->addChild(fondoTemp2);
}

void SelectorProfesor::irAMenu()
{
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    
    auto director = Director::getInstance();
    director->setAnimationInterval(1.0 / 60);
    auto scene = HelloWorld::createScene();
    auto transition = TransitionFade::create(1.0f, scene);
    director->replaceScene(transition);
    
}

void SelectorProfesor::initMusica(){

    //pongo musica
    if(!CocosDenshion::SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying()){
        CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("sintonia_mimostro.mp3", true);
    }
}

void SelectorProfesor::initTitulo(){
    //cargando titulo
    titulo = CCLabelTTF::create(LanguageManager::getInstance()->getString("SELEC_PROF_01"), "HVD_Comic_Serif_Pro.ttf", 120*escala,Size(visibleSize.width-(margenCE*2), 300*escala), TextHAlignment::CENTER);
    titulo->setVerticalAlignment(cocos2d::TextVAlignment::CENTER);
    titulo->setAnchorPoint(Vec2(0.5, 1));
    titulo->setPosition(visibleSize.width/2,visibleSize.height-(50*escala));
    titulo->setFontSize(120*escala);
    titulo->setColor(Color3B(255,255,255));
    titulo->retain();
    this->addChild(titulo, 1);
    
}

void SelectorProfesor::initParrafos(){
    
    //parrafos
    parrafoCentral = CCLabelTTF::create(LanguageManager::getInstance()->getString("SELEC_PROF_02"),
    		"HVD_Comic_Serif_Pro.ttf", 60*escala,Size(visibleSize.width-(margenCE*2), 350*escala), TextHAlignment::CENTER);
    parrafoCentral->setVerticalAlignment(cocos2d::TextVAlignment::CENTER);
    parrafoCentral->setAnchorPoint(Vec2(0.5, 1));
    parrafoCentral->setPosition(visibleSize.width/2,titulo->getPositionY()-(titulo->getContentSize().height*titulo->getScale()));
    parrafoCentral->setFontSize(60*escala);
    parrafoCentral->setColor(Color3B(255,255,255));
    parrafoCentral->retain();
    this->addChild(parrafoCentral, 1);
    
}


void SelectorProfesor::initProfesores(){
    //preguntator_profesor.png
    menu = Menu::create(NULL);
    menu->setPosition(Vec2::ZERO);
    menu->retain();
    addChild(menu);
    
    btProfesor1 = MenuItemImage::create("preguntator_profesor.png","preguntator_profesor.png",CC_CALLBACK_1(SelectorProfesor::selectorGeneral, this));
    btProfesor1->setScale(escala);
    btProfesor1->setAnchorPoint(Vec2(0.5,0));
    btProfesor1->setPosition(visibleSize.width/4*1,pieProfesor1->getPositionY());
    btProfesor1->setColor(Color3B(255,255,255));
    menu->addChild(btProfesor1);
    
    
    btProfesor2 = MenuItemImage::create("profesor_hipster.png","profesor_hipster.png",CC_CALLBACK_1(SelectorProfesor::selectorGeneral, this));
    btProfesor2->setScale(escala);
    btProfesor2->setAnchorPoint(Vec2(0.5,0));
    btProfesor2->setPosition(visibleSize.width/4*3,pieProfesor2->getPositionY());
    btProfesor2->setColor(Color3B(255,255,255));
    menu->addChild(btProfesor2);
    
}

void SelectorProfesor::selectorGeneral(Ref *pSender){
    float velocidad = 1;//velocidad con la que se realizan las animaciones.
    LabelTTF *pieElegido = NULL;
    LabelTTF *pieDescartado = NULL;
    MenuItem *profesorDescartado = NULL;
    MenuItem *profesorElegido = dynamic_cast<MenuItem*>(pSender);;
    MoveTo *movimientoFuera = NULL;
    
	UserDefault *preferencias = UserDefault::getInstance();
	if(pSender == btProfesor1){
		preferencias->setIntegerForKey("profesor",1);
        Configuracion::profesor = 1;
        pieElegido = pieProfesor1;
        pieDescartado = pieProfesor2;
        profesorDescartado = btProfesor2;
        
        movimientoFuera = MoveTo::create(velocidad, Vec2(visibleSize.width*2,0));
	}else if(pSender == btProfesor2){
		preferencias->setIntegerForKey("profesor",2);
        Configuracion::profesor = 2;
        pieElegido = pieProfesor2;
        pieDescartado = pieProfesor1;
        profesorDescartado = btProfesor1;
        movimientoFuera = MoveTo::create(velocidad, Vec2(visibleSize.width*-1,0));
	}

    
    //desplazamiento hacia arriba de los parrafos
    titulo->runAction(MoveTo::create(velocidad, Vec2(parrafoCentral->getPositionX(),visibleSize.height*1+(titulo->getContentSize().height*titulo->getScale()))));
    parrafoCentral->runAction(MoveTo::create(velocidad, Vec2(parrafoCentral->getPositionX(),visibleSize.height*1+(parrafoCentral->getContentSize().height*parrafoCentral->getScale()))));
    
    //animo los descartados
    profesorDescartado->runAction(movimientoFuera->clone());
    pieDescartado->runAction(movimientoFuera->clone());
    
    
    //defino animacion de elegidos
    MoveTo *movimientoCentroProfesor = MoveTo::create(velocidad, Vec2(visibleSize.width/2,profesorElegido->getPositionY()+margenCE));
    MoveTo *movimientoCentroPie = MoveTo::create(velocidad, Vec2(visibleSize.width/2,pieElegido->getPositionY()+margenCE));
    ScaleTo *escaladoProfe = ScaleTo::create(velocidad,profesorElegido->getScale()*1.8);
    ScaleTo *escaladoPie = ScaleTo::create(velocidad,pieElegido->getScale()*1.8);
    
    //animo escalando y desplazando a los elegidos
    profesorElegido->runAction(movimientoCentroProfesor->clone());
    profesorElegido->runAction(escaladoProfe->clone());
    pieElegido->runAction(movimientoCentroPie->clone());
    pieElegido->runAction(escaladoPie->clone());
    
    CallFunc *runCallback = CallFunc::create(CC_CALLBACK_0(SelectorProfesor::irAMenu, this));
    runAction(Sequence::create(DelayTime::create(velocidad),runCallback, NULL));
    
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("ganar.mp3");
    
}

void SelectorProfesor::initPiesProfesores(){
    //los dos parrafos inferiores
    pieProfesor1 = CCLabelTTF::create(LanguageManager::getInstance()->getString("SELEC_PROF_NOM_01"), "HVD_Comic_Serif_Pro.ttf", 70*escala,Size((visibleSize.width/2)-margenCE, 160*escala), TextHAlignment::CENTER);
    pieProfesor1->setVerticalAlignment(cocos2d::TextVAlignment::TOP);
    pieProfesor1->setAnchorPoint(Vec2(0.5, 1));
    pieProfesor1->setPosition(visibleSize.width/4*1,(margen*escala)+(pieProfesor1->getContentSize().height*pieProfesor1->getScale()));
    pieProfesor1->setFontSize(70*escala);
    pieProfesor1->setColor(Color3B(255,255,255));
    this->addChild(pieProfesor1, 1);
    
    
    pieProfesor2 = CCLabelTTF::create(LanguageManager::getInstance()->getString("SELEC_PROF_NOM_02"), "HVD_Comic_Serif_Pro.ttf", 70*escala,Size((visibleSize.width/2)-margenCE, 160*escala), TextHAlignment::CENTER);
    pieProfesor2->setVerticalAlignment(cocos2d::TextVAlignment::TOP);
    pieProfesor2->setAnchorPoint(Vec2(0.5, 1));
    pieProfesor2->setPosition(visibleSize.width/4*3,(margen*escala)+(pieProfesor2->getContentSize().height*pieProfesor2->getScale()));
    pieProfesor2->setFontSize(70*escala);
    pieProfesor2->setColor(Color3B(255,255,255));
    this->addChild(pieProfesor2, 1);
}

