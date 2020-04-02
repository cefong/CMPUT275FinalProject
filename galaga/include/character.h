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
#define BULLET_COLOR_B  TFT_GREEN
#define BULLET_SPEED    10

// #define PLAYER_COLOR    TFT_RED
// #define BOT_COLOR       TFT_BLUE
#define COLOR_1_PLAYER 0xF800
#define COLOR_2_PLAYER 0xF401
#define COLOR_3_PLAYER 0xFF20
#define COLOR_4_PLAYER 0x0000
#define COLOR_5_PLAYER 0xD6FC
#define COLOR_6_PLAYER 0x6EDD
#define COLOR_7_PLAYER 0xADB7

#define COLOR_1_ENEMY 0xF800
#define COLOR_2_ENEMY 0xF401
#define COLOR_3_ENEMY 0xFF20
#define COLOR_4_ENEMY 0x0000
#define COLOR_5_ENEMY 0xE9A6
#define COLOR_6_ENEMY 0xF3A0
#define COLOR_7_ENEMY 0xF260

#define COLOR_1_EXPLOSION 0xF800
#define COLOR_2_EXPLOSION 0xF401
#define COLOR_3_EXPLOSION 0xFF20
#define COLOR_4_EXPLOSION 0xFFFF

struct bullet {
    bool active = false;
    bool player;
    int x = 0;
    int y = 0;
};


extern MCUFRIEND_kbv tft;

void fire_bullet(bool is_player, int x, int y);
void bullet_update();
void drawSpaceship(int16_t anchorX, int16_t anchorY, int16_t x_pos, int16_t y_pos, int16_t scale, bool is_player);




#endif