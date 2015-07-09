#include "LanguageManager.h"
#include "Configuracion.h"

LanguageManager* LanguageManager::_instance = 0;

LanguageManager::LanguageManager()
{
    LanguageManager::recompilar();
}

LanguageManager* LanguageManager::getInstance()
{
    if(!_instance)
        _instance = new LanguageManager();
    return _instance;
}

string LanguageManager::getStringForKey(string key)
{
    if(!document[key.c_str()].IsNull())
        return document[key.c_str()].GetString();
    else{
        recompilar();
        if(!document[key.c_str()].IsNull())
            return document[key.c_str()].GetString();
        else
            return __String::create("")->getCString();
    }
}

void LanguageManager::recompilar(){
    string fileName;
    // detect current language
    switch(CCApplication::getInstance()->getCurrentLanguage())
    {
        case LanguageType::ENGLISH:
            fileName = "en.json";
            break;
        case  LanguageType::FRENCH:
            fileName = "es.json";
            break;
        case  LanguageType::SPANISH:
            fileName = "es.json";
            break;
        default:
            CCLOG("Unknown language. Use english");
            fileName = "idioma.json";
            break;
    };
    
    switch (Configuracion::idioma) {
        case 1:
            fileName = "es.json";
            break;
        case 2:
            fileName = "en.json";
            break;
        case 3:
            fileName = "en.json";
            break;
            
    }
    
    CCLOG("Language file %s",fileName.c_str());

    // below we open, read and parse language data file with rapidjson library
    string clearContent = FileUtils::getInstance()->getStringFromFile(fileName);
    
    document.Parse<0>(clearContent.c_str());
    if(document.HasParseError())
    {
        CCLOG("Language file parsing error!");
        return;
    }

}


string  LanguageManager::getString(string key)
{
    string value = getInstance()->getStringForKey(key);
    CCLOG("IDIOMAS->key: %s value: %s",key.c_str(),value.c_str());
    return value;
}
