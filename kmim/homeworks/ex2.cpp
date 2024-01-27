/*
    Napisz program, który tworzy kilka wątków (co najmniej 2). Każdy
    wątek zapisuje do tablicy wylosowaną liczbę całkowitą i dodaje ją
    do tablicy o ile nie istnieje. Wpisujemy do momentu wypełnienia
    całej tablicy.
    Zakres liczby losowej 0..2n
    Liczba elementów tablicy - n
*/

#include <iostream>
#include <thread>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <mutex>
#include <algorithm>
 
using namespace std;
mutex numbers_mutex;
vector<int> numbers;
int randomValue; // Współdzielona zmienna
string n;

void draw(int threadNum){
    
    // Inicjalizacja generatora liczb losowych
    srand(time(nullptr) + threadNum);

    // Losowanie liczby i wypisanie wiadomości   
    while (true)
    {
        lock_guard<mutex> guard(numbers_mutex); // Zapewnienie bezpieczeństwa wątków, blokada mutexu
        randomValue = (rand() % (2 * stoi(n))) + 1;     
        
        if (find(numbers.begin(), numbers.end(), randomValue) == numbers.end()) {
            // Liczba jest unikalna
            numbers.push_back(randomValue);
            break; // Wyjście z pętli
        }
    }    
}

bool isNumericInRange(const string& str) {
    if (str.empty()) {
        return false;
    }

    // Sprawdzenie, czy wszystkie znaki to cyfry
    for (char c : str) {
        if (!isdigit(c)) {
            return false;
        }
    }

    // Konwersja stringa na liczbę i sprawdzenie zakresu
    int value = stoi(str);
    return value >= 2 && value <= 10;
}

int main(){
    
    while (true)
    {
        cout << "Podaj liczbę całkowitą (Z przedziału 2 - 20).\n>> ";
        cin >> n;

        if (!isNumericInRange(n)) 
        {
            cout << "Nieprawidłowe dane. Proszę podać liczbę całkowitą z zakresu 2-20." << endl;
            cout << "----------------------------------------------------------------" << endl;
        } 
        else 
        {
            break; // Wyjście z pętli, jeśli dane są prawidłowe
        }
    }

    cout << "Zakres losowania od 1 do " << (2* stoi(n)) << endl;

    // wektor wątków
    vector<thread> threads;

    // wypełnienie wektora wątkami
    for (int i = 0; i < stoi(n); ++i)
    {
        threads.push_back(thread(draw, i));
    }
    
    for (int i = 0; i < stoi(n); ++i)
    {
        threads[i].join();
    }
    
    for (int i = 0; i < numbers.size(); i++)
    {
        cout << "{" << i + 1 << "} " << numbers[i] << endl;
    }
    cout << endl;

    return 0;
}