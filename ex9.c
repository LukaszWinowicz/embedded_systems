#include <stdio.h>
#include <string.h>
#include <ctype.h>

void draw_hangman(int mistakes) 
{
    switch (mistakes) {
        case 0:
            printf(" .----.\n");
            printf("       |\n");
            printf("       |\n");
            printf("       |\n");
            printf("      / \\\n");
            break;
        case 1:
            printf(" .----.\n");
            printf(" O     |\n");
            printf("       |\n");
            printf("       |\n");
            printf("      / \\\n");
            break;
        case 2:
            printf(" .----.\n");
            printf(" O     |\n");
            printf("  \\    |\n");
            printf("       |\n");
            printf("      / \\\n");
            break;
        case 3:
            printf(" .----.\n");
            printf(" O     |\n");
            printf(" |\\    |\n");
            printf("       |\n");
            printf("      / \\\n");
            break;
        case 4:
            printf(" .----.\n");
            printf(" O     |\n");
            printf("/|\\    |\n");
            printf("       |\n");
            printf("      / \\\n");
            break;
        case 5:
            printf(" .----.\n");
            printf(" O     |\n");
            printf("/|\\    |\n");
            printf("/      |\n");
            printf("      / \\\n");
            break;
        case 6:
            printf(" .----.\n");
            printf(" O     |\n");
            printf("/|\\    |\n");
            printf("/ \\    |\n");
            printf("      / \\\n");
            break;       
        default:
            printf("Niepoprawna liczba błędów.\n");
            break;
    }
}

int main() 
{
    char secretWord[] = "Warszawa";
    char guessedLetters[strlen(secretWord)];
    memset(guessedLetters, '_', strlen(secretWord));

    char guess[100];
    int mistakes = 0; // Licznik błędów

    while (mistakes < 6) 
    {
        draw_hangman(mistakes); // Wyświetl stan wisielca
        printf("----------------------------------------------------\n");
        printf("Guess the word: %s\n", guessedLetters);
        printf("Enter a letter or try to guess the word: ");
        fgets(guess, 100, stdin);

        // Usunięcie znaku nowej linii
        guess[strcspn(guess, "\n")] = 0;

        if (strlen(guess) == 1) 
        {
            int found = 0;
            for (int i = 0; i < strlen(secretWord); i++) 
            {
                if (tolower(secretWord[i]) == tolower(guess[0])) 
                {
                    guessedLetters[i] = secretWord[i];
                    found = 1;
                }
            }

            if (!found) 
            {
                printf("There is no such letter!\n");
                mistakes++; // Zwiększ licznik błędów
            }
        } 
        else if (strlen(guess) == strlen(secretWord)) 
        {
            if (strcasecmp(secretWord, guess) == 0) 
            {
                printf("Congratulations, you guessed the word: %s\n", secretWord);
                return 0;
            } 
            else 
            {
                printf("This is not the correct word!\n");
                mistakes++; // Zwiększ licznik błędów
            }
        } 
        else 
        {
            printf("Niepoprawne wejście!\n");
            mistakes++; // Zwiększ licznik błędów
        }

        if (strcmp(guessedLetters, secretWord) == 0) 
        {
            printf("Congratulations, you guessed the word: %s\n", secretWord);
            return 0;
        }

        printf("There are attempts left: %d\n\n", 6 - mistakes);
    }

    printf("End of the game! This word: %s\n", secretWord);
    return 0;
}