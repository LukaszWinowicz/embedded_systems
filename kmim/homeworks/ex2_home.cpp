/*
Napisz program, który tworzy kilka wątków (co najmniej 2). Każdy
wątek zapisuje do tablicy wylosowaną liczbę całkowitą i dodaje ją
do tablicy o ile nie istnieje. Wpisujemy do momentu wypełnienia
całej tablicy.
Zakres liczby losowej 0..2n
Liczba elementów tablicy - n
*/

/*
1. tworzenie wątków
2. losowanie liczb w tych wątkach
3. dodanie możliwości wpisania liczby, która pozwoli nam okreslić liczbę wątków
4. walidacja wprowadzanej liczby
5. obsługa błędów
6. testy
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
int counter = 0;

void message(int threadNum){
    
    // Inicjalizacja generatora liczb losowych
    srand(time(nullptr) + threadNum);

    // Losowanie liczby i wypisanie wiadomości   

    while (true)
    {
        int randomValue = (rand() % 10) + 1; // zakres od 1 do 5
        cout << "Adres w pamięci(" << counter << "): " << &randomValue << "\n" << endl;
        counter++;
        lock_guard<mutex> guard(numbers_mutex); // Zapewnienie bezpieczeństwa wątków
        
        if (find(numbers.begin(), numbers.end(), randomValue) == numbers.end()) {
            // Liczba jest unikalna
            numbers.push_back(randomValue);
            cout << "Wątek " << threadNum << " wylosował wartość: " << randomValue << endl;
            break; // Wyjście z pętli
        }
    }    
}

int main(){
    
    int n = 10;

    // wektor wątków
    vector<thread> threads;

    // wypełnienie wektora wątkami
    for (int i = 0; i < n; ++i)
    {
        threads.push_back(thread(message, i));
    }
    
    // oczekiwanie na zakończenie każdego z wątków
    for (auto& th : threads)
    {
        th.join();
    }
        
    for (int i = 0; i < numbers.size(); i++)
    {
        cout << numbers[i] << " | ";
    }
    cout << endl;

    return 0;
}