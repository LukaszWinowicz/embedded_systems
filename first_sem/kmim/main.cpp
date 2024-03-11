#include <iostream>
#include <thread>
#include <unistd.h>

using namespace std;

// Zmienne globalne
int HpEnamy = 1000;
int HpHero = 1000;

void EnemyFight(){

    while (HpHero > 0)
    {
        HpHero = HpHero - 100;
        if (HpHero <= 0)        
        {
            break;
        }
        else
        {
            cout << HpHero << " - punkty życia bohatera\n";
           sleep(2);
        }

        if (HpEnamy <= 0)
        {
            cout << "Hero wygrał! Zostało Tobie " << HpHero;
            break;
        }
    }    
}

void HeroFight(){

    while (HpEnamy > 0)
    {
        HpEnamy = HpEnamy - 100;
        if (HpEnamy <= 0)        
        {
            break;
        }
        else
        {
            cout << HpEnamy << " - punkty życia wroga\n";
            sleep(1);
        }

        if (HpHero <= 0)
        {
            cout << "Hero przegrał! Zostało wrogowi " << HpEnamy;
            break;
        }
    }    
}

int main(){

    thread thr1(EnemyFight);
    thread thr2(HeroFight);

    thr1.join();
    thr2.join();

    return 0;
}