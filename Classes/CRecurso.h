//
//
//  Mostrosity
//
//  Created by David Lopez Roldan on 29/11/14.
//
//

#ifndef __Mostrosity__CRecurso__
#define __Mostrosity__CRecurso__

#include <stdio.h>
#include "cocos2d.h"

using std::string;

#include "json/rapidjson.h"
#include "json/document.h"

using namespace cocos2d;
class  CRecurso : public cocos2d::Object,public Clonable
{
    private:
    
    
    public:
    CRecurso();
    CRecurso(__Integer *cod,__String *uri,__Integer *_bloqueo,__Integer *x,__Integer *y,__Integer *z,
             __Integer *giro,__Integer *doble,__Integer *separacion);
    __Integer *cod;
    __String *uri;
    __Integer *bloqueo;//NOTA ESTO SOLO ES PARA LEER INICIALMENTE
    __Integer *x;
    __Integer *y;
    __Integer *z;
    __Integer *giro;
    __Integer *doble;
    __Integer *separacion;
    const char* Imprimir();
    
    //usado solo para gestionar los bloqueos de recursos
    __Integer *tipoRecurso;
    virtual CRecurso* clone() const;

};



#endif
