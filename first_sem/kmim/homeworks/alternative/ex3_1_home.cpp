#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>

int main() {
    const char *fifo_gracz1 = "/tmp/fifo_gracz1";
    const char *fifo_gracz2 = "/tmp/fifo_gracz2";

    mkfifo(fifo_gracz1, 0666);
    mkfifo(fifo_gracz2, 0666);

    char bufor[256];
    int fd_gracz1 = open(fifo_gracz1, O_WRONLY);
    int fd_gracz2 = open(fifo_gracz2, O_RDONLY);

    while (true) {
        std::cout << "Gracz 1 >> ";
        std::cin.getline(bufor, 256);
        write(fd_gracz1, bufor, strlen(bufor) + 1);

        if (strcmp(bufor, "exit") == 0) {
            break;
        }

        read(fd_gracz2, bufor, 256);
        std::cout << "Gracz 2: " << bufor << std::endl;
    }

    close(fd_gracz1);
    close(fd_gracz2);
    unlink(fifo_gracz1);
    unlink(fifo_gracz2);

    return 0;
}
