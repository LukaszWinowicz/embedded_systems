#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <random>
#include <vector>

enum class Wybor { Kamien, Papier, Nozyce };
const int MAX_WYGRANYCH = 10;

std::mutex mtx;
std::condition_variable cv;
Wybor wyborGracza1, wyborGracza2;
bool turaZakonczona = true;
int wygraneGracza1 = 0, wygraneGracza2 = 0;

// Losowanie wyboru gracza
Wybor losujWybor() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dis(0, 2);
    return static_cast<Wybor>(dis(gen));
}

// Funkcja decydująca kto wygrał
int decyduj(Wybor w1, Wybor w2) {
    if (w1 == w2) return 0;
    if ((w1 == Wybor::Kamien && w2 == Wybor::Nozyce) || 
        (w1 == Wybor::Papier && w2 == Wybor::Kamien) ||
        (w1 == Wybor::Nozyce && w2 == Wybor::Papier)) return 1;
    return -1;
}

void gracz(int numerGracza) {
    while (wygraneGracza1 < MAX_WYGRANYCH && wygraneGracza2 < MAX_WYGRANYCH) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, []{ return turaZakonczona; });

        if (numerGracza == 1) {
            wyborGracza1 = losujWybor();
            std::cout << "Gracz 1 wybrał." << std::endl;
        } else {
            wyborGracza2 = losujWybor();
            std::cout << "Gracz 2 wybrał." << std::endl;
        }
        turaZakonczona = false;
        cv.notify_all();

        // Oczekiwanie na wynik
        cv.wait(lock, []{ return turaZakonczona; });
    }
}

int main() {
    std::thread gracz1(gracz, 1);
    std::thread gracz2(gracz, 2);

    while (wygraneGracza1 < MAX_WYGRANYCH && wygraneGracza2 < MAX_WYGRANYCH) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, []{ return !turaZakonczona; });

        int wynik = decyduj(wyborGracza1, wyborGracza2);
        if (wynik > 0) wygraneGracza1++;
        else if (wynik < 0) wygraneGracza2++;

        turaZakonczona = true;
        cv.notify_all();
    }

    gracz1.join();
    gracz2.join();

    std::cout << "Koniec gry! Wyniki: Gracz 1 - " << wygraneGracza1 << ", Gracz 2 - " << wygraneGracza2 << std::endl;
    return 0;
}
