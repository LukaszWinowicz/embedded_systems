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
#include <cstring> // Dla funkcji memset
#include <typeinfo> // Dla RTTI (typeid)

using namespace std;
const int DATA_SIZE = 100;

// Klasa BaseData
class BaseData{
protected:
    int data[DATA_SIZE];
    int currentPointer;

public:
    BaseData() : currentPointer(0) {
        memset(data, 0, sizeof(data));
    }

    virtual void putDate(int dataValue){
        if(currentPointer < DATA_SIZE){
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
};

// Klasa CircData
class CircData : public BaseData {
public:
    void putData(int dataIn) override {
        data[currentPointer] = dataIn;
        currentPointer = (currentPointer + 1) % DATA_SIZE;
    }

    void printDataType() override {
        cout << "Circular data" << endl;
    }
};

// Klasa CircData2
class CircData2 : public CircData {
public:
    int* getData(int &ptr) override {
        ptr = DATA_SIZE;
        return BaseData::data;
    }

    int getCurrentPointer() override {
        return DATA_SIZE;
    }
};

// Klasa OneData
class OneData : public BaseData {
public:
    void printDataType() override {
        cout << "One time data" << endl;
    }

    void flushBuffer() {
        memset(data, 0, sizeof(data));
        currentPointer = 0;
    }
};

// Funkcja printData
void printData(BaseData *ptr) {
    int pointer;
    int* dataArray = ptr->getData(pointer);

    cout << "Data: ";
    for (int i = 0; i < pointer; i++) {
        cout << dataArray[i] << " ";
    }
    cout << endl;

    ptr->printDataType();

    // Sprawdzenie, czy przekazany wskaźnik jest typu OneData i wykonanie flushBuffer()
    OneData* oneDataPtr = dynamic_cast<OneData*>(ptr);
    if (oneDataPtr) {
        oneDataPtr->flushBuffer();
    }
}