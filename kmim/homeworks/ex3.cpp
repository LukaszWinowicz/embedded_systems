#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

mutex mtx;  // Mutex do synchronizacji wypisów na konsolę
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
  

    //while (player1Score < WINNING_MIN && player2Score < WINNING_MIN)
    //{
        thread player1(playerFunction, 1);
        thread player2(playerFunction, 2);

        // 1 - papier, 2 kamień, 3 - nożyce
        
cout << "Gracz 1 " << player1.playerChoose() << endl;

        // Oczekiwanie na zakończenie wątków
        player1.join();
        player2.join();
   // }
    

    

    return 0;
}
