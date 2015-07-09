//
//
//  Mostrosity
//
//  Created by David Lopez Roldan on 29/11/14.
//
//

#ifndef __Mostrosity__CGestorRecursos__
#define __Mostrosity__CGestorRecursos__

#include <stdio.h>
#include "cocos2d.h"
#include "CRecurso.h"
#include "CTipoRecurso.h"

using std::string;

#include "json/rapidjson.h"
#include "json/document.h"
#include "../cocos2d/cocos/editor-support/spine/Json.h"

using namespace cocos2d;
class  CGestorRecursos : public cocos2d::Object
{
    public:
    
    CGestorRecursos();
    enum TIPOS{
        Indefinido = -1,
        Ojos = 3,
        Dientes = 4,
        Brazos = 5,
        Brazo_izq = 5,
        Brazo_der = -5,
        Pies = 6,
        Pies_izq = 6,
        Pies_der = -6,
        Alas = 7,
        Orejas = 8,
        Oreja_izq = 8,
        Oreja_der = -8,
        Pelo = 9,
        Cuerpo = 10,
        Accesorio = 11,
        Colores = 12,
        
        //PARA LA GESTION DEL FOREACH
        PrimerTipo = Ojos,
        UltimoTipo = Colores
        
    };
    
    
    
    
    int obtenerNumeroTiposRecursos();
    Json* obtenerJsonObjectTipoRecurso(TIPOS tipo);
    int obtenerNumeroRecursos(TIPOS tipo);
    CTipoRecurso* obtenerTipoRecursos(TIPOS tipo);
    
    int nColores = 10;
    Color3B* obtenerColorSeleccion(int iNumero);
    std::string obtenerJsonBloqueados(__Array* recursosBloqueados);
    void generarArchivoInicialRecursosBloqueados();
    void quitarRecursoBloqueado(CRecurso *recurso);
    void quitarRecursoBloqueado(TIPOS tipo,int cod);
    __Array* obtenerRecursosBloqueados();
    CRecurso* obtenerRecursoBloqueadoAleatorio();
    CRecurso* obtenerRecurso(TIPOS tipo, int cod);
    CRecurso* obtenerRecursoNoVacio(TIPOS tipo, int cod);
    CRecurso* obtenerRecursoAleatorio(TIPOS tipo);
    CRecurso* obtenerRecursoAleatorioNoVacio(TIPOS tipo);
    Sprite* obtenerSpriteMontado(Sprite *sp,CRecurso * recurso, float escala);
    
    TIPOS obtenerTipoRecursoPorInt(int tipo);
    __Array* ObtenerSonido(int n);
    __Array* sonidos = NULL;
    int indiceSonidoLabel = 0;
    int indiceSonidoValue = 1;
    //GENERAL
    const char* Imprimir();
    Json* obtenerArchivo();
    private:
    
    rapidjson::Document document;
    
    
    
        std::string keyRecursosBloqueados;
        std::string keyTipoRecursosBloqueado;
        std::string keyCodRecursosBloqueados;
    
    

};



#endif /* defined(__Mostrosity__CPreguntasPreguntator__) */
