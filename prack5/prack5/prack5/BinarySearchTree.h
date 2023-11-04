#pragma once
#include <string>
#include <iostream>

using namespace std;

struct country
{
    char name[100];
    long population;
    bool memberUN;
};

struct node
{
    string key = "";
    int value = NULL;
    char height;
    node* left, * right;
};
class BinarySearchTree
{
private:
    node* minValueNode(struct node* node);
public:
    node* root;
    node* newNode(string item, int value);
    node* insert(struct node* node, string key, int value);
    node* search(struct node* root, string key);
    node* deleteNode(struct node* root, string key);
    void printTree(node* node, int level = 0);
};

