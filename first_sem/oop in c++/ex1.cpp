// Write a program to get a number and display it in dec oct hex val.
// Ex: Decimal - 15 | Octal - 17 | Hexadecimal - F | Bindary - 1111
#include <iostream>
#include <iomanip>

using namespace std;

void decToBin(int number){

    int i = 0;
    int binaryNum[32]; 
    while (number > 0)
    {
        binaryNum[i] = number%2;
        number = number/2;        
        i++;
    }
    
    cout << "Binary: ";
    for (int j = i - 1; j >= 0; j--)
    {
        cout << binaryNum[j];
    }
    cout << endl;
    
}

int main(){

    int number;
    cout << "Enter a number (decimal): ";
    cin >> number;

    cout << "Decimal: " << number << endl;

    // Wykorzystanie biblioteki standardowej C++ do zmiany format na ósemkowy
    cout << "Octal: " << oct << number << endl;

    // Wykorzystanie biblioteki standardowej C++ do zmiany format na szesnastkowy
    cout << "Hexadecimal: " << hex << number << endl;

    // Funkcja przeliczająca na wartość binarną
    decToBin(number);
}