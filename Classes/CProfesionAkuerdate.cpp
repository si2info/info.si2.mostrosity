#ifndef  _CPROFESIONAKUERDATE_H_
#define  _CPROFESIONAKUERDATE_H_

#include "cocos2d.h"
#include "Configuracion.h"
#include "CProfesionAkuerdate.h"
#include "json/rapidjson.h"
#include "json/prettywriter.h"
#include "json/filestream.h"
#include "../cocos2d/cocos/editor-support/spine/Json.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

#include "android/CCFileUtils-android.h"

#endif


USING_NS_CC;
using namespace rapidjson;

CProfesionAkuerdate::CProfesionAkuerdate(){

}

int CProfesionAkuerdate::ObtenerNumeroProfesiones(){
    
//    Json *jsonConfig = Json_create(obtenerArchivo());
    
    __String *fileName = __String::create("configuracionAkuerdate.json");
    string clearContent = FileUtils::getInstance()->getStringFromFile(fileName->getCString());
    document.Parse<0>(clearContent.c_str());
    
    Json *jsonConfig = Json_create(clearContent.c_str());
    
    Json *arrayPaneles = jsonConfig->child;
    CCLOG("NumeroProfesiones %i",arrayPaneles->size);
    return arrayPaneles->size;
    
}

//const char* CProfesionAkuerdate::obtenerArchivo(){
//    __String *fileName = __String::create("configuracionAkuerdate.json");
//    
//    string clearContent = FileUtils::getInstance()->getStringFromFile(fileName->getCString());
//    
//    document.Parse<0>(clearContent.c_str());
//    if(document.HasParseError())
//    {
//        CCLOG("configuracionAkuerdate file parsing error!");
//        return NULL;
//    }
//    
//    return clearContent.c_str();
//}

void CProfesionAkuerdate::cargarProfesion(int numero){

//    Json *jsonConfig = Json_create(obtenerArchivo());
    
    __String *fileName = __String::create("configuracionAkuerdate.json");
    string clearContent = FileUtils::getInstance()->getStringFromFile(fileName->getCString());
    document.Parse<0>(clearContent.c_str());
    
    Json *jsonConfig = Json_create(clearContent.c_str());
    
    Json *arrayProfesion = jsonConfig->child;
    Json *jsonProfesion = arrayProfesion->child;
    for(int a=0;a<arrayProfesion->size;a++){
        
        if(numero==a){
        
            CCLOG("nombre %s",jsonProfesion->child->valueString);
            sNombreProfesion = __String::create(jsonProfesion->child->valueString);
            
            CCLOG("nombreEN %s",jsonProfesion->child->next->valueString);
            sNombreProfesionEN = __String::create(jsonProfesion->child->next->valueString);
            
            CCLOG("img fondo %s",jsonProfesion->child->next->next->valueString);
            sImagen = __String::create(jsonProfesion->child->next->next->valueString);
            spImgProfesion = Sprite::create(sImagen->getCString());
            
        //HUECOS
            Json *elementos = jsonProfesion->child->next->next->next;
            Json *jsonElemento = elementos->child;
            aElementosProfesion = __Array::createWithCapacity(elementos->size);
            aElementosProfesion->retain();
            for(int i= 0;i<elementos->size;i++){
                
                __Array *compuestoElemento = __Array::createWithCapacity(2);
                compuestoElemento->insertObject(__String::create(jsonElemento->child->valueString), indiceImgElementoProfesion);
                compuestoElemento->insertObject(__Float::create(jsonElemento->child->next->child->valueFloat), indiceX);
                compuestoElemento->insertObject(__Float::create(jsonElemento->child->next->child->next->valueFloat), indiceY);
                compuestoElemento->insertObject(__Integer::create(jsonElemento->child->next->next->valueInt), indiceZ);
                compuestoElemento->insertObject(__Float::create(jsonElemento->child->next->next->next->valueFloat), indiceGrados);
                compuestoElemento->insertObject(__String::create(jsonElemento->child->next->next->next->next->valueString), indiceTXT);
                compuestoElemento->insertObject(__String::create(jsonElemento->child->next->next->next->next->next->valueString), indiceAudio);
                compuestoElemento->insertObject(__String::create(jsonElemento->child->next->next->next->next->next->next->valueString), indiceTxtEN);
                compuestoElemento->insertObject(__String::create(jsonElemento->child->next->next->next->next->next->next->next->valueString), indiceAudioEN);
                aElementosProfesion->insertObject(compuestoElemento, i);
                
                jsonElemento = jsonElemento->next;
            }
       
            
        }
        jsonProfesion = jsonProfesion->next;
    }
    
}

Sprite* CProfesionAkuerdate::obtenerImgFondo(){
    
    if(spImgFondo!=NULL)
        return spImgFondo;
    
    spImgFondo = Sprite::create(sImagen->getCString());
    spImgFondo->setAnchorPoint(Vec2(0,0));
    spImgFondo->setPosition(0,0);
    spImgFondo->retain();
    return spImgFondo;
}

Sprite* CProfesionAkuerdate::obtenerImgProfesion(){
    
    if(spImgProfesion!=NULL)
        return spImgProfesion;
    
    CCLOG("DEBUG Img: %s", sImagen->getCString());
    
    spImgProfesion = Sprite::create(sImagen->getCString());
    spImgProfesion->setAnchorPoint(Vec2(0,0));
    spImgProfesion->setPosition(0,0);
    spImgProfesion->retain();
    return spImgProfesion;
}


Sprite* CProfesionAkuerdate::obtenerElemento(int numero){
    __Array* profesionActual = dynamic_cast<__Array*>(aElementosProfesion->getObjectAtIndex(numero));
    __String *sImgElemento = dynamic_cast<__String*>(profesionActual->getObjectAtIndex(indiceImgElementoProfesion));
    
    Sprite *spHueco = Sprite::create(sImgElemento->getCString());
    spHueco->setAnchorPoint(Vec2(0.5,0.5));
    //el tag es el orden original
    spHueco->setTag(numero);
    return spHueco;
    
}

__Array* CProfesionAkuerdate::obtenerElementosProfesion(){
    __Array *aElementosSP = __Array::createWithCapacity(aElementosProfesion->count());
    for(int i=0;i<aElementosSP->capacity();i++){
        aElementosSP->insertObject(obtenerElemento(i), i);
    }
    
    return aElementosSP;
}

Vec2 CProfesionAkuerdate::obternerPosElementoProfesion(int numero){

    __Array* elementoActual = dynamic_cast<__Array*>(aElementosProfesion->getObjectAtIndex(numero));
    __Float *x = dynamic_cast<__Float*>(elementoActual->getObjectAtIndex(indiceX));
    __Float *y = dynamic_cast<__Float*>(elementoActual->getObjectAtIndex(indiceY));
    
    return Vec2(x->getValue(),y->getValue());

}
int CProfesionAkuerdate::obtenerZIndexElemento(int numero){
    
    __Array* elementoActual = dynamic_cast<__Array*>(aElementosProfesion->getObjectAtIndex(numero));
    
    return dynamic_cast<__Integer*>(elementoActual->getObjectAtIndex(indiceZ))->getValue();
    
}

float CProfesionAkuerdate::obtenerGradosElemento(int numero){
    
    __Array* elementoActual = dynamic_cast<__Array*>(aElementosProfesion->getObjectAtIndex(numero));
    
    return dynamic_cast<__Float*>(elementoActual->getObjectAtIndex(indiceGrados))->getValue();
    
}

__String* CProfesionAkuerdate::obtenerPalabraElemento(int numero){
    
    __Array* elementoActual = dynamic_cast<__Array*>(aElementosProfesion->getObjectAtIndex(numero));
    
    if (Configuracion::idioma == 1) { // Español
        return dynamic_cast<__String*>(elementoActual->getObjectAtIndex(indiceTXT));
    } else { // Inglés
        return dynamic_cast<__String*>(elementoActual->getObjectAtIndex(indiceTxtEN));
    }
    
}

__String* CProfesionAkuerdate::obtenerAudioElemento(int numero){
    
    __Array* elementoActual = dynamic_cast<__Array*>(aElementosProfesion->getObjectAtIndex(numero));
    
    if (Configuracion::idioma == 1) { // Español
        return dynamic_cast<__String*>(elementoActual->getObjectAtIndex(indiceAudio));
    } else { // Inglés
        return dynamic_cast<__String*>(elementoActual->getObjectAtIndex(indiceAudioEN));
    }
    
}


const char* CProfesionAkuerdate::Imprimir(){
    
    __String *respuesta = String::createWithFormat("img %s",sImagen->getCString());
    return respuesta->getCString();
}

#endif
