#include "BinFiler.h"

void BinFiler::insertFromFile(string fileName, int index, RBTree* tree)
{
    country* country = getCountryByIndex(fileName, index);
    string str;
    str.append(country->name);
    tree->insert(str, index);
}

void BinFiler::createBDPFromFile(string fileName, int size, RBTree* tree)
{
    for (int i = 1; i <= size; i++)
        insertFromFile(fileName, i, tree);
}

void BinFiler::getFromFileByKey(string fileName, RBTree* tree, string key)
{
    auto begin = std::chrono::steady_clock::now();
    Node* foundNode = tree->getByKey(key);
    if (foundNode == NULL)
        cout << "There is no any value with this key in the tree" << endl;
    else {
        int index = foundNode->value;
        country* country = getCountryByIndex(fileName, index);
        string s;
        s.append(country->name);
        cout << country->name << " " << country->population << " " << country->memberUN << endl;
    }
    auto end = std::chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    std::cout << "The time: " << elapsed_ms.count() << " ns\n";

}

country* BinFiler::getCountryByIndex(string fileName, int index)
{
    ifstream binFile;
    binFile.open(fileName, ios::binary);

    if (binFile.is_open()) {
        binFile.seekg((index - 1) * sizeof(country));
        country* c = new country();
        if (!binFile.good()) {
            cout << "Error has occured while reading the file";
            return nullptr;
        }
        binFile.read((char*)c, sizeof(country));
        binFile.close();
        return c;
    }
    else
        cout << "Error has occured while reading the file" << endl;
    return nullptr;
}

void BinFiler::fromTextFile(string textFileName, string binFileName)
{
    ifstream textFile;
    textFile.open(textFileName);
    if (textFile.is_open()) {
        ofstream binFile;
        binFile.open(binFileName, ios::binary | ios::trunc);
        if (binFile.is_open()) {
            while (!textFile.eof()) {
                string name;
                long population;
                int memberUN;
                textFile >> name >> population >> memberUN;;
                auto* c = new country();
                if (!name.empty()) {
                    strcpy_s(c->name, name.c_str());
                    c->population = population;
                    c->memberUN = memberUN;
                    binFile.write((char*)c, sizeof(country));
                }
            }
        }
        else
            cout << "Error has occured while reading the file" << endl;
        if (!binFile.good() && !binFile.eof())
            cout << "Error has occured while reading the file" << endl;
        if (!textFile.good() && !textFile.eof())
            cout << "Error has occured while reading the file" << endl;
        textFile.close();
        binFile.close();
    }
    else {
        cout << "Error has occured while reading the file" << endl;
    }
}

void BinFiler::read(string fileName)
{
    ifstream file;
    file.open(fileName, ios::binary);

    if (file.is_open()) {
        auto* c = new country();
        while (file.read((char*)c, sizeof(country))) {
            cout << c->name << " " << c->population << " " << c->memberUN << endl;
        }
    }
    else
        cout << "Error has occured while reading the file" << endl;
}


void BinFiler::generateRandom(int size)
{
    ofstream file;
    file.open("random.txt");

    int stringLen = 6;
    int maxPopulation = 1000000;
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    for (int i = 0; i < size; i++)
    {
        string name;
        for (int i = 0; i < stringLen; i++)
            name += alphanum[rand() % (sizeof(alphanum) - 1)];
        int population = rand() % maxPopulation;
        bool unMember = rand() % 2;
        file << name << endl;
        file << population << endl;
        file << unMember << endl;
    }

    file.close();
}