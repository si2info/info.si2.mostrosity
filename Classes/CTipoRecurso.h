//
//
//  Mostrosity
//
//  Created by David Lopez Roldan on 29/11/14.
//
//

#ifndef __Mostrosity__CTipoRecurso__
#define __Mostrosity__CTipoRecurso__

#include <stdio.h>
#include "cocos2d.h"

using std::string;

#include "CRecurso.h"
#include "json/rapidjson.h"
#include "json/document.h"

using namespace cocos2d;
class  CTipoRecurso : public Ref
{
    private:
    
    
    public:
    CTipoRecurso();
    CTipoRecurso(__Integer *_cod,__String *_nombre,__Array * _recursos);
    
    __Integer *cod;
    __String *nombre;
    __Array * recursos;
    CRecurso * obtenerRecursoPorCod(int cod);
    CRecurso * obtenerRecurso(int n);
    const char* Imprimir();

};



#endif
