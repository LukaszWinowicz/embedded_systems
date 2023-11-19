/*Budzik zapisujący stan
Celem zadania jest rozszerzenie (Zadania 2.3 html, md)
o możliwość przechowywania stanu ustawionego budzika pomiędzy uruchomieniami programu.*/

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

int minute = -1;
int hour = -1;
int done;
pthread_mutex_t lock;

void *alarm_thread(void *arg)
{
    while (1) {
        sleep(1);

        pthread_mutex_lock(&lock);
        if (done) {
            pthread_mutex_unlock(&lock);
            break;
        }
        pthread_mutex_unlock(&lock);

        struct tm tm;
        time_t t = time(NULL);
        localtime_r(&t, &tm);

        pthread_mutex_lock(&lock);
        if (minute == tm.tm_min && hour == tm.tm_hour) {
            printf("<<ALARM>>\n");
            minute = -1;
            hour = -1;
        }
        pthread_mutex_unlock(&lock);
    }

    return NULL;
}

int main(void)
{
    pthread_t thread;

    int ret = pthread_mutex_init(&lock, NULL);
    if (ret)
        return ret;
    
    ret = pthread_create(&thread, NULL, alarm_thread, NULL);
    if (ret)
        goto err_destroy_mutex;

    while (1) {
        printf("> ");

        /* Odczytanie jednej linii - max 80 znaków */
        char line[80];
        if (!fgets(line, sizeof(line), stdin))
            break;

        int h, m;
        if (sscanf(line, "set %d:%d", &h, &m) == 2) {
            /* Ustaw czas */
            pthread_mutex_lock(&lock);
            minute = m;
            hour = h;
            pthread_mutex_unlock(&lock);
        }

        if (strcmp("clear\n", line) == 0) {
            /* Wyczyść czas */
            pthread_mutex_lock(&lock);
            minute = -1;
            hour = -1;
            pthread_mutex_unlock(&lock);
        }

        if (strcmp("get\n", line) == 0) {
            /* Wyświetl ustawiony czas */
            pthread_mutex_lock(&lock);
            if (minute < 0 || hour < 0)
                printf("alarm is not set\n");
            else 
                printf("%02d:%02d\n", hour, minute);
            pthread_mutex_unlock(&lock);
        }

        if (strcmp("exit\n", line) == 0) {
            break;
        }
    }

    pthread_mutex_lock(&lock);
    done = 1;
    pthread_mutex_unlock(&lock);

    ret = pthread_join(thread, NULL);
    if (ret)
        fprintf(stderr, "pthread_join() error");

err_destroy_mutex:
    pthread_mutex_destroy(&lock);

    return ret;
}

