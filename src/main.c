#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <time.h>

#include <ncurses.h>

#include "structs.h"
#include "defines.h"
#include "display.h"

static void add_on_screen(prjctl_t *projectils, ennemy1_t *ennemys1, int pos) {

    static time_t   timer = 0;

    if (time(NULL) != timer) {

        projectils->pos[projectils->nb].x = pos + 4;
        projectils->pos[projectils->nb].y = LINES-6;
        projectils->nb++;
        ennemys1->pos[ennemys1->nb].x = rand() % COLS;
        if (ennemys1->pos[ennemys1->nb].x == 0)
            ennemys1->pos[ennemys1->nb].x = 2;
        if (ennemys1->pos[ennemys1->nb].x > COLS-4)
            ennemys1->pos[ennemys1->nb].x = COLS-4;
        ennemys1->pos[ennemys1->nb].y = 0;
        ennemys1->nb++;

        if (projectils->nb >= MAX_PROJ)
            projectils->nb = 0;
        if (ennemys1->nb >= MAX_ENNEMY1)
            ennemys1->nb = 0;

        for (int i = 0; i < ennemys1->nb; i++)
            ennemys1->pos[i].y++;

        timer = time(NULL);
    }
}

static int check_deads(prjctl_t *projectils, ennemy1_t *ennemys1, int *score) {

    for (int j = 0; j < ennemys1->nb; j++) {
        if (ennemys1->pos[j].y >= LINES-6)
            return 1;
        for (int i = 0; i < projectils->nb; i++) {
            if (projectils->pos[i].x >= ennemys1->pos[j].x && projectils->pos[i].x <= ennemys1->pos[j].x+3 && projectils->pos[i].y == ennemys1->pos[j].y+1) {
                ennemys1->nb--;
                projectils->nb--;
                memmove(&projectils->pos[i], &projectils->pos[i+1], (projectils->nb - i) * sizeof(pos_t));
                memmove(&ennemys1->pos[j], &ennemys1->pos[j+1], (ennemys1->nb - j) * sizeof(pos_t));
                score[0]++;
            }
        }
    }
    return 0;
}

static void move_projectils(prjctl_t *projectils) {
    for (int i = 0; i < projectils->nb; i++) {
        projectils->pos[i].y--;
        if (projectils->pos[i].y <= 0) {
            projectils->nb--;
            memmove(&projectils->pos[i], &projectils->pos[i+1], (projectils->nb - i) * sizeof(pos_t));
        }
    }
}

static void move_player(char touch, int *pos) {
    if (pos[0] < COLS-8 && touch == 'd')
        pos[0] += 2;
    if (pos[0] > 1 && touch == 'q')
        pos[0] -= 2;
}

void game_loop(WINDOW *screen) {
    prjctl_t    projectils[MAX_PROJ];
    ennemy1_t   ennemys1[MAX_ENNEMY1];
    int         score = 0;
    int         pos = 11;
    char        touch;

    memset(projectils, 0, sizeof(prjctl_t) * MAX_PROJ);
    memset(ennemys1, 0, sizeof(ennemy1_t) * MAX_ENNEMY1);

    while (1)
    {
        if (check_deads(projectils, ennemys1, &score) == 1)
            break;
        add_on_screen(projectils, ennemys1, pos);
        move_projectils(projectils);

        werase(screen);
        box(screen, 0, 0); 
        display_screen(screen, pos, projectils, ennemys1, score);

        touch = wgetch(screen);
        if (touch != ERR)
            move_player(touch, &pos);

        napms(30);
    }
    display_end(screen);
    wrefresh(screen);
    for (;;) {
        usleep(20000);
    }
}

int main(void)
{
    WINDOW *screen = initscr();
    
    cbreak(); // sets raw like mode, CTRL chars still remains
    srand(time(NULL));
    curs_set(0); // remove cursor
    noecho(); // remove echo from getch
    nodelay(screen, TRUE); // getch non blocking
    game_loop(screen);
    endwin();  
    return 0;
}