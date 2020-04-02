#include "character.h"

static bullet ammo[PLAY_NUM_BULLET];

static void draw_bullet(bool is_player, int x, int y) {
    // draws a bullet starting from top or bottom depending on character type
    
    if(is_player) {
        // if player, start from bottom
        // draw a bullet at current x and y position
        tft.fillRoundRect(x, y, BULLET_WIDTH, BULLET_HEIGHT, BULLET_RAD, BULLET_COLOR_P);
        // draw black circle at old location
        tft.fillRoundRect(x, y + BULLET_HEIGHT, BULLET_WIDTH, BULLET_HEIGHT, BULLET_RAD, TFT_BLACK);
    }
    else {
        // if alien, start at top
        // draw bullet at current x and y pos 
        tft.fillRoundRect(x, y, BULLET_WIDTH, BULLET_HEIGHT, BULLET_RAD, BULLET_COLOR_B);
        // draw black circle at old location
        tft.fillRoundRect(x, y - BULLET_HEIGHT, BULLET_WIDTH, BULLET_HEIGHT, BULLET_RAD, TFT_BLACK);
    }


}


void draw_bot(int x, int y, int x_pos, int y_pos) {
    // draw alien: xy are new pos, x_pos/y_pos are old
    // draw black circle at old position
    tft.fillCircle(x_pos, y_pos, bot_size, TFT_BLACK);
    // draw blue circle at new position
    tft.fillCircle(x, y, bot_size, BOT_COLOR);
}

void draw_player(int x, int y, int x_pos, int y_pos) {
    // draw player: xy are new pos, x_pos/y_pos are old
    // draw black circle at old position
    tft.fillCircle(x_pos, y_pos, player_size, TFT_BLACK);
    // draw red circle at new position
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