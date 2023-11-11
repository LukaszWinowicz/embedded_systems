#include <stdio.h>
#include <string.h>

int main() {
    while (1) {
        char list[8];
        printf("> ");
    
        fgets(list, sizeof(list), stdin);

        // Usuń znak nowej linii z końca
        list[strcspn(list, "\n")] = '\0';

        // Oczyść bufor wejścia
        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        printf("\nWprowadzone dane:\n");
        printf("list: %s\n", list);

        printf("\nRozmiar zajmowany przez tablicę:\n");
        printf("list: %lu bajtów\n", strlen(list) + 1); // +1 dla null terminatora
    }

    return 0;
}
