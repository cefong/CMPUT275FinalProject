#include "player.h"
extern thread_t *engine_thread;

static int x = WIDTH/2;
static const int y = HEIGHT - 85;

void player_start() {
    msg_t stat = 0;
    int yVal = analogRead(JOY_VERT);
    if(yVal < JOY_CENTER - JOY_DEADZONE) {
        stat = -1;
    }
    else if(yVal > JOY_CENTER + JOY_DEADZONE) {
        stat = 1;
    }
    else {
        stat = 0;
    }
    chMsgSend(engine_thread, stat);
}

void player_game() {
    player_alien player;
    player.is_player = true;
    player.is_fire = false;
    int xVal = analogRead(JOY_HORZ);
    
    if(xVal < JOY_CENTER - JOY_DEADZONE) {
        x -= speed;
    }
    else if(xVal > JOY_CENTER + JOY_DEADZONE) {
        x += speed;
    }
    x = constrain(x, size*SCALE, WIDTH - size*SCALE);
    player.x = x;
    player.y = y;   
    chMsgSend(engine_thread, (msg_t)&player);
}

void player() {
    while(1) {
        chMsgWait();
        msg_t sig = chMsgGet(engine_thread);
        chMsgRelease(engine_thread, sig);
        if(sig == 1) {
            player_start();
        }
        else {
            player_game();
        }
    }

}