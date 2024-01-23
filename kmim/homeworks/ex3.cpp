#include <iostream>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

enum class Element { Kamien, Papier, Nozyce, Nieznany };

Element charToElement(char c) {
    switch (c) {
        case 'k': return Element::Kamien;
        case 'p': return Element::Papier;
        case 'n': return Element::Nozyce;
    }
    return Element::Nieznany;
}

const char *ElementToString(Element e) {
    switch (e) {
        case Element::Kamien: return "Kamien";
        case Element::Papier: return "Papier";
        case Element::Nozyce: return "Nozyce";
        default: return "Nieznany";
    }
}

int decyduj(Element e1, Element e2) {
    if (e1 == e2) return 0;
    if ((e1 == Element::Kamien && e2 == Element::Nozyce) || 
        (e1 == Element::Papier && e2 == Element::Kamien) ||
        (e1 == Element::Nozyce && e2 == Element::Papier)) return 1;
    return -1;
}

int main() {
    const char *fifo1 = "/tmp/fifo_gracz1";
    const char *fifo2 = "/tmp/fifo_gracz2";

    mkfifo(fifo1, 0666);
    mkfifo(fifo2, 0666);

    pid_t pid1, pid2;
    pid1 = fork();
    if (pid1 == 0) {
        int fd = open(fifo1, O_WRONLY);
        char wybor;

        while (true) {
            std::cout << "Gracz 1 (k, p, n): ";
            std::cin >> wybor;
            Element e = charToElement(wybor);
            if (e != Element::Nieznany) {
                write(fd, &e, sizeof(Element));
            } else {
                std::cout << "Niepoprawny wybór!" << std::endl;
            }
        }

        close(fd);
        exit(0);
    }

    pid2 = fork();
    if (pid2 == 0) {
        int fd = open(fifo2, O_WRONLY);
        char wybor;

        while (true) {
            std::cout << "Gracz 2 (k, p, n): ";
            std::cin >> wybor;
            Element e = charToElement(wybor);
            if (e != Element::Nieznany) {
                write(fd, &e, sizeof(Element));
            } else {
                std::cout << "Niepoprawny wybór!" << std::endl;
            }
        }

        close(fd);
        exit(0);
    }

    int fd1 = open(fifo1, O_RDONLY);
    int fd2 = open(fifo2, O_RDONLY);
    int wynik1 = 0, wynik2 = 0;

    while (wynik1 < 10 && wynik2 < 10) {
        Element e1, e2;
        read(fd1, &e1, sizeof(Element));
        read(fd2, &e2, sizeof(Element));

        std::cout << "Gracz 1: " << ElementToString(e1) << ", Gracz 2: " << ElementToString(e2) << std::endl;

        int wynik = decyduj(e1, e2);
        if (wynik > 0) {
            wynik1++;
            std::cout << "Gracz 1 wygrywa! Wynik: " << wynik1 << " - " << wynik2 << std::endl;
        } else if (wynik < 0) {
            wynik2++;
            std::cout << "Gracz 2 wygrywa! Wynik: " << wynik1 << " - " << wynik2 << std::endl;
        } else {
            std::cout << "Remis!" << std::endl;
        }
    }

    close(fd1);
    close(fd2);
    unlink(fifo1);
    unlink(fifo2);

    std::cout << "Koniec gry! Wyniki: Gracz 1 - " << wynik1 << ", Gracz 2 - " << wynik2 << std::endl;
    return 0;
}
