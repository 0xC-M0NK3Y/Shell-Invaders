#include <ncurses.h>

#include "structs.h"
#include "defines.h"

const char *ship[] = {  "   #   ",
                        "  ...  ",
                        " ..... ",
                        ".......",0};

const char *ennemy1[] = { "HHH", 
                          " H ",0};

static inline void print_score(WINDOW *w, int score) {
    mvwprintw(w, 0, 0, "SCORE = %d ", score);
}

static inline void print_ship(WINDOW *w, int pos) {
    mvwprintw(w, LINES-5, pos, "%s", ship[0]);
    mvwprintw(w, LINES-4, pos, "%s", ship[1]);
    mvwprintw(w, LINES-3, pos, "%s", ship[2]);
    mvwprintw(w, LINES-2, pos, "%s", ship[3]);
}

static inline void print_proj(WINDOW *w, const prjctl_t *projectils) {
    for (int i = 0; i < projectils->nb; i++) {
        mvwprintw(w, projectils->pos[i].y, projectils->pos[i].x, "|");
    }
}

static inline void print_ennemys1(WINDOW *w, const ennemy1_t *ennemys1) {
    for (int i = 0; i < ennemys1->nb; i++) {
        mvwprintw(w, ennemys1->pos[i].y, ennemys1->pos[i].x, "%s", ennemy1[0]);
        mvwprintw(w, ennemys1->pos[i].y+1, ennemys1->pos[i].x, "%s", ennemy1[1]);
    }
}

void display_screen(WINDOW *screen, int pos, const prjctl_t *projectils, const ennemy1_t *ennemys1, int score) {
    print_score(screen, score);
    print_ship(screen, pos);
    print_proj(screen, projectils);
    print_ennemys1(screen, ennemys1);
}

void display_end(WINDOW *screen) {
    mvwprintw(screen, LINES/2, COLS/2, "END");
    mvwhline(screen, LINES-6, 0, 0, COLS);
}