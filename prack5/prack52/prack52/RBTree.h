#pragma once
#include <string>
#include <iostream>
using namespace std;

struct Node {
	string key;
	Node* left, * right;

	int value;
	bool isRed;
};

class RBTree {
	
	int keysInserted = 0;
	int rotates = 0;
	Node* root;
	private:
		Node* newNode(string key, int value);			
		Node* rotateLeft(Node* node);		
		Node* rotateRight(Node* node);		
		void fixInsertion(Node** node);		
		bool fixRemoveLeft(Node** node);	
		bool fixRemoveRight(Node** node);		
		bool insert(string key, int value, Node** node);			
		bool minValueNode(Node** node, Node** res);	
		bool deleteNode(Node** node, string key);		
		void printLevel(Node* node, int level = 0);
		Node* getByKey(Node* node, string key);
	public:
		Node* getByKey(string key);			
		void insert(string key, int value);		
		void deleteNode(string key);		
		void print();
		float getAverageRotates();
		
};