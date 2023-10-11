
#include "BinModule.h"

// Выбор режима открытия файла
const string OPEN = "o";
const string CREATE = "c";
const string CREATE_FROM_TEXT = "cft";

const string END = "e";

// Работа с файлом
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
        cout << "Ошибка открытия файла" << endl;
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
            cout << "Ошибка открытия файла" << endl;
        if (!binFile.good() && !binFile.eof())
            cout << "Ошибка при записи в файл" << endl;
        if (!textFile.good() && !textFile.eof())
            cout << "Ошибка при чтении файла" << endl;
        textFile.close();
        binFile.close();
        return true;
    } else {
        cout << "Ошибка открытия файла" << endl;
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
            cout << "При чтении файла произошла ошибка";
            return;
        }
        binFile.read((char *) &d, sizeof(discipline));
        cout << d.title << " " << d.code << " " << d.directionCode << " " << d.semester << endl;
        binFile.close();
    } else
        cout << "Ошибка открытия файла" << endl;
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
            cout << "При чтении файла произошла ошибка";
        if (found)
            cout << "Запись удалена\n";
        else
            cout << "Запись не найдена\n";
        binFile.close();


    } else
        cout << "Ошибка открытия файла" << endl;
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
                cout << "Ошибка при записи в файл" << endl;
            }
            if (!textFile.good() && !textFile.eof()) {
                error = true;
                cout << "Ошибка при чтении файла" << endl;
            }

            if (!error)
                cout << "Файл сохранен\n";
            textFile.close();
            binFile.close();
        } else
            cout << "Ошибка открытия файла" << endl;
    } else
        cout << "Ошибка открытия файла" << endl;
}

void BinModule::replaceTitle(string fileName, string title, int sem, string direction, string newTitle) {
    fstream file;
    file.open(fileName, ios::binary | ios::in | ios::out);

    if (!file.is_open()) {
        cout << "Ошибка открытия файла" << endl;
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
        cout << "Ошибка при чтении файла" << endl;
    }

    if (!found)
        cout << "Запись не найдена";
    else
        cout << "Название дисциплины изменено\n";

    file.close();
}

void BinModule::getByDirectionAndSem(string fileName, string direction, int semester) {
    ifstream file;
    file.open(fileName, ios::binary);

    if (!file.is_open()) {
        cout << "Ошибка открытия файла" << endl;
        return;
    }

    auto d = discipline();
    while (file.read((char *) &d, sizeof (discipline))) {
        if (d.semester == semester && d.directionCode == direction) {
            cout << d.title << " " << d.code << " " << d.directionCode << " " << d.semester << endl;
        }
    }

    if (!file.good() && !file.eof()) {
        cout << "Ошибка при чтении файла" << endl;
    }
    file.close();
}

void BinModule::workWithFile(string fileName) {
    cout << "работа с файлом " << fileName << endl;
    cout << "Доступные операции над файлом:\n";
    cout << END << " - Завершить работу" <<  endl;
    cout << READ << " - Вывести содержимое файла" <<  endl;
    cout << SAVE_TO_TEXT << " {абсолютный путь к файлу на след. строке} - Сохранить в текстовыый файл" << endl;
    cout << GET_BY_INDEX << " {индекс записи} - Вывести запись по указанному индексу" << endl;
    cout << DELETE_BY_KEY << " {код дисциплины} - Удалить дисцпилину с указанным кодом" << endl;
    cout << REPLACE_TITLE << " {название дисциплины, код направления, семестр, новое название} - "
                             "Заменить название дисциплины" << endl;
    cout << GET_BY_DIRECT_AND_SEM << " {код направления} {номер семестра} - Список дисциплин, читаемых"
                                     "заданному направлению в заданном семестре\n";


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
            cout << "Работа с файлом " << fileName << " закончена\n";
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
            cout << "Неизвестная команда\n";
    }
}

int BinModule::startWork() {
    cout << "Доступные операции над файлом:\n";
    cout << OPEN << " {абсолютный путь к файлу на след. строке} - Открыть существующий файл" << endl;
    cout << CREATE_FROM_TEXT << " {абсолютный путь к старому файлу на след. строке} "
                           "{абсолютный путь к новому файлу на след. строке}\n - Создать бинарный файл из текстового" << endl;
    cout << END << " - Завершить работу" <<  endl;

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
            cout << "Неизвестная команда\n";
    }
}