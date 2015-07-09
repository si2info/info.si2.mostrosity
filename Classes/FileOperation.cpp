// to enable CCLOG()
#define COCOS2D_DEBUG 1

#include "cocos2d.h"
#include "FileOperation.h"
#include <stdio.h>

using namespace std;
USING_NS_CC;

bool FileOperation::saveFile(string archivo,string contenido)
{
	string path = getFilePath().append(archivo.c_str());
	log("Guardando archivo en %s",path.c_str());
    FILE *fp = fopen(path.c_str(), "w");

	if (! fp)
	{
		CCLOG("can not create file %s", path.c_str());
		return false;
	}

	fputs(contenido.c_str(), fp);
	fclose(fp);
    return true;
}

string FileOperation::readFile(string archivo)
{
    string path = getFilePath().append(archivo.c_str());
    return FileUtils::getInstance()->getStringFromFile(path);
    
}
string FileOperation::deleteFile(string archivo){
    string path = getFilePath().append(archivo.c_str());
    remove(path.c_str());
}

string FileOperation::getFilePath()
{
	string path("");
    

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	// In android, every programe has a director under /data/data.
	// The path is /data/data/ + start activity package name.
	// You can save application specific data here.
	path.append("/data/data/org.cocos2dx.application/tmpfile");
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	// You can save file in anywhere if you have the permision.
	path.append("D:/tmpfile");
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WOPHONE)
	path = cocos2d::CCApplication::sharedApplication().getAppDataPath();

#ifdef _TRANZDA_VM_
	// If runs on WoPhone simulator, you should insert "D:/Work7" at the
	// begin. We will fix the bug in no far future.
	path = "D:/Work7" + path;
	path.append("tmpfile");
#endif

#endif
    
    //REVISAR EN ANDROID
    path = FileUtils::getInstance()->getWritablePath().c_str();
    //log("%s",path.c_str());
	return path;
}