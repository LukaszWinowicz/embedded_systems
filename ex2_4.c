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
        
        // [test] Wypisanie zawartości 'line'
        //for (int i = 0; i < sizeof(line); i++) {
        //    printf("line[%d] = '%c'\n", i, line[i]);
        //}
              
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
	    }

        // Odczytanie danych z wejściowego ciągu znaków
        if (sscanf(line, "%2d:%2d%*1[ ]%[^\n]", &hours, &minutes, text) == 3  && hours >= 0 && hours <= 23 && minutes >= 0 && minutes <= 59) 
        {            
            if(counter <= 5)
            {
                for (int i = 0; i < 5; i++)
                {
                    if (reminders[i][0] == '\0' || reminders[i][0] == '\n')
                     {
                        printf("Added to reminder list.\n");
                        strcpy(reminders[i], line);
                        counter++;
                        break;
                    }
                }
            }
            else
            {
                printf("Reminder list is at this moment full.\n");
            }

            printf("Odczytano: %2d:%02d, tekst: %s\n", hours, minutes, text);

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

/*UWAGI
+ 1. format zapisu do tablicy, co jest nie tak
+ 2. format odczytu informacji po godzinie, powinno brać po uwagę spację (roziązane przez: "%d:%d%*1[ ]%[^\n]")
3. zabezpiecznie wpisywania formatu czasu HH:MM
+ 4. zabezpiecznie zakresu 00:00 -> 24:00
*/
