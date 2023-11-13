// Celem zadania jest implementacja listy przypomnień z użyciem wątków.
/*Program musi wspierać następujące komendy:

list - wyświetlanie przypomnień;
exit - kończenie programu;
H:M Text - dodawanie przypomnień.*/

#include <stdio.h>
#include <string.h>

// zainicjalizowanie pustej tablicy
char reminders[5][10] = {};

int main(void)
{    
    int counter = 0;
    printf("Enter the data in the format 'HH:MM reminder message': \n");
    while (1)     
    {         
        char line[10] = {}; // wprowadzona dana przez użytkowanika
        char text[10] = {};
        int hours, minutes;
	    printf("> ");
        if (fgets(line, sizeof(line), stdin) == NULL) {
            printf("Data reading error.\n");
            return 1;
        }

        if (strcmp("exit\n", line) == 0) 
        {
		    break;
	    }

        if (strcmp("list\n", line) == 0) 
        {            
            for (int i = 0; i < 5; i++)
            {
                if(reminders[i][0] != '\0')
                {
                    printf("%s\n", reminders[i]);
                }      
            }         
            continue;     
	    }

        // Odczytanie danych z wejściowego ciągu znaków
        if (sscanf(line, "%2d:%2d%*1[ ]%[^\n]", &hours, &minutes, text) == 3  && hours >= 0 && hours <= 23 && minutes >= 0 && minutes <= 59) 
        {        
            if(counter < 5)
            {
                for (int i = 0; i < 5; i++)
                {
                    if (reminders[i][0] == '\0' || reminders[i][0] == '\n')
                    {
                        // Przygotowanie ciągu do zapisania
                        char formattedString[10] = {};
                        snprintf(formattedString, sizeof(formattedString), "%02d:%02d %.3s", hours, minutes, text);

                        // Teraz możemy bezpiecznie skopiować do reminders
                        strcpy(reminders[i], formattedString);

                        printf("Added reminder '%s' at %.5s.\n", &reminders[i][6], reminders[i]);
                        counter++;
                        break;
                    }
                }
            }
            else
            {
                printf("Reminder list is at this moment full.\n");
            }
        }
        else 
        {
            printf("Błędny format lub niepoprawne wartości czasu.\n");
        }
      
        // Sprawdzenie, czy ostatni znak w 'line' jest znakiem nowej linii
        if (strchr(line, '\n') == NULL) {
            // Wyczyszczenie bufora, jeśli linia jest dłuższa niż bufor
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }
    }    
    return 0;
}
