//
//
//  Mostrosity
//
//  Created by David Lopez Roldan on 29/11/14.
//
//

#ifndef __Mostrosity__CProfesionAkuerdate__
#define __Mostrosity__CProfesionAkuerdate__

#include <stdio.h>
#include "cocos2d.h"

using std::string;

#include "json/rapidjson.h"
#include "json/document.h"

using namespace cocos2d;
class  CProfesionAkuerdate : public cocos2d::Object
{
    private:
    //PRIVADOS
    Sprite *spImgProfesion;
    Sprite *spImgFondo = NULL;
    
    int indiceImgElementoProfesion = 0;
    int indiceX = 1;
    int indiceY = 2;
    int indiceZ = 3;
    int indiceGrados = 4;
    int indiceTXT = 5;
    int indiceAudio = 6;
    int indiceTxtEN = 7;
    int indiceAudioEN = 8;
    __Array *aElementosProfesion;
    
    rapidjson::Document document;
//    const char* obtenerArchivo();
    
    public:
    CProfesionAkuerdate();
    
    //PROFESION
    __String *sNombreProfesion;
    __String *sNombreProfesionEN;
    __String *sImagen;
    __String *sFondo;
    
    void cargarProfesion(int numero);
    Sprite *obtenerImgProfesion();
    Sprite* obtenerImgFondo();
    int ObtenerNumeroProfesiones();
    
    
    //Elementos
    __Array *obtenerElementosProfesion();
    Sprite *obtenerElemento(int numero);
    Vec2 obternerPosElementoProfesion(int numero);
    int obtenerZIndexElemento(int numero);
    float obtenerGradosElemento(int numero);
    __String* obtenerPalabraElemento(int numero);
    __String* obtenerAudioElemento(int numero);
    
    
    
    
    //GENERAL
    const char* Imprimir();

};



#endif /* defined(__Mostrosity__CProfesionAkuerdate__) */
