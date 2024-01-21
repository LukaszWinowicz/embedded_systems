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

vector<int> numbers;

void message(int threadNum){
    
    // Inicjalizacja generatora liczb losowych
    srand(time(nullptr) + threadNum);

    // Losowanie liczby i wypisanie wiadomości   
    bool isUnique = true;

    while (isUnique == false)
    {
        int randomValue = (rand() % 5) + 1; // zakres od 1 do 5

        for (int i = 0; i < numbers.size(); i++)
        {
            if(numbers[i] == randomValue)
            {
                isUnique = false;
            }
        }

        if (isUnique == true)
        {
            numbers.push_back(randomValue);
            cout << "Wątek " << threadNum << " wylosował wartość: " << randomValue << endl;
        }
        
    }
}

int main(){
    
    thread thr1(message, 1); // Przekazanie funkcji i argumentu do wątku
    thread thr2(message, 2);
    thread thr3(message, 3);

    thr1.join();
    thr2.join();
    thr3.join();
    
    for (int i = 0; i < numbers.size(); i++)
    {
        cout << numbers[i] << " | ";
    }
    cout << endl;
    

    return 0;
}