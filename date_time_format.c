#include <stdio.h>
#include <string.h>

int main() {
    char input[100];  // Bufor na wejściowy ciąg znaków
    int hours, minutes;
    char text[100];   // Bufor na tekst
    while(1)
    {
        printf("Wprowadź dane w formacie 'HH:MM tekst': ");
        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("Błąd odczytu danych.\n");
            return 1;
        }

        // Odczytanie danych z wejściowego ciągu znaków
        int count = sscanf(input, "%2d:%2d%*1[ ]%[^\n]", &hours, &minutes, text);

        // Sprawdzenie poprawności formatu i zakresów dla godzin i minut
        if (count == 3 && hours >= 0 && hours <= 23 && minutes >= 0 && minutes <= 59) {
            printf("Odczytano: %2d:%02d, tekst: %s\n", hours, minutes, text);
        } else {
            printf("Błędny format lub niepoprawne wartości czasu.\n");
        }
    }
    return 0;
}
