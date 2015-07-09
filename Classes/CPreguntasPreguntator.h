//
//
//  Mostrosity
//
//  Created by David Lopez Roldan on 29/11/14.
//
//

#ifndef __Mostrosity__CPreguntasPreguntator__
#define __Mostrosity__CPreguntasPreguntator__

#include <stdio.h>
#include "cocos2d.h"

using std::string;

#include "json/rapidjson.h"
#include "json/document.h"

using namespace cocos2d;
class  CPreguntasPreguntator : public cocos2d::Object
{
    private:
    
    rapidjson::Document document;
//    const char* obtenerArchivo();
    
    public:
    CPreguntasPreguntator();
    
    //PROFESION
    __String *sPregunta;
    __String *sAudio;
    __String *sPreguntaEN;
    __String *sAudioEN;
    int iRespuestaOK;
    float fDuracion;
    __Array *aRespuestas;
    
    void cargarPregunta(int numero);
    int ObtenerNumeroPreguntas();
    
    //GENERAL
    const char* Imprimir();

};



#endif /* defined(__Mostrosity__CPreguntasPreguntator__) */
