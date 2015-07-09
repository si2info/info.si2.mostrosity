#ifndef  _CPANELARMAME_H_
#define  _CPANELARMAME_H_

#include "cocos2d.h"
#include "Configuracion.h"
#include "CPanelArmame.h"
#include "json/rapidjson.h"
#include "json/prettywriter.h"
#include "json/filestream.h"
#include "../cocos2d/cocos/editor-support/spine/Json.h"

USING_NS_CC;
using namespace rapidjson;

CPanelArmame::CPanelArmame(){

}

int CPanelArmame::ObtenerNumeroPaneles(){
    
//    Json *jsonConfig = Json_create(obtenerArchivo());
    
    __String *fileName = __String::create("configuracionArmame.json");
    string clearContent = FileUtils::getInstance()->getStringFromFile(fileName->getCString());
    document.Parse<0>(clearContent.c_str());
    
    Json *jsonConfig = Json_create(clearContent.c_str());
    
    Json *arrayPaneles = jsonConfig->child;
    
    return arrayPaneles->size;
    
}

//const char* CPanelArmame::obtenerArchivo(){
//    __String *fileName = __String::create("configuracionArmame.json");
//    string clearContent = FileUtils::getInstance()->getStringFromFile(fileName->getCString());
//    
//    document.Parse<0>(clearContent.c_str());
//    if(document.HasParseError())
//    {
//        CCLOG("Language file parsing error!");
//        return NULL;
//    }
//    
//    return clearContent.c_str();
//}

void CPanelArmame::cargarPanel(int numero){
    

//    Json *jsonConfig = Json_create(obtenerArchivo());
    
    __String *fileName = __String::create("configuracionArmame.json");
    string clearContent = FileUtils::getInstance()->getStringFromFile(fileName->getCString());
    document.Parse<0>(clearContent.c_str());
    
    Json *jsonConfig = Json_create(clearContent.c_str());
    
    Json *arrayPaneles = jsonConfig->child;
    Json *jsonPanel = arrayPaneles->child;
    for(int a=0;a<arrayPaneles->size;a++){
        
        if(numero==a){
        
            CCLOG("img panel %s",jsonPanel->child->valueString);
            sImagen = __String::create(jsonPanel->child->valueString);
            spImgPanel = Sprite::create(sImagen->getCString());
            
        //HUECOS
            Json *huecos = jsonPanel->child->next;
            Json *jsonHueco = huecos->child;
            aHuecos = __Array::createWithCapacity(huecos->size);
            aHuecos->retain();
            for(int i= 0;i<huecos->size;i++){
                
                __Array *compuestoHueco = __Array::createWithCapacity(3);
                compuestoHueco->insertObject(__String::create(jsonHueco->child->valueString), indiceImg);
                compuestoHueco->insertObject(__Float::create(jsonHueco->child->next->child->valueFloat), indiceX);
                compuestoHueco->insertObject(__Float::create(jsonHueco->child->next->child->next->valueFloat), indiceY);
                compuestoHueco->insertObject(__Integer::create(jsonHueco->child->next->next->valueInt), indiceZ);
                aHuecos->insertObject(compuestoHueco, i);
                
                jsonHueco = jsonHueco->next;
            }
            
        //COMPLEMENTOS
            Json *complementos = jsonPanel->child->next->next;
            Json *jsonComplemento = complementos->child;
            aComplementos = __Array::createWithCapacity(complementos->size);
            aComplementos->retain();
            for(int i= 0;i<complementos->size;i++){
                
                __Array *compuestoComplemento = __Array::createWithCapacity(3);
                compuestoComplemento->insertObject(__String::create(jsonComplemento->child->valueString), indiceImg);
                compuestoComplemento->insertObject(__Float::create(jsonComplemento->child->next->child->valueFloat), indiceX);
                compuestoComplemento->insertObject(__Float::create(jsonComplemento->child->next->child->next->valueFloat), indiceY);
                compuestoComplemento->insertObject(__Integer::create(jsonComplemento->child->next->next->valueInt), indiceZ);
                aComplementos->insertObject(compuestoComplemento, i);
                
                jsonComplemento = jsonComplemento->next;
            }
            
            
            
            
            
        }
        jsonPanel = jsonPanel->next;
    }
    
    

    
}

Sprite* CPanelArmame::obtenerImgPanel(){
    
    if(spImgPanel!=NULL)
        return spImgPanel;
    
    spImgPanel = Sprite::create(sImagen->getCString());
    spImgPanel->setAnchorPoint(Vec2(0,0));
    spImgPanel->setPosition(0,0);
    spImgPanel->retain();
    return spImgPanel;
}


Sprite* CPanelArmame::obtenerHueco(int numero){
    __Array* huecoActual = dynamic_cast<__Array*>(aHuecos->getObjectAtIndex(numero));
    __String *sImgHueco = dynamic_cast<__String*>(huecoActual->getObjectAtIndex(indiceImg));
    
    Sprite *spHueco = Sprite::create(sImgHueco->getCString());
    spHueco->setAnchorPoint(Vec2(0.5,0.5));
    spHueco->setPosition(obternerMedidasHueco(numero));
    return spHueco;
    
}

__Array* CPanelArmame::obtenerHuecos(){
    __Array *aHuecosSP = __Array::createWithCapacity(aHuecos->count());
    for(int i=0;i<aHuecosSP->capacity();i++){
        aHuecosSP->insertObject(obtenerHueco(i), i);
    }
    
    return aHuecosSP;
}

Vec2 CPanelArmame::obternerMedidasHueco(int numero){

    __Array* huecoActual = dynamic_cast<__Array*>(aHuecos->getObjectAtIndex(numero));
    __Float *x = dynamic_cast<__Float*>(huecoActual->getObjectAtIndex(indiceX));
    __Float *y = dynamic_cast<__Float*>(huecoActual->getObjectAtIndex(indiceY));
    
    return Vec2(x->getValue(),y->getValue());

}
int CPanelArmame::obtenerZIndexHueco(int numero){
    
    __Array* huecoActual = dynamic_cast<__Array*>(aHuecos->getObjectAtIndex(numero));
    
    return dynamic_cast<__Integer*>(huecoActual->getObjectAtIndex(indiceZ))->getValue();
    
}


Sprite* CPanelArmame::obtenerComplemento(int numero){
    __Array* complementoActual = dynamic_cast<__Array*>(aComplementos->getObjectAtIndex(numero));
    __String *sImgComplemento = dynamic_cast<__String*>(complementoActual->getObjectAtIndex(indiceImg));
    
    Sprite *spComplemento = Sprite::create(sImgComplemento->getCString());
    spComplemento->setAnchorPoint(Vec2(0,0));
    spComplemento->setPosition(obternerMedidasComplemento(numero));
    return spComplemento;
    
}

__Array* CPanelArmame::obtenerComplementos(){
    __Array *aComplementosSP = __Array::createWithCapacity(aComplementos->count());
    for(int i=0;i<aComplementosSP->capacity();i++){
        aComplementosSP->insertObject(obtenerComplemento(i), i);
    }
    
    return aComplementosSP;
}

Vec2 CPanelArmame::obternerMedidasComplemento(int numero){
    
    __Array* complementoActual = dynamic_cast<__Array*>(aComplementos->getObjectAtIndex(numero));
    __Float *x = dynamic_cast<__Float*>(complementoActual->getObjectAtIndex(indiceX));
    __Float *y = dynamic_cast<__Float*>(complementoActual->getObjectAtIndex(indiceY));
    
    return Vec2(x->getValue(),y->getValue());
    
}
int CPanelArmame::obtenerZIndexComplemento(int numero){
    
    __Array* complementoActual = dynamic_cast<__Array*>(aComplementos->getObjectAtIndex(numero));
    
    return dynamic_cast<__Integer*>(complementoActual->getObjectAtIndex(indiceZ))->getValue();
    
}

const char* CPanelArmame::Imprimir(){
    
    __String *respuesta = String::createWithFormat("img %s",sImagen->getCString());
    return respuesta->getCString();
}

#endif
