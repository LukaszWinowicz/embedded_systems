// Celem zadania jest implementacja listy przypomnień z użyciem wątków.
/*Program musi wspierać następujące komendy:

list - wyświetlanie przypomnień;
exit - kończenie programu;
H:M Text - dodawanie przypomnień.*/

#include <stdio.h>
#include <string.h>

int main(void)
{
    char reminders[5][48];
    while (1)     
    {
	    printf("> ");
        char line[48];
        fgets(line, sizeof(line), stdin);

        printf("%s\n", line);

        if (strcmp("exit\n", line) == 0) {
		break;
	    }
    }
    
    return 0;
}