// prack7.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#include <chrono>

using namespace std;


bool isAscending(vector<int> array) {
    auto begin = std::chrono::steady_clock::now();
    for (int i = 1; i < array.size(); i++) {
        if (array[i] <= array[i - 1])
            return false;
    }
    return true;
}

void bruteforce(int size) {
    //vector<int> answer;
    //vector<int> 
    auto begin = std::chrono::steady_clock::now();

    for (int i = 0; i < pow(2, size) * size; i++) {}
    auto end = std::chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    std::cout << "The time: " << elapsed_ms.count() << " ms\n";
}

vector<int> findAscending(int* array, int size) {
    int *dynamic = new int[size];
    int *prev = new int[size];

    auto begin = std::chrono::steady_clock::now();
    // Заполнение массивов
    dynamic[0] = 1;
    prev[0] = -1;
    for (int i = 1; i < size; i++) {
        int maxx = 0;
        prev[i] = -1;
        for (int j = 0; j < i; j++) {
            if (array[j] < array[i] && dynamic[j] > maxx) {
                maxx = dynamic[j];
                prev[i] = j;
            }
        }     
        dynamic[i] = 1 + maxx;
    }

    // Нахождение максимальной длины подпоследовательности
    int maxx = 0;
    for (int i = 0; i < size; i++) {
        if (dynamic[maxx] < dynamic[i])
            maxx = i;
    }
    // Восстановление ответа
    vector<int> answer;
    int x = prev[maxx];
    answer.push_back(array[maxx]);
    while (x != -1) {     
        answer.push_back(array[x]);
        x = prev[x];     
        
    }
    auto end = std::chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    std::cout << "The time: " << elapsed_ms.count() << " ms\n";

    reverse(answer.begin(), answer.end());

    return answer;
}

void random(int* array, int size) {
    for (int i = 0; i < size; i++) {
        array[i] = rand() % 1000;
    }
}

int main()
{
    //int size = 100000;
   // int* array = new int[size];
   // random(array, size);
    //findAscending(array, size);
    bruteforce(20);
}
