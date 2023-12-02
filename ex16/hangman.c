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
            break;
    }
}

int hangman() 
{
    char secretWord[] = "Warszawa";
    char guessedLetters[strlen(secretWord) + 1];
    memset(guessedLetters, '_', strlen(secretWord));
    guessedLetters[strlen(secretWord)] = '\0';

    char guess[100];
    int mistakes = 0;

    while (mistakes < 6) 
    {
        draw_hangman(mistakes);
        printf("----------------------------------------------------\n");
        printf("Guess the word: %s\n", guessedLetters);
        printf("Enter a letter or try to guess the word: ");
        fgets(guess, 100, stdin);

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
                mistakes++;
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
                mistakes++;
            }
        } 
        else 
        {
            printf("Invalid input!\n");
            mistakes++;
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