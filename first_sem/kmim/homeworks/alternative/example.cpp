#include <iostream>
#include <thread>
#include <cstdlib>
#include <ctime>

const int MAX_WYGRANYCH = 10;

int losujWybor(int playerNumber) {
    srand(time(nullptr) + playerNumber);
    return rand() % 3 + 1;  // 1 - kamień, 2 - papier, 3 - nożyce
}

int decyduj(int wybor1, int wybor2) {
    if (wybor1 == wybor2) return 0;
    if ((wybor1 == 1 && wybor2 == 3) || 
        (wybor1 == 2 && wybor2 == 1) ||
        (wybor1 == 3 && wybor2 == 2)) return 1;
    return -1;
}

int main() {
    int wygraneGracza1 = 0, wygraneGracza2 = 0;
    int ostatniZwyciezca = 2; // Zakładamy, że gracz 2 zaczyna

    while (wygraneGracza1 < MAX_WYGRANYCH && wygraneGracza2 < MAX_WYGRANYCH) {
        int wyborGracza1, wyborGracza2;

        // Losowanie wyborów graczy w osobnych wątkach
        std::thread t1([&]{ wyborGracza1 = losujWybor(1); });
        std::thread t2([&]{ wyborGracza2 = losujWybor(2); });

        t1.join();
        t2.join();

        int wynik = decyduj(wyborGracza1, wyborGracza2);
        if (wynik == 1) {
            std::cout << "Gracz 1 wygrywa rundę!" << std::endl;
            wygraneGracza1++;
            ostatniZwyciezca = 1;
        } else if (wynik == -1) {
            std::cout << "Gracz 2 wygrywa rundę!" << std::endl;
            wygraneGracza2++;
            ostatniZwyciezca = 2;
        } else {
            std::cout << "Remis!" << std::endl;
            // Gracz, który przegrał ostatnią rundę, zaczyna
            ostatniZwyciezca = ostatniZwyciezca == 1 ? 2 : 1;
        }
    }

    std::cout << "Koniec gry! Wynik: Gracz 1 - " << wygraneGracza1 << ", Gracz 2 - " << wygraneGracza2 << std::endl;
    return 0;
}
