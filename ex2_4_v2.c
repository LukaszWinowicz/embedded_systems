#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char reminders[5][10] = {};

void addReminder(const char *text, int hours, int minutes, int *counter) {
    if (*counter < 5) {
        for (int i = 0; i < 5; i++) {
            if (reminders[i][0] == '\0' || reminders[i][0] == '\n') {
                snprintf(reminders[i], sizeof(reminders[i]), "%02d:%02d %.3s", hours, minutes, text);
                printf("Added reminder '%s' at %.5s.\n", &reminders[i][6], reminders[i]);
                (*counter)++;
                break;
            }
        }
    } 
    else 
    {
        printf("Can't add reminder '%2d:%2d' at %.5s.\n", hours, minutes, text);
    }
}

void printReminders() {
    for (int i = 0; i < 5; i++) {
        if (reminders[i][0] != '\0') {
            printf("%s\n", reminders[i]);
        }
    }
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void parseInput(char *line, int *counter) {
    int hours, minutes;
    char text[10] = {};

    if (strcmp("exit\n", line) == 0) {
        exit(0);
    }

    if (strcmp("list\n", line) == 0) {
        printReminders();
        return;
    }

    if (sscanf(line, "%2d:%2d %[^\n]", &hours, &minutes, text) == 3 && hours >= 0 && hours <= 23 && minutes >= 0 && minutes <= 59) {
        addReminder(text, hours, minutes, counter);
    } else {
        printf("Invalid format or time values.\n");
    }
}

int main(void) {
    int counter = 0;
    printf("Enter the data in the format 'HH:MM reminder message': \n");

    while (1) {
        char line[10] = {};
        printf("> ");
        if (fgets(line, sizeof(line), stdin) == NULL) {
            printf("Data reading error.\n");
            return 1;
        }

        parseInput(line, &counter);

        if (strchr(line, '\n') == NULL) {
            clearInputBuffer();
        }
    }

    return 0;
}
