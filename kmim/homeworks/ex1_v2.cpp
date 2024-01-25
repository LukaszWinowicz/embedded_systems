#include <unistd.h>
#include <sys/wait.h>
#include <iostream>
#include <vector>

int main() {
    int n;
    std::cout << "Podaj liczbę n: ";
    std::cin >> n;

    for (int i = 0; i < 2 * n; ++i) {
        pid_t pid = fork();

        if (pid == -1) {
            std::cerr << "Błąd przy tworzeniu procesu." << std::endl;
            return -1;
        }

        if (pid == 0) {
            // Proces potomny
            std::cout << "Proces potomny uruchomiony. PID: " << getpid() << ", PID rodzica: " << getppid() << std::endl;
            _exit(0);  // Zakończenie procesu potomnego
        } else {
            // Proces macierzysty
            std::cout << "Proces macierzysty utworzył potomka. PID potomka: " << pid << std::endl;
            wait(NULL);  // Oczekiwanie na zakończenie procesu potomnego
        }
    }

    return 0;
}
