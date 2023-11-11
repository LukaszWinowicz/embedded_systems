// Celem zadania jest implementacja listy przypomnień z użyciem wątków.
/*Program musi wspierać następujące komendy:

list - wyświetlanie przypomnień;
exit - kończenie programu;
H:M Text - dodawanie przypomnień.*/

#include <stdio.h>
#include <string.h>

int main(void)
{
    char line[5][48];
    
    printf("Podaj wartosc do pierwsszego wiersza: ");
    fgets(line[0], sizeof(line[0]), stdin);

    printf("Pierwszy wiersz: %s", line[0]);

    return 0;
}