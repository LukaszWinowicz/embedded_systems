#include <iostream>
#include <thread>
#include <mutex>
using namespace std;
mutex mtx;  // Mutex do synchronizacji wypisów na konsolę

enum class Choose { Papier = 1, Kamien = 2, Nozyce = 3 };

Choose losujWybor() {
    return static_cast<Choose>(rand() % 3 + 1);
}

string wyborNaString(Choose wybor) {
    switch (wybor) {
        case Choose::Papier: return "Papier";
        case Choose::Kamien: return "Kamien";
        case Choose::Nozyce: return "Nozyce";
        default: return "Nieznany";
    }
}

void playerFunction(int playerNumber) {
    
    // Inicjalizacja generatora liczb losowych
    unique_lock<std::mutex> lock(mtx);
    srand(time(nullptr) + playerNumber);
    Choose wyborGracza = losujWybor();
    cout << "Gracz "<< playerNumber << " wybrał: " << wyborNaString(wyborGracza) << endl;


}

int main() {
    thread player1(playerFunction, 1);
    thread player2(playerFunction, 2);

    

    // Oczekiwanie na zakończenie wątków
    player1.join();
    player2.join();

    return 0;
}
