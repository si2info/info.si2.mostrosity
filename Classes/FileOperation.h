#ifndef __HELLOWORLD_FILE_OPERATION__
#define __HELLOWORLD_FILE_OPERATION__

#include <string>
using namespace std;
class FileOperation 
{
public:
	static bool saveFile(string archivo,string contenido);
	static string readFile(string archivo);
	static string getFilePath();
    static string deleteFile(string archivo);
};

#endif
