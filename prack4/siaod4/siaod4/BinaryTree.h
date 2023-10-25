#pragma once
#include "TreeNode.h"
#include <iostream>
#include <queue>

using namespace std;

class BinaryTree
{
private:
	TreeNode* root;
	TreeNode* createNode(int n);
	void printLevel(const std::string& prefix, TreeNode* node, const std::string& separator);
public:
	int size;
	int countPositiveLeaves();
	int countWithNumber(int number);
	void doubleValues();
	BinaryTree(int size);
	void print();
};

