#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>

char texts[5][255];
int hours[5];
int mins[5];
int quit;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void save(void){
    FILE *dst = fopen("state", "w");
    if (!dst) {
        fprintf(stderr, "unable to open file for writing\n");
        return;
    }

    // Wpisz do niego minuty i godziny
    for (int i = 0; i < 5; i++)
    {
        if (fprintf(dst, "%d %d %s\n", hours[i], mins[i], texts[i]) < 0) {
        fprintf(stderr, "unable to save file\n");
        fclose(dst);
        return;
        }
    }
    fclose(dst);

}

void list_reminders(void)
{
	pthread_mutex_lock(&lock);
	for (int i = 0; i < 5; ++i) {
		if (strlen(texts[i]))
			printf("%s\n", texts[i]);
	}
	pthread_mutex_unlock(&lock);
}

void add_reminder(int hour, int minute, const char *line)
{
	int i;
	pthread_mutex_lock(&lock);
	for (i = 0; i < 5; ++i) {
		if (strlen(texts[i]) == 0) {
			snprintf(texts[i], sizeof(texts[i]), "%s", line);
			hours[i] = hour;
			mins[i] = minute;
			printf("reminder set to %s\n", texts[i]);
            save();
			break;
		}
	}
	pthread_mutex_unlock(&lock);
	if (i == 5)
		printf("maximum number of reminders reached\n");
}

bool check_time(int h, int m)
{
	struct tm tm;
	time_t now = time(NULL);
	localtime_r(&now, &tm);
	return tm.tm_hour == h && tm.tm_min == m;
}

void trigger_reminder(void)
{
	pthread_mutex_lock(&lock);

	for (int i = 0; i < 5; ++i) {
		if (strlen(texts[i]) && check_time(hours[i], mins[i])) {
			printf("%s\n", texts[i]);
			texts[i][0] = 0;
		}
	}

	pthread_mutex_unlock(&lock);
}

int read_line(char *line, int size)
{
	if (!fgets(line, size, stdin))
		return -1;

	size_t len = strlen(line);
	if (len == 0)
		return -1;

	if (line[len - 1] != '\n') {
		do {
			char buf[32];
			if (!fgets(buf, sizeof(buf), stdin))
				break;
			if (buf[strlen(buf) - 1] == '\n')
				break;
		} while (1);

		return 1;
	}

	line[len - 1] = 0;
	return 0;
}

void *reminder_thread(void *unused)
{
	(void)unused;

	bool stop_thread = false;
	while (!stop_thread) {
		trigger_reminder();

		pthread_mutex_lock(&lock);
		stop_thread = quit;
		pthread_mutex_unlock(&lock);

		sleep(1);
	}

	return NULL;
}

int main(void)
{
	pthread_t thread;

	if (pthread_create(&thread, NULL, reminder_thread, NULL))
		return 1;

	while (1) {
		printf("remind> ");

		char line[32];
		int err = read_line(line, sizeof(line));
		if (err < 0)
			break;
		if (err > 0) {
			fprintf(stderr, "line too long\n");
			continue;
		}

		int hour;
		int minute;
		if (sscanf(line, "%d:%d", &hour, &minute) == 2) {
			add_reminder(hour, minute, line);
			continue;
		}


		if (strcmp("list", line) == 0) {
			list_reminders();
			continue;
		}

		if (strcmp("exit", line) == 0)
			save();
            break;
	}

	pthread_mutex_lock(&lock);
	quit = true;
	pthread_mutex_unlock(&lock);

	pthread_join(thread, NULL);

	return 0;
}