#include <iostream>
#include "Hashtable.h"
#include "FileManager.h"
#include <vector>
#include "BinModule.h"
#include <chrono>


using namespace std;

const string READ = "read";
const string GET = "get";
const string DELETE = "delete";
const string KEYS = "keys";
const string END = "end";
const string READ_ALL = "ra";


int main()
{
	std::cout << "Hello World!\n";
	

	cout << "Enter file's name: \n";
	string fileName;
	cin >> fileName;

	cout << "Enter file's size (for random generation): \n";
	int fileSize;
	cin >> fileSize;

	cout << "Enter hashtable size \n";
	int size;
	cin >> size;

	auto hashTable = HashTable(size);
	auto fileManager = FileManager(fileName);
	fileManager.generateFile(fileSize);

	// Для небольших данных
	//cout << "Generated file: " << endl;
	//fileManager.readAll();

	string command;
	cout << "Available commands: \n";
	cout << "Read from file by index - " << READ << " {line number}" << endl;
	cout << "Get by key - " << GET << " {key}" << endl;
	cout << "Delete by key - " << DELETE << " {key}" << endl;
	cout << "Print all hash Table keys - " << KEYS << endl;
	cout << "Read entire data from file to hash map " << READ_ALL << endl;
	while (true)
	{
		cin >> command;
		if (command == READ)
		{
			int index;
			cin >> index;
			auto *bankAccount = fileManager.read(index);
			hashTable.put(bankAccount);
		}
		else if (command == GET)
		{
			string key; 
			char k[8];
			cin >> key;
			strcpy_s(k, key.c_str());
			auto begin = chrono::steady_clock::now();
			auto *b = hashTable.get(k);
			if (b != nullptr)
			{
				auto end = chrono::steady_clock::now();
				cout << "Time spent: " << chrono::duration_cast<chrono::nanoseconds>(end - begin).count() << " ms" << endl;
				cout << "Account number " << b->accountNumber
					<< " address: " << b->address << " name: " << b->name << endl;
			}
			else
				cout << "Account not found" << endl;
		}
		else if (command == DELETE) {
			string key;
			char k[8];
			cin >> key;
			strcpy_s(k, key.c_str());
			hashTable.remove(k);
			fileManager.remove(k);
			cout << "Account has been deleted" << endl;
		}
		else if (command == KEYS)
		{
			auto v = hashTable.getKeys();
			for (auto k : v) {
				cout << k << endl;
			}
		}
		else if (command == READ_ALL)
		{
			auto begin = chrono::steady_clock::now();
			for (int i = 1; i <= fileSize; i++) {
				hashTable.put(fileManager.read(i));
			}
			auto end = chrono::steady_clock::now();
			cout << "Time spent: " << chrono::duration_cast<chrono::milliseconds>(end - begin).count() << " ms" << endl;
		}
	}
} 

