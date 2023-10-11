#ifndef PRACK22_BINMODULE_H
#define PRACK22_BINMODULE_H

#include <string>
#include "fstream"
#include "iostream"
#include "string.h"

using namespace std;

class BinModule {
public:
    void read(string fileName);
    bool fromTextFile(string textFileName, string binFileName);
    void saveToText(string textFileName, string binFileName);
    void workWithFile(string fileName);
    void getDisciplineByIndex(string fileName, int index);
    void deleteByIndex(string fileName, string key);
    void getByDirectionAndSem(string fileName, string direction, int semester);
    void replaceTitle(string fileName, string title, int sem, string direction, string newTitle);
    int startWork();
};


#endif //PRACK22_BINMODULE_H
