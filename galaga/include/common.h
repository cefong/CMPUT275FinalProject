#ifndef __COMMON_H
#define __COMMON_H

#include "ChRt.h"
#include "Arduino.h"

#define HEIGHT          480
#define WIDTH           320

#define JOY_CENTER      512
#define JOY_DEADZONE    64

#define JOY_HORZ        A10
#define JOY_VERT        A8
#define BUTT            21

#define speed           4
#define player_size     7
#define bot_size        7

#define PLAY_NUM_BULLET 100

struct loc {
    bool is_fire = false;
    int x;
    int y;
};
struct player_stats {
    int health = 3;
    int x;
    int y;
};





#endif