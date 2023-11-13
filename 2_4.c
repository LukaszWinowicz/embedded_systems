#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

void *thread_function(void *arg)
{
    sleep(1);
    printf("second thread\n");
    return NULL;
}

int main(void)
{
    pthread_t thread;
    int ret = pthread_create(&thread, NULL, thread_function, NULL);
    if (ret) {
        fprintf(stderr, "pthread_create failed with %d\n", ret);
        return 1;
    }

    /* Pętla z interfejsem użytkownika, wykonywana w wątku głównym */
    while (1) {
        /* Znak zachęty */
        printf("> ");

        /* Odczytywanie linii - maksymalnie wspieramy 80 znaków */
        char line[80];
        if (!fgets(line, sizeof(line), stdin)) {
            break;
        }

        /* Nie oczekujemy pustego ciągu znaków of fgets() */
        size_t len = strlen(line);
        if (len == 0) {
            fprintf(stderr, "unexpected empty string returned by fgets\n");
            break;
        }

        /* Jeżeli ciąg znaków nie kończy się znakiem nowej linii, oznacza
           to że część linii pozostała jeszcze nieodczytana */
        if (line[len - 1] != '\n') {
        
            /* W takim przypadku odczytaj reszte linii i zgłoś użytkowikowi
               że wpisał za dużo znaków */
            do {
                if (!fgets(line, sizeof(line), stdin)) {
                    perror("fgets");
                    break;
                }
            } while (line[strlen(line)] != '\n');

            fprintf(stderr, "line too long\n");
            continue;
        }

        line[len - 1] = 0;

        int h, m;
        if (sscanf(line, "%d:%d", &h, &m) == 2) {
            /* Dodaj przypomnienie */
        }

        if (strcmp("list", line) == 0) {
            /* Wyświetl liste przypomnień */
        }

        if (strcmp("exit", line) == 0) {
            /* Zakończ program */
            break;
        }
    }

    ret = pthread_join(thread, NULL);
    if (ret) {
        fprintf(stderr, "pthread_join failed with %d\n", ret);
        return 1;
    }

}