#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

#define MAP_W 5
#define MAP_H 5

struct character {
    char c;
    int x;
    int y;
};

/* Jeżeli dir to 'w', 's', 'a' lub 'd' to rusz graczem o jedną jednostkę w odpowiednim kierunku.
 * Pamiętaj że gracz nie może wyjść poza granice planszy (5x5) */

void character_move(struct character *ch, char dir){
    
    if (dir == 'w') // góra
    {
        // warunek ? wartość_gdy_prawda : wartość_gdy_fałsz
        ch->y = ch->y > 0 ? ch->y-1 : ch->y;
    };

    if (dir == 's') // dół
    {
        ch->y = ch->y < 4 ? ch->y+1 : ch->y;
    };
    
    if (dir == 'a') // lewo
    {
        ch->x = ch->x > 0 ? ch->x-1 : ch->x;
    };

    if (dir == 'd') // prawo
    {
        ch->x = ch->x < 4 ? ch->x+1 : ch->x;
    };
    
};

void character_random_move(struct character *c)
{
    int x = rand()%5;

    if (x == 0)
    {
        character_move(c, 'w');
    };

    if (x == 1)
    {
        character_move(c, 's');
    };

    if (x == 2)
    {
        character_move(c, 'a');
    };

    if (x == 3)
    {
        character_move(c, 'd');
    };
    

}

struct frame {
    char cells[MAP_W][MAP_H];
};

/* wyczyść bufor znakami '.' */
void frame_clear(struct frame *frame){
    for (int i = 0; i < MAP_W; i++)
    {
        for (int j = 0; j < MAP_H; j++)
        {
            frame->cells[i][j] = '.';
        };
    };
};

/* umieść gracza buforze */
void frame_add(struct frame *frame, struct character *ch){
    frame->cells[ch->y][ch->x] = ch->c;
};
 
/* wypisz bufor */
void frame_draw(struct frame *frame){
    for (int i = 0; i < MAP_W; i++)
    {
        for (int j = 0; j < MAP_H; j++)
        {
            printf("%c", frame->cells[i][j]);
        }
        printf("\n");
    };
};

void enableRawMode() {
    struct termios raw;
    tcgetattr(STDIN_FILENO, &raw);

    raw.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

int main(void){

    enableRawMode();

    struct character player = {'&', 0, 0};
    struct character enemies[] = {
        {'A', 0, MAP_H-1},
        {'B', MAP_W-1, 0},
        {'C', MAP_W-1, MAP_H-1}
    };

    while (1)
    {
        system("clear");
        struct frame frame;
        frame_clear(&frame);
        for (int i = 0; i < sizeof(enemies)/sizeof(enemies[0]); i++)
        {
             frame_add(&frame, &enemies[i]);
        };

        frame_add(&frame, &player);
        frame_draw(&frame);

        char c;
        if(read(STDIN_FILENO, &c, 1) == 1 && c != 'q')
        {
            character_move(&player, c);
        };
        
        for (int i = 0; i < sizeof(enemies)/sizeof(enemies[0]); i++)
        {
            character_random_move(&enemies[i]);
        }

    }
}

/*TODO:
1. czyszczenie obrazu po każdym kroku
2. wciskam wsda i bez entera już, kążdy inny przycisk nic nie robi*/