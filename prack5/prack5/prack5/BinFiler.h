#pragma once
#include "BinarySearchTree.h"
#include <fstream>
#include <chrono>

class BinFiler
{
public:
	void insertFromFile(string fileName, int index, BinarySearchTree* tree);
	void createTree(string fileName, int size, BinarySearchTree* tree);
	void getValue(string fileName, BinarySearchTree* tree, string key);
	country* getCountryByIndex(string fileName, int index);
	void fromTextFile(string textFileName, string binFileName);
	void read(string fileName);
};

