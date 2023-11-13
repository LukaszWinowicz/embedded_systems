#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 10

char reminders[5][MAX_LINE_LENGTH] = {};
int minutes = -1;
int hours = -1;
int done;
int minutes_a = -1;
int hours_a = -1;
pthread_mutex_t lock;

void *thread_function(void *arg)
{
    while (1) {
        
        sleep(1);
        struct tm tm;
        time_t t = time(NULL);
        localtime_r(&t, &tm);

        pthread_mutex_lock(&lock);
        for (int i = 0; i < 5; i++)
        {
            sscanf(reminders[i], "%2d", &hours_a);
            sscanf(reminders[i], "%*3c%2d", &minutes_a);
            if (minutes_a == tm.tm_min && hours_a == tm.tm_hour) {

                printf("<<ALARM>>\n");
                printf("Hours: %d, Minutes: %d\n", hours_a, minutes_a);
                printf("%s\n", reminders[i]);

                // Wyczyść wpis po aktywacji alarmu
                memset(reminders[i], 0, sizeof(reminders[i]));

                // Resetuj zmienne pomocnicze
                minutes_a = -1;
                hours_a = -1;
                
            }           
        }
        pthread_mutex_unlock(&lock);
       
    }

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
// -------------------------------------------
    int counter = 0;
    printf("Enter the data in the format 'HH:MM reminder message': \n");

    while (1) {
        char line[MAX_LINE_LENGTH] = {};
        printf("> ");
        if (fgets(line, sizeof(line), stdin) == NULL) {
            printf("Data reading error.\n");
            return 1;
        }

        char text[MAX_LINE_LENGTH] = {};

        if (strcmp("exit\n", line) == 0) {
            exit(0);
        }

        if (strcmp("list\n", line) == 0) {
            for (int i = 0; i < 5; i++) {
                if (reminders[i][0] != '\0') {
                printf("[%d] - %s\n", i, reminders[i]);
                }
            }
        }

        if (sscanf(line, "%2d:%2d %[^\n]", &hours, &minutes, text) == 3 && hours >= 0 && hours <= 23 && minutes >= 0 && minutes <= 59) {
            if (counter < 5) {
        for (int i = 0; i < 5; i++) {
            if (reminders[i][0] == '\0' || reminders[i][0] == '\n') {
                snprintf(reminders[i], sizeof(reminders[i]), "%02d:%02d %.3s", hours, minutes, text);
                printf("Added reminder '%s' at %.5s.\n", &reminders[i][6], reminders[i]);
                counter++;
                break;
            }
        }
    } 
    else 
    {
        printf("Can't add reminder '%2d:%2d' at %.5s.\n", hours, minutes, text);
    }
        } else {
            printf("Invalid format or time values.\n");
        }

        if (strchr(line, '\n') == NULL) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }

    }
//---------------------------------------------
    
    ret = pthread_join(thread, NULL);
    if (ret) {
        fprintf(stderr, "pthread_join failed with %d\n", ret);
        return 1;
    }
    return 0;
}