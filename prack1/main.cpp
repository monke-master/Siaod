#include <iostream>
#include "math.h"

using namespace std;

void coutp(unsigned int x) {
    int n = sizeof(int)*8;
    unsigned mask = (1 << (n - 1));
    for(int i = 1; i <= n; i++) {
        cout << ((x & mask) >> (n - i));
        mask = mask >> 1;
    }
    cout << endl;
}

void task1() {
    cout << "Задание 1\n";
    int x1 = 0x1482286;

    cout << "Переменная до применения маски равна\n";
    coutp(x1);


    int n = sizeof(int)*8;
    int m = (n + (n % 2)) / 2;
    int mask = (pow(4, m) - 1) / 3;
    x1 = x1 | mask;
    cout << "Применение маски:" << endl;
    coutp(x1);
}

void task2() {
    cout << "Задание 2\n";
    int x1;
    cout << "Введите число:" << endl;
    cin >> x1;
    cout << "Переменная до применения маски равна\n";
    coutp(x1);
    int mask = 0x17D7;
    x1 = mask & x1;
    cout << "Результат применения маски:\n";
    coutp(x1);
}

void task3() {
    cout << "Задание 3\n";
    int multiplier = 8;
    int x3;
    cout << "Введите множитель: \n";
    cin >> x3;
    int result3 = (x3 << 3);
    cout << "Применение маски: " << result3 << endl;
}

void task4() {
    cout << "Задание 4\n";
    int x4;
    cout << "Введите делимое: \n";
    cin >> x4;
    int result = (x4 >> 4);
    cout << "Применение маски: " << result << endl;
}

void task5() {
    cout << "Введите число для пятого задания: ";
    int x5;
    cin >> x5;
    int n;
    cout << endl << "Введите n: ";
    cin >> n;

    cout << "Число до применения маски: \n";
    coutp(x5);
    int mask = 0x1;
    cout << "Применение маски: \n";
    coutp(x5 & (~(mask << n)));
}



int main() {

    setlocale(LC_ALL, "Russian");
    task1();
    //task2();
    //task3();
    //task4();
    //task5();
    return 0;
}
