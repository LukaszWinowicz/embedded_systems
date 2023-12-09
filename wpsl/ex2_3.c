//Celem zadania jest implementacja interaktywnego budzika, który będzie pozwalał na:

// 1. Ustawienia godziny o której ma wystąpić alarm
// 2. Wyłączania alarmu

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

int minute = -1;
int hour = -1;
int done;

void *alarm_thread(void *arg)
{    
    while (1)
    {
        sleep(1);

        if (done)
        {
            break;
        }

        struct tm tm;
        time_t t = time(NULL);
        localtime_r(&t, &tm);

        if (minute == tm.tm_min && hour == tm.tm_hour) {
            printf("<<ALARM>>\n");
            minute = -1;
            hour = -1;
        }        
    }
    return NULL;
}

int main(void)
{
    pthread_t thread;
    
    int ret = pthread_create(&thread, NULL, alarm_thread, NULL);
    if (ret)
        return -1;
        
    while (1)
    {
        printf("> ");

        char line[80];
        /* fgets - "file gets" lub "string gets", 
        >> char *fgets(char *str, int n, FILE *stream);
        str: Wskaźnik na bufor, do którego zostaną zapisane wczytane dane.
        n: Maksymalna ilość znaków do wczytania (włączając w to znak nowej linii).
        stream: Strumień wejściowy, z którego dane będą czytane, najczęściej jest to plik 
        lub stdin (standardowe wejście).*/

        if(!fgets(line, sizeof(line), stdin))
            break;

        int h, m;

        /*sscanf to funkcja w języku C, która działa podobnie do funkcji scanf, 
        ale zamiast wczytywać dane ze strumienia wejściowego, czyta je ze łańcucha znaków (ciągu znaków).
        >> int sscanf(const char *str, const char *format, ...);
        str: Łańcuch znaków, z którego funkcja ma wczytywać dane.
        format: Ciąg formatujący, który określa, jakie dane i w jakim formacie mają być wczytane. 
        Podobnie jak w przypadku printf i scanf, formaty są oznaczone specjalnymi kodami 
        (np. %d dla liczby całkowitej, %f dla liczby zmiennoprzecinkowej itp.).
        ...: Dodatkowe argumenty, które są wskaźnikami na zmienne, do których wczytane zostaną dane zgodnie
        z określonym formatem.*/
        if (sscanf(line, "set %d:%d", &h, &m) == 2)
        {
            minute = m;
            hour = h;
        }    

        /*strcmp to funkcja w języku C, która służy do porównywania dwóch ciągów znaków.*/
        if (strcmp("clear\n", line) == 0)
        {
            minute = -1;
            hour = -1;
        }

        if (strcmp("get\n", line) == 0)
        {
            if (minute < 0 || hour < 0)
            {
                printf("alarm is not set\n");
            }
            else 
            {
                printf("%02d:%02d\n", hour, minute);
            }
        }

        if (strcmp("exit\n", line) == 0)
        {
            break;
        }
    }

    done = 1;

    pthread_join(thread, NULL);

    return 0;
}