// Write a program to get a number and display it in dec oct hex val.
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
    cout << "Enter a number: ";
    cin >> number;

    cout << "Decimal: " << number << endl;
    cout << "Octal: " << oct << number << endl;
    cout << "Hexadecimal: " << hex << number << endl;
    decToBin(number);
}