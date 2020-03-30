#ifndef __CHARACTER_H
#define __CHARACTER_H

#include <Adafruit_GFX.h>
#include "MCUFRIEND_kbv.h"
#include <SPI.h>
#include "common.h"

#define BULLET_WIDTH    3
#define BULLET_HEIGHT   10
#define BULLET_RAD      3
#define BULLET_COLOR_P  TFT_CYAN
#define BULLET_COLOR_B  TFT_DARKGREEN
#define BULLET_SPEED    10

#define PLAYER_COLOR    TFT_RED
#define BOT_COLOR       TFT_BLUE


struct bullet {
    bool active = false;
    bool player;
    int x = 0;
    int y = 0;
};


extern MCUFRIEND_kbv tft;

void fire_bullet(bool is_player, int x, int y);
void bullet_update();
void draw_player(int x, int y, int x_pos, int y_pos);
void draw_bot(int x, int y, int x_pos, int y_pos);




#endif