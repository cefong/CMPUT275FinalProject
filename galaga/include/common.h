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
#define size            7
#define SCALE           3

#define PLAY_NUM_BULLET 100

// struct loc {
//     bool is_fire = false;
//     int x;
//     int y;
// };

struct alien {
    int lives; // number of lives this alien has (1-3)
    int x; // x position where the alien is on the screen (0-320)
    int y; // y position of the alien (will stay constant until it jumpes as the aliens can only move side to side)
    bool is_fire = false;
};
// as alien moves down the rows, update its y position by like 10 pixels
// allow x position to move/follow player
// randomly generate lives when you generate alien

struct player_stats {
    int lives;
    int x;
    int y;
    bool is_fire = false;
};





#endif