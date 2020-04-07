#include "player.h"
extern thread_t *engine_thread;

static int x = WIDTH/2;
static const int y = HEIGHT - 85;

void player_vert() {
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

void player_horz(int speed_horz) {
    msg_t stat = 0;
    int xVal = analogRead(JOY_HORZ);
    
    if(xVal < JOY_CENTER - JOY_DEADZONE) {
        stat = -speed_horz;
    }
    else if(xVal > JOY_CENTER + JOY_DEADZONE) {
        stat = speed_horz;
    }
    chMsgSend(engine_thread, stat);
}

void player() {
    while(1) {
        chMsgWait();
        msg_t sig = chMsgGet(engine_thread);
        chMsgRelease(engine_thread, sig);
        if(sig == 1) {
            player_vert();
        }
        else {
            if(sig == 0) player_horz(speed);
            else if(sig == 3) player_horz(1);
        }
    }

}