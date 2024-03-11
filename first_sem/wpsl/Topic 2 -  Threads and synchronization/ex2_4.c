#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 64

char reminders[5][MAX_LINE_LENGTH] = {};
int minutes = -1;
int hours = -1;
int counter = 0;
pthread_mutex_t lock;
int text_lenght = MAX_LINE_LENGTH-7;

void *alarm_thread(void *arg)
{
    while (1) 
    {
        struct tm tm;
        time_t t = time(NULL);
        localtime_r(&t, &tm);
        pthread_mutex_lock(&lock);
        for (int i = 0; i < 5; i++)
        {
            sscanf(reminders[i], "%2d", &hours);
            sscanf(reminders[i], "%*3c%2d", &minutes);
            
            if (minutes == tm.tm_min && hours == tm.tm_hour) 
            {
                printf("\n%s\n> ", reminders[i]);
                fflush(stdout);
                memset(reminders[i], 0, sizeof(reminders[i]));
                
                minutes = -1;
                hours = -1;                    
                counter--;
            }
            
        }
        pthread_mutex_unlock(&lock);     
        sleep(60);
    }

    return NULL;
}

void addReminder(const char *text, int hours, int minutes, int *counter) 
{
    if (*counter < 5) 
    {
        pthread_mutex_lock(&lock);
        for (int i = 0; i < 5; i++) 
        {
            if (reminders[i][0] == '\0' || reminders[i][0] == '\n') 
            {
                snprintf(reminders[i], sizeof(reminders[i]), "%02d:%02d %.*s", hours, minutes, text_lenght, text);
                printf("Added reminder '%s' at %.5s.\n", &reminders[i][6], reminders[i]);
                (*counter)++;
                break;
            }
        }
        pthread_mutex_unlock(&lock); 
    } 
    else 
    {
        printf("Can't add reminder '%.*s' at %02d:%02d.\n", text_lenght, text, hours, minutes);
    }
}

void printReminders() 
{
    pthread_mutex_lock(&lock);
    for (int i = 0; i < 5; i++) 
    {
        if (reminders[i][0] != '\0') 
        {
            printf("[%d] - %s\n", i, reminders[i]);
        }
    }
    pthread_mutex_unlock(&lock); 
}

void clearInputBuffer() 
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void parseInput(char *line, int *counter) 
{    
    char text[MAX_LINE_LENGTH] = {};

    if (strcmp("exit\n", line) == 0) 
    {
        exit(0);
    }

    if (strcmp("list\n", line) == 0) 
    {
        printReminders();
        return;
    }

    if (sscanf(line, "%2d:%2d%*1[ ]%[^\n]", &hours, &minutes, text) == 3 && hours >= 0 && hours <= 23 && minutes >= 0 && minutes <= 59) 
    {
        int onlySpaces = 1;
        for (int i = 0; text[i] != '\0'; i++) 
        {
            if (!isspace((unsigned char)text[i])) {
                onlySpaces = 0;
                break;
            }
        }

        if (onlySpaces) 
        {
            printf("The text consists of whitespace only.\n");
        } else {
            addReminder(text, hours, minutes, counter);
        }
    } 
    else 
    {
        printf("Invalid format or time values.\n");
    }
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
    
    printf("Enter the data in the format 'HH:MM reminder message': \n");

    while (1) {
        char line[MAX_LINE_LENGTH] = {};
        printf("> ");
        if (fgets(line, sizeof(line), stdin) == NULL) 
        {
            printf("Data reading error.\n");
            return 1;
        }

        parseInput(line, &counter);

        if (strchr(line, '\n') == NULL) 
        {
            clearInputBuffer();
        }

    }    
  
    ret = pthread_join(thread, NULL);
    if (ret)
        fprintf(stderr, "pthread_join() error");

    err_destroy_mutex:
    pthread_mutex_destroy(&lock);

    return ret;
}