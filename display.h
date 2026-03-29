#ifndef DISPLAY_H
#define DISPLAY_H

#include "buffer.h"  

typedef struct {
    int row;
    int col;
    int screen_rows;
    int screen_cols;
} Display;

#define KEY_UP    1000
#define KEY_DOWN  1001
#define KEY_LEFT  1002
#define KEY_RIGHT 1003
#define KEY_QUIT  17