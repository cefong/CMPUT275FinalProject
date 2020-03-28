#include "player.h"
extern thread_t *engine_thread;

static int x = WIDTH/2;
static int y = 8;


void player_start() {
    msg_t stat = 0;
    uint8_t yVal = analogRead(JOY_VERT);
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
    loc player;
    uint8_t xVal = analogRead(JOY_HORZ);
    if(xVal < JOY_CENTER - JOY_DEADZONE) {
        int xspeed = map(xVal, 512, 0, 0, speed);
        x -= xspeed;
    }
    else if(xVal > JOY_CENTER + JOY_DEADZONE) {
        int xspeed = map(xVal, 512, 1023, 0, speed);
        x += xspeed;
    }
    constrain(x, 0, WIDTH);
    player.x = x;
    player.y = y;    
    chMsgSend(engine_thread, (msg_t)&player);
    chThdSleepMilliseconds(5);
}

void player() {
    while(1) {
        chMsgWait();
        chMsgGet(engine_thread);
    }

}