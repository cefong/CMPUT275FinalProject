/*
Names: Claire Martin (1571140), Celine Fong, Minh Dang, Zi Xue Lim
CMPUT 275, Winter 2020

Final Project: A Variation on 'Galaga'
common.h: Defines global constants for TFT display and structs for characters
*/

#ifndef __COMMON_H
#define __COMMON_H

#include "ChRt.h"
#include "Arduino.h"

// tft display constants
#define HEIGHT          480
#define WIDTH           320

// joystick constants
#define JOY_CENTER      512
#define JOY_DEADZONE    64
#define JOY_HORZ        A10
#define JOY_VERT        A8
#define BUTT            21

// gameplay/design constants
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

// number of bullets and bots
#define PLAY_NUM_BULLET 20
#define BOT_NUM         10
#define RELOADING       2000


// character struct
struct player_alien {
    int lives; // number of lives
    int x; // x position
    int y; // y position
    int x_temp = -5;
    int y_temp = -5;
    uint16_t score = 0; // current score
    bool is_fire = false; // is it firing? 
    bool is_player = false; // is it a player or alien?
    bool is_active; // dead or alive
    int bullets = 10; // number of bullets
};

// high score struct
struct high_score {
    uint32_t rookie; // rookie high score
    uint32_t intermediate; // intermediate high score
    uint32_t advanced; // advanced high score
};

// bullet struct
struct bullet {
    bool active = false; // is it active
    bool player; // from player or alien
    int x = 0; // x position
    int y = 0; // y position
};

#endif