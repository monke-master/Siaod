//
// Created by monke on 26.09.2023.
//

#include "FileModule.h"


// Выбор режима открытия файла
const string OPEN = "o";
const string CREATE = "c";
const string CREATE_FROM = "cf";

const string END = "e";

// Работа с файлом
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
            cout << "Ошибка при чтении файла" << endl;
    } else
        cout << "Ошибка открытия файла" << endl;
}

void FileModule::writeToFile(string fileName, string newLine) {
    ofstream file;
    file.open(fileName, ios::app);
    if (file.is_open()) {
        file << newLine << endl;
        if (!file.good() && !file.eof())
            cout << "Ошибка при записи в файл" << endl;
        file.close();
    } else
        cout << "Ошибка открытия файла" << endl;

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
            cout << "Ошибка при чтении файла" << endl;
        cout << k << endl;
    } else
        cout << "Ошибка открытия файла" << endl;
}

void FileModule::getNumberByIndex(string fileName, int index) {
    ifstream file;
    file.open(fileName);
    if (file.is_open()) {
        string x;
        for (int i = 1; i <= index && file.good(); i++) {
            if (!(file >> x)) {
                cout << "В файле меньше " << index << " элементов\n";
                return;
            }
        }
        if (!file.good() && !file.eof())
            cout << "Ошибка при чтении файла" << endl;
        cout << x << endl;
    } else
        cout << "Ошибка открытия файла" << endl;
}

void FileModule::workWithFile(string fileName) {
    cout << "работа с файлом " << fileName << endl;
    cout << "Доступные операции над файлом:\n";
    cout << END << " - Завершить работу" <<  endl;
    cout << READ << " - Вывести содержимое файла" <<  endl;
    cout << WRITE << " {числа со следующей строки} - Записать числа в конец файла" << endl;
    cout << READ_NUMBER << " {номер числа} - Вывести число с указанным порядковым номером" <<  endl;
    cout << NUMBER << " - Вывести количество чисел в файле" << endl;
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
            cout << "Работа с файлом " << fileName << " закончена\n";
            return;
        }
        else
            cout << "Неизвестная команда\n";
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
            cout << "Ошибка при записи в файл" << endl;
        return true;
    } else {
        cout << "Ошибка создания файла" << endl;
        return false;
    }
}

bool FileModule::createFileFromExisting(string oldFileName, string newFileName) {
    ifstream oldFile(oldFileName);
    if (oldFile.is_open()) {
        ofstream newFile(newFileName);
        if (newFile.is_open()) {
            int n;
            cout << "Введите количество чисел на строке в новом файле: \n";
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
                cout << "Ошибка при записи в файл" << endl;
            if (!oldFile.good() && !oldFile.eof())
                cout << "Ошибка при чтении файла" << endl;
        } else {
            cout << "Ошибка создания файла" << endl;
            return false;
        }
    } else {
        cout << "Ошибка открытия файла" << endl;
        return false;
    }
    return true;
}

int FileModule::startWork() {
    cout << "Доступные операции над файлом:\n";
    cout << OPEN << " {абсолютный путь к файлу на след. строке} - Открыть существующий файл" << endl;
    cout << CREATE << " {абсолютный путь к файлу на след. строке} - Создать новый файл" << endl;
    cout << CREATE_FROM << " {абсолютный путь к старому файлу на след. строке} "
                           "{абсолютный путь к новому файлу на след. строке}- Создать новый файл из существующего" << endl;
    cout << END << " - Завершить работу" <<  endl;

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
            cout << "Неизвестная команда\n";
    }
}