#include <iostream>
#include "FileModule.h"

using namespace std;


int main() {
    setlocale(LC_ALL, "Russian");
    FileModule fileModule = FileModule();
    fileModule.startWork();
}
