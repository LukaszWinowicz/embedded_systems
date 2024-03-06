/*
    Napisz program, który tworzy kilka wątków (co najmniej 2). 
    Każdy wątek zapisuje do tablicy wylosowaną liczbę całkowitą i dodaje ją
    do tablicy o ile nie istnieje. Wpisujemy do momentu wypełnienia całej tablicy.
    Zakres liczby losowej 0..2n
    Liczba elementów tablicy - n
*/

#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <random>

using namespace std;

mutex mtx; // Mutex do synchronizacji dostępu do wektora
vector<int> numbers;

void addNumberToVector(int maxNumbers) {
    // Utworzenie lokalnego generatora liczb losowych
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(1, 100);

    {
        lock_guard<mutex> lock(mtx); // Zabezpieczenie sekcji krytycznej
        if (numbers.size() < static_cast<size_t>(maxNumbers)) {
            int number = distrib(gen);
            numbers.push_back(number);
            cout << "Watek " << this_thread::get_id() << " dodal liczbe: " << number << endl;
        }
    }
}

int main() {
    int n;
    
    cout << "Podaj liczbe z przedzialu 2-10: ";
    while (true) {
        cin >> n;
        if (cin.fail() || n < 2 || n > 10) {
            cout << "Nieprawidlowa liczba. Sprobuj ponownie: ";
            cin.clear(); // Czyszczenie flag błędu strumienia
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignorowanie pozostałych znaków w strumieniu
        } else {
            break; // Wartość jest prawidłowa
        }
    }

    vector<thread> threads;

    // Uruchomienie wątków
    for (int i = 0; i < n; ++i) {
        threads.emplace_back(addNumberToVector, n);
    }

    // Oczekiwanie na zakończenie wątków
    for (auto& thread : threads) {
        thread.join();
    }

    // Wyświetlenie zawartości wektora
    cout << "Wylosowane liczby: ";
    for (int num : numbers) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}