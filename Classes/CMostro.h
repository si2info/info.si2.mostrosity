//
//  Configuracion.h
//  Mostrosity
//
//  Created by David Lopez Roldan on 29/11/14.
//
//

#ifndef __Mostrosity__CMostro__
#define __Mostrosity__CMostro__

#include <stdio.h>
#include "cocos2d.h"
using namespace cocos2d;

class  CMostro : public Ref
{
    static const int iPiernaIzq=1;
    static const int iPiernaDer=2;
    static const int iManoIzq=3;
    static const int iManoDer=4;
    static const int iCuerpo=5;
    static const int iAla=6;
    static const int iGorro=7;

    public:
    CMostro();
    CMostro(cocos2d::__String Pnombre,cocos2d::__String Psonido);
    void AgregarParte(int parte,cocos2d::__String valor);
    
    cocos2d::__String nombre;
    cocos2d::__String sonido;
    
    cocos2d::__String piernaIzq;
    cocos2d::__String piernaDer;
    cocos2d::__String manoIzq;
    cocos2d::__String manoDer;
    cocos2d::__String cuerpo;
    cocos2d::__String gorro;
    cocos2d::__String alas;
    
    cocos2d::Node *composicion;
    
    const char* Imprimir();
    const char* ImprimirCompleto();

    //nuevo
    cocos2d::__String *nombreMostro;
    cocos2d::__String *sonidoMostro;
    __Integer *color;
    LayerColor *mostro;
    Sprite *mostro_cuerpo;
    Sprite *mostro_pies;
    Sprite *mostro_ojos;
    Sprite *mostro_orejas;
    Sprite *mostro_boca;
    Sprite *mostro_brazos;
    Sprite *mostro_pelo;
    Sprite *mostro_alas;
    Sprite *mostro_accesorio;
    
    //RECURSOS
    void initRecursos();
    
    
};



#endif /* defined(__Mostrosity__CMostro__) */
