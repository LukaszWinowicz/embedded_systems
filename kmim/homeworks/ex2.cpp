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
 
using namespace std;
mutex numbers_mutex;
vector<int> numbers;
int randomValue; // Współdzielona zmienna
int n;

void draw(int threadNum){
    
    // Inicjalizacja generatora liczb losowych
    srand(time(nullptr) + threadNum);

    // Losowanie liczby i wypisanie wiadomości   
    while (true)
    {
        lock_guard<mutex> guard(numbers_mutex); // Zapewnienie bezpieczeństwa wątków, blokada mutexu
        randomValue = (rand() % (2 * n)) + 1;     
        
        if (find(numbers.begin(), numbers.end(), randomValue) == numbers.end()) {
            // Liczba jest unikalna
            numbers.push_back(randomValue);
            break; // Wyjście z pętli
        }
    }    
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

int main(){
    
    while (true)
    {
        cout << "Podaj liczbę całkowitą (Z przedziału 2 - 20).\n>> ";
        cin >> n;

        if (!isValidInput() || n < 2 || n > 20) 
        {
            cout << "Nieprawidłowe dane. Proszę podać liczbę całkowitą z zakresu 2-20." << endl;
            cout << "----------------------------------------------------------------" << endl;
        } 
        else 
        {
            break; // Wyjście z pętli, jeśli dane są prawidłowe
        }
    }

    cout << "Zakres losowania od 1 do " << (2*n) << endl;

    // wektor wątków
    vector<thread> threads;

    // wypełnienie wektora wątkami
    for (int i = 0; i < n; ++i)
    {
        threads.push_back(thread(draw, i));
    }
    
    // oczekiwanie na zakończenie każdego z wątków
    // [ ! ]
    for (auto& th : threads)
    {
        th.join();
    }

    for (int i = 0; i < numbers.size(); i++)
    {
        cout << "{" << i + 1 << "} " << numbers[i] << endl;
    }
    cout << endl;

    return 0;
}