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

using namespace std;

void child(int n) {
  // Informacja, że proces został uruchomiony
  cout << "Proces potomny " << n << " został uruchomiony\n";

  // Przekazanie przez proces poromny swoich PIDów oraz PIDów rodzica do wątku głównego
  cout << "Proces potomny " << n << " przekazuje PID: " << getpid() << ", PID rodzica: " << getppid() << "\n";
}

bool isValidInput() {
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (cin.gcount() > 1) return false; 
    return true;
}

int main() {

  int n = 0;
  while (true)
    {
        cout << "Podaj liczbę całkowitą (Z przedziału 2 - 20).\n>> ";
        cin >> n;

        if (!isValidInput() || n < 2 || n > 20) 
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
  for (int i = 1; i <= 2 * n; i++) {
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