/*
    Napisz program który emuluje grę kamień nożyce papier. 
    Program tworzy 2 wątki, które losują sobie jeden z elementów. 
    Przekazują go do arbitra (proces główny), który określa kto wygrał. 
    Gra toczy się do 10 zwycięstw. Podczas pojedynczej tury gry obowiązuje zasada, że pierwszy wpisuje ten co przegrał.
*/

#include <iostream>
#include <thread>
#include <mutex>
#include <random>
#include <string>
#include <map>

using namespace std;

int player1Score = 0;
int player2Score = 0;
int player1Choose = 0;
int player2Choose = 0;
int startingPlayer = 1;
int WINNING_MIN = 10;
mutex mtx;

void player(int playerNumber, int &playerChoice) {
    unique_lock<mutex> lock(mtx);
    // Tworzenie lokalnego generatora liczb losowych
    random_device rd;
    mt19937 gen(rd() + playerNumber);
    uniform_int_distribution<> dis(1, 3);
    playerChoice = dis(gen);
}

// Funkcja pomocnicza do wyświetlania wyboru
string choiceToString(int choice) {
    static map<int, string> choices = {
        {1, "Kamień ✊"},
        {2, "Papier ✋"},
        {3, "Nożyce ✌️"}
    };
    return choices[choice];
}

int main() {
    

    while (player1Score < WINNING_MIN && player2Score < WINNING_MIN){

        cout << "Rundę zaczyna gracz: " << startingPlayer << endl;
        cout << "|Gracz 1| " << player1Score << " : " << player2Score << " |Gracza 2|" << endl;

        if (startingPlayer == 1) {
            thread player1(player, 1, ref(player1Choose));
            thread player2(player, 2, ref(player2Choose));
            player1.join();
            player2.join();
        } 
        else {
            thread player2(player, 2, ref(player2Choose));        
            thread player1(player, 1, ref(player1Choose));
            player1.join();
            player2.join();
        }

        cout << "Gracz 1 wybrał: " << choiceToString(player1Choose) << endl;
        cout << "Gracz 2 wybrał: " << choiceToString(player2Choose) << endl;

        if (player1Choose == player2Choose) {
            cout << ">> REMIS" << endl;
        } else if ((player1Choose == 1 && player2Choose == 3) ||
                (player1Choose == 2 && player2Choose == 1) ||
                (player1Choose == 3 && player2Choose == 2)) {
            cout << ">> WYGRAŁ GRACZ 1" << endl;
            player1Score++;
            startingPlayer = 2;
        } else {
            cout << ">> WYGRAŁ GRACZ 2" << endl;
            player2Score++;
            startingPlayer = 1;
        }
           cout << "------------------------------" << endl;

    }

    cout << "--- OSTATECZNE WYNIKI ---" << endl;
    cout << "Wynik gracza 1: " << player1Score << endl;
    cout << "Wynik gracza 2: " << player2Score << endl;     

    


    return 0;
}

