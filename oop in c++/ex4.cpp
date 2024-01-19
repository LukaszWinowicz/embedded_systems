/*
Write a program to concatenate two tables

C style table
vector<>
Excercise

Reverse a table:

[]
std::vector<>
*/
#include <iostream>
#include <vector>
#include <algorithm>  // dla reverse
using namespace std;

int main(){

    // Tablica w stylu C
    int cStyleArray[] = {1, 2, 3};
    int arraySize = sizeof(cStyleArray) / sizeof(cStyleArray[0]);

    // Vector (kontener - dynamiczna tablica)
    vector<int> Array = {4, 5, 6};

    // Nowa tablica łącząca cStyleArray + Array
    vector<int> newArray;
    newArray.reserve(arraySize + Array.size());

    // Dodanie elementów z tablicy w stylu C
    for (int i = 0; i < arraySize; ++i) {
        newArray.push_back(cStyleArray[i]);
    }

    // Dodaj elementy z vector
    newArray.insert(newArray.end(), Array.begin(), Array.end());

    // Odwrócenie kolejności elementów
    reverse(newArray.begin(), newArray.end());

    // Wyświetl wynik
    for (int val : newArray) {
        cout << val << " ";
    }

    cout << endl;

    return 0;

}