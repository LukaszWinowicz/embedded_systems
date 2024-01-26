#include <iostream>
#include <thread>
#include <mutex>
#include <random>
#include <string>
#include <map>

using namespace std;

int player1Score = 0;
int player2Score = 0;
int startingPlayer = 1;
mutex scoreMutex;
int WINNING_MIN = 10;
mutex mtx;

// Funkcja symulująca wybór gracza
int playerChoice(int playerNumber) {
    static random_device rd;
    static mt19937 gen(rd() + playerNumber);
    uniform_int_distribution<> dis(1, 3);

    return dis(gen);
}

// Funkcja pomocnicza do wyświetlania wyboru
string choiceToString(int choice) {
    static map<int, string> choices = {
        {1, "Kamień"},
        {2, "Papier"},
        {3, "Nożyce"}
    };
    return choices[choice];
}

int main() {
    while (player1Score < WINNING_MIN && player2Score < WINNING_MIN) {
        
        cout << "Rundę zaczyna gracz: " << startingPlayer << endl;
        int player1Choose = playerChoice(1);
        int player2Choose = playerChoice(2);

        cout << "Gracz 1 wybrał: " << choiceToString(player1Choose) << endl;
        cout << "Gracz 2 wybrał: " << choiceToString(player2Choose) << endl;

        if (player1Choose == player2Choose) {
            cout << ">> REMIS" << endl;
        } else if ((player1Choose == 1 && player2Choose == 3) ||
                   (player1Choose == 2 && player2Choose == 1) ||
                   (player1Choose == 3 && player2Choose == 2)) {
            cout << ">> WYGRAŁ GRACZ 1" << endl;
            lock_guard<mutex> lock(scoreMutex);
            player1Score++;
        } else {
            cout << ">> WYGRAŁ GRACZ 2" << endl;
            lock_guard<mutex> lock(scoreMutex);
            player2Score++;
        }

        cout << "Wynik gracza 1: " << player1Score << endl;
        cout << "Wynik gracza 2: " << player2Score << endl;
        cout << "------------------------------" << endl;
    }

    cout << "--- OSTATECZNE WYNIKI ---" << endl;
    cout << "Wynik gracza 1: " << player1Score << endl;
    cout << "Wynik gracza 2: " << player2Score << endl;

    return 0;
}
