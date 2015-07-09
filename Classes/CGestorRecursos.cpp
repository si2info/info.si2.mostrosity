#ifndef  _CPREGUNTASPREGUNTATOR_H_
#define  _CPREGUNTASPREGUNTATOR_H_

#include "cocos2d.h"
#include "Configuracion.h"
#include "CRecurso.h"
#include "CTipoRecurso.h"
#include "CGestorRecursos.h"
#include "json/rapidjson.h"
#include "json/prettywriter.h"
#include "json/filestream.h"


USING_NS_CC;
using namespace rapidjson;


CGestorRecursos::CGestorRecursos(){
    keyRecursosBloqueados = "recursosBloquedos";
    keyTipoRecursosBloqueado = "tipoRecurso";
    keyCodRecursosBloqueados = "codRecurso";
}

Json* CGestorRecursos::obtenerArchivo(){
    std::string contenido = Configuracion::leerArchivo(Configuracion::archivoConfiguracion,true);
    //rapidjson::Document document;
    document.Parse<0>(contenido.c_str());
    if(document.HasParseError())
    {
        CCLOG("configuracionPreguntator file parsing error!");
        return NULL;
    }
    
    const char* archivo = contenido.c_str();
    return Json_create(archivo);
}

int CGestorRecursos::obtenerNumeroTiposRecursos(){
    
    Json *jsonConfig = obtenerArchivo();
    
    Json *arrayTiposRecursos = jsonConfig->child;
    //CCLOG("Numero TIPO Recursos %i",arrayTiposRecursos->size);
    return arrayTiposRecursos->size;
    
}

Json* CGestorRecursos::obtenerJsonObjectTipoRecurso(TIPOS tipo){
    
    Json *jsonConfig = obtenerArchivo();
    
    Json *arrayTiposRecursos = jsonConfig->child;
    //CCLOG("Numero TIPO Recursos %i",arrayTiposRecursos->size);
    
    Json *RecursosTipo = arrayTiposRecursos->child;
    Json *retorno = NULL;
    for(int i=0;i<arrayTiposRecursos->size;i++){
        
        if(tipo == RecursosTipo->child->valueInt){
            retorno = RecursosTipo;
        }
        RecursosTipo = RecursosTipo->next;
    }
    
    return retorno;
};

int CGestorRecursos::obtenerNumeroRecursos(TIPOS tipo){
    
    Json *jsonObjectTipoRecurso = obtenerJsonObjectTipoRecurso(tipo);
    
    if(jsonObjectTipoRecurso!=NULL){
        Json *aContenidoTipoRecurso = jsonObjectTipoRecurso->child->next->next;
        return aContenidoTipoRecurso->size;
    }
    
    return 0;
    
}

CTipoRecurso* CGestorRecursos::obtenerTipoRecursos(TIPOS tipo){
    int nRecursos = obtenerNumeroRecursos(tipo);
    
    if(nRecursos>0){
        __Array *arrayRecursos = __Array::createWithCapacity(nRecursos);
        arrayRecursos->retain();
        
        Json *RecursosTipo = obtenerJsonObjectTipoRecurso(tipo);
        __Integer *cod = __Integer::create(RecursosTipo->child->valueInt);
        cod->retain();
        __String *nombre = __String::create(RecursosTipo->child->next->valueString);
        nombre->retain();
        
        Json *aContenidoTipoRecurso = RecursosTipo->child->next->next;
        Json *jsonRecurso = aContenidoTipoRecurso->child;
        for(int i=0;i<aContenidoTipoRecurso->size;i++){
            CRecurso *recurso = new CRecurso();
            
            recurso->cod =          __Integer::create(jsonRecurso->child->valueInt);
            recurso->uri =          __String::create(jsonRecurso->child->next->valueString);
            recurso->bloqueo =      __Integer::create(jsonRecurso->child->next->next->valueInt);
            recurso->x =            __Integer::create(jsonRecurso->child->next->next->next->valueInt);
            recurso->y =            __Integer::create(jsonRecurso->child->next->next->next->next->valueInt);
            recurso->z =            __Integer::create(jsonRecurso->child->next->next->next->next->next->valueInt);
            recurso->giro =         __Integer::create(jsonRecurso->child->next->next->next->next->next->next->valueInt);
            recurso->doble =        __Integer::create(jsonRecurso->child->next->next->next->next->next->next->next->valueInt);
            recurso->separacion =   __Integer::create(jsonRecurso->child->next->next->next->next->next->next->next->next->valueInt);
            recurso->tipoRecurso = __Integer::create(tipo);
            
            arrayRecursos->addObject(recurso);
            jsonRecurso = jsonRecurso->next;
        }
        
        CTipoRecurso *tipoRecurso = new CTipoRecurso(cod,nombre,arrayRecursos);
        
        return tipoRecurso;
    }else{
        return NULL;
    }
}



Color3B* CGestorRecursos::obtenerColorSeleccion(int cod){
    if(cod==0)
        cod = 1;
    CTipoRecurso *tipoRecurso = obtenerTipoRecursos(TIPOS::Colores);
    CRecurso *rColor = tipoRecurso->obtenerRecursoPorCod(cod);
    return new Color3B(rColor->x->getValue(),rColor->y->getValue(),rColor->z->getValue());
}

void CGestorRecursos::generarArchivoInicialRecursosBloqueados(){
    __Array * recursosBloqueados = __Array::create();
    
    
    for (int r = PrimerTipo; r <= UltimoTipo; ++r) {
        log("obtenerRecursosBloqueados] Tipo Recurso: %i",TIPOS(r));
        CTipoRecurso *TipoRecursoActual = obtenerTipoRecursos(TIPOS(r));
        if(TipoRecursoActual!=NULL){
            for (int i=0; i<TipoRecursoActual->recursos->count(); i++) {
                CRecurso *recursoActual = dynamic_cast<CRecurso*>(TipoRecursoActual->recursos->getObjectAtIndex(i));
                if(recursoActual->bloqueo->getValue()==1){
                    recursosBloqueados->addObject(recursoActual);
                }
            }
        }
    }
    
    //guardo el archivo inicial
    Configuracion::guardarArchivo(Configuracion::nombreArchivoRecursosBloqueados,obtenerJsonBloqueados(recursosBloqueados));
}
void CGestorRecursos::quitarRecursoBloqueado(CRecurso *recurso){
    TIPOS tipo = obtenerTipoRecursoPorInt(recurso->tipoRecurso->getValue());
    quitarRecursoBloqueado(tipo, recurso->cod->getValue());
}
void CGestorRecursos::quitarRecursoBloqueado(TIPOS tipo,int cod){
    __Array * recursosBloqueados = __Array::create();
    
    std::string txtRecursosBloqueados = Configuracion::leerArchivo(Configuracion::nombreArchivoRecursosBloqueados,false);
    Json *json = Json_create(txtRecursosBloqueados.c_str());
    Json *jsonRecursosBloqueados = json->child;
    Json *jsonRecursoActual = json->child->child;
    for (int i=0; i<jsonRecursosBloqueados->size;i++) {
        CRecurso *recursoBloqueado = new CRecurso();
        
        recursoBloqueado->tipoRecurso = __Integer::create(jsonRecursoActual->child->valueInt);
        recursoBloqueado->cod = __Integer::create(jsonRecursoActual->child->next->valueInt);
        
        if(recursoBloqueado->tipoRecurso->getValue()==tipo&&recursoBloqueado->cod->getValue()==cod)
            log("QUITADO RECURSO cod %i tipo %i",recursoBloqueado->cod->getValue(),recursoBloqueado->tipoRecurso->getValue());
        else{
            recursosBloqueados->addObject(recursoBloqueado);
        }
        
        jsonRecursoActual = jsonRecursoActual->next;
    }
    
    log("QUEDAN %zi recursos por desbloquear",recursosBloqueados->count());
    std::string txtJsonBloqueados = obtenerJsonBloqueados(recursosBloqueados);
    Configuracion::guardarArchivo(Configuracion::nombreArchivoRecursosBloqueados,obtenerJsonBloqueados(recursosBloqueados));
    
}

std::string CGestorRecursos::obtenerJsonBloqueados(cocos2d::__Array *recursosBloqueados){

    std::string jsonRecursosBloqueados = __String::createWithFormat("{ \"%s\":[",keyRecursosBloqueados.c_str())->getCString();
    
    for(int i=0;i<recursosBloqueados->count();i++){
        CRecurso *recursoActual = dynamic_cast<CRecurso*>(recursosBloqueados->getObjectAtIndex(i));
        __String *jsonRecursoActual = __String::createWithFormat("{\"%s\": %i ,\"%s\":%i}",keyTipoRecursosBloqueado.c_str(),recursoActual->tipoRecurso->getValue(),keyCodRecursosBloqueados.c_str(),recursoActual->cod->getValue());
        
        jsonRecursosBloqueados.append(jsonRecursoActual->getCString());
        if(i!=recursosBloqueados->count()-1){
            jsonRecursosBloqueados.append(",");
        }
    }
    
    jsonRecursosBloqueados.append("]}");
    //log("%s",jsonRecursosBloqueados.c_str());
    return jsonRecursosBloqueados;
}


CRecurso* CGestorRecursos::obtenerRecursoBloqueadoAleatorio(){
    std::string txtRecursosBloqueados = Configuracion::leerArchivo(Configuracion::nombreArchivoRecursosBloqueados,false);
    Json *json = Json_create(txtRecursosBloqueados.c_str());
    Json *jsonRecursosBloqueados = json->child;
    Json *jsonRecursoActual = json->child->child;
    
    CRecurso *recursoBloqueado = NULL;
    int nAleatorio = Configuracion::aleatorioEnteros(0, jsonRecursosBloqueados->size-1);
    for (int i=0; i<jsonRecursosBloqueados->size;i++) {
        
        if(i==nAleatorio){
            recursoBloqueado = new CRecurso();
            recursoBloqueado->tipoRecurso = __Integer::create(jsonRecursoActual->child->valueInt);
            recursoBloqueado->cod = __Integer::create(jsonRecursoActual->child->next->valueInt);
        }
        jsonRecursoActual = jsonRecursoActual->next;
    }
    
    if(recursoBloqueado!=NULL){
        CGestorRecursos::TIPOS tipo =obtenerTipoRecursoPorInt(recursoBloqueado->tipoRecurso->getValue());
        return obtenerRecurso(tipo,recursoBloqueado->cod->getValue());
    }
    
    return NULL;
    
}

__Array* CGestorRecursos::obtenerRecursosBloqueados(){
    std::string txtRecursosBloqueados = Configuracion::leerArchivo(Configuracion::nombreArchivoRecursosBloqueados,false);
    Json *json = Json_create(txtRecursosBloqueados.c_str());
    Json *jsonRecursosBloqueados = json->child;
    Json *jsonRecursoActual = json->child->child;
    
    __Array *recursosBloqueados = __Array::createWithCapacity(jsonRecursosBloqueados->size);
    for (int i=0; i<jsonRecursosBloqueados->size;i++) {
        
        CRecurso *recursoBloqueado = new CRecurso();
        recursoBloqueado->tipoRecurso = __Integer::create(jsonRecursoActual->child->valueInt);
        recursoBloqueado->cod = __Integer::create(jsonRecursoActual->child->next->valueInt);
        recursoBloqueado->tipoRecurso->retain();
        recursoBloqueado->cod->retain();
        recursoBloqueado->retain();
        recursosBloqueados->addObject(recursoBloqueado);
        
        jsonRecursoActual = jsonRecursoActual->next;
    }
    
    return recursosBloqueados;
}

CRecurso* CGestorRecursos::obtenerRecurso(TIPOS tipo, int cod){

    CTipoRecurso *tipoRecursoActual = obtenerTipoRecursos(tipo);
    return tipoRecursoActual->obtenerRecursoPorCod(cod);
    
}
CRecurso* CGestorRecursos::obtenerRecursoNoVacio(TIPOS tipo, int cod){
    
    CTipoRecurso *tipoRecursoActual = obtenerTipoRecursos(tipo);
    CRecurso * recursoRetorno = tipoRecursoActual->obtenerRecursoPorCod(cod);
    if(cod == 0)
        recursoRetorno->uri = __String::create("vacio.png");
    return recursoRetorno;
    
}

CRecurso* CGestorRecursos::obtenerRecursoAleatorioNoVacio(TIPOS tipo){
    CRecurso * recurso = obtenerRecursoAleatorio(tipo);
    while (recurso->cod->getValue()==0) {
        recurso = obtenerRecursoAleatorio(tipo);
    }
    log("no vacio recurso %i tipo %i cod ",recurso->tipoRecurso->getValue(),recurso->cod->getValue());
    return recurso;
}

CRecurso* CGestorRecursos::obtenerRecursoAleatorio(TIPOS tipo){
    
    CTipoRecurso *tipoRecursoActual = obtenerTipoRecursos(tipo);
    int cantidad = tipoRecursoActual->recursos->count();
    int nAleatorio = Configuracion::aleatorioEnteros(0,cantidad-1);
    
    return dynamic_cast<CRecurso*>(tipoRecursoActual->recursos->getObjectAtIndex(nAleatorio));
    
}

CGestorRecursos::TIPOS CGestorRecursos::obtenerTipoRecursoPorInt(int tipo){

    for (int r = PrimerTipo; r <= UltimoTipo; ++r) {
        if(TIPOS(r)==tipo)
            return TIPOS(r);
    }
    
    return TIPOS::Indefinido;
}

__Array* CGestorRecursos::ObtenerSonido(int n){

    sonidos = __Array::createWithCapacity(Configuracion::nSonido);
    sonidos->retain();

    __Array *objSonido1 = __Array::createWithCapacity(2);
    objSonido1->insertObject(__String::create("Biup Biup"),indiceSonidoLabel);
    objSonido1->insertObject(__String::create("mimostro_biupbiup.mp3"), indiceSonidoValue);
    sonidos->addObject(objSonido1);
    
    __Array *objSonido2 = __Array::createWithCapacity(2);
    objSonido2->insertObject(__String::create("Bla Bla"),indiceSonidoLabel);
    objSonido2->insertObject(__String::create("mimostro_blabla.mp3"), indiceSonidoValue);
    sonidos->addObject(objSonido2);
    
    __Array *objSonido3 = __Array::createWithCapacity(2);
    objSonido3->insertObject(__String::create("Fiui"),indiceSonidoLabel);
    objSonido3->insertObject(__String::create("mimostro_fiui.mp3"), indiceSonidoValue);
    sonidos->addObject(objSonido3);
    
    __Array *objSonido4 = __Array::createWithCapacity(2);
    objSonido4->insertObject(__String::create("Groar"),indiceSonidoLabel);
    objSonido4->insertObject(__String::create("mimostro_groar.mp3"), indiceSonidoValue);
    sonidos->addObject(objSonido4);
    
    __Array *objSonido5 = __Array::createWithCapacity(2);
    objSonido5->insertObject(__String::create("Jeje 1"),indiceSonidoLabel);
    objSonido5->insertObject(__String::create("mimostro_jeje_1.mp3"), indiceSonidoValue);
    sonidos->addObject(objSonido5);
    
    __Array *objSonido6 = __Array::createWithCapacity(2);
    objSonido6->insertObject(__String::create("Jeje 2"),indiceSonidoLabel);
    objSonido6->insertObject(__String::create("mimostro_jeje_2.mp3"), indiceSonidoValue);
    sonidos->addObject(objSonido6);
    
    __Array *objSonido7 = __Array::createWithCapacity(2);
    objSonido7->insertObject(__String::create("Pedorreta"),indiceSonidoLabel);
    objSonido7->insertObject(__String::create("mimostro_pedorreta.mp3"), indiceSonidoValue);
    sonidos->addObject(objSonido7);
    
    __Array *objSonido8 = __Array::createWithCapacity(2);
    objSonido8->insertObject(__String::create("Pollo"),indiceSonidoLabel);
    objSonido8->insertObject(__String::create("mimostro_pollo.mp3"), indiceSonidoValue);
    sonidos->addObject(objSonido8);
    
    __Array *objSonido9 = __Array::createWithCapacity(2);
    objSonido9->insertObject(__String::create("Pulgoso"),indiceSonidoLabel);
    objSonido9->insertObject(__String::create("mimostro_pulgoso.mp3"), indiceSonidoValue);
    sonidos->addObject(objSonido9);
    
    __Array *objSonido10 = __Array::createWithCapacity(2);
    objSonido10->insertObject(__String::create("Queja"),indiceSonidoLabel);
    objSonido10->insertObject(__String::create("mimostro_queja.mp3"), indiceSonidoValue);
    sonidos->addObject(objSonido10);
    
    __Array *objSonido11 = __Array::createWithCapacity(2);
    objSonido11->insertObject(__String::create("Wiii"),indiceSonidoLabel);
    objSonido11->insertObject(__String::create("mimostro_wiii.mp3"), indiceSonidoValue);
    sonidos->addObject(objSonido11);
    
    __Array *objSonido12 = __Array::createWithCapacity(2);
    objSonido12->insertObject(__String::create("Yeee"),indiceSonidoLabel);
    objSonido12->insertObject(__String::create("mimostro_yeee.mp3"), indiceSonidoValue);
    sonidos->addObject(objSonido12);

    return dynamic_cast<__Array*>(sonidos->getObjectAtIndex(n));

}

Sprite* CGestorRecursos::obtenerSpriteMontado(cocos2d::Sprite *mostroRecibido, CRecurso *recurso, float escala){

    mostroRecibido->setTexture(recurso->uri->getCString());
    float x = mostroRecibido->getPositionX()+(recurso->x->getValue()*escala);
    float y = mostroRecibido->getPositionY()+(recurso->y->getValue()*escala);
    int z = mostroRecibido->getLocalZOrder()+recurso->z->getValue();
    int giro = mostroRecibido->getRotation()+recurso->giro->getValue();
    
    mostroRecibido->setPosition(x,y);
    mostroRecibido->setLocalZOrder(z);
    mostroRecibido->setRotation(giro);

    return mostroRecibido;
}

#endif
