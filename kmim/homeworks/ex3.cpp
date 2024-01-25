/*
std::string roc = "1) ✌️Rock\n";
  std::string pap = "2) ✋Paper\n";
  std::string sci = "3) ✌️Scissors\n";
*/

#include <iostream>
#include <thread>
#include <mutex>
#include <future>
#include <cstdlib>
#include <ctime>

using namespace std;

mutex mtx;  // Mutex do synchronizacji
int WINNING_MIN = 10;
int player1Score = 0;
int player2Score = 0;

int playerFunction(int playerNumber){
    // Inicjalizacja generatora liczb losowych
    srand(time(nullptr) + playerNumber);
    lock_guard<mutex> lock(mtx);
    int playerChoose = rand() % 3 + 1;
    return playerChoose;
}

int main() {
    // Uruchomienie wątków za pomocą std::async
    thread player1Result(playerFunction, 1);
    thread player2Result(playerFunction, 2);

    // Oczekiwanie na wyniki i ich wyświetlenie
    cout << "Gracz 1 wybrał: " << "✌️" << endl;
    cout << "Gracz 2 wybrał: " << "✋" << endl;

    return 0;
}
