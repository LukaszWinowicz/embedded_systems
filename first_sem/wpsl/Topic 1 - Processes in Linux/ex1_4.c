#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <ncurses.h>

#define NUM_GAMES 6
char* games[NUM_GAMES] = { "nudoku", "greed", "moon-buggy", "ninvaders", "nsnake", "exit"};

void displayMenu(int selectedOption) 
{
    printw(" _____ _____ ____  __  __ ____   _____  __\n");
    printw("|_   _| ____|  _ \\|  \\/  | __ ) / _ \\ \\/ /\n");
    printw("  | | |  _| | |_) | |\\/| |  _ \\| | | \\  /\n");
    printw("  | | | |___|  _ <| |  | | |_) | |_| /  \\\n");
    printw("  |_| |_____|_| \\_\\_|  |_|____/ \\___/_/\\_\\\n\n");
    printw("            Terminal Gaming Console\n\n");

    for (int i = 1; i <= NUM_GAMES; ++i)
    {
        if (i == selectedOption) 
        {
            printw("-> ");
        }
        else {
            printw("   ");
        }

        if (i == 6)
        {
            printw("0) %s\n", games[i - 1]);
        }
        else
        {
            printw("%d) %s\n", i, games[i - 1]);
        }
    }
}

void runGame(int gameNumber) 
{
    char* gameCommand;

    switch (gameNumber) {
    case 1:
        gameCommand = "nudoku";
        break;
    case 2:
        gameCommand = "greed";
        break;
    case 3:
        gameCommand = "moon-buggy";
        break;
    case 4:
        gameCommand = "ninvaders";
        break;
    case 5:
        gameCommand = "nsnake";
        break;
    default:
        return;
    }

    execlp(gameCommand, gameCommand, NULL); // launch the game whose name is stored in the gameCommand variable
    perror("Exec failed"); // Display an error if execlp() fails
    exit(EXIT_FAILURE);
}

int main() 
{
    int selectedOption = 1;
    initscr(); // nitializes the curses mode, which is used by the ncurses library for handling text-based interfaces
    
    while (1) {
        clear(); // clears the terminal screen        
        keypad(stdscr, TRUE); // enables keyboard input
        noecho(); // turns off echoing of typed characters,
        curs_set(0); // hides the cursor on the screen.
        displayMenu(selectedOption);

        int c = getch(); // getting a character from the keyboard
        switch (c) 
        {
            case KEY_UP:
                selectedOption = (selectedOption == 1) ? NUM_GAMES : selectedOption - 1;
                break;
            case KEY_DOWN:
                selectedOption = (selectedOption == NUM_GAMES) ? 1 : selectedOption + 1;
                break;
            case 10: // Enter
                if (selectedOption == 6) 
                {
                    endwin(); // end ncurses
                    return 0;
                }
                else 
                {
                    pid_t pid = fork();

                    if (pid == 0) 
                    {
                        // Child process
                        system("clear");
                        curs_set(1); // show the cursor on the screen (need to game like nudoku)
                        runGame(selectedOption); // run selected game                  
                    }
                    else if (pid == -1) 
                    {
                        perror("Fork failed");
                        exit(EXIT_FAILURE);
                    }
                    else 
                    {
                        // Parent process
                        endwin(); // end ncurses - used to return default terminal settings
                        wait(NULL); // wait for the child process to complete
                        printf("Please press Enter!\n");
                        while ((c = getch()) != 10);
                        system("clear");
                    }
                }
                break;
            default:
                break;
        }
    }
 
    endwin(); // end ncurses
    return 0;
}