#include "Splash.h"
#include "SelectorProfesor.h"
#include "HelloWorldScene.h"
#include "Preguntator.h"
#include "Configuracion.h"
#include "LanguageManager.h"
#include "AppDelegate.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "JniLink.h"
#endif


USING_NS_CC;

Scene* Splash::createScene()
{
    
    auto scene = Scene::create();
    
    auto layer = Splash::create();
    scene->addChild(layer);
    return scene;
}

bool Splash::init()
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

    
    fijarFondo();
    fijarPublicidad();
    cargarAnimacionLogo();


    iniciarCarga();
    
    
    return true;
}


void Splash::cargarAnimacionLogo(){
    
    
    ///logo
    SpriteFrameCache* frameCache = SpriteFrameCache::sharedSpriteFrameCache();
    frameCache->addSpriteFramesWithFile("splashAnimacion.plist");
    
    ssLogo = SpriteBatchNode::create("splashImagenAnimacion.png");
    this->addChild(ssLogo);
    
    Vector<SpriteFrame*>  LogoFrames(2);
    for(int i=1;i<=2;i++){
        String* archivo = String::createWithFormat("mostrosity_splash_logo%d.png",i);
        SpriteFrame* frame = SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(archivo->getCString());
        LogoFrames.pushBack(frame);
    }
    
    sLogo = Sprite::createWithSpriteFrameName("mostrosity_splash_logo1.png");
    sLogo->setAnchorPoint(Vec2(0.5, 0));
    sLogo->setPosition(visibleSize.width/2,visibleSize.height/2);
    sLogo->setScale(escala);
    ssLogo->addChild(sLogo);
    
    //cargando
    label = CCLabelTTF::create(LanguageManager::getInstance()->getString("CARGANDO"), "HVD_Comic_Serif_Pro.ttf", 50*escala,Size(600*escala, 200*escala), TextHAlignment::LEFT);
    label->setAnchorPoint(Vec2(0.5, 1));
    label->setPosition(visibleSize.width/2,sLogo->getPositionY()-(50*escala));
    label->setFontSize(80*escala);
    label->setColor(ccc3(227,253,78));
    this->addChild(label, 1);
    
    aniLogo = Animation::createWithSpriteFrames(LogoFrames,0.2f);
    
    CallFunc *runCallback = CallFunc::create(CC_CALLBACK_0(Splash::modificarCargando, this));
    sLogo->runAction(RepeatForever::create(Animate::create(aniLogo)));
    cocos2d::Action* accLogoTexto = RepeatForever::create(Sequence::create(runCallback,DelayTime::create(0.5),NULL));
    this->runAction(accLogoTexto);
    
}

void Splash::fijarFondo(){
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

void Splash::fijarPublicidad(){
    Sprite* publicidad = Sprite::create("splash_publicidad.png");
    publicidad->setScale(escala);
    publicidad->setPosition(visibleSize.width,0);
    publicidad->setAnchorPoint(Vec2(1,0));
    this->addChild(publicidad);
    
}

void Splash::irAMenu()
{
    auto director = Director::getInstance();
    director->setAnimationInterval(1.0 / 60);

    if(Configuracion::profesor==-1){
        //aun no hay profesor elegido
        auto scene = SelectorProfesor::createScene();
        auto transition = TransitionFade::create(1.0f, scene);
        director->replaceScene(transition);
    }else{
        auto scene = HelloWorld::createScene();
        auto transition = TransitionFade::create(1.0f, scene);
        director->replaceScene(transition);
    }
    
}

void Splash::modificarCargando(){
    std::string puntos = "";
    int longitud = LanguageManager::getInstance()->getString("CARGANDO").length();
    
    if(label->getString().length()==longitud+0){
        puntos = ".";
    }else if(label->getString().length()==longitud+1){
        puntos = "..";
    }else if(label->getString().length()==longitud+2){
        puntos = "...";
    }else if(label->getString().length()==longitud+3){
        puntos = "";
    }
    __String *texto = __String::createWithFormat("%s%s",LanguageManager::getInstance()->getString("CARGANDO").c_str(),puntos.c_str());
    label->setString(texto->getCString());
}

void Splash::iniciarCarga(){
    
    recursos = Array::createWithCapacity(100);
    recursos->addObject(__String::create("menu_botonera_preguntator.png"));
    recursos->addObject(__String::create("menu_botonera_preguntator_down.png"));
    
    recursos->addObject(__String::create("menu_botonera_dimeketekito.png"));
    recursos->addObject(__String::create("menu_botonera_dimeketekito_down.png"));
    
    recursos->addObject(__String::create("menu_botonera_armame.png"));
    recursos->addObject(__String::create("menu_botonera_armame_down.png"));
    
    recursos->addObject(__String::create("menu_botonera_akuerdate.png"));
    recursos->addObject(__String::create("menu_botonera_akuerdate_down.png"));
    
    recursos->addObject(__String::create("preguntatorImagenAnimacion.png"));
    recursos->addObject(__String::create("dimeketekitoImagenAnimacion.png"));
    recursos->addObject(__String::create("armameImagenAnimacion.png"));
    recursos->addObject(__String::create("akuerdateImagenAnimacion.png"));
    
    recursos->addObject(__String::create("configuracionImagenAnimacion.png"));
    recursos->addObject(__String::create("mimostroImagenAnimacion.png"));
    recursos->addObject(__String::create("mosterlandImagenAnimacion.png"));
    
    recursos->addObject(__String::create("mosterlandImagenAnimacion.png"));
    recursos->addObject(__String::create("mosterlandImagenAnimacion.png"));
    
    recursos->addObject(__String::create("menu_botonera_preguntator.png"));
    recursos->addObject(__String::create("menu_botonera_armame.png"));
    recursos->addObject(__String::create("menu_botonera_akuerdate.png"));
    recursos->addObject(__String::create("menu_bttop_config.png"));
    recursos->addObject(__String::create("menu_bttop_mimostro.png"));
    recursos->addObject(__String::create("menu_bttop_mosterlan.png"));
    recursos->addObject(__String::create("menu_bttop_murcielago.png"));
    recursos->addObject(__String::create("menu_bttop_logo.png"));
    recursos->addObject(__String::create("menu_bg_d.png"));
    recursos->addObject(__String::create("menu_bg_i.png"));
    recursos->addObject(__String::create("menu_botonera_akuerdate.png"));
    recursos->addObject(__String::create("menu_botonera_akuerdate_down.png"));
    recursos->addObject(__String::create("menu_botonera_armame.png"));
    recursos->addObject(__String::create("menu_botonera_armame_down.png"));
    recursos->addObject(__String::create("menu_botonera_dimeketekito.png"));
    recursos->addObject(__String::create("menu_botonera_dimeketekito_down.png"));
    recursos->addObject(__String::create("menu_botonera_preguntator.png"));
    recursos->addObject(__String::create("menu_botonera_preguntator_down.png"));
    recursos->addObject(__String::create("menu_bttop_config.png"));
    recursos->addObject(__String::create("menu_bttop_config_down.png"));
    recursos->addObject(__String::create("menu_bttop_logo.png"));
    recursos->addObject(__String::create("menu_bttop_mimostro.png"));
    recursos->addObject(__String::create("menu_bttop_mimostro_down.png"));
    recursos->addObject(__String::create("menu_bttop_mosterlan.png"));
    recursos->addObject(__String::create("menu_bttop_mosterlan_down.png"));
    recursos->addObject(__String::create("menu_bttop_murcielago.png"));
  
    
    
    recursos->retain();
    
    
    
    
    LanguageManager::getInstance();
    
    CallFunc *runCallback = CallFunc::create(CC_CALLBACK_0(Splash::cargarContenidos, this));
    
    secuenciaCarga = RepeatForever::create(Sequence::create(DelayTime::create(0.1),runCallback->clone(), NULL));
    secuenciaCarga->retain();
    runAction(secuenciaCarga);
    
}

void Splash::cargarContenidos(){
    
    log("Carga: %i",nContenidoActual);
    
    if(recursos->count()> nContenidoActual){
        
        TextureCache* texturas = Director::getInstance()->getTextureCache();
        __String *recurso = dynamic_cast<__String*>(recursos->getObjectAtIndex(nContenidoActual));
        texturas->addImage(recurso->getCString());
        
    }else if(recursos->count()== nContenidoActual){
        
        this->stopAction(secuenciaCarga);
        
        CallFunc *runCallback = CallFunc::create(CC_CALLBACK_0(Splash::irAMenu, this));
        runAction(Sequence::create(DelayTime::create(1),runCallback,NULL));
    }


    
    nContenidoActual++;
    
}
