#ifndef  _CMOSTRO_H_
#define  _CMOSTRO_H_

#include "cocos2d.h"
#include "CMostro.h"

USING_NS_CC;

CMostro::CMostro(){

}

CMostro::CMostro(__String Pnombre,__String Psonido){
    
    nombre = Pnombre;
    sonido = Psonido;
}

void CMostro::AgregarParte(int parte,__String valor){
    switch (parte) {
        case iPiernaIzq:
            piernaIzq = valor;
            break;
        case iPiernaDer:
            piernaDer = valor;
            break;
        case iManoIzq:
            manoIzq = valor;
            break;
        case iManoDer:
            manoDer = valor;
            break;
        case iCuerpo:
            cuerpo = valor;
            break;
        case iAla:
            alas = valor;
            break;
        case iGorro:
            gorro = valor;
            break;
            
        default:
            break;
    }
};

const char* CMostro::Imprimir(){
    
    __String *respuesta = String::createWithFormat("Nombre: %s, Sonido: %s",nombre.getCString(),sonido.getCString());
    return respuesta->getCString();
}

const char* CMostro::ImprimirCompleto(){
    
    __String *respuesta = String::createWithFormat("Nombre: %s, Sonido: %s ,Pierna Izquierda: %s,Pierna Derecha: %s,Mano Izquierda: %s,Mano Derecha: %s,Cuerpo: %s,Alas: %s,Gorro: %s",nombre.getCString(),sonido.getCString(),piernaIzq.getCString(),piernaDer.getCString(),manoIzq.getCString(),manoDer.getCString(),cuerpo.getCString(),alas.getCString(),gorro.getCString());
    return respuesta->getCString();
}

#endif
