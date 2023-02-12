#ifndef STRUCTS_H
# define STRUCTS_H

#include "defines.h"

typedef struct pos {
    int x;
    int y;
}   pos_t;

typedef struct projectil {
    pos_t   pos[MAX_PROJ];
    int     nb;
}   prjctl_t;

typedef struct ennemy1 {
    pos_t   pos[MAX_ENNEMY1];
    int     nb;
}   ennemy1_t;

#endif /* structs.h */