#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

int time_left;
int stop;
pthread_mutex_t lock;

void *timer(void *arg)
{
    while (1) {
        /* Czekamy sekundę */
        sleep(1);

        pthread_mutex_lock(&lock);
        int tmp = stop;
        pthread_mutex_unlock(&lock);
        if (tmp)
            break;

        pthread_mutex_lock(&lock);
        /* Aktualizujemy stan "minutnika" */
        if (time_left > 0) {
            time_left--;
            if (time_left == 0)
                printf("<<ALARM>>\n");
        }
        pthread_mutex_unlock(&lock);
    }

    return NULL;
}

int main(void)
{
    int ret = pthread_mutex_init(&lock, NULL);
    if (ret)
        return 1;

    /* Tworzenie wątku */
    pthread_t thread;
    ret = pthread_create(&thread, NULL, timer, NULL);
    if (ret) {
        pthread_mutex_destroy(&lock);
        return 1;
    }

    while (1) {
        printf("> ");

        /* Odczytanie jednej linii - max 80 znaków */
        char line[80];
        if (!fgets(line, sizeof(line), stdin))
            break;

        int seconds;
        if (sscanf(line, "%d", &seconds) == 1) {
            /* Użytkownik podał liczbę sekund */
            pthread_mutex_lock(&lock);
            time_left = seconds;
            pthread_mutex_unlock(&lock);
            continue;
        }

        char option;
        if (sscanf(line, "%c", &option) == 1 && option == '?') {
            /* Użytkownik podał znak zapytania */
            pthread_mutex_lock(&lock);
            printf("remaining: %d\n", time_left);
            pthread_mutex_unlock(&lock);
            continue;
        }
    }
    pthread_mutex_lock(&lock);
    /* Informujemy wątek że powinień już kończyć pracę */
    stop = 1;
    pthread_mutex_unlock(&lock);

    /* Oczekiwanie na zakończenie wątku */
    pthread_join(thread, NULL);

    pthread_mutex_destroy(&lock);

    return 0;
}