#include "MiMostro.h"
#include "HelloWorldScene.h"
#include "Configuracion.h"
#include "LanguageManager.h"
#include "Ajustes.h"
#include "SimpleAudioEngine.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "JniLink.h"
#endif


USING_NS_CC;

Scene* MiMostro::createScene()
{
    
    auto scene = Scene::create();
    
    auto layer = MiMostro::create();
    scene->addChild(layer);
    return scene;
}

bool MiMostro::init()
{
    
    oldLanguage = Configuracion::idioma;
    
    if ( !Layer::init() )
    {
        return false;
    }
    this->setKeypadEnabled(true);
    
    initRecursos();
    
    obtenerMedidas();
    initFondoTemp();
    initBotonAtras();
    initCuadroJuego();
    initBtAjustes();
    initBtColor();
    initBtCompartir();
    initBtSonido();
    initTxtLateral();
    initCajas();
    initCapasPartes();
    initMostro();
    initMostroPropiedades(CGestorRecursos::TIPOS::Indefinido);
    
    
    
    cambiarRecurso(CGestorRecursos::TIPOS::Ojos,Configuracion::ojosMiMostro);
    cambiarRecurso(CGestorRecursos::TIPOS::Dientes,Configuracion::dientesMiMostro);
    cambiarRecurso(CGestorRecursos::TIPOS::Brazos,Configuracion::brazosMiMostro);
    cambiarRecurso(CGestorRecursos::TIPOS::Orejas,Configuracion::orejasMiMostro);
    cambiarRecurso(CGestorRecursos::TIPOS::Pies,Configuracion::piesMiMostro);
    cambiarRecurso(CGestorRecursos::TIPOS::Alas,Configuracion::alasMiMostro);
    cambiarRecurso(CGestorRecursos::TIPOS::Pelo,Configuracion::peloMiMostro);
    cambiarRecurso(CGestorRecursos::TIPOS::Accesorio,Configuracion::accesorioMiMostro);

    cambiarColor(Configuracion::colorMiMostro);
    cambiarSonido(Configuracion::sonidoMiMostro,false);

     
    this->schedule(schedule_selector(MiMostro::UpdateScrollView), 1);
    this->scheduleUpdate();
    return true;
}

void MiMostro::onEnterTransitionDidFinish(){
    initMusica();
    
    //activo los tocuh de pantalla
    auto listener1 = EventListenerTouchOneByOne::create();
    listener1->setSwallowTouches(true);
    listener1->onTouchBegan = CC_CALLBACK_2(MiMostro::onTouchBegan, this);
    listener1->onTouchMoved = CC_CALLBACK_2(MiMostro::onTouchMoved, this);
    listener1->onTouchEnded = CC_CALLBACK_2(MiMostro::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);
    
    escuchadoresBtyCapas = true;
    escuchadores = true;
    
    if (oldLanguage != Configuracion::idioma) {
        oldLanguage = Configuracion::idioma;
        eliminarTextos();
        initCapasPartes();
    }
    
}

void MiMostro::onExitTransitionDidStart() {
    
    cleanMemory();
    
}

MiMostro::~MiMostro() {
    
    cleanMemory();
    
}

void MiMostro::cleanMemory() {
    
    CCDirector::sharedDirector()->purgeCachedData();
    
    CCTextureCache::sharedTextureCache()->removeUnusedTextures();
    CCTextureCache::sharedTextureCache()->removeAllTextures();
    CCTextureCache::purgeSharedTextureCache();
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames();
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFrames();
    CCSpriteFrameCache::purgeSharedSpriteFrameCache();
    
    SpriteFrameCache::getInstance()->removeUnusedSpriteFrames();
    
}

void MiMostro::initMusica(){
    //pongo musica
    if(!Configuracion::desarrollo){
        if(CocosDenshion::SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying()){
            
        }else{
            CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("sintonia_mimostro.mp3", true);
        }
    }
}

void MiMostro::obtenerMedidas(){
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    
    relacion = visibleSize.width/visibleSize.height;
    escalaAncha = visibleSize.width/2560;
    escalaAlta = visibleSize.height/1600;
    if(escalaAncha>escalaAlta){
        escala = escalaAncha;
        escalaCajas = escalaAlta;
    }else{
        escala = escalaAlta;
        escalaCajas = escalaAncha;
    }
    
    anchoLateralCE = (visibleSize.width/100)*20;
    anchoNoLateralCE = ((visibleSize.width/100)*80);
    
    espacioBordesCuadroCE = espacioBordesCuadro*escala;
    espacioSuperiorBtAtrasCE = espacioSuperiorBtAtras*escala;
    
    tamLetraCE = tamLetra * escala;
    margenLetrasCE = margenLetras * escala;
    
    margenEntreCajasCE = margenEntreCajas*escalaCajas;
    
    altoModal = visibleSize.height;
    altoModalCE = visibleSize.height;
    tamLetraModalTituloCE = tamLetraModalTitulo * escala;
    margenElementosCE = 50*escala;
    /*
    if(escala==escalaAlta){
        anchoCajaHorizontalCE = anchoCajaHorizontal*escalaAncha;
        altoCajaHorizontalCE = altoCajaHorizontal*escalaAncha;
        anchoCajaVerticalCE = anchoCajaVertical*escalaAncha;
        altoCajaVerticalCE = altoCajaVertical*escalaAncha;
    }else{
        anchoCajaHorizontalCE = anchoCajaHorizontal*escalaAlta;
        altoCajaHorizontalCE = altoCajaHorizontal*escalaAlta;
        anchoCajaVerticalCE = anchoCajaVertical*escalaAlta;
        altoCajaVerticalCE = altoCajaVertical*escalaAlta;
    }*/
    
    
}

void MiMostro::initBotonAtras(){
    botonAtras = MenuItemImage::create("preguntator_bt_atras.png","preguntator_bt_atras_down.png",CC_CALLBACK_1(MiMostro::irAtras, this));
    
    botonAtras->setScale(escala);
    botonAtras->setAnchorPoint(Vec2(0, 1));
    //calculo espacio sobrante
    float espacio = anchoLateralCE-(botonAtras->getContentSize().width*escala);
    
    botonAtras->setPosition(0+(espacio/2),visibleSize.height-(espacioSuperiorBtAtras*escala));
    
    menu = Menu::create(botonAtras, NULL);
    menu->setPosition(Vec2::ZERO);
    menu->retain();
    this->addChild(menu, 1);

}



void MiMostro::sincronizar(){


    cocos2d::network::HttpRequest* request = new cocos2d::network::HttpRequest();
    request->setUrl("http://mostrosity.com/SI2-API/subir.php");
    request->setRequestType(cocos2d::network::HttpRequest::Type::POST);
    request->setResponseCallback( CC_CALLBACK_2(MiMostro::sincronizado, this) );
    
    // write the post data
    
    __String *sNombre = String::createWithFormat("\"mostro_nombre\":\"%s\"",Configuracion::nombreMiMostro.c_str());
    __String *sSonido = String::createWithFormat("\"mostro_sonido\":\"%i\"",Configuracion::sonidoMiMostro);
    __String *sOjos = String::createWithFormat("\"mostro_ojos\":\"%i\"",Configuracion::ojosMiMostro);
    __String *sBoca = String::createWithFormat("\"mostro_boca\":\"%i\"",Configuracion::dientesMiMostro);
    __String *sBrazos = String::createWithFormat("\"mostro_brazos\":\"%i\"",Configuracion::brazosMiMostro);
    __String *sPies = String::createWithFormat("\"mostro_pies\":\"%i\"",Configuracion::piesMiMostro);
    __String *sAlas = String::createWithFormat("\"mostro_alas\":\"%i\"",Configuracion::alasMiMostro);
    __String *sOrejas = String::createWithFormat("\"mostro_orejas\":\"%i\"",Configuracion::orejasMiMostro);
    __String *sPelo = String::createWithFormat("\"mostro_pelo\":\"%i\"",Configuracion::peloMiMostro);
    __String *sAccesorio = String::createWithFormat("\"mostro_accesorio\":\"%i\"",Configuracion::accesorioMiMostro);
    __String *sColor = String::createWithFormat("\"mostro_color\":\"%i\"",Configuracion::colorMiMostro);
    
    __String *sObjJson = __String::createWithFormat("{%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s}",
                                                           sNombre->getCString(),
                                                           sSonido->getCString(),
                                                           sOjos->getCString(),
                                                           sBoca->getCString(),
                                                           sBrazos->getCString(),
                                                           sPies->getCString(),
                                                           sAlas->getCString(),
                                                           sOrejas->getCString(),
                                                           sPelo->getCString(),
                                                           sAccesorio->getCString(),
                                                           sColor->getCString()
                                                           );

    const char* IDDEVICE = Configuracion::getIDDEVICE();
    const char* postData = __String::createWithFormat("dispositivo=%s&mostro=%s",IDDEVICE,sObjJson->getCString())->getCString();
    request->setRequestData(postData, strlen(postData));
    
    request->setTag("POST test1");
    cocos2d::network::HttpClient::getInstance()->send(request);
    request->release();
}

void MiMostro::sincronizado(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response){
    
    Configuracion *config = new Configuracion();
    const char *respuesta = config->charTochar(response->getResponseData());
    log("Respuesta %s",respuesta);
    log("LLEGADO");
    


    
}



void MiMostro::initTxtLateral(){
    
    float posicionActual = botonAtras->getPositionY()-(espacioSuperiorBtAtrasCE)-(botonAtras->getContentSize().height*escala);
    
    Sprite *textoLateral = Sprite::create("mostrosity_mimostro_titulo_lateral.png");
    textoLateral->setScale(escala);
    textoLateral->setAnchorPoint(Vec2(0, 1));
    textoLateral->setPosition(espacioSuperiorBtAtrasCE,posicionActual);
    this->addChild(textoLateral);
    
    posicionActual = posicionActual - (textoLateral->getContentSize().height*escala)-(50*escala);
    
    EditBox *_editName;
    std::string pNormalSprite = "mostrosity_mimostro_input_bg.png";
    _editName = EditBox::create(Size(anchoLateralCE, (tamLetraCE+margenLetrasCE)*2), Scale9Sprite::create(pNormalSprite));
    _editName->cocos2d::Node::setPosition(espacioBordesCuadroCE, posicionActual);
    _editName->setAnchorPoint(Vec2(0,1));
    _editName->setFontName("HVD_Comic_Serif_Pro.ttf");
    _editName->setFontSize(tamLetraCE);
    _editName->setFont("HVD_Comic_Serif_Pro.ttf", tamLetraCE);
    _editName->setFontColor(Color3B(194,233,251));
    _editName->setPlaceHolder(LanguageManager::getInstance()->getString("MiMostroBtNombre").c_str());
    _editName->setPlaceholderFontColor(Color3B(140,205,235));
    _editName->setPlaceholderFont("HVD_Comic_Serif_Pro.ttf", tamLetraCE);
    _editName->setMaxLength(30);
    _editName->setReturnType(EditBox::KeyboardReturnType::DONE);
    _editName->setDelegate(this);
    _editName->setInputMode(EditBox::InputMode::SINGLE_LINE);
    _editName->setText(Configuracion::nombreMiMostro.c_str());
    addChild(_editName);
    
    //MessageBox2("sda", "");
    
    posicionActual = posicionActual- (_editName->getContentSize().height*escala)-(100*escala);
    
    
}

void MiMostro::irAtras(Ref* pSender)
{
    if(!escuchadoresBtyCapas)
        return;
    
    
    sincronizar();
    
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
    
//    auto scene = HelloWorld::createScene();
//    auto transicion = TransitionFade::create(0.0f, scene);
//    Director::getInstance()->replaceScene(transicion);

    Director::getInstance()->popScene();
    
}

void MiMostro::initFondoTemp(){
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
}



//--------CUADRO-------//




void MiMostro::initCuadroJuego(){
    altoIndividalCuadroJuego = visibleSize.height-((espacioBordesCuadro*2*escala));
    anchoIndividualCuadroJuego = anchoNoLateralCE-(espacioBordesCuadro*2*escala);
    
    cuadroJuego = LayerColor::create(Color4B(0,69,107,255));
    cuadroJuego->setContentSize(Size(anchoIndividualCuadroJuego,altoIndividalCuadroJuego));
    cuadroJuego->setPosition(anchoLateralCE+(espacioBordesCuadro*escala),(espacioBordesCuadro*escala));
    cuadroJuego->setZOrder(6);
    cuadroJuego->retain();
    this->addChild(cuadroJuego);
    
    cuadroJuegoInterior = LayerColor::create(Color4B(0,23,39,255));
    cuadroJuegoInterior->setContentSize(Size(anchoIndividualCuadroJuego-((espacioBordesCuadro/2)*2*escala),altoIndividalCuadroJuego/2));
    cuadroJuegoInterior->setPosition(cuadroJuego->getPositionX()+((espacioBordesCuadro/2)*escala),cuadroJuego->getPositionY()+((espacioBordesCuadro/2)*escala));
    cuadroJuegoInterior->setZOrder(6);
    cuadroJuegoInterior->retain();
    this->addChild(cuadroJuegoInterior);
    
}

void MiMostro::selectorGeneral(cocos2d::Ref *pSender){
    if(!escuchadoresBtyCapas)
        return;
    
    if(pSender==btColor){
        selectorColor();
    }else if(pSender==btAjustes){
        selectorAjustes();
    }else if(pSender==btSonido){
        selectorSonido();
    }else if(pSender==btCompartir){
    	selectorCompartir();
    }
}

void MiMostro::initBtSonido(){
    btSonido = MenuItemImage::create("mostrosity_mimostro_bt_sonido.png","mostrosity_mimostro_bt_sonido_down.png",CC_CALLBACK_1(MiMostro::selectorGeneral, this));
    btSonido->setScale(escala);
    btSonido->setAnchorPoint(Vec2(0.5,0));
    btSonido->setPosition(anchoLateralCE/2,espacioBordesCuadro*2);
    btSonido->retain();
    menu->setZOrder(11);
    menu->addChild(btSonido);
    
    textSonido = CCLabelTTF::create(LanguageManager::getInstance()->getString("MiMostroBtSonido"), "HVD_Comic_Serif_Pro.ttf", tamLetra*0.8,Size(btSonido->getContentSize().width, tamLetraCE*2), TextHAlignment::CENTER);
    textSonido->setColor(Color3B(194,233,251));
    textSonido->setVerticalAlignment(TextVAlignment::CENTER);
    textSonido->setAnchorPoint(Vec2(0, 0));
    textSonido->setPosition(0,0);
    btSonido->addChild(textSonido);
    
    
    
    uiLabelSonido = CCLabelTTF::create(obtenerDatoSonido(indiceSonidoLabel)->getCString(), "HVD_Comic_Serif_Pro.ttf", tamLetraCE,Size(anchoLateralCE, tamLetraCE*4), TextHAlignment::CENTER);
    uiLabelSonido->retain();
    uiLabelSonido->setColor(Color3B(194,233,251));
    uiLabelSonido->setVerticalAlignment(TextVAlignment::BOTTOM);
    uiLabelSonido->setAnchorPoint(Vec2(0, 0));
    uiLabelSonido->setPosition(0,btSonido->getPositionY()+(btSonido->getContentSize().height*escala)+espacioBordesCuadroCE);
    this->addChild(uiLabelSonido);
}

void MiMostro::initBtColor(){
    btColor = MenuItemImage::create("mostrosity_mimostro_bt_color.png","mostrosity_mimostro_bt_color_down.png",CC_CALLBACK_1(MiMostro::selectorGeneral, this));
    btColor->setScale(escala);
    btColor->setAnchorPoint(Vec2(0,1));
    btColor->setPosition(anchoLateralCE+espacioBordesCuadroCE*2,altoIndividalCuadroJuego);
    btColor->retain();
    menu->setZOrder(11);
    menu->addChild(btColor);
}




void MiMostro::selectorSonido(){
    if(Configuracion::desarrollo)
        CCLOG("Selector sonido");
    
    __Array *array = __Array::createWithCapacity(Configuracion::nSonido);
    for(int i=0;i<array->capacity();i++){
        __String *nombre = __String::createWithFormat("fondo_transparente_select.png");
        MenuItemImage *sonido = MenuItemImage::create(nombre->getCString(),nombre->getCString(),CC_CALLBACK_1(MiMostro::cambiarSonidoBT,this));
        sonido->setScale(escala);
        anchoUltElementoCE = sonido->getContentSize().width*escala;
        array->addObject(sonido);
        
        __Array *objSonido = dynamic_cast<__Array*>(gRecursos->ObtenerSonido(i));
        __String *labelSonido = dynamic_cast<__String*>(objSonido->getObjectAtIndex(indiceSonidoLabel));
        __String *valueSonido = dynamic_cast<__String*>(objSonido->getObjectAtIndex(indiceSonidoValue));
        
        LabelTTF *txtSonido = CCLabelTTF::create(labelSonido->getCString(), "HVD_Comic_Serif_Pro.ttf", tamLetra*1.5,Size(sonido->getContentSize()), TextHAlignment::CENTER);
        txtSonido->setColor(Color3B(194,233,251));
        txtSonido->setVerticalAlignment(TextVAlignment::CENTER);
        txtSonido->setAnchorPoint(Vec2(0, 0.5));
        txtSonido->setPosition(0,sonido->getContentSize().height/2);
        sonido->addChild(txtSonido);
    }
    
    //ABRIMOS SELECTOR DE COLOR
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("tambores_3.mp3");
    initModal(0,array);
    desplazarModal(Configuracion::sonidoMiMostro);
}
void MiMostro::cambiarSonidoBT(cocos2d::Ref *pSender){
    
    MenuItemImage *btSonidoPulsado = dynamic_cast<MenuItemImage*>(pSender);
    Rect rBtSonidoPulsado = Rect(btSonidoPulsado->getPosition().x,btSonidoPulsado->getPosition().y,
                                btSonidoPulsado->getContentSize().width,btSonidoPulsado->getContentSize().height);
    
    Rect rScrollView = Rect(scrollView->getPosition().x,scrollView->getPosition().y,
                            scrollView->getContentSize().width,scrollView->getContentSize().height);
    
    if(rBtSonidoPulsado.intersectsRect(rScrollView)){
        CCLOG("TOCADO");
    }
    
    for(int i=0;i<ultimoArrayPasado->count();i++){
        if(pSender==ultimoArrayPasado->getObjectAtIndex(i)){
            CCLOG("Sonido elegido: %i",i);
            cambiarSonido(i,true);
            
        }
    }
    cerrarModal(NULL);
}

void MiMostro::cambiarSonido(int nSonido,bool reproducir){
    
    __Array *objSonido = dynamic_cast<__Array*>(gRecursos->ObtenerSonido(nSonido));
    __String *labelSonido = dynamic_cast<__String*>(objSonido->getObjectAtIndex(indiceSonidoLabel));
    __String *valueSonido = dynamic_cast<__String*>(objSonido->getObjectAtIndex(indiceSonidoValue));
    
    if(reproducir){
        CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(valueSonido->getCString());
    }
    
    uiLabelSonido->setString(labelSonido->getCString());
    
    //guardado
    Configuracion::sonidoMiMostro = nSonido;
    UserDefault::getInstance()->setIntegerForKey("sonidoMiMostro", nSonido);
    
}

__String* MiMostro::obtenerDatoSonido(int indice){
    __String *retorno = NULL;
    __Array *objSonido = dynamic_cast<__Array*>(gRecursos->ObtenerSonido(Configuracion::sonidoMiMostro));
    if(indice==indiceSonidoLabel){
        __String *txtLabelSonido = dynamic_cast<__String*>(objSonido->getObjectAtIndex(indiceSonidoLabel));
        return txtLabelSonido;
    }else{
        __String *txtValueSonido = dynamic_cast<__String*>(objSonido->getObjectAtIndex(indiceSonidoValue));
        return txtValueSonido;
    }
    
    
}



void MiMostro::selectorColor(){
    if(Configuracion::desarrollo)
        CCLOG("Selector color");
    
    recursosBloqueados = gRecursos->obtenerRecursosBloqueados()->clone();
    recursosBloqueados->retain();
    
    CTipoRecurso *tipoRecursoColor = gRecursos->obtenerTipoRecursos(CGestorRecursos::TIPOS::Colores);
    __Array *array = __Array::createWithCapacity(tipoRecursoColor->recursos->count());
    for(int i=0;i<array->capacity();i++){
        CRecurso *rColor = tipoRecursoColor->obtenerRecurso(i);
        __String *nombre = rColor->uri;
        MenuItemImage *color = MenuItemImage::create(nombre->getCString(),nombre->getCString(),CC_CALLBACK_1(MiMostro::cambiarColorBT, this));
        color->setTag(rColor->cod->getValue());
        color->setScale(escala);
        anchoUltElementoCE = color->getContentSize().width*escala;
        if(recursoBloqueado(rColor)){
            color->setEnabled(false);
            color->setOpacity(150);
            color->runAction(TintTo::create(0,0,0,0));
        }
        array->addObject(color);
    }
    
    //ABRIMOS SELECTOR DE COLOR
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("tambores_3.mp3");
    initModal(0,array);
    desplazarModal(Configuracion::colorMiMostro);
}

void MiMostro::cambiarColorBT(cocos2d::Ref *pSender){
    
    MenuItemImage *btColorPulsado = dynamic_cast<MenuItemImage*>(pSender);
    Rect rBtColorPulsado = Rect(btColorPulsado->getPosition().x,btColorPulsado->getPosition().y,
                btColorPulsado->getContentSize().width,btColorPulsado->getContentSize().height);
    
    Rect rScrollView = Rect(scrollView->getPosition().x,scrollView->getPosition().y,
                                scrollView->getContentSize().width,scrollView->getContentSize().height);
    
    if(rBtColorPulsado.intersectsRect(rScrollView)){
        CCLOG("TOCADO");
    }
    
    for(int i=0;i<ultimoArrayPasado->count();i++){
        if(pSender==ultimoArrayPasado->getObjectAtIndex(i)){
            
            MenuItemImage *btColorTocado = dynamic_cast<MenuItemImage *>(pSender);
            CCLOG("Color elegido: %i",i);
            if(btColorPulsado->isEnabled())
                cambiarColor(btColorPulsado->getTag());
            else
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sonido_error.mp3");
        }
    }
    cerrarModal(NULL);
}

void MiMostro::cambiarColor(int nColor){

    Color3B *color = gRecursos->obtenerColorSeleccion(nColor);
    mostro_cuerpo->runAction(TintTo::create(0.5, color->r, color->g, color->b));
    
    for(int i=0;i<mostro->getChildrenCount();i++){
        Node * parte = mostro->getChildren().at(i);
        if(parte!=mostro_boca&&parte!=mostro_ojos&&parte!=mostro_accesorio)
            parte->runAction(TintTo::create(0.5, color->r, color->g, color->b));
    }
    /*mostro_orejas->runAction(TintTo::create(0.5, color->r, color->g, color->b));
    mostro_brazos->runAction(TintTo::create(0.5, color->r, color->g, color->b));
    mostro_pies->runAction(TintTo::create(0.5, color->r, color->g, color->b));*/
    mostro->setVisible(true);
    
    //guardado
    Configuracion::colorMiMostro = nColor;
    UserDefault::getInstance()->setIntegerForKey("colorMiMostro", nColor);
    
}



void MiMostro::initBtAjustes(){
    btAjustes = MenuItemImage::create("mostrosity_mimostro_bt_ajustes.png","mostrosity_mimostro_bt_ajustes_down.png",CC_CALLBACK_1(MiMostro::selectorGeneral, this));
    btAjustes->setScale(escala);
    btAjustes->setAnchorPoint(Vec2(1,1));
    btAjustes->setPosition(anchoLateralCE+anchoIndividualCuadroJuego,altoIndividalCuadroJuego);
    btAjustes->retain();
    menu->setZOrder(11);
    menu->addChild(btAjustes);
}

void MiMostro::selectorAjustes(){
    if(Configuracion::desarrollo)
        CCLOG("Selector ajustes");

    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();

//    Ajustes::desdeEscena = Ajustes::desdeMiMostro;
//    auto scene = Ajustes::createScene();
//    auto transicion = TransitionFade::create(0.3f, scene);
//    Director::getInstance()->replaceScene(transicion);
    
    auto scene = Ajustes::createScene();
    Director::getInstance()->pushScene(scene);
    
}

void MiMostro::initBtCompartir(){
    btCompartir = MenuItemImage::create("mimostro_bt_compartir.png","mimostro_bt_compartir_down.png",CC_CALLBACK_1(MiMostro::selectorGeneral, this));
    btCompartir->setScale(escala);
    btCompartir->setAnchorPoint(Vec2(1,1));
    btCompartir->setPosition(anchoLateralCE+anchoIndividualCuadroJuego-espacioBordesCuadro-(btCompartir->getContentSize().width*escala),altoIndividalCuadroJuego);
    btCompartir->retain();
    menu->setZOrder(11);
    menu->addChild(btCompartir);
}

void MiMostro::selectorCompartir(){
    
    CCLOG("%s", "sincronizando");
    sincronizar();
    
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
    
//    if(Configuracion::desarrollo)
//        CCLOG("Selector compartir");
//    
//    CCLOG("%s", "sincronizando");
//    sincronizar();
//
//    log("llamando a whatapp");
//    //borro el archivo
//    char r = Configuracion::callWhatsApp("1");
//    CCLOG("Result callWhatsapp %c", r);
//    if(r == 's'){
//        //archivo borrado
//        if(crearCaptura()){
//            CallFunc *runCallback1 = CallFunc::create(CC_CALLBACK_0(MiMostro::posCapturaMostro, this));
//            runAction(Sequence::create(DelayTime::create(0.5),runCallback1,NULL));
//        }else{
//            MessageBox("Error","No se ha guardado la captura");
//        }
//    }else{
//        MessageBox("Error","No se ha borrado la captura");
//    }

}


bool MiMostro::crearCaptura(){

    log("guardar mostro");
    
    RenderTexture* renderTexture = RenderTexture::create(visibleSize.width, visibleSize.height, Texture2D::PixelFormat::RGBA8888);
    renderTexture->begin();
    this->visit();
    renderTexture->end();
    mostrarCapaLoadingCaptura();
    if(renderTexture->saveToFile("mimostro.png", Image::Format::PNG)){
        log("ARCHIVO GUARDADO");
        return true;
    }else
        log("ARCHIVO FALLO AL GUARDAR");
    
    log("Deberia de llamar a whatsApp");
    
    return false;
}

void MiMostro::mostrarCapaLoadingCaptura(){
    if(capaLoadingCaptura==NULL){
        capaLoadingCaptura = LayerColor::create(Color4B(16,46,75,230), visibleSize.width, visibleSize.height);
        addChild(capaLoadingCaptura,999);
    }
    
    if(capaLoadingCapturaTxt==NULL){
        capaLoadingCapturaTxt = LabelTTF::create("Generando captura...","HVD_Comic_Serif_Pro.ttf", tamLetra,Size(visibleSize.width,visibleSize.height), TextHAlignment::CENTER);
        capaLoadingCapturaTxt->setColor(Color3B(255,255,255));
        capaLoadingCapturaTxt->setVerticalAlignment(TextVAlignment::CENTER);
        capaLoadingCapturaTxt->setAnchorPoint(Vec2(0, 0));
        capaLoadingCapturaTxt->setPosition(0,0);
        capaLoadingCaptura->addChild(capaLoadingCapturaTxt);
    }
}


void MiMostro::eliminarCapaLoadingCaptura(){
    
    if(capaLoadingCapturaTxt!=NULL){
        capaLoadingCaptura->removeChild(capaLoadingCapturaTxt);
        capaLoadingCapturaTxt = NULL;
    }
    if(capaLoadingCaptura!=NULL){
        removeChild(capaLoadingCaptura);
        capaLoadingCaptura = NULL;
    }
}

void MiMostro::mostrarSelectorCompartir(){
    
    if(capaLoadingCaptura==NULL){
        capaLoadingCaptura = LayerColor::create(Color4B(16,46,75,230), visibleSize.width, visibleSize.height);
        addChild(capaLoadingCaptura,999);
    }
    
    if(capaLoadingCaptura!=NULL){
//    	capaLoadingCapturaTxt->setOpacity(0);

        menuCompartir = Menu::create(NULL);
        menuCompartir->setPosition(Vec2::ZERO);
        menuCompartir->retain();
        capaLoadingCaptura->addChild(menuCompartir);
        
        btMenuCompartirTwitter = MenuItemImage::create("mimostro_bt_compartir_selector_twitter.png", "mimostro_bt_compartir_selector_twitter_down.png",CC_CALLBACK_1(MiMostro::finAccionMenuCompartir, this));
        btMenuCompartirTwitter->setAnchorPoint(Vec2(1,0.5));
        btMenuCompartirTwitter->setPosition(visibleSize.width/2-espacioBordesCuadro, visibleSize.height/2);
        menuCompartir->addChild(btMenuCompartirTwitter);
        
        btMenuCompartirFacebook = MenuItemImage::create("mimostro_bt_compartir_selector_face.png", "mimostro_bt_compartir_selector_face_down.png",CC_CALLBACK_1(MiMostro::finAccionMenuCompartir, this));
        btMenuCompartirFacebook->setAnchorPoint(Vec2(0,0.5));
        btMenuCompartirFacebook->setPosition(visibleSize.width/2+espacioBordesCuadro, visibleSize.height/2);
        menuCompartir->addChild(btMenuCompartirFacebook);
        
        btMenuCompartirCerrar = MenuItemImage::create("mimostro_bt_cerrar_modal.png", "mimostro_bt_cerrar_modal.png",CC_CALLBACK_1(MiMostro::finAccionMenuCompartir, this));
        btMenuCompartirCerrar->setScale(escala);
        btMenuCompartirCerrar->setAnchorPoint(Vec2(1,1));
        btMenuCompartirCerrar->setPosition(visibleSize.width-espacioBordesCuadro, visibleSize.height-espacioBordesCuadro);
        menuCompartir->addChild(btMenuCompartirCerrar);
        
    }

}

void MiMostro::finAccionMenuCompartir(cocos2d::Ref *boton){
    
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

void MiMostro::posCapturaMostro(){
    
    //compruebo si existe el archivo
    char r = Configuracion::callWhatsApp("2");
    if(r == 's'){
        //si existe, lo copio a la externa
        char r1 = Configuracion::callWhatsApp("3");
        if(r == 's'){
            //si ha sido copiado lo comparto
            mostrarSelectorCompartir();
        }else{
            MessageBox("Error","No se ha copiado la captura");
        }
    }else{
        log("Error existe el archivo");
        CallFunc *runCallback1 = CallFunc::create(CC_CALLBACK_0(MiMostro::posCapturaMostro, this));
        runAction(Sequence::create(DelayTime::create(0.5),runCallback1,NULL));
    }
}




void MiMostro::initCajas(){
    //Parte inicial
    /*LayerColor *capaHorizontalCajas = LayerColor::create(Color4B(179,95,38,255), anchoCajaHorizontalCE, altoCajaHorizontalCE);
    capaHorizontalCajas->setPosition(cuadroJuego->getPositionX()+espacioSuperiorBtAtrasCE,espacioBordesCuadroCE+espacioSuperiorBtAtrasCE);
    capaHorizontalCajas->setAnchorPoint(Vec2(0,0));
    capaHorizontalCajas->setLocalZOrder(20);
    addChild(capaHorizontalCajas);
    
    LayerColor *capaVerticalCajas = LayerColor::create(Color4B(179,95,38,255), anchoCajaVerticalCE, altoCajaVerticalCE);
    capaVerticalCajas->setPosition(visibleSize.width-anchoCajaVerticalCE-espacioSuperiorBtAtrasCE-espacioBordesCuadroCE,espacioBordesCuadroCE+espacioSuperiorBtAtrasCE);
    capaVerticalCajas->setAnchorPoint(Vec2(1,0));
    capaVerticalCajas->setLocalZOrder(20);
    addChild(capaVerticalCajas);*/
    
    cjHori = Sprite::create("mostrosity_mimostro_caja_horizontal.png");
    cjHori->setScale(escalaCajas);
    cjHori->setPosition(cuadroJuego->getPositionX()+espacioSuperiorBtAtrasCE,espacioBordesCuadroCE+espacioSuperiorBtAtrasCE);
    cjHori->setAnchorPoint(Vec2(0,0));
    cjHori->setLocalZOrder(20);
    addChild(cjHori);
    
    
    cjVert = Sprite::create("mostrosity_mimostro_caja_vertical.png");
    cjVert->setScale(escalaCajas);
    cjVert->setPosition(visibleSize.width-espacioSuperiorBtAtrasCE-espacioBordesCuadroCE,espacioBordesCuadroCE+espacioSuperiorBtAtrasCE);
    cjVert->setAnchorPoint(Vec2(1,0));
    cjVert->setLocalZOrder(20);
    addChild(cjVert);
    
}

void MiMostro::initCapasPartes(){
    //horizontales
    aCapasPartesHor = __Array::createWithCapacity(4);
    aCapasPartesHor->retain();
    //25 % de ancho de cajas
    float anchoPorParte = ((cjHori->getContentSize().width)-(margenEntreCajasCE*5))/4;
    float altoPorParte = cjHori->getContentSize().height;
    for (int i=0;i<4; i++) {
        LayerColor *capa = LayerColor::create(Color4B(i*50,i*50,i*50,opacidadCapasSeleccion),anchoPorParte, altoPorParte);
        capa->setPosition((i*anchoPorParte)+(margenEntreCajasCE*(i+1)),0);
        capa->setAnchorPoint(Vec2(0,0));
        capa->retain();
        aCapasPartesHor->addObject(capa);
        cjHori->addChild(capa);
        
        LabelTTF *txt = LabelTTF::create(obtenerTextoCaja(true, i+1),"HVD_Comic_Serif_Pro.ttf", tamLetra,Size(anchoPorParte,tamLetra+(20)), TextHAlignment::CENTER);
        txt->setColor(obtenerColorTxtCaja(true,i+1));
        txt->setVerticalAlignment(TextVAlignment::CENTER);
        txt->setAnchorPoint(Vec2(0, 0));
        txt->setPosition(0,10*escala);//10 por poner algo de margen
        capa->addChild(txt, 1);
        
    }
    
    //verticales
    aCapasPartesVer = __Array::createWithCapacity(4);
    aCapasPartesVer->retain();
    //25 % de ancho de cajas
    altoPorParte = ((cjVert->getContentSize().height))/4;
    anchoPorParte = cjVert->getContentSize().width;
    for (int i=0;i<4; i++) {
        LayerColor *capa = LayerColor::create(Color4B(i*50,i*50,i*50,opacidadCapasSeleccion),anchoPorParte, altoPorParte);
        capa->setPosition(0,(i*altoPorParte));
        capa->setAnchorPoint(Vec2(0,0));
        capa->retain();
        aCapasPartesVer->addObject(capa);
        cjVert->addChild(capa);
        
        LabelTTF *txt = LabelTTF::create(obtenerTextoCaja(false, i+1),"HVD_Comic_Serif_Pro.ttf", tamLetra,Size(anchoPorParte,tamLetra+(20)), TextHAlignment::CENTER);
        txt->setColor(obtenerColorTxtCaja(false,i+1));
        txt->setVerticalAlignment(TextVAlignment::CENTER);
        txt->setAnchorPoint(Vec2(0, 0));
        txt->setPosition(0,0);
        capa->addChild(txt, 1);
    }
}

void MiMostro::eliminarTextos() {
    
    cjHori->removeAllChildren();
    cjVert->removeAllChildren();
    btSonido->removeChild(textSonido);
    textSonido = NULL;
    
    textSonido = CCLabelTTF::create(LanguageManager::getInstance()->getString("MiMostroBtSonido"), "HVD_Comic_Serif_Pro.ttf", tamLetra*0.8,Size(btSonido->getContentSize().width, tamLetraCE*2), TextHAlignment::CENTER);
    textSonido->setColor(Color3B(194,233,251));
    textSonido->setVerticalAlignment(TextVAlignment::CENTER);
    textSonido->setAnchorPoint(Vec2(0, 0));
    textSonido->setPosition(0,0);
    btSonido->addChild(textSonido);
    
}

int MiMostro::comprobarToqueCajas(Touch * toque){
    if(!escuchadoresBtyCapas)
        return -1;
    
    int numero = -1;
    for(int i=0;i<aCapasPartesHor->count();i++){
        LayerColor * capaActual = dynamic_cast<LayerColor*>(aCapasPartesHor->getObjectAtIndex(i));
        if(Configuracion::comprobarToque(toque, capaActual)){
            numero = i;
        }
    }

    for(int i=0;i<aCapasPartesVer->count();i++){
        LayerColor * capaActual = dynamic_cast<LayerColor*>(aCapasPartesVer->getObjectAtIndex(i));
        if(Configuracion::comprobarToque(toque, capaActual)){
            numero = i+4;
        }
    }
    
    if(numero!=-1){
        return numero;
    }else{
        return -1;
    }
    
}

int MiMostro::comprobarToquePartes(Touch * toque){
    if(!escuchadoresBtyCapas)
        return -1;
    
    int numero = -1;
    
    __Array *partesTocadas = __Array::createWithCapacity(mostro->getChildrenCount());
    
    for(int i=0;i<mostro->getChildrenCount();i++){
        Node * parteActual = dynamic_cast<Node*>(mostro->getChildren().at(i));
        if(Configuracion::comprobarToque(toque, parteActual)){
            partesTocadas->addObject(parteActual);
        }
    }
    
    int ultimoZ = -1;
    for(int i=0;i<partesTocadas->count();i++){
        Node * parteActual = dynamic_cast<Node*>(partesTocadas->getObjectAtIndex(i));
        int tagActual =parteActual->getTag();
        int codRecursoActual = obtenerActualCodRecurso(gRecursos->obtenerTipoRecursoPorInt(tagActual));
        
        //cogo el que tenga la capa más alta y que sea visible.
        if(parteActual->getLocalZOrder()>=ultimoZ&&codRecursoActual!=0&&codRecursoActual!=-1){
            ultimoZ = parteActual->getLocalZOrder();
            numero = parteActual->getTag();
        }
        
    }
    
    return numero;
}


std::string MiMostro::obtenerTextoCaja(bool Hori, int iNumero){
    
    __String* key;
    if(Hori)
        key = String::createWithFormat("MiMostroCaja_Hori_%i",iNumero);
    else
        key = String::createWithFormat("MiMostroCaja_Vert_%i",iNumero);
    
    
    return LanguageManager::getInstance()->getString(key->getCString()).c_str();
}

Color3B MiMostro::obtenerColorTxtCaja(bool Hori, int iNumero){
    Color3B color;
    
    if(Hori){
        switch (iNumero) {
            case 1:
                color = Color3B(224,35,35);
                break;
            case 2:
                color = Color3B(41,128,199);
                break;
            case 3:
                color = Color3B(132,165,1);
                break;
            case 4:
                color = Color3B(182,61,182);
                break;
        }
    }else{
        switch (iNumero) {
            case 1:
                color = Color3B(240,0,78);
                break;
            case 2:
                color = Color3B(149,99,49);
                break;
            case 3:
                color = Color3B(240,61,0);
                break;
            case 4:
                color = Color3B(40,164,164);
                break;
        }
    }
    
    
    return color;
}

void MiMostro::initMostro(){
    
    //la posicion horizontal del mostro sera la mitad entre el boton color y la paleta vertical de elementos.
    //posicion derecha de btColor
    float xBtColor = (btColor->getPositionX()+(btColor->getContentSize().width*escalaCajas));
    //posición izquierda de cjVert
    float xCjVert = (cjVert->getPositionX()-(cjVert->getContentSize().width*escalaCajas));
    
    float x = xBtColor+((xCjVert-xBtColor)/2);
    
    mostro = LayerColor::create(Color4B(255,255,250,0), 200, 200);
    mostro->setPosition(x,cuadroJuegoInterior->getPositionY()+cuadroJuegoInterior->getContentSize().height);
    mostro->setLocalZOrder(21);
    mostro->setVisible(true);
    addChild(mostro);
    
    mostro_cuerpo = Sprite::create("mostrosity_mimostro_mostro_cuerpo.png");
    mostro->addChild(mostro_cuerpo);
    
    
    mostro_pies = Sprite::create("recursoVacioMostro.png");
    mostro->addChild(mostro_pies);
    
    
    mostro_alas = Sprite::create("recursoVacioMostro.png");
    mostro->addChild(mostro_alas);
    
    
    mostro_brazos = Sprite::create("recursoVacioMostro.png");
    mostro->addChild(mostro_brazos);
    
    
    mostro_ojos = Sprite::create("recursoVacioMostro.png");
    mostro->addChild(mostro_ojos);
    
    
    mostro_boca = Sprite::create("recursoVacioMostro.png");
    mostro->addChild(mostro_boca);
    
    mostro_pelo = Sprite::create("recursoVacioMostro.png");
    mostro->addChild(mostro_pelo);
    
    mostro_orejas = Sprite::create("recursoVacioMostro.png");
    mostro->addChild(mostro_orejas);
    
    mostro_accesorio =Sprite::create("recursoVacioMostro.png");
    mostro->addChild(mostro_accesorio);
    
    mostro->setPositionY(mostro->getPositionY()+((mostro_cuerpo->getContentSize().height*escala)/4));
}

void MiMostro::initMostroPropiedades(CGestorRecursos::TIPOS tipo){
    
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
    
    if(tipo==-1||tipo==CGestorRecursos::TIPOS::Alas){
        mostro_alas->setScale(escala);
        mostro_alas->setAnchorPoint(Vec2(0.5,0.5));
        mostro_alas->setPosition(0,200*escala);
        mostro_alas->setLocalZOrder(1);
        mostro_alas->setTag(Configuracion::rcsTipoAlas);
        mostro_alas->setRotation(0);
    }
    
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
    
    if(tipo==-1||tipo==CGestorRecursos::TIPOS::Pelo){
        mostro_pelo->setScale(escala);
        mostro_pelo->setAnchorPoint(Vec2(0.5,0.5));
        mostro_pelo->setPosition(0,270*escala);
        mostro_pelo->setLocalZOrder(6);
        mostro_pelo->setTag(Configuracion::rcsTipoPelo);
        mostro_pelo->setRotation(0);
    }
    
    if(tipo==-1||tipo==CGestorRecursos::TIPOS::Orejas){
        mostro_orejas->setScale(escala);
        mostro_orejas->setAnchorPoint(Vec2(0.5,0.5));
        mostro_orejas->setPosition(0,370*escala);
        mostro_orejas->setLocalZOrder(2);
        mostro_orejas->setTag(Configuracion::rcsTipoOrejas);
        mostro_orejas->setRotation(0);
    }
    
    if(tipo==-1||tipo==CGestorRecursos::TIPOS::Accesorio){
        mostro_accesorio->setScale(escala);
        mostro_accesorio->setAnchorPoint(Vec2(0.5,0.5));
        mostro_accesorio->setPosition(0,0);
        mostro_accesorio->setLocalZOrder(7);
        mostro_accesorio->setTag(Configuracion::rcsTipoAccesorio);
        mostro_accesorio->setRotation(0);
    }
    
}

void MiMostro::initRecursos(){
    gRecursos = new CGestorRecursos();
    
    recursosBloqueados = gRecursos->obtenerRecursosBloqueados()->clone();
    recursosBloqueados->retain();
}

bool MiMostro::recursoBloqueado(CRecurso *recurso){
    log("_________recurso solicitantes cod %i tipo %i ",recurso->cod->getValue(),recurso->tipoRecurso->getValue());
    for(int i=0;i<recursosBloqueados->count();i++){
        CRecurso *recursoActual = dynamic_cast<CRecurso*>(recursosBloqueados->getObjectAtIndex(i));
        log("recurso actual cod %i tipo %i ",recursoActual->tipoRecurso->getValue(),recursoActual->cod->getValue());
        if(recursoActual->tipoRecurso->getValue() == recurso->tipoRecurso->getValue()&&recursoActual->cod->getValue() == recurso->cod->getValue())
            return true;
    }
    return false;
}

void MiMostro::iniciarCajaXNumero(int nCaja){
    switch (nCaja) {
        case MiMostro::cajas::nCajaOjos:
            TipoRecursoSelecionado = CGestorRecursos::TIPOS::Ojos;
            break;
        case MiMostro::cajas::nCajaDientes:
            TipoRecursoSelecionado = CGestorRecursos::TIPOS::Dientes;
            break;
        case MiMostro::cajas::nCajaOrejas:
            TipoRecursoSelecionado = CGestorRecursos::TIPOS::Orejas;
            break;
        case MiMostro::cajas::nCajaBrazos:
            TipoRecursoSelecionado = CGestorRecursos::TIPOS::Brazos;
            break;
        case MiMostro::cajas::nCajaAccesorios:
            TipoRecursoSelecionado = CGestorRecursos::TIPOS::Accesorio;
            break;
        case MiMostro::cajas::nCajaPelo:
            TipoRecursoSelecionado = CGestorRecursos::TIPOS::Pelo;
            break;
        case MiMostro::cajas::nCajaAlas:
            TipoRecursoSelecionado = CGestorRecursos::TIPOS::Alas;
            break;
        case MiMostro::cajas::nCajaPatas:
            TipoRecursoSelecionado = CGestorRecursos::TIPOS::Pies;
            break;
    }
    
    //LLAMAMOS AL SELECTOR
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("tambores_3.mp3");
    selectorRecurso();
}

void MiMostro::iniciarCajaXRecurso(int nRecurso){
    TipoRecursoSelecionado = gRecursos->obtenerTipoRecursoPorInt(nRecurso);
    selectorRecurso();
}


int MiMostro::obtenerActualCodRecurso(CGestorRecursos::TIPOS Tipo){
    
    switch (Tipo) {
        case CGestorRecursos::TIPOS::Ojos:
            return Configuracion::ojosMiMostro;
            break;
        case CGestorRecursos::TIPOS::Dientes:
            return Configuracion::dientesMiMostro;
            break;
        case CGestorRecursos::TIPOS::Orejas:
            return Configuracion::orejasMiMostro;
            break;
        case CGestorRecursos::TIPOS::Brazos:
            return Configuracion::brazosMiMostro;
            break;
        case CGestorRecursos::TIPOS::Pies:
            return Configuracion::piesMiMostro;
            break;
        case CGestorRecursos::TIPOS::Pelo:
            return Configuracion::peloMiMostro;
            break;
        case CGestorRecursos::TIPOS::Alas:
            return Configuracion::alasMiMostro;
            break;
        case CGestorRecursos::TIPOS::Accesorio:
            return Configuracion::accesorioMiMostro;
            break;

            
        default:
            return 0;
            break;
    }
}

int MiMostro::guardarActualCodRecurso(CGestorRecursos::TIPOS Tipo,int codElemento){
    
    switch (Tipo) {
        case CGestorRecursos::TIPOS::Ojos:
            Configuracion::ojosMiMostro = codElemento;
            UserDefault::getInstance()->setIntegerForKey("ojosMiMostro", codElemento);
            break;
        case CGestorRecursos::TIPOS::Dientes:
            Configuracion::dientesMiMostro = codElemento;
            UserDefault::getInstance()->setIntegerForKey("dientesMiMostro", codElemento);
            break;
        case CGestorRecursos::TIPOS::Orejas:
            Configuracion::orejasMiMostro = codElemento;
            UserDefault::getInstance()->setIntegerForKey("orejasMiMostro", codElemento);
            break;
        case CGestorRecursos::TIPOS::Brazos:
            Configuracion::brazosMiMostro = codElemento;
            UserDefault::getInstance()->setIntegerForKey("brazosMiMostro", codElemento);
            break;
        case CGestorRecursos::TIPOS::Pies:
            Configuracion::piesMiMostro = codElemento;
            UserDefault::getInstance()->setIntegerForKey("piesMiMostro", codElemento);
            break;
        case CGestorRecursos::TIPOS::Alas:
            Configuracion::alasMiMostro = codElemento;
            UserDefault::getInstance()->setIntegerForKey("alasMiMostro", codElemento);
            break;
        case CGestorRecursos::TIPOS::Pelo:
            Configuracion::peloMiMostro = codElemento;
            UserDefault::getInstance()->setIntegerForKey("peloMiMostro", codElemento);
            break;
        case CGestorRecursos::TIPOS::Accesorio:
            Configuracion::accesorioMiMostro = codElemento;
            UserDefault::getInstance()->setIntegerForKey("accesorioMiMostro", codElemento);
            break;
            
        default:
            return 0;
            break;
    }
}

Sprite* MiMostro::obtenerPartePorTipo(CGestorRecursos::TIPOS Tipo){
    switch (Tipo) {
        case CGestorRecursos::TIPOS::Ojos:
            return mostro_ojos;
            break;
        case CGestorRecursos::TIPOS::Dientes:
            return mostro_boca;
            break;
        case CGestorRecursos::TIPOS::Orejas:
            return mostro_orejas;
            break;
        case CGestorRecursos::TIPOS::Brazos:
            return mostro_brazos;
            break;
        case CGestorRecursos::TIPOS::Pies:
            return mostro_pies;
            break;
        case CGestorRecursos::TIPOS::Alas:
            return mostro_alas;
            break;
        case CGestorRecursos::TIPOS::Pelo:
            return mostro_pelo;
            break;
        case CGestorRecursos::TIPOS::Accesorio:
            return mostro_accesorio;
            break;
            
            
        default:
            return 0;
            break;
    }
}



void MiMostro::selectorRecurso(){
    recursosBloqueados = gRecursos->obtenerRecursosBloqueados()->clone();
    recursosBloqueados->retain();
    
    ultimoTipoRecurso = gRecursos->obtenerTipoRecursos(TipoRecursoSelecionado);
    if(ultimoTipoRecurso==NULL)
        return;
    ultimoTipoRecurso->retain();
    
    if(Configuracion::desarrollo)
        CCLOG("Selector %s",ultimoTipoRecurso->nombre->getCString());
    
    //obj no bloqueados
    __Array *array = __Array::createWithCapacity(ultimoTipoRecurso->recursos->count());
    __Array *arrayBloqueados = __Array::createWithCapacity(ultimoTipoRecurso->recursos->count());
    int indiceElegido = 0;
    for(int i=0;i<array->capacity();i++){
        CRecurso *recursoActual = dynamic_cast<CRecurso*>(ultimoTipoRecurso->recursos->getObjectAtIndex(i));
        if(recursoActual->cod->getValue()==obtenerActualCodRecurso(TipoRecursoSelecionado)){
            indiceElegido = i;
        }
        bool bloqueado = false;
        Sprite *uno = NULL;
        Sprite *dos = NULL;
        if(!recursoBloqueado(recursoActual)){
            int valorActualDelRecurso = obtenerActualCodRecurso(TipoRecursoSelecionado);
            if(recursoActual->cod->getValue()==valorActualDelRecurso){
                uno = Sprite::create("fondo_transparente_select.png");
                dos = Sprite::create("fondo_transparente_select.png");
            }else{
                uno = Sprite::create("fondo_transparente.png");
                dos = Sprite::create("fondo_transparente.png");
            }
        }else{
            bloqueado = true;
            uno = Sprite::create("fondo_transparente_rojo.png");
            dos = Sprite::create("fondo_transparente_rojo.png");
        }
        
        Sprite *subUno = Sprite::create(recursoActual->uri->getCString());
        Sprite *subDos = Sprite::create(recursoActual->uri->getCString());
        subUno->setAnchorPoint(Vec2(0.5,0.5));
        subDos->setAnchorPoint(Vec2(0.5,0.5));
        subUno->setPosition(uno->getContentSize().width/2, uno->getContentSize().height/2);
        subDos->setPosition(dos->getContentSize().width/2, dos->getContentSize().height/2);
        
        float escalaDentroCuadro = uno->getContentSize().width/subUno->getContentSize().width;
        if(escalaDentroCuadro<1){
            subUno->setScale(escalaDentroCuadro);
            subDos->setScale(escalaDentroCuadro);
        }
        
        
        //subUno->setPosition(subUno->getPositionX()+recursoActual->x->getValue(),subUno->getPositionY()+recursoActual->y->getValue());
        //subUno->setLocalZOrder(subUno->getLocalZOrder()+recursoActual->z->getValue());
        subUno->setRotation(subUno->getRotation()+recursoActual->giro->getValue());
        
        //subDos->setPosition(subDos->getPositionX()+recursoActual->x->getValue(),subDos->getPositionY()+recursoActual->y->getValue());
        //subDos->setLocalZOrder(subDos->getLocalZOrder()+recursoActual->z->getValue());
        subDos->setRotation(subDos->getRotation()+recursoActual->giro->getValue());
        
        if(bloqueado){
            subUno->setOpacity(0);
            subDos->setOpacity(0);
            subUno->runAction(Sequence::create(TintTo::create(0,0, 0,0),FadeTo::create(0,100),NULL));
            subDos->runAction(Sequence::create(TintTo::create(0,0, 0,0),FadeTo::create(0,100),NULL));
        }
        
        uno->addChild(subUno);
        dos->addChild(subDos);
        log("bt tag metido %i",recursoActual->cod->getValue());
        MenuItemSprite *btRecurso = MenuItemSprite::create(uno,dos,CC_CALLBACK_1(MiMostro::cambiarRecursoBT, this));
        btRecurso->setTag(recursoActual->cod->getValue());
        btRecurso->setScale(escala);
        anchoUltElementoCE = btRecurso->getContentSize().width*escala;
        if(!bloqueado)
            array->addObject(btRecurso);
        else{
            arrayBloqueados->addObject(btRecurso);
        }
    }
    

    for(int i=0;i<arrayBloqueados->count();i++){
        MenuItemSprite *btRecursoBloqueadoActual = dynamic_cast<MenuItemSprite *>(arrayBloqueados->getObjectAtIndex(i));
        array->addObject(btRecursoBloqueadoActual);
    }


    initModal(0,array);
    desplazarModal(indiceElegido);
}


void MiMostro::cambiarRecursoBT(cocos2d::Ref *pSender){
    
    MenuItemSprite *btPulsado = dynamic_cast<MenuItemSprite*>(pSender);
    cambiarRecurso(TipoRecursoSelecionado,btPulsado->getTag());
    
}

void MiMostro::cambiarRecurso(CGestorRecursos::TIPOS Tipo,int codElemento){
    recursosBloqueados = gRecursos->obtenerRecursosBloqueados()->clone();
    recursosBloqueados->retain();
    
    
    ultimoTipoRecurso = gRecursos->obtenerTipoRecursos(Tipo);
    if(ultimoTipoRecurso==NULL){
        log("ERROR DEPUERAR cambiarRecurso()");
        return;
    }
    
    bool correcto = false;
    CCLOG("%s selecionado %i",ultimoTipoRecurso->nombre->getCString(),codElemento);
    for(int i=0;i<ultimoTipoRecurso->recursos->count();i++){
        CRecurso *recursoActual = dynamic_cast<CRecurso*>(ultimoTipoRecurso->recursos->getObjectAtIndex(i));
        if(codElemento == 0){
            Sprite *parteMostro = obtenerPartePorTipo(Tipo);
            parteMostro->setVisible(false);
            correcto = true;
            break;
        }else if(!recursoBloqueado(recursoActual)&&codElemento == recursoActual->cod->getValue()){
            /*SI ESTA DESBLOQUEADO*/
            Sprite *parteMostro = obtenerPartePorTipo(Tipo);
            parteMostro->setVisible(true);
            parteMostro->setTexture(recursoActual->uri->getCString());
            initMostroPropiedades(Tipo);
            float x = parteMostro->getPositionX()+(recursoActual->x->getValue()*escala);
            float y = parteMostro->getPositionY()+(recursoActual->y->getValue()*escala);
            int z = parteMostro->getLocalZOrder()+recursoActual->z->getValue();
            int giro = parteMostro->getRotation()+recursoActual->giro->getValue();
            
            parteMostro->setPosition(x,y);
            parteMostro->setLocalZOrder(z);
            parteMostro->setRotation(giro);
            
            
            correcto = true;
            break;
        }
    }
    
    if(!correcto)/*SI ESTA BLOQUEADO*/
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sonido_error.mp3");
    else{
        cerrarModal(NULL);
        guardarActualCodRecurso(TipoRecursoSelecionado,codElemento);
    }
    

}



void MiMostro::cerrarModal(cocos2d::Ref *pSender){
    CallFunc *runCallback1 = CallFunc::create(CC_CALLBACK_0(MiMostro::destrozarModal, this));
    //Sequence *secuencia = Sequence::create(FadeOut::create(0.5),runCallback1, NULL);
    //bgModal->runAction(secuencia);
    if(bgModal!=NULL)
        bgModal->runAction(runCallback1);
    removeChild(spBtDesplizamiento);
    spBtDesplizamiento = NULL;
    removeChild(spBarraBtDesplizamiento);
    spBarraBtDesplizamiento = NULL;
}

void MiMostro::destrozarModal(){
    //reactivo botones
    escuchadoresBtyCapas = true;
    
    scrollView = NULL;
    bgModal->removeAllChildren();
    bgModal->removeAllComponents();
    bgModal->setTag(999);
    removeChildByTag(999);
    bgModal = NULL;
}

void MiMostro::initModal(int tipo,__Array *elementos){
    //desactivo bt atras
    escuchadoresBtyCapas = false;
    
    ultimoArrayPasado = elementos;
    ultimoArrayPasado->retain();
    
    bgModal = LayerColor::create(Color4B(16,46,75,230), visibleSize.width, visibleSize.height);
    bgModal->setPosition(0,0);
    bgModal->setLocalZOrder(30);
    addChild(bgModal);
    
    modal = LayerColor::create(Color4B(23,71,109,255), visibleSize.width, altoModalCE);
    modal->setPosition(0, (visibleSize.height-altoModalCE)/2);
    bgModal->addChild(modal);
    
    
    
    MenuItemImage *btDesIzq = MenuItemImage::create("mostrosity_mimostro_bt_modal_des_izq.png", "mostrosity_mimostro_bt_modal_des_izq.png",CC_CALLBACK_1(MiMostro::DesplazarIzquierda, this));
    btDesIzq->setScale(escala);
    btDesIzq->setPosition(0+espacioSuperiorBtAtrasCE, altoModalCE/2);
    btDesIzq->setAnchorPoint(Vec2(0,0.5));
    
    MenuItemImage *btDesDer = MenuItemImage::create("mostrosity_mimostro_bt_modal_des_der.png", "mostrosity_mimostro_bt_modal_des_der.png",CC_CALLBACK_1(MiMostro::DesplazarDerecha, this));
    btDesDer->setScale(escala);
    btDesDer->setPosition(visibleSize.width-espacioSuperiorBtAtrasCE, altoModalCE/2);
    btDesDer->setAnchorPoint(Vec2(1,0.5));
    
    
    
    float yActual = altoModalCE;
    
    modalTitulo = LabelTTF::create(LanguageManager::getInstance()->getString("MiMostroTituloModal_1"),"HVD_Comic_Serif_Pro.ttf", tamLetraModalTituloCE,Size(visibleSize.width,(tamLetraModalTituloCE +(1*margenModal))), TextHAlignment::CENTER);
    modalTitulo->setColor(verdeModal);
    modalTitulo->setVerticalAlignment(TextVAlignment::CENTER);
    modalTitulo->setAnchorPoint(Vec2(0, 1));
    modalTitulo->setPosition(0,altoModalCE);
    modalTitulo->setLocalZOrder(2);
    modal->addChild(modalTitulo);
    
    yActual = yActual-modalTitulo->getContentSize().height;
    
    //obtengo el marco de la ventana y le aplico unos bordes para no pisar el marco
    float correspondiente = ((anchoUltElementoCE+margenElementosCE)*elementos->count())+margenElementosCE;
    anchoContenedorScroll = correspondiente;
    altoContenedorScroll = modal->getContentSize().height-modalTitulo->getContentSize().height-margenModal;
    
    //capa inferior que ha de ser mas grande que la ventana que permite ver el contenido
    scrollContainer = Layer::create();
    scrollContainer->setAnchorPoint(Vec2::ZERO);
    scrollContainer->setContentSize(Size(anchoContenedorScroll,altoContenedorScroll));
    scrollContainer->setColor(Color3B(45,65,12));
    scrollContainer->retain();
    
    //este es el fondo seria opcional porque el contenido se podria meter en el scrollContainer pero es una ejemplo de que se le puede aplicar un fondo cualquiera. esta debe tener el mismo tamaño.
    fondoContenedor = LayerColor::create(Color4B(0,53,0,00), scrollContainer->getContentSize().width, scrollContainer->getContentSize().height);
    fondoContenedor->setAnchorPoint(Vec2::ZERO);
    fondoContenedor->setPosition(0,0);
    fondoContenedor->retain();
    scrollContainer->addChild(fondoContenedor);
    
    
    /*LabelTTF *txt = LabelTTF::create("Prueba texto inferior","HVD_Comic_Serif_Pro.ttf", 50,Size(anchoContenedorScroll,altoContenedorScroll), TextHAlignment::CENTER);
    txt->setVerticalAlignment(TextVAlignment::CENTER);
    txt->setAnchorPoint(Vec2(0, 0));
    txt->setPosition(0,0);
    fondoContenedor->addChild(txt, 1);
     */
    
    anchoBtDespCE = (btDesIzq->getContentSize().width*escala);
    //esta es la ventana que permite que se vea el contenido del contenedor ocultando lo demas.
    anchoScrollView = visibleSize.width-(margenModal*2)-(anchoBtDespCE*2);
    scrollView = ScrollView::create(Size(anchoScrollView,altoContenedorScroll), scrollContainer);
    scrollView->setPosition(margenModal+anchoBtDespCE,margenModal);
    scrollView->setDirection(ScrollView::Direction::HORIZONTAL);
    scrollView->setContentOffset(scrollView->maxContainerOffset(), false);
    //animacion de movimiento
    //scrollView->setContentOffsetInDuration(scrollView->minContainerOffset(),1);
    scrollView->setAnchorPoint(Vec2(0,0));
    modal->addChild(scrollView);
    
    Menu *menuModal;
    if(tipo==modalConMenu){
        menuModal = Menu::create(NULL);
        menuModal->setPosition(Vec2::ZERO);
        menuModal->retain();
        scrollContainer->addChild(menuModal);
    }
    
    for(int i=0;i<elementos->count();i++){
        Node *elemento = dynamic_cast<Node*>(elementos->getObjectAtIndex(i));
        if(tipo == modalConMenu){
            menuModal->addChild(elemento);
        }else{
            scrollContainer->addChild(elemento);
        }
        float y = (altoContenedorScroll-(elemento->getContentSize().height*escala))/2;
        
        elemento->setPosition((elemento->getContentSize().width*escala*i)+(margenElementosCE*i), y);
        elemento->setAnchorPoint(Vec2(0,0));
    }
    
    Menu *menuModalBT = Menu::create(btDesIzq,btDesDer, NULL);
    menuModalBT->setContentSize(visibleSize);
    menuModalBT->setPosition(0,0);
    modal->addChild(menuModalBT,50);
    
    float espacioSupModal = (visibleSize.height - modal->getContentSize().height)/2;
    float altoBt = modal->getContentSize().height+espacioSupModal-espacioBordesCuadroCE;
    
    MenuItemImage *btCerrarModal = MenuItemImage::create("mimostro_bt_cerrar_modal.png","mimostro_bt_cerrar_modal_down.png",CC_CALLBACK_1(MiMostro::cerrarModal, this));
    btCerrarModal->setScale(escala);
    btCerrarModal->setAnchorPoint(Vec2(1,1));
    btCerrarModal->setPosition(visibleSize.width-espacioBordesCuadroCE,altoBt);
    menuModalBT->addChild(btCerrarModal);
    
    //barra de scroll
    spBtDesplizamiento = Sprite::create("mimostro_bt_scroll.png");
    spBtDesplizamiento->setScale(escala);
    spBtDesplizamiento->setAnchorPoint(Vec2(0.5,0));
    spBtDesplizamiento->setPosition(visibleSize.width/2,margenModal);
    spBtDesplizamiento->setOpacity(0);
    addChild(spBtDesplizamiento,999);
    
    spBarraBtDesplizamiento = Sprite::create("ajustes_barra_sonido.png");
    float escalaBarra = visibleSize.width/spBarraBtDesplizamiento->getContentSize().width;
    spBarraBtDesplizamiento->setScale(escalaBarra);
    spBarraBtDesplizamiento->setAnchorPoint(Vec2(0.5,0));
    spBarraBtDesplizamiento->setPosition(visibleSize.width/2,margenModal);
    spBarraBtDesplizamiento->setOpacity(0);
    addChild(spBarraBtDesplizamiento,998);
    
}

void MiMostro::desplazarModal(int nElemento){
    
    Vec2 posicion = scrollView->getContentOffset();
    posicion.x = anchoUltElementoCE*(nElemento-1)*-1;
    scrollView->setContentOffset(posicion);
    
    float anchoPorElemento = visibleSize.width/ultimoArrayPasado->count();
    desplazarBtDesplizamiento(anchoPorElemento*(ultimoArrayPasado->count()-nElemento));
}


void MiMostro::update(float dt){
    

}

void MiMostro::UpdateScrollView(float dt){
    
    if(scrollView!= NULL){
        if(anchoUltElementoCE!=0){

            //CONTROL DE SCROLLVIEW PASADO DE POSICION
            //CCLOG("Scroll valido y ancho");
            Vec2 posicion = scrollView->getContentOffset();
            float xMaxDer = (anchoContenedorScroll*-1)+(anchoScrollView);
            float xMaxIzq = 0;
            if(anchoContenedorScroll>anchoScrollView){
                if(posicion.x<xMaxDer-(anchoUltElementoCE*1.10)){
                    //scrollView->stopAllActions();
                    posicion.x = xMaxDer;
                    if(scrollView->getNumberOfRunningActions()==0)
                        scrollView->setContentOffset(posicion);
                }else if(posicion.x>xMaxIzq+(anchoUltElementoCE*1.10)){
                    //scrollView->stopAllActions();
                    posicion.x = xMaxIzq;
                    if(scrollView->getNumberOfRunningActions()==0)
                        scrollView->setContentOffset(posicion);
                }
            }
        }
    
    }
}

void MiMostro::DesplazarDerecha(Ref* pSender){
    
    if(scrollView!=NULL){
        Vec2 posicion = scrollView->getContentOffset();
        
        float xMax = (anchoContenedorScroll*-1)+(anchoScrollView);
        float intervalo = (anchoUltElementoCE+margenElementosCE);
        float diferencia = xMax - posicion.x;
        CCLOG("der___  x %f x %f",posicion.x,xMax);
        if(posicion.x>xMax){
            if(diferencia<intervalo){
                posicion.x = posicion.x - intervalo;
            }else{
                posicion.x = xMax;
            }
            
        }else{
            CCLOG("NO MOVIDO");
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("tambores_3.mp3");
        }
        if(scrollView->getNumberOfRunningActions()==0){
            scrollView->setContentOffsetInDuration(posicion,0.3);
            float posXbtBarra = (visibleSize.width*posicion.x)/xMax;
            desplazarBtDesplizamiento(visibleSize.width-posXbtBarra);
        }
    }
    
}

void MiMostro::DesplazarIzquierda(Ref* pSender){
    
    if(scrollView!=NULL){
        Vec2 posicion = scrollView->getContentOffset();
        
        float xMax = (anchoContenedorScroll*-1)+(anchoScrollView);
        float intervalo = (anchoUltElementoCE+margenElementosCE)*-1;
        float diferencia = posicion.x - intervalo;
        CCLOG("izq___  x %f",posicion.x);
        if(posicion.x<0){
            if(diferencia<intervalo){
                posicion.x = posicion.x - intervalo;
            }else{
                posicion.x = 0;
            }
        }else{
            CCLOG("NO MOVIDO");
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("tambores_3.mp3");
        }
        if(scrollView->getNumberOfRunningActions()==0){
            scrollView->setContentOffsetInDuration(posicion,0.3);
            float posXbtBarra = (visibleSize.width*posicion.x)/xMax;
            desplazarBtDesplizamiento(visibleSize.width-posXbtBarra);
        }
    }

}

void MiMostro::desplazarBtDesplizamiento(float xPos){
    
    float extremoDerecho = visibleSize.width-((spBtDesplizamiento->getContentSize().width*escala)/2);
    float extremoIzquierdo = (spBtDesplizamiento->getContentSize().width*escala)/2;
    if(xPos<extremoIzquierdo){
        spBtDesplizamiento->setPositionX(extremoIzquierdo);
    }else if(xPos>extremoDerecho){
        spBtDesplizamiento->setPositionX(extremoDerecho);
    }else{
        spBtDesplizamiento->setPositionX(xPos);
    }
    
}

//--------ESCUCHADORES-------//





void MiMostro::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event){
    irAtras(NULL);
}

bool MiMostro::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
    if(!escuchadores){
        return false;
    }
    if(Configuracion::desarrollo)
        log("BEGAN %f %f",touch->getLocation().x,touch->getLocation().y);
    
    if(Configuracion::comprobarToque(touch, uiLabelSonido)){
        cambiarSonido(Configuracion::sonidoMiMostro, true);
    }
    
    if(spBtDesplizamiento != NULL && Configuracion::comprobarToque(touch, spBtDesplizamiento)){
        CCLOG("TOCADO spBtDesplizamiento");
        moviendoScroll = true;
        return true;
    }
    
    if(modal!=NULL&&bgModal!=NULL&&!escuchadoresBtyCapas){
        if(Configuracion::comprobarToque(touch, bgModal)){
            if(!Configuracion::comprobarToque(touch, modal)){
                destrozarModal();
                CCLOG("TOCADO EXTERIOR DE MODAL");
            }
            
        }
    }else{
        int iCajaTocada = comprobarToqueCajas(touch);
        if (iCajaTocada!=-1&&escuchadoresBtyCapas) {
            CCLOG("TOCADA CAJA %i",iCajaTocada);
            iniciarCajaXNumero(iCajaTocada);
        }else{
            int iParteTocada = comprobarToquePartes(touch);
            if (iParteTocada!=-1&&escuchadoresBtyCapas) {
                CCLOG("TOCADA PARTE %i",iParteTocada);
                iniciarCajaXRecurso(iParteTocada);
            }
        }
    }
    
    
    
    
    
    
    return  true;
}
void MiMostro::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event)
{
    if(Configuracion::desarrollo)
        log("MOVED %f %f ",touch->getLocation().x,touch->getLocation().y);
    
    if(spBtDesplizamiento != NULL && moviendoScroll){
        if(touch->getPreviousLocation().x<(spBtDesplizamiento->getContentSize().width*escala)/2){
            //si esta el btDesplazamientoScroll a la izquierda
            return;
        }else if(touch->getPreviousLocation().x>visibleSize.width-((spBtDesplizamiento->getContentSize().width*escala)/2)){
            //si esta el btDesplazamientoScroll a la derecha
            return;
        }
        //desplazo la barra lateral
        desplazarBtDesplizamiento(touch->getLocation().x);
        
        float xActual = touch->getLocation().x;
        //log("total %f actual %f",visibleSize.width-margenElementosCE,xActual);
        float porcenjeDesplazadoGlobal = xActual/(visibleSize.width-margenElementosCE);
        //log("Desplzado %f \uFF05",porcenjeDesplazadoGlobal);
        float anchoScr = ((anchoUltElementoCE+margenElementosCE)*ultimoArrayPasado->count())-anchoScrollView;
        float xPos = (anchoScr*porcenjeDesplazadoGlobal)-anchoScr;
        //log("posicion nueva %f de %f",xPos,anchoScr);
        
        scrollView->setContentOffset(Vec2(xPos,scrollView->getContentOffset().y));
        //CCLOG("TOCADO spBtDesplizamiento");
    }
    
}
void MiMostro::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
{
    if(Configuracion::desarrollo)
        log("ENDED %f %f ",touch->getLocation().x,touch->getLocation().y);
    if(moviendoScroll)
        moviendoScroll = false;
}

void MiMostro::showEditBox() { // Solo para iOS
    
    float posicionActual = botonAtras->getPositionY()-(espacioSuperiorBtAtrasCE)-(botonAtras->getContentSize().height*escala);
    
    std::string pNormalSprite = "mostrosity_mimostro_input_bg.png";
    myName = EditBox::create(Size((1200*escalaAncha), (tamLetraCE+margenLetrasCE)*3), Scale9Sprite::create(pNormalSprite));
    
    float posX = (visibleSize.width - myName->boundingBox().size.width) / 2;
    
    myName->cocos2d::Node::setPosition(posX, posicionActual);
    myName->setAnchorPoint(Vec2(0,1));
    myName->setFontName("HVD_Comic_Serif_Pro.ttf");
    myName->setFontSize(tamLetraMiMostro);
    myName->setFont("HVD_Comic_Serif_Pro.ttf", tamLetraMiMostro);
    myName->setFontColor(Color3B(194,233,251));
    myName->setPlaceHolder(LanguageManager::getInstance()->getString("MiMostroBtNombre").c_str());
    myName->setPlaceholderFontColor(Color3B(140,205,235));
    myName->setPlaceholderFont("HVD_Comic_Serif_Pro.ttf", tamLetraMiMostro);
    myName->setMaxLength(30);
    myName->setReturnType(EditBox::KeyboardReturnType::DONE);
    myName->setDelegate(this);
    myName->setInputMode(EditBox::InputMode::SINGLE_LINE);
    myName->setText(Configuracion::nombreMiMostro.c_str());
    myName->setZOrder(50);
    addChild(myName);
    
}

void MiMostro::hideEditBox() { // Solo para iOS
    
    removeChild(myName);
    
}

//interfaz de delegado de editbox

void MiMostro::editBoxEditingDidBegin(EditBox* editBox) {
    CCLOG("_____1-editing began");
    
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    showEditBox();
    #endif
};


/**
 * This method is called when an edit box loses focus after keyboard is hidden.
 * @param editBox The edit box object that generated the event.
 * @js NA
 * @lua NA
 */
void MiMostro::editBoxEditingDidEnd(EditBox* editBox) {
    CCLOG("_____2-Editing end");
    
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    hideEditBox();
    #endif
};

/**
 * This method is called when the edit box text was changed.
 * @param editBox The edit box object that generated the event.
 * @param text The new text.
 * @js NA
 * @lua NA
 */
void MiMostro::editBoxTextChanged(EditBox* editBox, const std::string& text) {
    CCLOG("_____3 TEXT CHANGE %s ",text.c_str());
    
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    myName->setText(text.c_str());
    #endif
};

/**
 * This method is called when the return button was pressed or the outside area of keyboard was touched.
 * @param editBox The edit box object that generated the event.
 * @js NA
 * @lua NA
 */
void MiMostro::editBoxReturn(EditBox* editBox){
    CCLOG("_____4 - return");
    
    CCLOG("FINAL %s",editBox->getText());
    Configuracion::nombreMiMostro = editBox->getText();
    UserDefault::getInstance()->setStringForKey("nombreMiMostro", Configuracion::nombreMiMostro);
    

}
