#include <stdio.h>

struct character {
    char c;
    int x;
    int y;
}

/* Jeżeli dir to 'w', 's', 'a' lub 'd' to rusz graczem o jedną jednostkę w odpowiednim kierunku.
 * Pamiętaj że gracz nie może wyjść poza granice planszy (5x5) */

void character_move(struct character *ch, char dir){
    
    if (dir == 'w') // góra
    {
        // warunek ? wartość_gdy_prawda : wartość_gdy_fałsz
        ch->y = ch->y > 0 ? ch->y-1 : ch->y;
    }

    if (dir == 's') // dół
    {
        ch->y = ch->y < 4 ? ch->y+1 : ch->y;
    }
    
    if (dir == 'a') // lewo
    {
        ch->x = ch->x > 0 ? ch->x-1 : ch->x;
    }

    if (dir == 'd') // prawo
    {
        ch->x = ch->x < 4 ? ch->x-1 : ch->x;
    }

    
};