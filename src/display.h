#ifndef DISPLAY_H
# define DISPLAY_H

#include "structs.h"

void display_screen(WINDOW *screen, int pos, const prjctl_t *projectils, const ennemy1_t *ennemys1, int score);
void display_end(WINDOW *screen);

#endif /* display.h */