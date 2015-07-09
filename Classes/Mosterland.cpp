#include "Mosterland.h"
#include "HelloWorldScene.h"
#include "Configuracion.h"
#include "CMostro.h"
#include "CGestorRecursos.h"
#include "../cocos2d/cocos/network/HttpClient.h"
#include "../cocos2d/extensions/GUI/CCControlExtension/CCControlExtensions.h"
#include "../cocos2d/cocos/editor-support/spine/Json.h"
#include "SimpleAudioEngine.h"


#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "JniLink.h"
#endif


USING_NS_CC;

Scene* Mosterland::createScene()
{
    
    auto scene = Scene::create();
    
    auto layer = Mosterland::create();
    scene->addChild(layer);
    return scene;
}

bool Mosterland::init()
{
    
    if ( !Layer::init() )
    {
        return false;
    }
    this->setKeypadEnabled(true);
    
    
    obtenerMedidas();
    initFondoTemp();
    initBotonAtras();
    initBtCompartir();
    initMusicaFondo();
    
    return true;
}

void Mosterland::onEnterTransitionDidFinish(){
    if(Configuracion::desarrollo)
        CCLOG("[Mosterland] idioma %i",Configuracion::idioma);
    playMusicaFondo();
    initEscuchadores();
    
    initMostroPersonal();
    cargarMostrosInternet();
    
    
    //EJEMPLO DE CONFIGURACION NO VOLATIL
    UserDefault *prueba = UserDefault::getInstance();
    //prueba->setStringForKey("patas", "las mas chulas");
    __String texto = prueba->getStringForKey("patas");
    
    if(Configuracion::desarrollo)
        CCLOG("%s ",texto.getCString());
    
}

void Mosterland::onExitTransitionDidStart() {
    
    cleanMemory();
    
}

Mosterland::~Mosterland() {
    
    cleanMemory();
    
}

void Mosterland::cleanMemory() {
    
    CCDirector::sharedDirector()->purgeCachedData();
    
    CCTextureCache::sharedTextureCache()->removeUnusedTextures();
    CCTextureCache::sharedTextureCache()->removeAllTextures();
    CCTextureCache::purgeSharedTextureCache();
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames();
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFrames();
    CCSpriteFrameCache::purgeSharedSpriteFrameCache();
    
    SpriteFrameCache::getInstance()->removeUnusedSpriteFrames();
    
}

void Mosterland::obtenerMedidas(){
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
}
void Mosterland::initEscuchadores(){
    //activo los tocuh de pantalla
    auto listener1 = EventListenerTouchOneByOne::create();
    listener1->setSwallowTouches(true);
    listener1->onTouchBegan = CC_CALLBACK_2(Mosterland::onTouchBegan, this);
    listener1->onTouchMoved = CC_CALLBACK_2(Mosterland::onTouchMoved, this);
    listener1->onTouchEnded = CC_CALLBACK_2(Mosterland::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);
}

void Mosterland::initBotonAtras(){
    botonAtras = MenuItemImage::create("preguntator_bt_atras.png","preguntator_bt_atras_down.png",CC_CALLBACK_1(Mosterland::irAtras, this));
    
    botonAtras->setScale(escala);
    botonAtras->setAnchorPoint(Vec2(0, 1));
    //calculo espacio sobrante
    float espacio = anchoLateral-(botonAtras->getContentSize().width*escala);
    
    botonAtras->setPosition(0+(espacio/2),visibleSize.height-(espacioSuperiorBtAtras*escala));
    
    auto menu = Menu::create(botonAtras, NULL);
    menu->setPosition(Vec2::ZERO);
    botonAtras->setZOrder(10);
    this->addChild(menu, 1);
}

void Mosterland::initBtCompartir(){
    btCompartir = MenuItemImage::create("mimostro_bt_compartir.png","mimostro_bt_compartir_down.png",CC_CALLBACK_1(Mosterland::compartir, this));
    btCompartir->setScale(escala);
    btCompartir->setAnchorPoint(Vec2(1,1));
    btCompartir->setPosition(visibleSize.width-(espacioSuperiorBtAtras*escala),botonAtras->getPositionY());
    btCompartir->retain();
    
    auto menu = Menu::create(btCompartir, NULL);
    menu->setPosition(Vec2::ZERO);
    botonAtras->setZOrder(10);
    this->addChild(menu, 1);
    
}

void Mosterland::compartir(Ref* pSender) {
    
    CCLOG("%s", "Click compartir en Mosterland");
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    
    const char *idDevice = Configuracion::getIDDEVICE();
    CCLOG("extMethod_idDevice:", idDevice);
    
    __String *url = __String::createWithFormat("http://mostrosity.com/mimostro/%s ", Configuracion::idMiMostro.c_str());
    __String *text = __String::createWithFormat("¿Quieres conocer a mi Mostro? Se llama \"%s\".\nVisítalo en http://mostrosity.com/mimostro/%s ", Configuracion::nombreMiMostro.c_str(), Configuracion::idMiMostro.c_str());
    
    Configuracion::shareOnAndroid(url->getCString(), "Mostrosity", text->getCString());
    
#endif
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    
    mostrarSelectorCompartir();
    
#endif
    
}

void Mosterland::irAtras(Ref* pSender)
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
    CocosDenshion::SimpleAudioEngine::sharedEngine()->stopAllEffects();
    
//    auto scene = HelloWorld::createScene();
//    auto transicion = TransitionFade::create(0.3f, scene);
//    Director::getInstance()->replaceScene(transicion);
    
    Director::getInstance()->popScene();
    
}
void Mosterland::initMusicaFondo(){
    if(!Configuracion::desarrollo){
        CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(cancionFondo);
    }
}

void Mosterland::playMusicaFondo(){
    if(!Configuracion::desarrollo){
        CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(cancionFondo,true);
        
    }
}



Node* Mosterland::iniciarMostroObj(CMostro *mostro){
    
    LayerColor *mostroRetorno = LayerColor::create(Color4B(255,255,250,1), 0, 0);//GUIA PARA POSICION MOSTROS
    mostroRetorno->setPosition(visibleSize.width/2,visibleSize.height*2);
    mostroRetorno->setLocalZOrder(21);
    mostroRetorno->setVisible(true);
    addChild(mostroRetorno);
    
    float escalaMostros = escala/2;
    
    Sprite *mostro_cuerpo = Sprite::create("mostrosity_mimostro_mostro_cuerpo.png");
    mostro_cuerpo->setScale(escalaMostros);
    mostro_cuerpo->setAnchorPoint(Vec2(0.5,0.5));
    mostro_cuerpo->setPosition(0,0);
    mostro_cuerpo->setLocalZOrder(3);
    mostro_cuerpo->setTag(Configuracion::rcsTipoCuerpo);
    mostroRetorno->addChild(mostro_cuerpo);
    
    if(mostro!=NULL){

            mostro->mostro_pies->setScale(escalaMostros);
            mostro->mostro_pies->setAnchorPoint(Vec2(0.5,0.5));
            mostro->mostro_pies->setPosition(0,-300*escalaMostros);
            mostro->mostro_pies->setLocalZOrder(1);
            mostro->mostro_pies->setTag(Configuracion::rcsTipoPies);
            mostro->mostro_pies->setRotation(0);
    
            mostro->mostro_alas->setScale(escalaMostros);
            mostro->mostro_alas->setAnchorPoint(Vec2(0.5,0.5));
            mostro->mostro_alas->setPosition(0,200*escalaMostros);
            mostro->mostro_alas->setLocalZOrder(1);
            mostro->mostro_alas->setTag(Configuracion::rcsTipoAlas);
            mostro->mostro_alas->setRotation(0);
        
            mostro->mostro_brazos->setScale(escalaMostros);
            mostro->mostro_brazos->setAnchorPoint(Vec2(0.5,0.5));
            mostro->mostro_brazos->setPosition(0,0);
            mostro->mostro_brazos->setLocalZOrder(1);
            mostro->mostro_brazos->setTag(Configuracion::rcsTipoBrazos);
            mostro->mostro_brazos->setRotation(0);
        
            mostro->mostro_ojos->setScale(escalaMostros);
            mostro->mostro_ojos->setAnchorPoint(Vec2(0.5,0.5));
            mostro->mostro_ojos->setPosition(0,150*escalaMostros);
            mostro->mostro_ojos->setLocalZOrder(6);
            mostro->mostro_ojos->setTag(Configuracion::rcsTipoOjos);
            mostro->mostro_ojos->setRotation(0);
        
            mostro->mostro_boca->setScale(escalaMostros);
            mostro->mostro_boca->setAnchorPoint(Vec2(0.5,0.5));
            mostro->mostro_boca->setPosition(0,-150*escalaMostros);
            mostro->mostro_boca->setLocalZOrder(6);
            mostro->mostro_boca->setTag(Configuracion::rcsTipoDientes);
            mostro->mostro_boca->setRotation(0);
        
            mostro->mostro_pelo->setScale(escalaMostros);
            mostro->mostro_pelo->setAnchorPoint(Vec2(0.5,0.5));
            mostro->mostro_pelo->setPosition(0,270*escalaMostros);
            mostro->mostro_pelo->setLocalZOrder(6);
            mostro->mostro_pelo->setTag(Configuracion::rcsTipoPelo);
            mostro->mostro_pelo->setRotation(0);
        
            mostro->mostro_orejas->setScale(escalaMostros);
            mostro->mostro_orejas->setAnchorPoint(Vec2(0.5,0.5));
            mostro->mostro_orejas->setPosition(0,370*escalaMostros);
            mostro->mostro_orejas->setLocalZOrder(2);
            mostro->mostro_orejas->setTag(Configuracion::rcsTipoOrejas);
            mostro->mostro_orejas->setRotation(0);
        
            mostro->mostro_accesorio->setScale(escalaMostros);
            mostro->mostro_accesorio->setAnchorPoint(Vec2(0.5,0.5));
            mostro->mostro_accesorio->setPosition(0,0);
            mostro->mostro_accesorio->setLocalZOrder(7);
            mostro->mostro_accesorio->setTag(Configuracion::rcsTipoAccesorio);
            mostro->mostro_accesorio->setRotation(0);

        
        
        
        
        mostroRetorno->addChild(mostro->mostro_pies);
        mostroRetorno->addChild(mostro->mostro_alas);
        mostroRetorno->addChild(mostro->mostro_brazos);
        mostroRetorno->addChild(mostro->mostro_ojos);
        mostroRetorno->addChild(mostro->mostro_boca);
        mostroRetorno->addChild(mostro->mostro_pelo);
        mostroRetorno->addChild(mostro->mostro_orejas);
        mostroRetorno->addChild(mostro->mostro_accesorio);
        
        //tintado priueba
        
        
        CGestorRecursos *gRecursos = new CGestorRecursos();
        Color3B *color = gRecursos->obtenerColorSeleccion(mostro->color->getValue());
        mostro_cuerpo->runAction(TintTo::create(0.5, color->r, color->g, color->b));
        
        for(int i=0;i<mostroRetorno->getChildrenCount();i++){
            Node * parte = mostroRetorno->getChildren().at(i);
            if(parte!=mostro->mostro_boca&&parte!=mostro->mostro_ojos&&parte!=mostro->mostro_accesorio)
                parte->runAction(TintTo::create(0.5, color->r, color->g, color->b));
                parte->setOpacity(1);
        }
        
        
    }
    return mostroRetorno;
}

void Mosterland::initMostroPersonal(){
    CGestorRecursos *gRecursos = new CGestorRecursos();
    
    CMostro *personal = new CMostro();
    personal->nombreMostro = __String::create(UserDefault::getInstance()->getStringForKey("nombreMiMostro","Mi mostro personal"));
    personal->nombreMostro->retain();
    __String *valueSonido = dynamic_cast<__String*>(gRecursos->ObtenerSonido(Configuracion::sonidoMiMostro)->getObjectAtIndex(gRecursos->indiceSonidoValue));
    personal->sonidoMostro = valueSonido;
    personal->sonidoMostro->retain();
    
    
    CRecurso* recursoOjos = gRecursos->obtenerRecursoNoVacio(CGestorRecursos::TIPOS::Ojos,Configuracion::ojosMiMostro);
    CRecurso* recursoDientes = gRecursos->obtenerRecursoNoVacio(CGestorRecursos::TIPOS::Dientes,Configuracion::dientesMiMostro);
    CRecurso* recursoBrazos = gRecursos->obtenerRecursoNoVacio(CGestorRecursos::TIPOS::Brazos,Configuracion::brazosMiMostro);
    CRecurso* recursoPies = gRecursos->obtenerRecursoNoVacio(CGestorRecursos::TIPOS::Pies,Configuracion::piesMiMostro);
    CRecurso* recursoAlas = gRecursos->obtenerRecursoNoVacio(CGestorRecursos::TIPOS::Alas,Configuracion::alasMiMostro);
    CRecurso* recursoOrejas = gRecursos->obtenerRecursoNoVacio(CGestorRecursos::TIPOS::Orejas,Configuracion::orejasMiMostro);
    CRecurso* recursoPelo = gRecursos->obtenerRecursoNoVacio(CGestorRecursos::TIPOS::Pelo,Configuracion::peloMiMostro);
    CRecurso* recursoAccesorio = gRecursos->obtenerRecursoNoVacio(CGestorRecursos::TIPOS::Accesorio,Configuracion::accesorioMiMostro);
    
    personal->mostro_ojos = Sprite::create(recursoOjos->uri->getCString());
    personal->mostro_ojos->retain();
    
    
    personal->mostro_boca = Sprite::create(recursoDientes->uri->getCString());
    personal->mostro_boca->retain();
    personal->mostro_brazos = Sprite::create(recursoBrazos->uri->getCString());
    personal->mostro_brazos->retain();
    personal->mostro_pies = Sprite::create(recursoPies->uri->getCString());
    personal->mostro_pies->retain();
    personal->mostro_alas = Sprite::create(recursoAlas->uri->getCString());
    personal->mostro_alas->retain();
    personal->mostro_orejas = Sprite::create(recursoOrejas->uri->getCString());
    personal->mostro_orejas->retain();
    personal->mostro_pelo = Sprite::create(recursoPelo->uri->getCString());
    personal->mostro_pelo->retain();
    personal->mostro_accesorio = Sprite::create(recursoAccesorio->uri->getCString());
    personal->mostro_accesorio->retain();
    
    
    
    personal->color = __Integer::create(Configuracion::colorMiMostro);
    personal->color->retain();
    
    if(mostrosObj==NULL){
        mostrosObj = __Array::createWithCapacity(50);
        mostrosObj->createWithObject(personal);
        mostrosObj->addObject(personal);
        mostrosObj->retain();
    }else{
        mostrosObj->addObject(personal);
        mostrosObj->retain();
    }

    
    miMostroBase1 = iniciarMostroObj(personal);
    personal->composicion = miMostroBase1;
    miMostroBase1->setOpacity(255);
    miMostroBase1->runAction(FadeIn::create(1));
    Vector<Node*> hijos = miMostroBase1->getChildren();
    for(int i=0;i<hijos.size();i++){
        Node* hijo = hijos.at(i);
        hijo->runAction(FadeIn::create(1));
    }
    
    // cargar los desplazamiento y demas configuracion especifica de cada mostro
    float escalaMostros = escala/2;
    personal->mostro_ojos = gRecursos->obtenerSpriteMontado(personal->mostro_ojos,recursoOjos,escalaMostros);
    personal->mostro_boca = gRecursos->obtenerSpriteMontado(personal->mostro_boca,recursoDientes,escalaMostros);
    personal->mostro_brazos = gRecursos->obtenerSpriteMontado(personal->mostro_brazos,recursoBrazos,escalaMostros);
    personal->mostro_pies = gRecursos->obtenerSpriteMontado(personal->mostro_pies,recursoPies,escalaMostros);
    personal->mostro_alas = gRecursos->obtenerSpriteMontado(personal->mostro_alas,recursoAlas,escalaMostros);
    personal->mostro_orejas = gRecursos->obtenerSpriteMontado(personal->mostro_orejas,recursoOrejas,escalaMostros);
    personal->mostro_pelo = gRecursos->obtenerSpriteMontado(personal->mostro_pelo,recursoPelo,escalaMostros);
    personal->mostro_accesorio = gRecursos->obtenerSpriteMontado(personal->mostro_accesorio,recursoAccesorio,escalaMostros);
    
    //RepeatForever *repeticion = RepeatForever::create(dameAnimacion(1));
    //miMostroBase1->runAction(repeticion);
    
    //COMENZA ANIMACION
    this->schedule( schedule_selector(Mosterland::update), 3 );
    
    /*TintTo *tintado = TintTo::create(1, 0, 255, 0);
    Vector<Node *> hijosMostroBase = miMostroBase->getChildren();
    for(int i=0;i<hijosMostroBase.size();i++){
        Sprite *hijo = dynamic_cast<Sprite *>(hijosMostroBase.at(i));
        hijo->runAction(tintado->clone());
    }
    */

    

}


void Mosterland::update(float tiempo){
    CCLOG("UPDATE MOSTROS");
    for (int i=0;i<mostrosObj->count();i++) {
        CMostro *mostroActual = dynamic_cast<CMostro *>(mostrosObj->getObjectAtIndex(i));
        Node *spMostro = mostroActual->composicion;
        
        if(spMostro->getPositionX()>visibleSize.width+150+(spMostro->getContentSize().width*spMostro->getScale())){
            if(spMostro->getNumberOfRunningActions()==0){
                RepeatForever *repeticion = RepeatForever::create(dameAnimacion(getRandom(4)));
                spMostro->runAction(repeticion);
            }else{
                spMostro->stopAllActions();
                spMostro->setPositionY(espacioEntreFondoMostros*escala);
            }
        }else if(spMostro->getPositionX()<-150-(spMostro->getContentSize().width*spMostro->getScale())){
            if(spMostro->getNumberOfRunningActions()==0){
                RepeatForever *repeticion = RepeatForever::create(dameAnimacion(getRandom(4)));
                spMostro->runAction(repeticion);
            }else{
                spMostro->stopAllActions();
                spMostro->setPositionY(espacioEntreFondoMostros*escala);
            }
        }
    }
    
}

void Mosterland::cargarMostrosInternet(){
    const char* idDevice = Configuracion::getIDDEVICE();
    __String *url = __String::createWithFormat("http://mostrosity.com/SI2-API/bajar.php?dispositivo=%s",idDevice);
    
    network::HttpRequest *request = new network::HttpRequest();
    request->setUrl(url->getCString());
    request->setRequestType(network::HttpRequest::Type::GET);
    request->setResponseCallback([this](network::HttpClient *sender, network::HttpResponse *response) {
        if(Configuracion::desarrollo)
            CCLOG("OBTENIDA RESPUESTA");
        
        std::vector<char>* respuesta = response->getResponseData();
        if(Configuracion::desarrollo)
            CCLOG("Cantidad de caracteres %lu",respuesta->size());
        

        if(respuesta->size()!=0){
            CGestorRecursos *gRecursos = new CGestorRecursos();
            Configuracion *config = new Configuracion();            
            Json *jsonRespuesta = Json_create(config->charTochar(respuesta));
            
            Json *mostrosJSON = jsonRespuesta->child->next;
            
            Json *mostro = mostrosJSON->child;
            for(int i=0;i<mostrosJSON->size;i++){
                __String *nombre = __String::create(mostro->child->valueString);
                
                __Array *objSonido = gRecursos->ObtenerSonido(mostro->child->next->valueInt);
                __String *sonido = dynamic_cast<__String*>(objSonido->getObjectAtIndex(1));
                CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(sonido->getCString());
                Json *partes = mostro->child->next->next;
                
                CMostro *mostroPropio = new CMostro();
                
                
                CRecurso* recursoOjos = gRecursos->obtenerRecursoNoVacio(CGestorRecursos::TIPOS::Ojos,              partes->child->valueInt);
                CRecurso* recursoDientes = gRecursos->obtenerRecursoNoVacio(CGestorRecursos::TIPOS::Dientes,        partes->child->next->valueInt);
                CRecurso* recursoBrazos = gRecursos->obtenerRecursoNoVacio(CGestorRecursos::TIPOS::Brazos,          partes->child->next->next->valueInt);
                CRecurso* recursoPies = gRecursos->obtenerRecursoNoVacio(CGestorRecursos::TIPOS::Pies,              partes->child->next->next->next->valueInt);
                CRecurso* recursoAlas = gRecursos->obtenerRecursoNoVacio(CGestorRecursos::TIPOS::Alas,              partes->child->next->next->next->next->valueInt);
                CRecurso* recursoOrejas = gRecursos->obtenerRecursoNoVacio(CGestorRecursos::TIPOS::Orejas,          partes->child->next->next->next->next->next->valueInt);
                CRecurso* recursoPelo = gRecursos->obtenerRecursoNoVacio(CGestorRecursos::TIPOS::Pelo,              partes->child->next->next->next->next->next->next->valueInt);
                CRecurso* recursoAccesorio = gRecursos->obtenerRecursoNoVacio(CGestorRecursos::TIPOS::Accesorio,    partes->child->next->next->next->next->next->next->next->valueInt);
                mostroPropio->color =  __Integer::create(                                                           partes->child->next->next->next->next->next->next->next->next->valueInt);
                mostroPropio->color->retain();
                
                CMostro *mostroDescargado = new CMostro();
                mostroDescargado->nombreMostro = nombre;
                mostroDescargado->nombreMostro->retain();
                mostroDescargado->sonidoMostro = sonido;
                mostroDescargado->sonidoMostro->retain();
                mostroDescargado->mostro_ojos =         Sprite::create(recursoOjos->uri->getCString());
                mostroDescargado->mostro_ojos->retain();
                mostroDescargado->mostro_boca =         Sprite::create(recursoDientes->uri->getCString());
                mostroDescargado->mostro_boca->retain();
                mostroDescargado->mostro_brazos =       Sprite::create(recursoBrazos->uri->getCString());
                mostroDescargado->mostro_brazos->retain();
                mostroDescargado->mostro_pies =         Sprite::create(recursoPies->uri->getCString());
                mostroDescargado->mostro_pies->retain();
                mostroDescargado->mostro_alas =         Sprite::create(recursoAlas->uri->getCString());
                mostroDescargado->mostro_alas->retain();
                mostroDescargado->mostro_orejas =       Sprite::create(recursoOrejas->uri->getCString());
                mostroDescargado->mostro_orejas->retain();
                mostroDescargado->mostro_pelo =         Sprite::create(recursoPelo->uri->getCString());
                mostroDescargado->mostro_pelo->retain();
                mostroDescargado->mostro_accesorio =    Sprite::create(recursoAccesorio->uri->getCString());
                mostroDescargado->mostro_accesorio->retain();

                
                mostroDescargado->color =              __Integer::create(partes->child->next->next->next->next->next->next->next->next->valueInt);
                mostroDescargado->color->retain();
                
                mostro = mostro->next;
                
                if(mostrosObj==NULL){
                    mostrosObj = __Array::createWithCapacity(50);
                    mostrosObj->createWithObject(mostroDescargado);
                    mostrosObj->addObject(mostroDescargado);
                    mostrosObj->retain();
                }else{
                    mostrosObj->addObject(mostroDescargado);
                }
                Node *spMostro = iniciarMostroObj(mostroDescargado);
                mostroDescargado->composicion = spMostro;
                
                // cargar los desplazamiento y demas configuracion especifica de cada mostro
                float escalaMostros = escala/2;
                mostroDescargado->mostro_ojos = gRecursos->obtenerSpriteMontado(mostroDescargado->mostro_ojos,recursoOjos,escalaMostros);
                mostroDescargado->mostro_boca = gRecursos->obtenerSpriteMontado(mostroDescargado->mostro_boca,recursoDientes,escalaMostros);
                mostroDescargado->mostro_brazos = gRecursos->obtenerSpriteMontado(mostroDescargado->mostro_brazos,recursoBrazos,escalaMostros);
                mostroDescargado->mostro_pies = gRecursos->obtenerSpriteMontado(mostroDescargado->mostro_pies,recursoPies,escalaMostros);
                mostroDescargado->mostro_alas = gRecursos->obtenerSpriteMontado(mostroDescargado->mostro_alas,recursoAlas,escalaMostros);
                mostroDescargado->mostro_orejas = gRecursos->obtenerSpriteMontado(mostroDescargado->mostro_orejas,recursoOrejas,escalaMostros);
                mostroDescargado->mostro_pelo = gRecursos->obtenerSpriteMontado(mostroDescargado->mostro_pelo,recursoPelo,escalaMostros);
                mostroDescargado->mostro_accesorio = gRecursos->obtenerSpriteMontado(mostroDescargado->mostro_accesorio,recursoAccesorio,escalaMostros);
            }
            
            
            for(int a=0;a<mostrosObj->count();a++){
                
                CMostro *mostroActualFor = dynamic_cast<CMostro *>(mostrosObj->getObjectAtIndex(a));
                
                CallFunc *runCallback1 = CallFunc::create(CC_CALLBACK_0(Mosterland::iniciarAnimacionMostro, this));
                Sequence *secuencia = Sequence::create(DelayTime::create(a*Mosterland::iSegundosEntreEntradas),runCallback1, NULL);
                this->runAction(secuencia);
               
            }
        
        
        }else{
            CCLOG("RESPUESTA ERRONEA HTTP .");
            for(int a=0;a<mostrosObj->count();a++){
                
                CMostro *mostroActualFor = dynamic_cast<CMostro *>(mostrosObj->getObjectAtIndex(a));
                
                CallFunc *runCallback1 = CallFunc::create(CC_CALLBACK_0(Mosterland::iniciarAnimacionMostro, this));
                Sequence *secuencia = Sequence::create(DelayTime::create(a*Mosterland::iSegundosEntreEntradas),runCallback1, NULL);
                this->runAction(secuencia);
                
            }
        }
        
    });
    
    if(Configuracion::desarrollo)
        CCLOG("COMIENZA LA PETICION HTTP called.");
    network::HttpClient::getInstance()->send(request);
    //#endif
}

void Mosterland::iniciarAnimacionMostro(){
    if(Configuracion::desarrollo)
        CCLOG("iniciar animacion del mostro %i",proximoMostro);
    
    if(proximoMostro == 3 || proximoMostro == 6){
        //proximoMostro++;
        //return;
    }
    CMostro *mostroActualFor = dynamic_cast<CMostro *>(mostrosObj->getObjectAtIndex(proximoMostro));
    mostroActualFor->composicion->setOpacity(255);
    
    Node *spMostro = mostroActualFor->composicion;
    spMostro->setLocalZOrder(proximoMostro);
    
    MoveTo *movimiento = MoveTo::create(0.5, Vec2(spMostro->getPositionX(),espacioEntreFondoMostros*escala));
    spMostro->setPositionY(visibleSize.height);
    spMostro->runAction(FadeIn::create(0));
    spMostro->runAction(movimiento);
    
    
    Vector<Node*> hijos = spMostro->getChildren();
    for(int i=0;i<hijos.size();i++){
        Node* hijo = hijos.at(i);
        
        //hijo->setLocalZOrder(proximoMostro);
        
        MoveTo *movimiento = MoveTo::create(0.5, Vec2(hijo->getPositionX(),hijo->getPositionY()));
        hijo->setPositionY(visibleSize.height+(hijo->getPositionY()-espacioEntreFondoMostros*escala));
        hijo->runAction(movimiento);
        hijo->runAction(FadeIn::create(0));
        
    }
    
    RepeatForever *repeticion = RepeatForever::create(dameAnimacion(getRandom(4)));
    if(proximoMostro%2==0) {
        
        if (proximoMostro == 2) {
            repeticion = RepeatForever::create(dameAnimacion(2));
        } else {
            repeticion = RepeatForever::create(dameAnimacion(4));
        }
        
    }
    
    spMostro->runAction(repeticion);
    
    
    proximoMostro++;
}

Sequence* Mosterland::dameAnimacion(int numero){
    Sequence *animacion;
    switch (numero) {
        case 1:{
            MoveBy *salto1 = MoveBy::create(0.3, Vec2(20*escala,40*escala));
            MoveBy *vuelta1 = MoveBy::create(0.3, Vec2(20*escala,-40*escala));
            animacion = Sequence::create(salto1,vuelta1,NULL);
            break;
        }
        case 2:{
            MoveBy *salto2 = MoveBy::create(0.3, Vec2(-20*escala,40*escala));
            MoveBy *vuelta2 = MoveBy::create(0.3, Vec2(-20*escala,-40*escala));
            animacion = Sequence::create(salto2,vuelta2,NULL);
            break;
        }
            
        case 3:{
            MoveBy *salto1 = MoveBy::create(0.3, Vec2(100*escala,100*escala));
            RotateBy *rotando1 = RotateBy::create(0.5, 360);
            MoveBy *desplazamiento1 = MoveBy::create(0.5, Vec2(0*escala,-100*escala));
            animacion = Sequence::create(salto1,salto1,rotando1,desplazamiento1,NULL);
            break;
        }
        case 4:{
            MoveBy *salto2 = MoveBy::create(0.3, Vec2(-100*escala,100*escala));
            RotateBy *rotando2 = RotateBy::create(0.5, -360);
            MoveBy *desplazamiento2 = MoveBy::create(0.5, Vec2(0*escala,-100*escala));
            animacion = Sequence::create(salto2, desplazamiento2, salto2,desplazamiento2,NULL);
            break;
        }
    }
    
    return animacion;
}

void Mosterland::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event){
    irAtras(NULL);
}
bool Mosterland::comprobarToque(cocos2d::Touch *touch,Sprite *sprite){
    
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

void Mosterland::initFondoTemp(){

    fondoTemp_i = Sprite::create("mosterland_fondo_d.png");
    fondoTemp_i->setScale(escala);
    fondoTemp_i->setAnchorPoint(Vec2(0,0.5));
    fondoTemp_i->setPosition(visibleSize.width/2,visibleSize.height/2);
    this->addChild(fondoTemp_i);
    
    
    
    fondoTemp_d = Sprite::create("mosterland_fondo_i.png");
    fondoTemp_d->setScale(escala);
    fondoTemp_d->setAnchorPoint(Vec2(1,0.5));
    fondoTemp_d->setPosition(visibleSize.width/2,visibleSize.height/2);
    this->addChild(fondoTemp_d);
    
}
bool Mosterland::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
    
    if(!escuchadores){
        return false;
    }
    if(Configuracion::desarrollo)
        if(Configuracion::desarrollo)
            log("BEGAN %f %f",touch->getLocation().x,touch->getLocation().y);
    
    if(mostrosObj!=NULL){
        int mostroTocado = -1;

        for (int i=0; i<mostrosObj->count(); i++) {
            CMostro *mostro = dynamic_cast<CMostro*>(mostrosObj->getObjectAtIndex(i));
            Node *sprite = mostro->composicion;
            
            Vector<Node *> hijosMostroBase = sprite->getChildren();
            //primero quito el label
            for(int a=0;a<hijosMostroBase.size();a++){
                CCLabelTTF *tituloNombre = dynamic_cast<CCLabelTTF *>(hijosMostroBase.at(a));
                if(tituloNombre!=NULL){
                    sprite->cocos2d::Node::removeChild(tituloNombre);
                }
            }
            
            
            
            if(!Configuracion::comprobarToque(touch,sprite)){
                ///si no has tocado el cuerpo
                
                
                if(Configuracion::desarrollo)
                    CCLOG("COMPROBANDO HIJOS ");
                
                for(int a=0;a<hijosMostroBase.size();a++){
                    
                        Sprite *hijo = dynamic_cast<Sprite *>(hijosMostroBase.at(a));
                        if(hijo!=NULL){
                            if(comprobarToque(touch, hijo)){
                                if(Configuracion::desarrollo)
                                    CCLOG("TOCADA PARTE %i",a);
                                
                                if(mostroTocado ==-1){
                                    //aun no habia mostro tocado
                                    mostroTocado = i;
                                }else{
                                    CMostro *mostroANTERIOR = dynamic_cast<CMostro*>(mostrosObj->getObjectAtIndex(mostroTocado));
                                    Node *spriteANTERIOR = mostroANTERIOR->composicion;
                                    int iZlocalAnterior = spriteANTERIOR->getLocalZOrder();
                                    int iZlocal = sprite->getLocalZOrder();
                                    if(iZlocalAnterior<iZlocal){
                                        mostroTocado = i;
                                    }
                                    
                                }
                            }
                        }
                }
                
                
            }else{
                //si has tocado el cuerpo
                
                if(Configuracion::desarrollo)
                    CCLOG("TOCADO CUERPO");

                    if(mostroTocado ==-1){
                        //aun no habia mostro tocado
                        mostroTocado = i;
                    }else{
                        CMostro *mostroANTERIOR = dynamic_cast<CMostro*>(mostrosObj->getObjectAtIndex(mostroTocado));
                        Node *spriteANTERIOR = mostroANTERIOR->composicion;
                        int iZlocalAnterior = spriteANTERIOR->getLocalZOrder();
                        int iZlocal = sprite->getLocalZOrder();
                        if(iZlocalAnterior<iZlocal){
                            mostroTocado = i;
                        }
                        
                    }
            }
        }
        
        if(mostroTocado!= -1){
            CMostro *mostro = dynamic_cast<CMostro*>(mostrosObj->getObjectAtIndex(mostroTocado));
            Node *sprite = mostro->composicion;
            if(sprite->isVisible()&&sprite->getOpacity()>0){
                __String *sonido = mostro->sonidoMostro;
                CocosDenshion::SimpleAudioEngine *audio = CocosDenshion::SimpleAudioEngine::getInstance();
                audio->stopAllEffects();
                audio->playEffect(sonido->getCString());
                
                __String *nombre = mostro->nombreMostro;
                
                LabelTTF *cartel = LabelTTF::create(nombre->getCString(), "HVD_Comic_Serif_Pro.ttf", 50,Size(sprite->getContentSize()), TextHAlignment::CENTER);
                cartel->setAnchorPoint(Vec2(0.5,0));
                cartel->setHorizontalAlignment(TextHAlignment::CENTER);
                cartel->setVerticalAlignment(TextVAlignment::CENTER);
                cartel->setPosition(0,250*escala);
                cartel->setLocalZOrder(999);
                sprite->addChild(cartel);
            }
        }
        
        
    }else{
        if(Configuracion::desarrollo)
            CCLOG("mostros aun es nulo");
    }
    
    return  true;
}
void Mosterland::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event)
{
    if(Configuracion::desarrollo)
        if(Configuracion::desarrollo)
            log("MOVED %f %f ",touch->getLocation().x,touch->getLocation().y);
    
}
void Mosterland::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
{
    if(Configuracion::desarrollo)
        if(Configuracion::desarrollo)
            log("ENDED %f %f ",touch->getLocation().x,touch->getLocation().y);
    
    
    
}

void Mosterland::mostrarSelectorCompartir(){
    
    if(capaLoadingCaptura==NULL){
        capaLoadingCaptura = LayerColor::create(Color4B(16,46,75,230), visibleSize.width, visibleSize.height);
        addChild(capaLoadingCaptura,999);
    }
    
    if(capaLoadingCaptura!=NULL){
        
        auto menuCompartir = Menu::create(NULL);
        menuCompartir->setPosition(Vec2::ZERO);
        menuCompartir->retain();
        capaLoadingCaptura->addChild(menuCompartir);
        
        btMenuCompartirTwitter = MenuItemImage::create("mimostro_bt_compartir_selector_twitter.png", "mimostro_bt_compartir_selector_twitter_down.png",CC_CALLBACK_1(Mosterland::finAccionMenuCompartir, this));
        btMenuCompartirTwitter->setAnchorPoint(Vec2(1,0.5));
        btMenuCompartirTwitter->setPosition(visibleSize.width/2-espacioBordesCuadro, visibleSize.height/2);
        menuCompartir->addChild(btMenuCompartirTwitter);
        
        btMenuCompartirFacebook = MenuItemImage::create("mimostro_bt_compartir_selector_face.png", "mimostro_bt_compartir_selector_face_down.png",CC_CALLBACK_1(Mosterland::finAccionMenuCompartir, this));
        btMenuCompartirFacebook->setAnchorPoint(Vec2(0,0.5));
        btMenuCompartirFacebook->setPosition(visibleSize.width/2+espacioBordesCuadro, visibleSize.height/2);
        menuCompartir->addChild(btMenuCompartirFacebook);
        
        btMenuCompartirCerrar = MenuItemImage::create("mimostro_bt_cerrar_modal.png", "mimostro_bt_cerrar_modal.png",CC_CALLBACK_1(Mosterland::finAccionMenuCompartir, this));
        btMenuCompartirCerrar->setScale(escala);
        btMenuCompartirCerrar->setAnchorPoint(Vec2(1,1));
        btMenuCompartirCerrar->setPosition(visibleSize.width-espacioBordesCuadro, visibleSize.height-espacioBordesCuadro);
        menuCompartir->addChild(btMenuCompartirCerrar);
        
    }
    
}

void Mosterland::finAccionMenuCompartir(cocos2d::Ref *boton){
    
    __String *urlMiMostro = __String::createWithFormat("http://mostrosity.com/mimostro/%s", Configuracion::idMiMostro.c_str());
    
    if(boton == btMenuCompartirCerrar){
        
        eliminarCapaLoadingCaptura();
        
    }else if(boton == btMenuCompartirTwitter){
        
        __String *twitter = __String::createWithFormat("http://twitter.com/share?text=Visita mi mostro. Se llama %s&url=%s&hashtags=mostrosity,cmi,cmidocentic,si2,",
                                                       Configuracion::nombreMiMostro.c_str(),
                                                       urlMiMostro->getCString());
        
        Configuracion::callOpenURL(twitter->getCString());
        
    }else if(boton == btMenuCompartirFacebook){
        
        __String *facebook = __String::createWithFormat("https://www.facebook.com/sharer/sharer.php?s=100&p[title]=Mostrosity&p[summary]=Visita mi mostro. Se llama %s&p[url]=%s",
                                                        Configuracion::nombreMiMostro.c_str(),
                                                        urlMiMostro->getCString());
        
        Configuracion::callOpenURL(facebook->getCString());
        
    }
    
}

void Mosterland::eliminarCapaLoadingCaptura(){
    
    if(capaLoadingCaptura!=NULL){
        removeChild(capaLoadingCaptura);
        capaLoadingCaptura = NULL;
    }
    
}

int Mosterland::getRandom(int end) {
    
    return rand() % end + 1;
    
}
