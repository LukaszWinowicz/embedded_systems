#include <unistd.h>
#include <iostream>
#include <vector>

void createProcesses(int n) {
    std::vector<int> pipes;
    
    for (int i = 0; i < n; ++i) {
        // Utworzenie pipe dla każdej warstwy
        int pipefd[2];
        if (pipe(pipefd) == -1) {
            perror("pipe");
            exit(EXIT_FAILURE);
        }
        pipes.push_back(pipefd[0]); // Czytanie
        pipes.push_back(pipefd[1]); // Pisanie

        pid_t pid = fork();
        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (pid == 0) { // Proces potomny
            // Robi coś, np. wysyła dane przez pipe
            write(pipefd[1], &i, sizeof(i));
            close(pipefd[1]);

            exit(0); // Zakończenie procesu potomnego
        } else {
            // Proces rodzica
            close(pipefd[1]); // Rodzic nie będzie pisał do pipe
        }
    }

    // Proces rodzica może tu czytać z pipes
    for (size_t i = 0; i < pipes.size(); i += 2) {
        int val;
        read(pipes[i], &val, sizeof(val));
        std::cout << "Otrzymano wartość: " << val << std::endl;
        close(pipes[i]);
    }
}

int main() {
    createProcesses(3);
    return 0;
}
