#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

void child(int n) {
  // Informujemy, że proces został uruchomiony
  std::cout << "Proces potomny " << n << " został uruchomiony\n";

  // Informujemy, że proces przekazuje informację do wątku głównego
  std::cout << "Proces potomny " << n << " przekazuje informację do wątku głównego\n";

  // Przekazujemy swój PID oraz PID rodzica do wątku głównego
  std::cout << "Proces potomny " << n << " przekazuje PID: " << getpid() << ", PID rodzica: " << getppid() << "\n";
}

int main() {
  // Informujemy, że wątek główny został uruchomiony
  std::cout << "Wątek główny został uruchomiony\n";
  int n = 2;
  // Tworzymy 2n procesów
  for (int i = 0; i < 2 * n; i++) {
    if (fork() == 0) {
      // Uruchamiamy funkcję child() w procesie potomnym
      child(i);
      exit(0);
    }
  }

  // Informujemy, że wątek główny czeka na zakończenie procesów potomnych
  std::cout << "Wątek główny czeka na zakończenie procesów potomnych\n";

  // Czekamy na zakończenie procesów potomnych
  while (wait(NULL) > 0);

  // Informujemy, że wątek główny został zakończony
  std::cout << "Wątek główny został zakończony\n";

  return 0;
}