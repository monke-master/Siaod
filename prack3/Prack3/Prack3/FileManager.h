#ifndef __file_manager_h__
#define __file_manager_h__

#include "Hashtable.h"
#include "string"
#include <vector>
#include "fstream"
#include "iostream"
#include <time.h>


class FileManager
{
private: 
	string fileName;
public:
	FileManager(string fileName);
	BankAccount* read(int index);
	void remove(char * key);
	void generateFile(int size);
	void readAll();
};


#endif
