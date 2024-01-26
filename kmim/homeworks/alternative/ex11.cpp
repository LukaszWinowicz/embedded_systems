#include <unistd.h>
#include <sys/wait.h>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

int main() {
    int n;
    std::cout << "Podaj liczbę n: ";
    std::cin >> n;

    int pipes[2 * n][2];  // Tworzymy potok dla każdego procesu potomnego

    for (int i = 0; i < 2 * n; ++i) {
        if (pipe(pipes[i]) == -1) {
            std::cerr << "Nie można utworzyć potoku." << std::endl;
            return -1;
        }

        pid_t pid = fork();

        if (pid == -1) {
            std::cerr << "Błąd przy tworzeniu procesu." << std::endl;
            return -1;
        }

        if (pid == 0) {
            // Proces potomny
            close(pipes[i][0]);  // Zamknięcie odczytu potoku w potomnym

            std::ostringstream ss;
            ss << "Proces potomny uruchomiony. PID: " << getpid() << ", PID rodzica: " << getppid() << "\n";
            std::string message = ss.str();

            write(pipes[i][1], message.c_str(), message.size());
            close(pipes[i][1]);  // Zamknięcie zapisu po przesłaniu

            _exit(0);
        } else {
            // Proces macierzysty
            close(pipes[i][1]);  // Zamknięcie zapisu potoku w macierzystym
        }
    }

    // Proces macierzysty odczytuje dane z potoków
    for (int i = 0; i < 2 * n; ++i) {
        char buffer[1024];
        read(pipes[i][0], buffer, sizeof(buffer));
        std::cout << buffer;
        close(pipes[i][0]);  // Zamknięcie odczytu po odczytaniu
    }

    // Czekanie na zakończenie wszystkich procesów potomnych
    for (int i = 0; i < 2 * n; ++i) {
        wait(NULL);
    }

    return 0;
}
