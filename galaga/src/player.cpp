/*
Names: Claire Martin (1571140), Celine Fong, Minh Dang, Zi Xue Lim
CMPUT 275, Winter 2020

Final Project: A Variation on 'Galaga'
player.cpp: Handles player movement and joystick control
*/

#include "player.h"
extern thread_t *engine_thread;

// initialize player position


void player_vert() {
    /*
    Read vertical joystick input
    */
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
    // send reading to engine
    chMsgSend(engine_thread, stat);
}


void player_horz(int speed_horz) {
    /*
    Read horizontal joystick input.

    PARAMETERS:
        speed_horz: horizontal player speed
    */
    msg_t stat = 0;
    int xVal = analogRead(JOY_HORZ);
    
    if(xVal < JOY_CENTER - JOY_DEADZONE) {
        stat = -speed_horz;
    }
    else if(xVal > JOY_CENTER + JOY_DEADZONE) {
        stat = speed_horz;
    }
    // send reading to engine
    chMsgSend(engine_thread, stat);
}


void player() {
    /*
    Read in joystick input to control player movement
    */
    while(1) {
        // get engine thread
        chMsgWait();
        msg_t sig = chMsgGet(engine_thread);
        chMsgRelease(engine_thread, sig);
        // if we are in a selection screen, read vertical
        if(sig == 1) {
            player_vert();
        }
        // else, read horizontal
        else {
            // if playing game, use game speed
            if(sig == 0) player_horz(speed);
            // if viewing high scores, use speed 1
            else if(sig == 3) player_horz(1);
        }
    }

}