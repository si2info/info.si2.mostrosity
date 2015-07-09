#ifndef  _CPREGUNTASPREGUNTATOR_H_
#define  _CPREGUNTASPREGUNTATOR_H_

#include "cocos2d.h"
#include "Configuracion.h"
#include "CPreguntasPreguntator.h"
#include "json/rapidjson.h"
#include "json/prettywriter.h"
#include "json/filestream.h"
#include "../cocos2d/cocos/editor-support/spine/Json.h"

USING_NS_CC;
using namespace rapidjson;

CPreguntasPreguntator::CPreguntasPreguntator(){

}

int CPreguntasPreguntator::ObtenerNumeroPreguntas(){
    
//    Json *jsonConfig = Json_create(obtenerArchivo());
    
    __String *fileName = __String::create("configuracionPreguntator.json");
    string clearContent = FileUtils::getInstance()->getStringFromFile(fileName->getCString());
    
    document.Parse<0>(clearContent.c_str());
    
    Json *jsonConfig = Json_create(clearContent.c_str());
    
    Json *arrayPreguntas = jsonConfig->child;
    CCLOG("NumeroPreguntas %i",arrayPreguntas->size);
    return arrayPreguntas->size;
    
}

//const char* CPreguntasPreguntator::obtenerArchivo(){
//    __String *fileName = __String::create("configuracionPreguntator.json");
//    string clearContent = FileUtils::getInstance()->getStringFromFile(fileName->getCString());
//    
//    document.Parse<0>(clearContent.c_str());
//    if(document.HasParseError())
//    {
//        CCLOG("configuracionPreguntator file parsing error!");
//        return NULL;
//    }
//    
//    return clearContent.c_str();
//}

void CPreguntasPreguntator::cargarPregunta(int numero){
    

//    Json *jsonConfig = Json_create(obtenerArchivo());
    
    __String *fileName = __String::create("configuracionPreguntator.json");
    string clearContent = FileUtils::getInstance()->getStringFromFile(fileName->getCString());
    
    document.Parse<0>(clearContent.c_str());
    
    Json *jsonConfig = Json_create(clearContent.c_str());
    
    Json *arrayPreguntas = jsonConfig->child;
    Json *jsonPregunta = arrayPreguntas->child;
    for(int a=0;a<arrayPreguntas->size;a++){
        
        if(numero==a){
        
            CCLOG("pregunta %s",jsonPregunta->child->valueString);
            sPregunta = __String::create(jsonPregunta->child->valueString);
            sPregunta->retain();
            
            CCLOG("audio pregunta %s",jsonPregunta->child->next->valueString);
            sAudio = __String::create(jsonPregunta->child->next->valueString);
            sAudio->retain();
            
            // Inglés
            CCLOG("preguntaEN %s",jsonPregunta->child->next->next->valueString);
            sPreguntaEN = __String::create(jsonPregunta->child->next->next->valueString);
            sPreguntaEN->retain();
            
            CCLOG("audioEN pregunta %s",jsonPregunta->child->next->next->next->valueString);
            sAudioEN = __String::create(jsonPregunta->child->next->next->next->valueString);
            sAudioEN->retain();
            
            // Audio
            CCLOG("audio duracion %f",jsonPregunta->child->next->next->next->next->valueFloat);
            fDuracion = jsonPregunta->child->next->next->next->next->valueFloat;
            
            
            CCLOG("preguntaOK %i",jsonPregunta->child->next->next->next->next->next->valueInt);
            iRespuestaOK = jsonPregunta->child->next->next->next->next->next->valueInt;
            
        //Respuestas
            Json *respuestas = jsonPregunta->child->next->next->next->next->next->next;
            Json *jsonRespuesta = respuestas->child;
            aRespuestas = __Array::createWithCapacity(respuestas->size);
            aRespuestas->retain();
            for(int i= 0;i<respuestas->size;i++){
                __String *imgRespuesta = __String::create(jsonRespuesta->child->valueString);
                aRespuestas->addObject(imgRespuesta);
                CCLOG("respuesta %i: %s",a,imgRespuesta->getCString());
                jsonRespuesta = jsonRespuesta->next;
            }
       
            
        }
        jsonPregunta = jsonPregunta->next;
    }
}
#endif
