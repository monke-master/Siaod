#include "FileManager.h"

FileManager::FileManager(string fileName) : fileName(fileName)
{

}

BankAccount* FileManager::read(int index)
{
	ifstream binFile;
	binFile.open(fileName, ios::binary);
	if (binFile.is_open()) {
		binFile.seekg((index - 1) * sizeof(BankAccount));
		BankAccount *b = new BankAccount();
		binFile.read((char *)b, sizeof(BankAccount));
		binFile.close();
		return b;		
	}
	else
		cout << "error occured while reading file" << endl;
	return nullptr;
}

void FileManager::readAll() {
	ifstream file;
	file.open(fileName, ios::binary);

	if (file.is_open()) {
		auto *d = new BankAccount();
		while (file.read((char *)d, sizeof(BankAccount))) {
			cout << d->address << " " << d->name << " " << d->accountNumber << endl;
		}
		file.close();
	}
	else
		cout << "Îøèáêà îòêðûòèÿ ôàéëà" << endl;
}

void FileManager::remove(char* key)
{
	ifstream file;
	ofstream temp;
	file.open(fileName, ios::binary);
	temp.open("temp.bin", ios::binary | ios::trunc);

	if (file.is_open() && temp.is_open()) {
		auto *b = new BankAccount();
		while (file.read((char *)b, sizeof(BankAccount))) {
			if (strcmp(b->accountNumber, key))
				temp.write((char *)b, sizeof(BankAccount));

		}
		temp.close();
		file.close();
	}
	else {
		cout << "error occured while reading file" << endl;
		return;
	}

    ofstream binFile;
	ifstream tempFile;
	binFile.open(fileName, ios::binary | ios::trunc);
	tempFile.open("temp.bin", ios::binary);


	if (binFile.is_open() && tempFile.is_open()) {
		auto *b = new BankAccount();
		while (tempFile.read((char *)b, sizeof(BankAccount))) {
			binFile.write((char *)b, sizeof(BankAccount));
		}
		tempFile.close();
		binFile.close();
	}
	else {
		cout << "error occured while reading file" << endl;
		return;
	}
}

void FileManager::generateFile(int size)
{
	srand((unsigned)time(NULL));
	ofstream binFile;
	binFile.open(fileName, ios::binary | ios::trunc);
	string adresses[10] {
		"Lunnaya", "Sovietskaya", "Propastinskaya", "Prospekt Berkova", "Voloshuk avenu",
		"Machno alley", "Hemirovkiy Broadway", "Berkistov highway", "Popov street", "Boolean avenu"
	};
	string names[10] {
		"Dzerzhinky R. I.", "Ricardo Millos", "Billy Harrington", "Popov M. A.", "Letov I. F.",
		"Mayakovky V. V.", "Pushkin A. S.", "Oldos Hacksli", "July Caesar", "Gaius Julius Caesar Octavianus Augustus"
	};

	for (int i = 1000000; i < 1000000 + size; i++) {
		char key[7];
		auto *b = new BankAccount();
		strcpy_s(b->address, adresses[rand() % 10].c_str());
		strcpy_s(b->name, names[rand() % 10].c_str());
		strcpy_s(b->accountNumber, to_string(i).c_str());
		binFile.write((char *)b, sizeof(BankAccount));
	}

	binFile.close();
}
