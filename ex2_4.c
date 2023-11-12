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
   
    while (1)     
    {         
	    printf("> ");

        char line[8];
        
        if(!fgets(line, sizeof(line), stdin))
            break;

        int hours, minutes;
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

        if (sscanf(line, "%d:%d%*1[ ]%[^\n]", &hours, &minutes, text) == 3) {
            for (int i = 0; i < 5; i++)
            {
                if (reminders[i][0] == '\0' || reminders[i][0] == '\n')
                {
                    printf("Dodano przypomnienie\n");
                    strcpy(reminders[i], line);
                    break;
                }
            }
        }
    }
    
    return 0;
}

/*UWAGI
1. format zapisu do tablicy, co jest nie tak
2. format odczytu informacji po godzinie, powinno brać po uwagę spację (roziązane przez: "%d:%d%*1[ ]%[^\n]")
*/
