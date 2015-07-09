#ifndef  _CTIPORECURSO_H_
#define  _CTIPORECURSO_H_

#include "cocos2d.h"
#include "CTipoRecurso.h"


USING_NS_CC;
using namespace cocos2d;

CTipoRecurso::CTipoRecurso(){

}

CTipoRecurso::CTipoRecurso(__Integer *_cod,__String *_nombre,__Array * _recursos){
    
    cod = _cod;
    nombre = _nombre;
    recursos = _recursos;

}

CRecurso * CTipoRecurso::obtenerRecursoPorCod(int cod){
    CRecurso *recursoRetorno = NULL;
    for(int i=0;i<this->recursos->count();i++){
        CRecurso *recursoActual = dynamic_cast<CRecurso*>(this->recursos->getObjectAtIndex(i));
        if(recursoActual->cod->getValue()==cod){
            recursoRetorno = recursoActual;
            break;
        }
    }
    
    return recursoRetorno;
    
}
CRecurso * CTipoRecurso::obtenerRecurso(int n){
    return dynamic_cast<CRecurso*>(this->recursos->getObjectAtIndex(n));
}


#endif
