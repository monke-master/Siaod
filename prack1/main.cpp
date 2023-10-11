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
    cout << "������� 1\n";
    int x1 = 0x1482286;

    cout << "���������� �� ���������� ����� �����\n";
    coutp(x1);


    int n = sizeof(int)*8;
    int m = (n + (n % 2)) / 2;
    int mask = (pow(4, m) - 1) / 3;
    x1 = x1 | mask;
    cout << "���������� �����:" << endl;
    coutp(x1);
}

void task2() {
    cout << "������� 2\n";
    int x1;
    cout << "������� �����:" << endl;
    cin >> x1;
    cout << "���������� �� ���������� ����� �����\n";
    coutp(x1);
    int mask = 0x17D7;
    x1 = mask & x1;
    cout << "��������� ���������� �����:\n";
    coutp(x1);
}

void task3() {
    cout << "������� 3\n";
    int multiplier = 8;
    int x3;
    cout << "������� ���������: \n";
    cin >> x3;
    int result3 = (x3 << 3);
    cout << "���������� �����: " << result3 << endl;
}

void task4() {
    cout << "������� 4\n";
    int x4;
    cout << "������� �������: \n";
    cin >> x4;
    int result = (x4 >> 4);
    cout << "���������� �����: " << result << endl;
}

void task5() {
    cout << "������� ����� ��� ������ �������: ";
    int x5;
    cin >> x5;
    int n;
    cout << endl << "������� n: ";
    cin >> n;

    cout << "����� �� ���������� �����: \n";
    coutp(x5);
    int mask = 0x1;
    cout << "���������� �����: \n";
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
