#include "character.h"

extern bullet bul[PLAY_NUM_BULLET];

static void draw_bullet(bool is_player, int x, int y) {
    tft.fillRoundRect(x, y, BULLET_WIDTH, BULLET_HEIGHT, BULLET_RAD, BULLET_COLOR);
    if(is_player) {
        tft.fillRoundRect(x, y + BULLET_HEIGHT, BULLET_WIDTH, BULLET_HEIGHT, BULLET_RAD, TFT_BLACK);
    }
    else {
        tft.fillRoundRect(x, y - BULLET_HEIGHT, BULLET_WIDTH, BULLET_HEIGHT, BULLET_RAD, TFT_BLACK);
    }


}

void player_character(int x, int y, int x_pos, int y_pos) {
    tft.fillCircle(x_pos, y_pos, player_size, TFT_BLACK);
    tft.fillCircle(x, y, player_size, TFT_RED);
}
void fire_bullet(bool is_player, int x, int y) {
    for(int i = 0; i < PLAY_NUM_BULLET; i++) {
        if(!bul[i].active) {
            bul[i].active = true;
            bul[i].player = is_player;
            bul[i].x = x;
            bul[i].y = y;
            break;
        }
    }
}
void bullet_update() {
    for(int i = 0; i < PLAY_NUM_BULLET; i++) {
        if(bul[i].active) {
            draw_bullet(bul[i].player, bul[i].x, bul[i].y);
            if(bul[i].y < 50 + BULLET_HEIGHT || bul[i].y > HEIGHT - 50 - BULLET_HEIGHT) {
                tft.fillRoundRect(bul[i].x, bul[i].y, BULLET_WIDTH, BULLET_HEIGHT, BULLET_RAD, TFT_BLACK);
                bul[i].active = false;
            }
            else {
                if(bul[i].player) {
                    bul[i].y -= BULLET_HEIGHT;
                }
                else {
                    bul[i].y += BULLET_HEIGHT;
                }
            }
        }
    }
}