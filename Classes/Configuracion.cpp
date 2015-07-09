#ifndef  _CONFIGURACION_H_
#define  _CONFIGURACION_H_

#include "cocos2d.h"
#include "Configuracion.h"
#include "FileOperation.h"
#include "external/json/writer.h"
#include "external/json/stringbuffer.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "CGestorRecursos.h"
#include "SimpleAudioEngine.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "JniLink.h"
#include "JniHelper.h"
#endif

USING_NS_CC;

bool Configuracion::desarrollo = false;
char * Configuracion::paginaWeb = "http://mostrosity.com/";
char * Configuracion::paginaLicencia = "http://mostrosity.com/el-proyecto/";
int Configuracion::profesor =-1;//-1 valor inicial y  1 o 2 segun la eleccion en la instalación
int Configuracion::idioma = 1;//idiomas 1 -> español 2 -> ingles
float Configuracion::volumenEfectos = 1;
float Configuracion::volumenMusica = 0.7;

//MiMostro

//DEFINO CONSTANTES
int const Configuracion::rcsTipoMostro = 1;
int const Configuracion::rcsTipoExpositor = 2;


int const Configuracion::rcsTipoOjos = 3;
int const Configuracion::rcsTipoDientes = 4;
int const Configuracion::rcsTipoBrazos = 5;
    int const Configuracion::rcsTipoBrazo_izq = 5;
    int const Configuracion::rcsTipoBrazo_der = -5;
int const Configuracion::rcsTipoPies = 6;
    int const Configuracion::rcsTipoPies_izq = 6;
    int const Configuracion::rcsTipoPies_der = -6;
int const Configuracion::rcsTipoAlas = 7;
int const Configuracion::rcsTipoOrejas = 8;
    int const Configuracion::rcsTipoOreja_izq = 8;
    int const Configuracion::rcsTipoOreja_der = -8;
int const Configuracion::rcsTipoPelo = 9;
int const Configuracion::rcsTipoCuerpo = 10;
int const Configuracion::rcsTipoAccesorio = 11;
int const Configuracion::rcsTipoColor = 12;

//partes a pintar en el juego
int Configuracion::partesDimeketekito[11] = {
    Configuracion::rcsTipoOjos,
    Configuracion::rcsTipoBrazos,
        Configuracion::rcsTipoBrazo_izq,
        Configuracion::rcsTipoBrazo_der,
    Configuracion::rcsTipoPies,
        Configuracion::rcsTipoPies_izq,
        Configuracion::rcsTipoPies_der,
    Configuracion::rcsTipoOrejas,
        Configuracion::rcsTipoOreja_izq,
        Configuracion::rcsTipoOreja_der,
    Configuracion::rcsTipoDientes
};

//numero de recursos que existen (Utilizado para el seleccionador en mimostro)
//esto pasara a no utilizarse
int Configuracion::nOjos = 7;
int Configuracion::nDientes = 6;
int Configuracion::nBrazos = 0;
int Configuracion::nPies = 0;
int Configuracion::nAlas = 0;
int Configuracion::nOrejas = 0;
int Configuracion::nPelo = 0;
int Configuracion::nAccesorio = 0;
int Configuracion::nSonido = 12;//ESTE SI ES UTILIZADO

//palabra clave de maestro para nombrar los recursos
std::string Configuracion::mstDientes = "dientes";
std::string Configuracion::mstOjos = "ojos";
std::string Configuracion::mstBrazos = "brazos";
std::string Configuracion::mstPies = "pies";
std::string Configuracion::mstAlas = "alas";
std::string Configuracion::mstOrejas = "orejas";
std::string Configuracion::mstPelo = "pelo";
std::string Configuracion::mstAccesorio = "accesorio";

// ID MiMostro Default
std::string Configuracion::idMiMostro = "";

//recursos por defecto
int Configuracion::colorMiMostro = 1;
int Configuracion::sonidoMiMostro = 1;
std::string Configuracion::nombreMiMostro ="";
int Configuracion::ojosMiMostro = 1;
int Configuracion::dientesMiMostro = 1;
int Configuracion::brazosMiMostro = 0;
int Configuracion::piesMiMostro = 0;
int Configuracion::alasMiMostro = 0;
int Configuracion::orejasMiMostro = 0;
int Configuracion::peloMiMostro = 0;
int Configuracion::accesorioMiMostro = 0;


    //GENERALES
//CONSTANTES
std::string Configuracion::archivoConfiguracion = "configuracionRecursos.json";
std::string Configuracion::nombreArchivoRecursosBloqueados = "recursosBloquedos.json";

std::string Configuracion::getRecurso(int numero,std::string maestro,int tipo){
    
    std::string sTipo = "";
    if(tipo == 1)//mostro
        sTipo = "m";
    else if(tipo == 2)//expositor
        sTipo = "exp";
    
    __String *recurso = __String::createWithFormat("mostrosity_mimostro_mostro_%s_%s__000%i.png",maestro.c_str(),sTipo.c_str(),numero);
    if(numero>9)
        recurso = __String::createWithFormat("mostrosity_mimostro_mostro_%s_%s__00%i.png",maestro.c_str(),sTipo.c_str(),numero);

    
    return recurso->getCString();
}


const char* Configuracion::charTochar(std::vector<char>* caracteres){
    
    __String *texto = __String::create("");
    for (unsigned int i = 0; i < caracteres->size(); i++)
    {
        texto = __String::createWithFormat("%s%c",texto->getCString(),(*caracteres)[i]);
    }
    return texto->getCString();
}

bool Configuracion::comprobarToque(Touch *touch,Node *sprite){
    
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

int Configuracion::aleatorioEnteros(int min, int max){
    float low_bound = min;
    float high_bound = max+1;
    float rndValue = (((float)arc4random()/0x100000000)*(high_bound-low_bound)+low_bound);
    
    if(Configuracion::desarrollo)
        log("ALEATORIO max:%i min:%i resultado %i",max,min,(int)rndValue);
    
    return (int)rndValue;
}

bool Configuracion::existeArchivo(std::string archivo){
    FileUtils *gArchivos = FileUtils::getInstance();
    std::string rutaAbsoluta = gArchivos->getWritablePath().append(archivo);
    
    bool existe = gArchivos->isFileExist(rutaAbsoluta);
    return existe;

}

void Configuracion::cargarConfiguracion(){

    //CARGO CONFIUGURACION
    UserDefault *preferencias = UserDefault::getInstance();
    Configuracion::profesor = preferencias->getIntegerForKey("profesor", -1);
    Configuracion::idioma = preferencias->getIntegerForKey("idioma", 1);
    Configuracion::volumenMusica = preferencias->getFloatForKey("volMusica", 0.5);
    Configuracion::volumenEfectos = preferencias->getFloatForKey("volEfectos", 1);
    
    //MiMostro
    Configuracion::colorMiMostro = preferencias->getIntegerForKey("colorMiMostro",Configuracion::colorMiMostro);
    Configuracion::ojosMiMostro = preferencias->getIntegerForKey("ojosMiMostro", Configuracion::ojosMiMostro);
    Configuracion::dientesMiMostro = preferencias->getIntegerForKey("dientesMiMostro", Configuracion::dientesMiMostro);
    Configuracion::orejasMiMostro = preferencias->getIntegerForKey("orejasMiMostro",Configuracion::orejasMiMostro);
    Configuracion::brazosMiMostro = preferencias->getIntegerForKey("brazosMiMostro",Configuracion::brazosMiMostro);
    Configuracion::piesMiMostro = preferencias->getIntegerForKey("piesMiMostro",Configuracion::piesMiMostro);
    Configuracion::alasMiMostro = preferencias->getIntegerForKey("alasMiMostro",Configuracion::alasMiMostro);
    Configuracion::peloMiMostro = preferencias->getIntegerForKey("peloMiMostro",Configuracion::peloMiMostro);
    Configuracion::accesorioMiMostro = preferencias->getIntegerForKey("accesorioMiMostro",Configuracion::accesorioMiMostro);
    Configuracion::nombreMiMostro = preferencias->getStringForKey("nombreMiMostro", "");
    Configuracion::sonidoMiMostro = preferencias->getIntegerForKey("sonidoMiMostro", Configuracion::sonidoMiMostro);
    
    
    CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(Configuracion::volumenMusica);
    CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(Configuracion::volumenEfectos);

}
void Configuracion::reiniciarDatos(){

    
    FileOperation::deleteFile(Configuracion::nombreArchivoRecursosBloqueados);
    CGestorRecursos *gArchivos = new CGestorRecursos();
    gArchivos->generarArchivoInicialRecursosBloqueados();
    log("Implementar reinicio datos");

    UserDefault *preferencias = UserDefault::getInstance();
    log("file preferenst %s",preferencias->getXMLFilePath().c_str());
    
    
    Configuracion::desarrollo = true;
    Configuracion::profesor = -1;
    Configuracion::idioma = 1;//idiomas 1 -> español 2 -> ingles
    Configuracion::volumenEfectos = 1;
    Configuracion::volumenMusica = 0.7;
    //recursos por defecto
    Configuracion::colorMiMostro = 1;
    Configuracion::sonidoMiMostro = 1;
    Configuracion::nombreMiMostro ="";
    Configuracion::ojosMiMostro = 1;
    Configuracion::dientesMiMostro = 1;
    Configuracion::brazosMiMostro = 0;
    Configuracion::piesMiMostro = 0;
    Configuracion::alasMiMostro = 0;
    Configuracion::orejasMiMostro = 0;
    Configuracion::peloMiMostro = 0;
    Configuracion::accesorioMiMostro = 0;
    
    
    preferencias->setIntegerForKey("profesor", Configuracion::profesor);
    preferencias->setIntegerForKey("idioma", Configuracion::idioma);
    preferencias->setFloatForKey("volMusica", Configuracion::volumenMusica);
    preferencias->setFloatForKey("volEfectos",Configuracion::volumenEfectos);
    
    //MiMostro
    preferencias->setIntegerForKey("colorMiMostro",Configuracion::colorMiMostro);
    preferencias->setIntegerForKey("ojosMiMostro", Configuracion::ojosMiMostro);
    preferencias->setIntegerForKey("dientesMiMostro", Configuracion::dientesMiMostro);
    preferencias->setIntegerForKey("orejasMiMostro",Configuracion::orejasMiMostro);
    preferencias->setIntegerForKey("brazosMiMostro",Configuracion::brazosMiMostro);
    preferencias->setIntegerForKey("piesMiMostro",Configuracion::piesMiMostro);
    preferencias->setIntegerForKey("alasMiMostro",Configuracion::alasMiMostro);
    preferencias->setIntegerForKey("peloMiMostro",Configuracion::peloMiMostro);
    preferencias->setIntegerForKey("accesorioMiMostro",Configuracion::accesorioMiMostro);
    preferencias->setStringForKey("nombreMiMostro", "");
    
    Configuracion::cargarConfiguracion();
    
}

std::string Configuracion::leerArchivo(std::string archivo,bool esRutaAbsoluta){
    
    FileUtils *gArchivos = FileUtils::getInstance();
    std::string rutaAbsoluta = archivo;
    
    if(!esRutaAbsoluta)
        rutaAbsoluta = gArchivos->getWritablePath().append(archivo);
    
    if(gArchivos->isFileExist(rutaAbsoluta)){
        if(esRutaAbsoluta)
            return gArchivos->getStringFromFile(Configuracion::archivoConfiguracion);
        else
            return FileOperation::readFile(archivo);
    }
    
    return NULL;
}

bool Configuracion::guardarArchivo(std::string archivo,std::string contenido){
    
    return FileOperation::saveFile(archivo, contenido);
}

const char* Configuracion::getIDDEVICE(){
    std::string retorno = "";
    const char* imei;
    
    #define COCOS2D_DEBUG 1
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t,
                                       "org/cocos2dx/lib/Cocos2dxGLSurfaceView",
                                       "getIdDevice",
                                       "()Ljava/lang/String;")) {
        
        jstring jstr = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
        std::string obj = JniHelper::jstring2string(jstr);
        t.env->DeleteLocalRef(jstr);
        
        char *cstr = new char[obj.length() + 1];
        strcpy(cstr, obj.c_str());
        imei = cstr;
        
    }

    CCLOG("method_idDevice: %s",imei);
    return imei;
        
    #endif

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

    std::string obj = Application::getInstance()->getUUID();
    CCLOG("UUID: %s",obj.c_str());
    char *cstr = new char[obj.length() + 1];
    strcpy(cstr, obj.c_str());
    imei = cstr;

    #endif
    
    if(retorno.length()>0){
        __String *obj = __String::createWithFormat("%s",imei);
        retorno = obj->getCString();
    }
    

    return imei;
}

char Configuracion::callTwitter(const char * txt){
    
#define COCOS2D_DEBUG 1
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//    CCLOG("Configuracion::callWhatsApp____");
//    char r = callWhatsAppJNI(txt);
//    return r;
#endif
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    Application *app = Application::getInstance();
    return app->callCompartir(txt,app->TipoTwitter);
#endif
    
    return 'x';
}

char Configuracion::callWhatsApp(const char * txt){

#define COCOS2D_DEBUG 1
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	CCLOG("Configuracion::callWhatsApp____");
	char r = callWhatsAppJNI(txt);
	return r;
#endif
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    Application *app = Application::getInstance();
    return app->callCompartir(txt,app->TipoWhatsApp);
#endif
    
    return 'x';
}

void Configuracion::shareOnAndroid(const char *web, const char *subject, const char *text) {
    
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    CCLOG("Configuracion::callFacebook____");
    
    __String *data = __String::createWithFormat("%s,%s,%s", web, subject, text);
    const char *dataShare = data->getCString();
    
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t,
                                       "org/cocos2dx/lib/Cocos2dxGLSurfaceView",
                                       "intentShare",
                                       "(Ljava/lang/String;)V")) {
        
        jstring string = t.env->NewStringUTF(dataShare);
        
        t.env->CallStaticVoidMethod(t.classID,
                                   t.methodID,
                                   string);
        
        t.env->DeleteLocalRef(t.classID);
        t.env->DeleteLocalRef(string);
        
    }
    #endif
    
}


char Configuracion::callFacebook(const char * web){
    
#define COCOS2D_DEBUG 1
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    
    // Método shareOnAndroid
    
    return 'x';
#endif
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    Application *app = Application::getInstance();
    return app->callCompartir(web,app->TipoFacebook);
#endif
    
    return 'x';
}


char Configuracion::callOpenURL(const char * txt){

    CCLOG("%s", Configuracion::paginaWeb);
    
#define COCOS2D_DEBUG 1
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    CCLOG("Configuracion::callOpenURL____");
    
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t,
                                       "org/cocos2dx/lib/Cocos2dxGLSurfaceView",
                                       "openWebURL",
                                       "(Ljava/lang/String;)V")) {
        jstring stringArg = t.env->NewStringUTF(txt);
        t.env->CallStaticVoidMethod(t.classID, t.methodID, stringArg);
        t.env->DeleteLocalRef(stringArg);
        t.env->DeleteLocalRef(t.classID);
    }
    
    return 'x';
#endif
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    return Application::getInstance()->callOpenUrl(txt);
#endif
    
    return 'x';
}

#endif
