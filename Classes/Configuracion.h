//
//  Configuracion.h
//  Mostrosity
//
//  Created by David Lopez Roldan on 29/11/14.
//
//

#ifndef __Mostrosity__Configuracion__
#define __Mostrosity__Configuracion__

#include <stdio.h>
#include <string.h>

using namespace cocos2d;

class  Configuracion : public cocos2d::Ref
{
    
    public:
    
        static bool desarrollo;
        static char * paginaWeb;
        static char * paginaLicencia;
        static int profesor;
        static int idioma;
        static float volumenEfectos;
        static float volumenMusica;
    
        //MIMOSTRO
        //MAESTROS
        static int const rcsTipoMostro;
        static int const rcsTipoExpositor;
    
        static int const rcsTipoOjos;
        static int const rcsTipoDientes;
        static int const rcsTipoBrazos;
            static int const rcsTipoBrazo_izq;
            static int const rcsTipoBrazo_der;
        static int const rcsTipoPies;
            static int const rcsTipoPies_izq;
            static int const rcsTipoPies_der;
        static int const rcsTipoAlas;
        static int const rcsTipoOrejas;
            static int const rcsTipoOreja_izq;
            static int const rcsTipoOreja_der;
        static int const rcsTipoPelo;
        static int const rcsTipoCuerpo;
        static int const rcsTipoAccesorio;
        static int const rcsTipoColor;

    
        static int nOjos;
        static int nDientes;
        static int nBrazos;
        static int nPies;
        static int nAlas;
        static int nOrejas;
        static int nPelo;
        static int nAccesorio;
        static int nSonido;
    
        static int partesDimeketekito[11];
    
        static std::string mstDientes;
        static std::string mstOjos;
        static std::string mstBrazos;
        static std::string mstPies;
        static std::string mstAlas;
        static std::string mstOrejas;
        static std::string mstPelo;
        static std::string mstAccesorio;
    
        static std::string idMiMostro;
        static int sonidoMiMostro;
        static int colorMiMostro;
        static std::string nombreMiMostro;
        static int ojosMiMostro;
        static int dientesMiMostro;
        static int brazosMiMostro;
        static int piesMiMostro;
        static int alasMiMostro;
        static int orejasMiMostro;
        static int peloMiMostro;
        static int accesorioMiMostro;
        static std::string getRecurso(int numero,std::string maestro,int tipo);
    
    
    
    //generales
//CONSTANTES
    static std::string archivoConfiguracion;
    static std::string nombreArchivoRecursosBloqueados;
//VARIABLES
    
//METODOS
    static int aleatorioEnteros(int min,int max);
    const char* charTochar(std::vector<char>*);
    static bool comprobarToque(Touch *touch,Node *sprite);
    static bool existeArchivo(std::string archivo);
    static std::string leerArchivo(std::string archivo,bool esRutaAbsoluta);
    static bool guardarArchivo(std::string archivo,std::string contenido);
    static void cargarConfiguracion();
    static void reiniciarDatos();
    
    static const char* getIDDEVICE();
    static char callWhatsApp(const char *);
    static char callFacebook(const char * web);
    static char callTwitter(const char * txt);
    static char callOpenURL(const char *);
    static void shareOnAndroid(const char *webFacebook, const char *subject, const char *text);
    //constantes idiomas.
        //menu
    void cargarIdiomas();
    
};

#endif /* defined(__Mostrosity__Configuracion__) */
