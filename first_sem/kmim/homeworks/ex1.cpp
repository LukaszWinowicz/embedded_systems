/*
  Napisz program, który tworzy 2n procesów.
  Każdy nowo utworzony proces przekazuje swój PID oraz PID rodzica do wątku głównego.
  Każdy wątek powinien informować co robi, tzn że został uruchomiony, 
  utworzył potomka, przekazał informację itp.
*/

#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <limits>
#include <string>

using namespace std;

void child(int n) {
  // Informacja, że proces został uruchomiony
  cout << "Proces potomny " << n << " został uruchomiony\n";

  // Przekazanie przez proces poromny swoich PIDów oraz PIDów rodzica do wątku głównego
  cout << "Proces potomny " << n << " przekazuje PID: " << getpid() << ", PID rodzica: " << getppid() << "\n";
}

bool isNumericInRange(const string& str) {
    if (str.empty()) {
        return false;
    }

    // Sprawdzenie, czy wszystkie znaki to cyfry
    for (char c : str) {
        if (!isdigit(c)) {
            return false;
        }
    }

    // Konwersja stringa na liczbę i sprawdzenie zakresu
    int value = stoi(str);
    return value >= 2 && value <= 10;
}

int main() {

  string n = "0";
  while (true)
    {
        cout << "Podaj liczbę całkowitą (Z przedziału 2 - 20).\n>> ";
        cin >> n;

        if (!isNumericInRange(n)) 
        {
            cout << "Nieprawidłowe dane. Proszę podać liczbę całkowitą z zakresu 2-20." << endl;
            cout << "----------------------------------------------------------------" << endl;
        } 
        else 
        {
            break; // Wyjście z pętli, jeśli dane są prawidłowe
        }
    }

  cout << "Wątek główny został uruchomiony\n";
 
  // Utowrzenie 2n procesów
  for (int i = 1; i <= 2 * stoi(n); i++) {
    if (fork() == 0) {
      // Uruchoamienie funkcji child() w procesie potomnym
      child(i);
      exit(0);
    }
  }
  
  // Oczewkiwanie na zakończenie procesów potomnych
  while (wait(NULL) > 0);

  // Informacja, że wątek główny został zakończony
  cout << "Wątek główny został zakończony\n";

  return 0;
}