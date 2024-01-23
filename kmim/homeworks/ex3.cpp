#include <iostream>
#include <thread>

using namespace std;
int WINNING_MIN = 10;
int player1Score = 0;
int player2Score = 0;

void player(int playerNumber){

}


int main(){
    thread player1(player, 1);
    thread player2(player, 2);

    while (player1Score == WINNING_MIN || player2Score == WINNING_MIN)
    {
        /* code */
    }
    


    watekGracza1.join();
    watekGracza2.join();
}