/*
Stwórz klasę "wektor, która będzie posiadać pole int* table.
W konstruktorze tabela powinna być zaalakowana z rozmiarem 10 elementów.
W destruktorze tablica powinna być zwolniona.
Stwrz metodę push_back(int val), która umieszcza elementy na pierwszym wolnym miejscu w tabeli.
Jeżeli dodamy element na ostatnim miejscu tabeli, powinna ona zostać rozszerzona o następne 10 elementów.
*/

#include <iostream>
using namespace std;

class myVector{
    public:
    int* tab;

    // Konstruktor:
    myVector(){
        new int[10];

    }

    // Destruktor:
    ~myVector(){
        delete tab;
    }

};

int main(){
    myVector vect;
    
}