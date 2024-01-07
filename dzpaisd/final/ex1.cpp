/*Zaimplementuj funkcję alokującą i wyświetlajacą tablice trójkątną
o podanym przez użytkownika wymiarze X:
    X=3
    1
    1 2
    1 2 3
*/

#include <iostream>
#include <limits>
using namespace std;

void TriangularArray(int x){
    int ** triangleArray = new int * [x];
    for(int i = 0; i< x; ++i){
        triangleArray[i]=new int [i+1];
        for(int j=0; j<i+1; ++j){
            triangleArray[i][j]=j+1;
            cout << triangleArray[i][j] << " ";
        }   
        cout<<endl;     
    }
    
    // Zwolnienie pamięci
    for (int i = 0; i < x; ++i) {
        delete[] triangleArray[i];
    }
    delete[] triangleArray;
}

bool isValidInput() {
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (cin.gcount() > 1) return false; 
    return true;
}

int main (void){

    int x;

    while (true)
    {
        cout << "Podaj wymiar X tablicy trójkątnej (max do 10): ";
        cin >> x;

        if (!isValidInput() || x <= 0 || x > 10) 
        {
            cout << "Nieprawidłowe dane. Proszę podać liczbę całkowitą z zakresu 1-10." << endl;
            cout << "----------------------------------------------------------------" << endl;
        } 
        else 
        {
            break; // Wyjście z pętli, jeśli dane są prawidłowe
        }
    }

    TriangularArray(x);

    return 0;
}