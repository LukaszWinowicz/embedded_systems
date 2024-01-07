/*
 1) Stwórz klasę BaseData zawierającą: 
 • pole int data[100] 
 • pole int currentPointer - które zawiera aktualną pozycję w data[] 
 • w konstruktorze pola powinny być zerowane
 • metodę virtualną void putData(int data) - zapisującą jedną liczbę do data[] i inkrementującą currentPointer. 
   Jeśli wielkość tablicy zostanie przekroczona, funkcja nie ma efektu. 
 • metodę wirtualną int getCurrentPointer(), która zwraca currentPointer
 • metodę int* getData(int &ptr) która zwraca wskaźnik na data[] oraz currentPointer przez referencję
 • metodę czysto wirtualną void printDataType()
2) Stwórz klasę CircData dziedziczącą po BaseData: 
 • przysłonięta metoda bool putData(int dataIn) po osiągnięciu ostatniej pozycji, powinna zapisywać tablicę od początku
 • przysłonięta metoda printDataType() powinna wyświetlać " Circular data"
3) Stwórz klasę CircData2 dziedziczącą CircData
 • przysłonięta metoda int* getData(int &ptr) powinna działać tak jak BaseData z tą różnicą, że ptr będzie zawsze równe 100 • getCurrentPointer zawsze zwraca 100
4) Stwórz klasę oneData dziedziczącą po BaseData • przysłonięta metoda printDataType() powinna wyświetlać " one time data"
 • metodę void flushBuffer() która zeruje tablicę i ustawia currentPointer = 0
5) Stwórz funkcję void printData(BaseData *ptr) - która powinna wyświetlać pole data[] do aktualnego zapisu. Dodatkowo 
   jeśli przekazanym typem jest oneData po wyświetleniu powinna zostać wykonana metoda flushBuffer()
6) W funkcji main() stwórz zmienną BaseData *dataptr = nullptr, po kolei dla każdego typu: • Wykonaj dynamiczne lokowanie na określony typ • Kilkukrotnie wykonaj putData
 • przekaż do printData

*/

#include <iostream>

using namespace std;

class BaseData{
protected:
    int data[100];
    int currentPointer;

public:
    BaseData() : currentPointer(0){
        for (int i = 0; i < 100; i++)
        {
            data[i] = 0;
        }        
    };

    virtual void putDate(int dataValue){
        if(current_exception < 100){
            data[currentPointer] = dataValue;
            currentPointer++;
        }
    };

    virtual int getCurrentPointer(){
        return currentPointer;
    };

    virtual int* getData(int &ptr) {
        ptr = currentPointer;
        return data;
    };

    virtual void printDataType() = 0;
}