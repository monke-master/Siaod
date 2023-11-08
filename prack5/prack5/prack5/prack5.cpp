#include <iostream>
#include "BinarySearchTree.h"
#include "BinFiler.h"


int SEARCH = 1;
int DELETE = 2;
int PRINT = 3;
int END = 4;


int main()
{
	cout << "Enter entries count: " << endl;
	int count;
	cin >> count;
	cout << "Enter file's name: " << endl;
	string fileName;
	cin >> fileName;

	auto filer = BinFiler();
	filer.fromTextFile(fileName + ".txt", fileName + ".bin");
	cout << "Data from file: " << endl;
	filer.read("test.bin");

	
	auto* tree = new BinarySearchTree();
	filer.createTree(fileName + ".bin", count, tree);
	cout << "Created tree: " << endl;
	tree->printTree(tree->root, 0);

	cout << "Avalable commands: \n";
	cout << "Search by key: " << SEARCH << endl;
	cout << "Delete by key: " << DELETE << endl;
	cout << "Print tree: " << PRINT << endl;
	cout << "End: " << END << endl;

	while (true) {
		int command;
		cin >> command;
		if (command == SEARCH)
		{
			string key;
			cin >> key;
			filer.getValue(fileName + ".bin", tree, key);
		}
		else if (command == DELETE)
		{
			string key;
			cin >> key;
			tree->deleteNode(tree->root, key);
		}
		else if (command == PRINT)
		{
			tree->printTree(tree->root, 0);
		}
		else if (command == END)
		{
			return 0;
		}
	}
}
