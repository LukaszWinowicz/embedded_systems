/*
std::map

- podobnie jak std::set, posortowany wzlgędem wartości jednak podzielny na klucz i wartość
- operator [] napdoisuje element o określonym kluczu lub tworzy nowy
- metoda insert() ...

*/ 
#include <map>
#include <vector>
#include <list>
#include <string>
#include <iostream>

using namespace std;

void paintC(map<int, string> mapa){
    for (auto it : mapa)
    {
        std::cout << it.first << std::endl;
    }
}

int main(){
    map<int, string> mapa;

    mapa[0] = "kowalski";
    mapa[2] = "nowak";
    mapa[3] = "maliniak";

    paintC(mapa);
}
