// Celem zadania jest implementacja listy przypomnień z użyciem wątków.
/*Program musi wspierać następujące komendy:

list - wyświetlanie przypomnień;
exit - kończenie programu;
H:M Text - dodawanie przypomnień.*/

#include <stdio.h>
#include <string.h>

// zainicjalizowanie pustej tablicy
char reminders[5][10] = {};
char line[10] = {}; // wprowadzona dana przez użytkowanika
char text[10] = {};
int hours, minutes;

int main(void)
{
    int counter = 0;
    printf("Enter the data in the format 'HH:MM reminder message': \n");
    while (1)     
    {         
	    printf("> ");
        if (fgets(line, sizeof(line), stdin) == NULL) {
            printf("Data reading error.\n");
            return 1;
        }

        // [test] Wypisanie zawartości 'line'
        for (int i = 0; i < sizeof(line); i++) {
            printf("line[%d] = '%c'\n", i, line[i]);
        }

        // Wyczyszczenie bufora wejściowego
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        

    }
    
    return 0;
}

/*UWAGI
1. format zapisu do tablicy, co jest nie tak
+ 2. format odczytu informacji po godzinie, powinno brać po uwagę spację (roziązane przez: "%d:%d%*1[ ]%[^\n]")
3. zabezpiecznie wpisywania formatu czasu HH:MM
4. zabezpiecznie zakresu 00:00 -> 24:00
*/
