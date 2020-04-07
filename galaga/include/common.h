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

#define YP              A3
#define XM              A2
#define YM              9
#define XP              8

#define TS_MINX         100
#define TS_MINY         120
#define TS_MAXX         940
#define TS_MAXY         920
#define MINPRESSURE     10
#define MAXPRESSURE     1000

#define speed           5
#define size            7
#define SCALE           3

#define PLAY_NUM_BULLET 100
#define BOT_NUM         10

// struct loc {
//     bool is_fire = false;
//     int x;
//     int y;
// };

// as alien moves down the rows, update its y position by like 10 pixels
// allow x position to move/follow player
// randomly generate lives when you generate alien

struct player_alien {
    int lives;
    int x;
    int y;
    int x_temp = -5;
    int y_temp = -5;
    uint32_t score = 0;
    bool is_fire = false;
    bool is_player = false;
    bool is_active;
};

struct high_score {
    uint32_t rookie;
    uint32_t intermediate;
    uint32_t advanced;
};

struct bullet {
    bool active = false;
    bool player;
    int x = 0;
    int y = 0;
};




#endif