#include <stdio.h>
#include "hangman.h"
#include "rps.h"
#include "movement.h"

int main(void){
    int c;
    do
    {
        printf("> ");
        scanf("%d", &c);

        switch (c)
        {
        case 1:
            hangman();
            break;
        case 2:
            rps();
            break;
        case 3:
            movement();
            break;

        default:
            break;
        }

    } while (c != 4);
    
}