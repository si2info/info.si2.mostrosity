//
//  Configuracion.h
//  Mostrosity
//
//  Created by David Lopez Roldan on 29/11/14.
//
//

#ifndef __Mostrosity__CPanelArmame__
#define __Mostrosity__CPanelArmame__

#include <stdio.h>
#include "cocos2d.h"

using std::string;

#include "json/rapidjson.h"
#include "json/document.h"

using namespace cocos2d;
class  CPanelArmame : public cocos2d::Object
{
    private:
    //PRIVADOS
    Sprite *spImgPanel;
    int indiceImg = 0;
    int indiceX = 1;
    int indiceY = 2;
    int indiceZ = 3;
    int indicePosComplemento = 2;
    __Array *aHuecos;
    __Array *aComplementos;
    
    rapidjson::Document document;
//    const char* obtenerArchivo();
    
    public:
    CPanelArmame();
    
    //PANEL
    __String *sImagen;
    
    void cargarPanel(int numero);
    Sprite *obtenerImgPanel();
    int ObtenerNumeroPaneles();
    //HUECOS
    
    __Array *obtenerHuecos();
    Sprite *obtenerHueco(int numero);
    Vec2 obternerMedidasHueco(int numero);
    __Array *obtenerMedidasHuecos();
    int obtenerZIndexHueco(int numero);
    
    //COMPLEMENTOS
    __Array *obtenerComplementos();
    Sprite *obtenerComplemento(int numero);
    Vec2 obternerMedidasComplemento(int numero);
    __Array *obtenerMedidasComplementos();
    int obtenerZIndexComplemento(int numero);
    
    //GENERAL
    const char* Imprimir();

};



#endif /* defined(__Mostrosity__CPanelArmame__) */
