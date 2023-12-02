#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "hangman.h"
#include "rps.h"
#include "movement.h"

#define NUM_GAMES 4
char* games[NUM_GAMES] = { "hangman", "rps", "movement", "exit"};

void displayMenu() 
{
    printf("          _           \n");                                      
    printf("         | |          \n");                                      
    printf(" _ __ ___| |_ _ __ ___    __ _  __ _ _ __ ___   ___  ___ \n");
    printf("| '__/ _ \\ __| '__/ _ \\  / _` |/ _` | '_ ` _ \\ / _ \\/ __|\n");
    printf("| | |  __/ |_| | | (_) || (_| | (_| | | | | | |  __/\\__ \\\n");
    printf("|_|  \\___|\\__|_|  \\___/  \\__, |\\__,_|_| |_| |_|\\___||___/\n");
    printf("                         __/ |                          \n"); 
    printf("                        |___/                           \n");

    for (int i = 1; i <= NUM_GAMES; ++i)
    {
        printf("%d) %s\n", i, games[i - 1]);        
    }
}


void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

int main(void) {
    while (1) {
        system("clear"); 
        displayMenu();
        printf("> ");

        int d;
        if (1 != scanf("%d", &d)) {
            clearInputBuffer();  // Czyści bufor, jeśli scanf nie odczyta liczby
            continue;
        }

        clearInputBuffer();  // Czyści bufor po poprawnym odczytaniu liczby
        system("clear");
        switch (d) {
           // system("clear");
        case 1:
            hangman();
            break;
        case 2:
            rps();
            break;
        case 3:
            movement();            
            break;
        case 4:
            return 0;
        default:
            printf("Invalid choice. Please try again.\n");
        }
        sleep(1);
    }

    return 0;
}