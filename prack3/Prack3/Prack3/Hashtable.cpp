#include "Hashtable.h"


HashTable::HashTable(int size) {
	this->size = size;
	indexesUsed = 0;
	for (int i = 0; i < size; i++) {
		TableItem *item = new TableItem();
		values.push_back(item);
	}
}

void HashTable::put(BankAccount* data) {
	if ((float)(indexesUsed + indexesDeleted) > size * 0.75)
		rehash();	
	int index = hash(data->accountNumber);
	int f = index;
	int count = 0;
	while (!values.at(index)->open) {
		count++;
		index = (f + count*count) % size;
	}
		
	TableItem *item = new TableItem();
	item->data = data;
	item->open = false;
	values[index] = item;
	indexesUsed++;
}

void HashTable::rehash() {
	size *= 2;
	indexesDeleted = 0;
	indexesUsed = 0;
	vector<TableItem*> newValues;
	for (int i = 0; i < size; i++) {
		TableItem *item = new TableItem();
		newValues.push_back(item);
	}
	vector<TableItem*> oldValues;
	for (auto item : values)
		oldValues.push_back(item);
	values = newValues;
	for (auto item : oldValues) {
		if (!item->open) {
			put(item->data);
		}
	}
}

void HashTable::remove(char key[])
{
	auto item = get(key);
	int index = hash(key);
	int f = index;
	int count = 0;
	while (strcmp(values[index]->data->accountNumber, key)) {
		count++;
		index = (f + count * count) % size;
	}
	values[index]->deleted = true;
	values[index]->data = nullptr;
	values[index]->open = true;
	indexesDeleted++;
	indexesUsed--;
}

BankAccount * HashTable::get(char key[])
{
	int hashKey = hash(key);
	if (values[hashKey]->open)
		return nullptr;
	if (values[hashKey]->data->accountNumber == key)
		return values[hashKey]->data;
	int count = 0;
	int f = hashKey;
	while (hashKey < size && (!values[hashKey]->open || values[hashKey]->deleted))
	{
		if (!strcmp(values[hashKey]->data->accountNumber, key))
			return values[hashKey]->data;
		count++;
		hashKey = (f + count * count) % size;
	}
	return nullptr;
}


int HashTable::hash(char key[])
{
	std::hash<std::string> hasher;
	return hasher(key) % size;
}

vector<char*> HashTable::getKeys()
{
	vector<char*> v;
	for (auto val : values) {
		if (!val->open)
			v.push_back(val->data->accountNumber);
	}
	return v;
}

int HashTable::nextIndex(int index, int q)
{
	return index + q*q;
}

