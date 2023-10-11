
#include "BinModule.h"

// ����� ������ �������� �����
const string OPEN = "o";
const string CREATE = "c";
const string CREATE_FROM_TEXT = "cft";

const string END = "e";

// ������ � ������
const string READ = "r";
const string GET_BY_INDEX = "gbi";
const string SAVE_TO_TEXT = "stt";
const string DELETE_BY_KEY = "dbk";
const string GET_BY_DIRECT_AND_SEM = "gbds";
const string REPLACE_TITLE = "rt";

struct discipline {
public:
    char code[100];
    char directionCode[100];
    char title[100];
    int semester;
};

void BinModule::read(std::string fileName) {
    ifstream file;
    file.open(fileName, ios::binary);

    if (file.is_open()) {
        auto *d = new discipline();
        while (file.read((char *) d, sizeof (discipline))) {
            cout << d->title << " " << d->code << " " << d->directionCode << " " << d->semester << endl;
        }
    } else
        cout << "������ �������� �����" << endl;
}

bool BinModule::fromTextFile(string textFileName, string binFileName) {
    ifstream textFile;
    textFile.open(textFileName);
    if (textFile.is_open()) {
        ofstream binFile;
        binFile.open(binFileName, ios::binary | ios::trunc);
        if (binFile.is_open()) {
            while (!textFile.eof()) {
                string disciplineTitle, code, directionCode;
                int semester;
                textFile >> disciplineTitle >> code >> directionCode >> semester;
                auto *d = new discipline();
                if (!disciplineTitle.empty()) {
                    strcpy(d->title, disciplineTitle.c_str());
                    strcpy(d->code, code.c_str());
                    strcpy(d->directionCode, directionCode.c_str());
                    d->semester = semester;

                    binFile.write((char *) d, sizeof(discipline));
                }
            }
        } else
            cout << "������ �������� �����" << endl;
        if (!binFile.good() && !binFile.eof())
            cout << "������ ��� ������ � ����" << endl;
        if (!textFile.good() && !textFile.eof())
            cout << "������ ��� ������ �����" << endl;
        textFile.close();
        binFile.close();
        return true;
    } else {
        cout << "������ �������� �����" << endl;
        return false;
    }
}

void BinModule::getDisciplineByIndex(string fileName, int index) {
    ifstream binFile;
    binFile.open(fileName, ios::binary);

    if (binFile.is_open()) {
        binFile.seekg((index - 1)*sizeof(discipline));
        discipline d;
        if (!binFile.good()) {
            cout << "��� ������ ����� ��������� ������";
            return;
        }
        binFile.read((char *) &d, sizeof(discipline));
        cout << d.title << " " << d.code << " " << d.directionCode << " " << d.semester << endl;
        binFile.close();
    } else
        cout << "������ �������� �����" << endl;
}

void BinModule::deleteByIndex(string fileName, string key) {
    fstream binFile;
    binFile.open(fileName, ios::binary | ios::in | ios::out);

    if (binFile.is_open()) {
        binFile.seekg(-sizeof(discipline), ios::end);
        discipline lastD;
        binFile.read((char *) &lastD, sizeof(discipline));

        binFile.seekg(0, ios::beg);
        discipline d;
        bool found = false;
        while (binFile.read((char *) &d, sizeof(discipline))) {
            if (d.code == key) {
                binFile.seekp(-sizeof (discipline), ios::cur);
                binFile.write((char *)&lastD, sizeof (discipline));
                found = true;
            }
        }
        if (!binFile.good() && !binFile.eof())
            cout << "��� ������ ����� ��������� ������";
        if (found)
            cout << "������ �������\n";
        else
            cout << "������ �� �������\n";
        binFile.close();


    } else
        cout << "������ �������� �����" << endl;
}

void BinModule::saveToText(string textFileName, string binFileName) {
    ifstream binFile;
    binFile.open(binFileName, ios::binary);

    if (binFile.is_open()) {
        ofstream textFile;
        textFile.open(textFileName);

        if (textFile.is_open()) {
            auto *d = new discipline();
            while (binFile.read((char *) d, sizeof (discipline))) {
                textFile << d->title << "\n" << d->code << "\n" << d->directionCode << "\n" << d->semester << endl;
            }

            bool error = false;
            if (!binFile.good() && !binFile.eof()) {
                error = true;
                cout << "������ ��� ������ � ����" << endl;
            }
            if (!textFile.good() && !textFile.eof()) {
                error = true;
                cout << "������ ��� ������ �����" << endl;
            }

            if (!error)
                cout << "���� ��������\n";
            textFile.close();
            binFile.close();
        } else
            cout << "������ �������� �����" << endl;
    } else
        cout << "������ �������� �����" << endl;
}

void BinModule::replaceTitle(string fileName, string title, int sem, string direction, string newTitle) {
    fstream file;
    file.open(fileName, ios::binary | ios::in | ios::out);

    if (!file.is_open()) {
        cout << "������ �������� �����" << endl;
        return;
    }

    auto d = discipline();
    bool found = false;
    while (file.read((char *) &d, sizeof (discipline))) {
        if (d.title == title && d.directionCode == direction && d.semester == sem) {
            file.seekp(-sizeof (discipline), ios::cur);
            strcpy(d.title, newTitle.c_str());
            file.write((char *)&d, sizeof (discipline));
            found = true;
        }
    }

    if (!file.good() && !file.eof()) {
        cout << "������ ��� ������ �����" << endl;
    }

    if (!found)
        cout << "������ �� �������";
    else
        cout << "�������� ���������� ��������\n";

    file.close();
}

void BinModule::getByDirectionAndSem(string fileName, string direction, int semester) {
    ifstream file;
    file.open(fileName, ios::binary);

    if (!file.is_open()) {
        cout << "������ �������� �����" << endl;
        return;
    }

    auto d = discipline();
    while (file.read((char *) &d, sizeof (discipline))) {
        if (d.semester == semester && d.directionCode == direction) {
            cout << d.title << " " << d.code << " " << d.directionCode << " " << d.semester << endl;
        }
    }

    if (!file.good() && !file.eof()) {
        cout << "������ ��� ������ �����" << endl;
    }
    file.close();
}

void BinModule::workWithFile(string fileName) {
    cout << "������ � ������ " << fileName << endl;
    cout << "��������� �������� ��� ������:\n";
    cout << END << " - ��������� ������" <<  endl;
    cout << READ << " - ������� ���������� �����" <<  endl;
    cout << SAVE_TO_TEXT << " {���������� ���� � ����� �� ����. ������} - ��������� � ���������� ����" << endl;
    cout << GET_BY_INDEX << " {������ ������} - ������� ������ �� ���������� �������" << endl;
    cout << DELETE_BY_KEY << " {��� ����������} - ������� ���������� � ��������� �����" << endl;
    cout << REPLACE_TITLE << " {�������� ����������, ��� �����������, �������, ����� ��������} - "
                             "�������� �������� ����������" << endl;
    cout << GET_BY_DIRECT_AND_SEM << " {��� �����������} {����� ��������} - ������ ���������, ��������"
                                     "��������� ����������� � �������� ��������\n";


    string command;

    while (command != END) {
        cin >> command;
        if (command == READ) {
            read(fileName);
        } else if (command == SAVE_TO_TEXT) {
            cin.ignore();
            string textFileName;
            getline(cin, textFileName);
            saveToText(textFileName, fileName);
        } else if (command == GET_BY_INDEX) {
            int index;
            cin >> index;
            getDisciplineByIndex(fileName, index);
        } else if (command == END) {
            cout << "������ � ������ " << fileName << " ���������\n";
            return;
        } else if (command == DELETE_BY_KEY) {
            string key;
            cin >> key;
            deleteByIndex(fileName, key);
        } else if (command == REPLACE_TITLE) {
            string title, newTitle, dirCode;
            int sem;
            cin >> title >> dirCode >> sem >> newTitle;
            replaceTitle(fileName, title, sem, dirCode, newTitle);
        } else if (command == GET_BY_DIRECT_AND_SEM) {
            string dirCode;
            int sem;
            cin >> dirCode >> sem;
            getByDirectionAndSem(fileName, dirCode, sem);
        }
        else
            cout << "����������� �������\n";
    }
}

int BinModule::startWork() {
    cout << "��������� �������� ��� ������:\n";
    cout << OPEN << " {���������� ���� � ����� �� ����. ������} - ������� ������������ ����" << endl;
    cout << CREATE_FROM_TEXT << " {���������� ���� � ������� ����� �� ����. ������} "
                           "{���������� ���� � ������ ����� �� ����. ������}\n - ������� �������� ���� �� ����������" << endl;
    cout << END << " - ��������� ������" <<  endl;

    string fileName;
    string command;
    while (true) {
        cin >> command;
        if (command == OPEN) {
            cin.ignore();
            getline(cin, fileName);
            workWithFile(fileName);
        } else if (command == CREATE_FROM_TEXT) {
            string oldFileName;
            string newFileName;
            cin.ignore();
            getline(cin, oldFileName);
            getline(cin, newFileName);
            if (fromTextFile(oldFileName, newFileName))
                workWithFile(newFileName);
        }  else if (command == END) {
            return 0;
        } else
            cout << "����������� �������\n";
    }
}