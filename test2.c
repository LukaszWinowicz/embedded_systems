#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char secretWord[] = "Warszawa";
    char guessedLetters[strlen(secretWord)];
    memset(guessedLetters, '_', strlen(secretWord));

    char guess[100];
    int attempts = 10; // Możesz zmienić liczbę prób

    while (attempts > 0) {
        printf("Aktualny stan słowa: %s\n", guessedLetters);
        printf("Podaj literę lub próbuj odgadnąć słowo: ");
        fgets(guess, 100, stdin);

        // Usunięcie znaku nowej linii
        guess[strcspn(guess, "\n")] = 0;

        if (strlen(guess) == 1) { // Gdy podana jest pojedyncza litera
            int found = 0;
            for (int i = 0; i < strlen(secretWord); i++) {
                if (tolower(secretWord[i]) == tolower(guess[0])) {
                    guessedLetters[i] = secretWord[i];
                    found = 1;
                }
            }

            if (!found) {
                printf("Nie ma takiej litery!\n");
                attempts--;
            }
        } else if (strlen(guess) == strlen(secretWord)) { // Gdy próba odgadnięcia całego słowa
            if (strcasecmp(secretWord, guess) == 0) {
                printf("Gratulacje, odgadłeś słowo: %s\n", secretWord);
                return 0;
            } else {
                printf("To nie jest poprawne słowo!\n");
                attempts--;
            }
        } else {
            printf("Niepoprawne wejście!\n");
            attempts--;
        }

        if (strcmp(guessedLetters, secretWord) == 0) {
            printf("Gratulacje, odgadłeś słowo: %s\n", secretWord);
            return 0;
        }

        printf("Pozostało prób: %d\n\n", attempts);
    }

    printf("Koniec gry! Słowo to: %s\n", secretWord);
    return 0;
}
