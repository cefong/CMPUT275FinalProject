#ifndef __CHARACTER_H
#define __CHARACTER_H

#include <Adafruit_GFX.h>
#include "MCUFRIEND_kbv.h"
#include <SPI.h>
#include "common.h"

#define BULLET_WIDTH    3
#define BULLET_HEIGHT   10
#define BULLET_RAD      3
#define BULLET_COLOR    TFT_CYAN
#define BULLET_SPEED    10

extern MCUFRIEND_kbv tft;

void fire_bullet(bool is_player, int x, int y);
void bullet_update();
void player_character(int x, int y, int x_pos, int y_pos);





#endif