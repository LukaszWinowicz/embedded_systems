#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void){

    char password[] = "Warszawa";
    printf("%s\n", password);
    char buffor[10]; // tutaj będą zapisywane odpowiedzi użytkowanika, chyba lepiej zapisać to w tablicy [][]

    // pobranie długości tablicy '\0'
    int pLen = strlen(password); // pomija znak końca łańcucha 
    size_t size = sizeof(password) / sizeof(password[0]);

    printf("%d\n", pLen);
    printf("%ld\n", size);
    return 0;
}