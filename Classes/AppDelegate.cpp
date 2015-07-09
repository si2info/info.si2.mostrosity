#include "AppDelegate.h"
#include "Configuracion.h"
#include "CGestorRecursos.h"
#include "MiMostro.h"
#include "Akuerdate.h"
#include "Splash.h"
#include "LanguageManager.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
#include "CCGLViewImpl-android.h"
#include "android/CCFileUtils-android.h"
#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS
#include "CCGLViewImpl-ios.h"
#endif

USING_NS_CC;
using namespace rapidjson;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::create("Mostrosity");
        director->setOpenGLView(glview);
    }
    
    Configuracion::cargarConfiguracion();
    
    //prueba->setStringForKey("patas", "las mas chulas");
    //String clearContent = FileUtils::getInstance()->getStringFromFile("idioma.json");
    //ejemplo de lectura de archivo interno

    // turn on display FPS
    //director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);
    
    #if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::RGB5A1);
    #elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::RGBA4444);
    #endif
    
    
    /*
    //compruebo que no existe el archivo de datos y si es asi le copio la plantilla (Esto solo se haria una vez)
    if(!Configuracion::existeArchivo(Configuracion::archivoConfiguracion)){
        std::string contenido = FileUtils::getInstance()->getStringFromFile(Configuracion::archivoConfiguracion);
        
        if(!Configuracion::guardarArchivo(Configuracion::archivoConfiguracion,contenido)){
            MessageBox("No se han podido guardar el archivo de configuración, los logros no seran acumulados.","Error datos");
        }
        
    }*/
    
    if(!Configuracion::existeArchivo(Configuracion::Configuracion::nombreArchivoRecursosBloqueados)){
        CGestorRecursos * gRecursos = new CGestorRecursos();
        gRecursos->generarArchivoInicialRecursosBloqueados();
    }
    
    #if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    
//    prepareResourcesForAndroid(CCDirector::getInstance());
    
    #endif
    
    
    
    // create a scene. it's an autorelease object
    //DESARROLLANDO
    if(!Configuracion::desarrollo){
        auto scene = Splash::createScene();
        director->runWithScene(scene);
    }else{//desarrollo
        auto scene = Akuerdate::createScene();
        director->runWithScene(scene);
    }
    
    
    /*
     rapidjson::Document jsonDoc; // create the object
     jsonDoc.SetObject(); // flag it as an object rather than an array,a necessary step for Serialization
     
     std::string key = "key";
     std::string value = "value";
     jsonDoc.AddMember(key.c_str(),value.c_str(),jsonDoc.GetAllocator());
     
     
     rapidjson::StringBuffer sb;
     rapidjson::Writer<rapidjson::StringBuffer> writer(sb);
     jsonDoc.Accept(writer);
     String* jsonString = String::create(sb.GetString());
     log("json %s",jsonString->getCString());
     
     
     FileUtils *gArchivos = FileUtils::getInstance();
     std::string nombreArchivo = "datos.json";
     std::string contenido = "{\"david\":{\"pelo\":{\"tamano\":\"GIGANTE\"}}}";
     
     FileOperation *fileGestor = new FileOperation();
     std::string contenidoArchivoDespuesSave;
     if(fileGestor->saveFile(nombreArchivo,contenido)){
     contenidoArchivoDespuesSave = fileGestor->readFile(nombreArchivo);
     log("DESPUES %s",contenidoArchivoDespuesSave.c_str());
     }
     
     
     rapidjson::Document document;
     document.Parse<0>(contenidoArchivoDespuesSave.c_str());
     
     //rapidjson::Value contact(rapidjson::Type::kObjectType);
     //contact.AddMember("name", "Milo", document.GetAllocator());
     //contact.AddMember("married", true, document.GetAllocator());
     
     //document["david"]["pelo"];
     //log("%s",document["david"]["pelo"]["tamano"]);
     
     
     //carga de archivos de memoria
     /*string path;
     path = FileUtils::getInstance()->getWritablePath().c_str();
     path.append("piernas_01.png");
     CCSprite *sprite = CCSprite::create(path);
     sprite->setPosition(visibleSize.width/2,visibleSize.height/2);
     sprite->setLocalZOrder(500);
     sprite->setScale(escala);
     addChild(sprite);
     */


    
    return true;
}

void AppDelegate::prepareResourcesForAndroid(Director* pDirector) {
    
    Size windowSize = pDirector->getWinSize();
    
    auto glview = pDirector->getOpenGLView();
    auto fileutils = FileUtils::getInstance();
    std::vector < std::string > resDirOrders;
    int dpi = Device::getDPI();
    
    if (dpi >= 640) {
        //Pushing back the resolution directories allows the application to fall back to
        //lower-resolution assets if a higher-resolution asset is missing.
        resDirOrders.push_back("drawable-xxxhdpi");
        resDirOrders.push_back("drawable-xxhdpi");
        resDirOrders.push_back("drawable-hdpi");
        resDirOrders.push_back("drawable-mdpi");
        resDirOrders.push_back(".");
        
        glview->setDesignResolutionSize(windowSize.width, windowSize.height,ResolutionPolicy::NO_BORDER);
        
        CCLOG("Scale 4");
        
    } else if (dpi >= 321 && dpi <= 480) {
        
        resDirOrders.push_back("drawable-xxhdpi");
        resDirOrders.push_back("drawable-xhdpi");
        resDirOrders.push_back("drawable-hdpi");
        resDirOrders.push_back("drawable-mdpi");
        resDirOrders.push_back(".");
        
        glview->setDesignResolutionSize(windowSize.width, windowSize.height,ResolutionPolicy::NO_BORDER);
        
        CCLOG("Scale 3.0");
        
    } else if (dpi >= 241 && dpi <= 320) {
        
        resDirOrders.push_back("drawable-xhdpi");
        resDirOrders.push_back("drawable-hdpi");
        resDirOrders.push_back("drawable-mdpi");
        resDirOrders.push_back(".");
        
        glview->setDesignResolutionSize(windowSize.width, windowSize.height,ResolutionPolicy::NO_BORDER);
        
        CCLOG("Scale 2.0");
        
    } else if (dpi >= 161 && dpi <= 240) {
        resDirOrders.push_back("drawable-hdpi");
        resDirOrders.push_back("drawable-mdpi");
        resDirOrders.push_back(".");
        
        glview->setDesignResolutionSize(windowSize.width, windowSize.height,ResolutionPolicy::NO_BORDER);
        
        CCLOG("Scale 1.5");
        
    } else { //base line
        
        resDirOrders.push_back("drawable-mdpi");
        resDirOrders.push_back(".");
        
        glview->setDesignResolutionSize(windowSize.width, windowSize.height,ResolutionPolicy::NO_BORDER);
        
        CCLOG("Scale 1");
        
    }
    
    fileutils->setSearchPaths(resDirOrders);
    
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
