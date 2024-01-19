/*
Write a program to copy:

C style string as char*
std::string
into another one.

Excercise

Reverse a string:

char*
std::string
*/

#include <iostream>
#include <string>
#include <cstring>
using namespace std;

int reversedAsString(){
    string word = "Warszawa";
    string reversed = "";

    cout << word << endl;

    // Odwrócenie słowa ręcznie
    for (int i = word.length() - 1; i >= 0; --i)
    {
       reversed += word[i];
    }
    
    cout << reversed << endl;

    return 0;

}

int reverseAsChar(){
    char word[] = "Łódź";
    int length = strlen(word);
    char reversed[length + 1]; // tutaj uwzględniam pusty znak po ostatniej literze
    cout << word << endl;

    for (int i = 0; i < length; i++)
    {
        reversed[i] = word[length - 1 - i];
    }
    reversed[length] = '\0'; // Dodanie znaku null na koniec

    cout << reversed << endl;

    return 0;
}


int main(){
    reverseAsChar();
    return 0;
}