#include <iostream>
#include "RBTree.h"
#include "BinFiler.h"

int SEARCH = 1;
int DELETE = 2;
int PRINT = 3;
int AV_ROT = 4;
int END = 5;


int main()
{
	auto filer = BinFiler();
	filer.generateRandom(100000);
	cout << "Enter entries count: " << endl;
	int count;
	cin >> count;
	cout << "Enter file's name: " << endl;
	string fileName;
	cin >> fileName;

	filer.fromTextFile(fileName + ".txt", fileName + ".bin");
	//cout << "Data from file: " << endl;
	//filer.read(fileName + ".bin");


	auto rbt = new RBTree();
	filer.createBDPFromFile(fileName + ".bin", count, rbt);
	cout << "Created tree: " << endl;
	rbt->print();

	cout << "Avalable commands: \n";
	cout << "Search by key: " << SEARCH << endl;
	cout << "Delete by key: " << DELETE << endl;
	cout << "Print tree: " << PRINT << endl;
	cout << "Get average rotates: " << AV_ROT << endl;
	cout << "End: " << END << endl;
	

	while (true) {
		int command;
		cin >> command;
		if (command == SEARCH)
		{
			string key;
			cin >> key;
			filer.getFromFileByKey(fileName + ".bin", rbt, key);
		}
		else if (command == DELETE)
		{
			string key;
			cin >> key;
			rbt->deleteNode(key);
		}
		else if (command == PRINT)
		{
			rbt->print();
		}
		else if (command == AV_ROT)
		{
			cout << rbt->getAverageRotates() << endl;
		}
		else if (command == END)
		{
			return 0;
		}
	}
}

