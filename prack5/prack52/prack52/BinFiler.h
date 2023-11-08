#pragma once
#include "RBTree.h"
#include <fstream>
#include <chrono>

struct country
{
	char name[100];
	long population;
	bool memberUN;
};

class BinFiler
{
public:
	void insertFromFile(string fileName, int index, RBTree* tree);
	void createBDPFromFile(string fileName, int size, RBTree* tree);
	void getFromFileByKey(string fileName, RBTree* tree, string key);
	country* getCountryByIndex(string fileName, int index);
	void fromTextFile(string textFileName, string binFileName);
	void read(string fileName);
	void generateRandom(int size);
};

