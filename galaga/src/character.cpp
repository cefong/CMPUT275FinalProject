#include "character.h"

static bullet ammo[PLAY_NUM_BULLET];

static void draw_bullet(bool is_player, int x, int y) {
    
    if(is_player) {
        tft.fillRoundRect(x, y, BULLET_WIDTH, BULLET_HEIGHT, BULLET_RAD, BULLET_COLOR_P);
        tft.fillRoundRect(x, y + BULLET_HEIGHT, BULLET_WIDTH, BULLET_HEIGHT, BULLET_RAD, TFT_BLACK);
    }
    else {
        tft.fillRoundRect(x, y, BULLET_WIDTH, BULLET_HEIGHT, BULLET_RAD, BULLET_COLOR_B);
        tft.fillRoundRect(x, y - BULLET_HEIGHT, BULLET_WIDTH, BULLET_HEIGHT, BULLET_RAD, TFT_BLACK);
    }


}


void draw_bot(int x, int y, int x_pos, int y_pos) {
    tft.fillCircle(x_pos, y_pos, bot_size, TFT_BLACK);
    tft.fillCircle(x, y, bot_size, BOT_COLOR);
}

void draw_player(int x, int y, int x_pos, int y_pos) {
    tft.fillCircle(x_pos, y_pos, player_size, TFT_BLACK);
    tft.fillCircle(x, y, player_size, PLAYER_COLOR);
}
void fire_bullet(bool is_player, int x, int y) {
    for(int i = 0; i < PLAY_NUM_BULLET; i++) {
        if(!ammo[i].active) {
            ammo[i].active = true;
            ammo[i].player = is_player;
            ammo[i].x = x;
            if(is_player) ammo[i].y = y - 2 * BULLET_HEIGHT;
            else ammo[i].y = y + 2 * BULLET_HEIGHT;
            
            break;
        }
    }
}
void bullet_update() {
    for(int i = 0; i < PLAY_NUM_BULLET; i++) {
        if(ammo[i].active) {
            draw_bullet(ammo[i].player, ammo[i].x, ammo[i].y);
            if(ammo[i].y < 50 + 2*BULLET_HEIGHT || ammo[i].y > HEIGHT - 50 - 2*BULLET_HEIGHT) {
                tft.fillRoundRect(ammo[i].x, ammo[i].y, BULLET_WIDTH, BULLET_HEIGHT, BULLET_RAD, TFT_BLACK);
                ammo[i].active = false;
            }
            else {
                if(ammo[i].player) {
                    ammo[i].y -= BULLET_HEIGHT;
                }
                else {
                    ammo[i].y += BULLET_HEIGHT;
                }
            }
        }
    }
}