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
using namespace std;

int main(){

    // Tablica w stylu C
    int cStyleArray[] = {1, 2, 3};
    int arraySize = sizeof(cStyleArray) / sizeof(cStyleArray[0]);

    cout << cStyleArray << endl;
    cout << arraySize << endl;
}