#include <iostream>
#include "BinaryTree.h"


string PRINT = "pr";
string POS_LEAV = "pl";
string COUNT = "c";
string DOUBLE = "d";
string END = "end";

int main()
{

    cout << "Enter tree size: " << endl;
    int size;
    cin >> size;
    auto tree = BinaryTree(size);

    cout << "Available commands: \n";
    cout << "Print tree: " << PRINT << endl;
    cout << "Count nodes with number: " << COUNT << " {number}\n";
    cout << "Double node's values: " << DOUBLE << endl;
    cout << "Count positive leaves: " << POS_LEAV << endl;
    cout << "End work: " << END << endl;

    string command;
    while (command != END)
    {
        cin >> command;
        if (command == PRINT)
        {
            tree.print();
            cout << endl;
        }
        else if (command == COUNT)
        {
            int num;
            cin >> num;
            cout << tree.countWithNumber(num) << endl;
        }
        else if (command == POS_LEAV)
        {
            cout << tree.countPositiveLeaves() << endl;
        }
        else if (command == DOUBLE)
        {
            tree.doubleValues();
        }
    }
}
