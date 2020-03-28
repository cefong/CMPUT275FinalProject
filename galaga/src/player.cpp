#include "player.h"
extern thread_t *engine_thread;

static int x = WIDTH/2;
static int y = HEIGHT/2;


void player() {
    location player;
    while(1) {
        uint8_t yVal = analogRead(JOY_VERT);
        uint8_t xVal = analogRead(JOY_HORZ);
        if(yVal < JOY_CENTER - JOY_DEADZONE) {
            int yspeed = map(yVal, 512, 0, 0, speed);
            y -= yspeed;
        }
        else if(yVal > JOY_CENTER + JOY_DEADZONE) {
            int yspeed = map(yVal, 512, 1023, 0, speed);
            y += yspeed;
        }
        if(xVal < JOY_CENTER - JOY_DEADZONE) {
            int xspeed = map(yVal, 512, 0, 0, speed);
            x -= xspeed;
        }
        else if(xVal > JOY_CENTER + JOY_DEADZONE) {
            int xspeed = map(yVal, 512, 1023, 0, speed);
            x += xspeed;
        }
        player.x = x;
        player.y = y;
        chMsgSend(engine_thread, (msg_t)&player);
        chThdSleepMilliseconds(5);
    }

}