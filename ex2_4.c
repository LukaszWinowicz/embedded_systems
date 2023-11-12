// Celem zadania jest implementacja listy przypomnień z użyciem wątków.
/*Program musi wspierać następujące komendy:

list - wyświetlanie przypomnień;
exit - kończenie programu;
H:M Text - dodawanie przypomnień.*/

#include <stdio.h>
#include <string.h>

// zainicjalizowanie pustej tablicy
char reminders[5][8] = {};
int main(void)
{
   int counter = 0;
    while (1)     
    {         
	    printf("> ");

        char line[8];
        
        if(!fgets(line, sizeof(line), stdin))
            break;

        int hours, minutes;
        char hoursStr[3], minutesStr[3];
        char text[8];

        if (strcmp("exit\n", line) == 0) {
		break;
	    }

        if (strcmp("list\n", line) == 0) {            
            for (int i = 0; i < 5; i++)
            {
                if(reminders[i] != NULL)
                {
                    printf("%s", reminders[i]);
                }      
            }                  
	    }
        
        if (sscanf(line, "%02s:%02s%*1[ ]%[^\n]", &hours, &minutes, text) == 3 && strlen(hoursStr) == 2 && strlen(minutesStr) == 2) 
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
        }
       // printf("counter: %d\n", counter);
    }
    
    return 0;
}

/*UWAGI
1. format zapisu do tablicy, co jest nie tak
+ 2. format odczytu informacji po godzinie, powinno brać po uwagę spację (roziązane przez: "%d:%d%*1[ ]%[^\n]")
3. zabezpiecznie wpisywania formatu czasu HH:MM
4. zabezpiecznie zakresu 00:00 -> 24:00
*/
