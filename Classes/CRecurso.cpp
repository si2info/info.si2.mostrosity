#ifndef  _CRECURSO_H_
#define  _CRECURSO_H_

#include "cocos2d.h"
#include "CRecurso.h"


USING_NS_CC;
using namespace cocos2d;

CRecurso::CRecurso(){

}

CRecurso::CRecurso(__Integer *_cod,__String *_uri,__Integer *_bloqueo,__Integer *_x,__Integer *_y,__Integer *_z,
         __Integer *_giro,__Integer *_doble,__Integer *_separacion){
    
    cod = _cod;
    uri = _uri;
    bloqueo = _bloqueo;//NOTA ESTO SOLO ES PARA LEER INICIALMENTE
    x = _x;
    y = _y;
    z = _z;
    giro = _giro;
    doble = _doble;
    separacion = _separacion;
    
    
}


CRecurso* CRecurso::clone()const{
    
    CRecurso *retorno = new CRecurso();
    retorno->cod = __Integer::create(this->cod->getValue());
    retorno->tipoRecurso = __Integer::create(this->tipoRecurso->getValue());
    
    return retorno;
    
}
#endif
