#pragma once

#ifndef __hashtable_h__
#define __hashtable_h__

#include "string"
#include <vector>

using namespace std;

struct BankAccount {
public:
	char address[50];
	char accountNumber[8];
	char name[50];
};

struct TableItem {
	BankAccount* data;
	bool open = true;
	bool deleted = false;
};


class HashTable
{
private:
	int size;
	int indexesUsed;
	int indexesDeleted;
	int nextIndex(int index, int q);
	void rehash();
	vector<TableItem*> values;
public:
	HashTable(int size);
	void put(BankAccount* data);
	void remove(char key[]);
	BankAccount* get(char key[]);
	int hash(char key[]);
	vector<char*> getKeys();
};

#endif

