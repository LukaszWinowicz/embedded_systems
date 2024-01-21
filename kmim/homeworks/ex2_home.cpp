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
using namespace std;

void message(int threadNum){
    
    // Inicjalizacja generatora liczb losowych
    srand(time(nullptr) + threadNum);

    // Losowanie liczby i wypisanie wiadomości
    int randomValue = rand() % 101;

    cout << "Wątek " << threadNum << " wylosował wartość: " << randomValue << endl;

}

int main(){
    
    thread thr1(message, 1); // Przekazanie funkcji i argumentu do wątku
    thread thr2(message, 2);
    thread thr3(message, 3);

    thr1.join();
    thr2.join();
    thr3.join();
    
    return 0;
}