//
// Created by monke on 26.09.2023.
//

#ifndef PRACK2_FILEMODULE_H
#define PRACK2_FILEMODULE_H

#include <iostream>
#include "fstream"

using namespace std;

class FileModule {
public:
    void read(string fileName);
    void writeToFile(string fileName, string newLine);

    void getNumberOfLines(string fileName);

    void getNumberByIndex(string fileName, int index);

    void workWithFile(string fileName);

    bool createFile(string fileName);

    bool createFileFromExisting(string oldFileName, string newFileName);

    int startWork();
};


#endif //PRACK2_FILEMODULE_H
