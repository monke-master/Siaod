//
// Created by monke on 26.09.2023.
//

#include "FileModule.h"


// ����� ������ �������� �����
const string OPEN = "o";
const string CREATE = "c";
const string CREATE_FROM = "cf";

const string END = "e";

// ������ � ������
const string READ = "r";
const string WRITE = "w";
const string READ_NUMBER = "rn";
const string NUMBER = "cn";



void FileModule::read(string fileName) {
    ifstream file;
    file.open(fileName);
    string line;
    if (file.is_open()) {
        while (getline(file, line)) {
            cout << line << std::endl;
        }
        if (!file.good() && !file.eof())
            cout << "������ ��� ������ �����" << endl;
    } else
        cout << "������ �������� �����" << endl;
}

void FileModule::writeToFile(string fileName, string newLine) {
    ofstream file;
    file.open(fileName, ios::app);
    if (file.is_open()) {
        file << newLine << endl;
        if (!file.good() && !file.eof())
            cout << "������ ��� ������ � ����" << endl;
        file.close();
    } else
        cout << "������ �������� �����" << endl;

}

void FileModule::getNumberOfLines(string fileName) {
    ifstream file;
    file.open(fileName);
    if (file.is_open()) {
        int x;
        int k = 0;
        while (file >> x && file.good()) {
            k++;
        }
        if (!file.good() && !file.eof())
            cout << "������ ��� ������ �����" << endl;
        cout << k << endl;
    } else
        cout << "������ �������� �����" << endl;
}

void FileModule::getNumberByIndex(string fileName, int index) {
    ifstream file;
    file.open(fileName);
    if (file.is_open()) {
        string x;
        for (int i = 1; i <= index && file.good(); i++) {
            if (!(file >> x)) {
                cout << "� ����� ������ " << index << " ���������\n";
                return;
            }
        }
        if (!file.good() && !file.eof())
            cout << "������ ��� ������ �����" << endl;
        cout << x << endl;
    } else
        cout << "������ �������� �����" << endl;
}

void FileModule::workWithFile(string fileName) {
    cout << "������ � ������ " << fileName << endl;
    cout << "��������� �������� ��� ������:\n";
    cout << END << " - ��������� ������" <<  endl;
    cout << READ << " - ������� ���������� �����" <<  endl;
    cout << WRITE << " {����� �� ��������� ������} - �������� ����� � ����� �����" << endl;
    cout << READ_NUMBER << " {����� �����} - ������� ����� � ��������� ���������� �������" <<  endl;
    cout << NUMBER << " - ������� ���������� ����� � �����" << endl;
    string command;

    while (command != END) {
        cin >> command;
        if (command == READ) {
            read(fileName);
        } else if (command == WRITE) {
            string line;
            cin.ignore();
            getline(cin, line);
            writeToFile(fileName, line);
        } else if (command == NUMBER) {
            getNumberOfLines(fileName);
        } else if (command == READ_NUMBER) {
            int index;
            cin >> index;
            getNumberByIndex(fileName, index);
        } else if (command == END) {
            cout << "������ � ������ " << fileName << " ���������\n";
            return;
        }
        else
            cout << "����������� �������\n";
    }
}

bool FileModule::createFile(string fileName) {
    ofstream file;
    file.open(fileName);

    if (file.is_open()) {
        for (int i = 1; i <= 20 && file.good(); i++) {
            file << i << " ";
            if (i % 4 == 0)
                file << endl;
        }
        if (!file.good() && !file.eof())
            cout << "������ ��� ������ � ����" << endl;
        return true;
    } else {
        cout << "������ �������� �����" << endl;
        return false;
    }
}

bool FileModule::createFileFromExisting(string oldFileName, string newFileName) {
    ifstream oldFile(oldFileName);
    if (oldFile.is_open()) {
        ofstream newFile(newFileName);
        if (newFile.is_open()) {
            int n;
            cout << "������� ���������� ����� �� ������ � ����� �����: \n";
            cin >> n;
            int i = 0;
            int x;
            while (oldFile >> x && oldFile.good() && newFile.good()) {
                i++;
                newFile << x;
                if (i % n == 0)
                    newFile << endl;
                else
                    newFile << " ";
            }
            if (!newFile.good() && !newFile.eof())
                cout << "������ ��� ������ � ����" << endl;
            if (!oldFile.good() && !oldFile.eof())
                cout << "������ ��� ������ �����" << endl;
        } else {
            cout << "������ �������� �����" << endl;
            return false;
        }
    } else {
        cout << "������ �������� �����" << endl;
        return false;
    }
    return true;
}

int FileModule::startWork() {
    cout << "��������� �������� ��� ������:\n";
    cout << OPEN << " {���������� ���� � ����� �� ����. ������} - ������� ������������ ����" << endl;
    cout << CREATE << " {���������� ���� � ����� �� ����. ������} - ������� ����� ����" << endl;
    cout << CREATE_FROM << " {���������� ���� � ������� ����� �� ����. ������} "
                           "{���������� ���� � ������ ����� �� ����. ������}- ������� ����� ���� �� �������������" << endl;
    cout << END << " - ��������� ������" <<  endl;

    string fileName;
    string command;
    while (true) {
        cin >> command;
        if (command == OPEN) {
            cin.ignore();
            getline(cin, fileName);
            workWithFile(fileName);
        } else if (command == CREATE) {
            cin.ignore();
            getline(cin, fileName);
            if (createFile(fileName))
                workWithFile(fileName);
        } else if (command == CREATE_FROM) {
            string oldFileName;
            string newFileName;
            cin.ignore();
            getline(cin, oldFileName);
            getline(cin, newFileName);
            if (createFileFromExisting(oldFileName, newFileName))
                workWithFile(newFileName);
        } else if (command == END) {
            return 0;
        } else
            cout << "����������� �������\n";
    }
}