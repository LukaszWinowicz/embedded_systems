/*
std::string roc = "1) ✌️Rock\n";
  std::string pap = "2) ✋Paper\n";
  std::string sci = "3) ✌️Scissors\n";

    Napisz program który emuluje grę kamień nożyce papier. 
    Program tworzy 2 wątki, które losują sobie jeden z elementów. 
    Przekazują go do arbitra (proces główny), który określa kto wygrał. 
    Gra toczy się do 10 zwycięstw. Podczas pojedynczej tury gry obowiązuje zasada, że pierwszy wpisuje ten co przegrał.

*/

#include <iostream>
#include <thread>
#include <mutex>

using namespace std;
int player1Score = 0;
int player2Score = 0;

mutex mtx;

void player() {
    
}

int main() {
       
    thread player1(player, 1);
    thread player2(player, 2);

    player1.join();
    player2.join();

    return 0;
}
