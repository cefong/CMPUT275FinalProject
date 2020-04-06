#include "bot.h"

// define initial variables
static int is_left = 0;
extern player_alien unit[BOT_NUM];
static bool is_jump = false;
static int temp = 0;
int alien_speed = 2;
// define variables for start and end times
systime_t timestamp_start_b, timestamp_end_b, timestamp_start_j, timestamp_end_j,
timestamp_start_s, timestamp_end_s;
void bot() {
    /*
    Controls the movement of the bot based on time and player movement
    */
    // define initial position of bot
    unit[1].x = WIDTH/2;
    unit[1].y = 85;
    // define time delays for bullet and bot jump
    int time_delay_bullet = 200;
    int time_delay_jump = 5000;
    int time_delay_speed = 10000;
    // get both start times
    timestamp_start_b = chVTGetSystemTime();
    timestamp_start_j = chVTGetSystemTime();
    timestamp_start_s = chVTGetSystemTime();
    unit[1].lives = 3;
    while(1) {
        // get engine thread
        chMsgWait();
        msg_t stat = chMsgGet(engine_thread);
        chMsgRelease(engine_thread, stat);
        if(!stat) {
            if(unit->is_active) {
                // get end time for bullet
                timestamp_end_b = chVTGetSystemTime();
                if(unit[1].x <= unit[0].x + 10 && unit[1].x >= unit[0].x - 10 && timestamp_end_b - timestamp_start_b >= TIME_MS2I(time_delay_bullet)) {
                    // fire bullet when in line with player
                    unit[1].is_fire = true;
                    // restart bullet time
                    timestamp_start_b = chVTGetSystemTime();
                }
                else {
                    // don't fire
                    unit[1].is_fire = false;
                }

                // get end time for jump
                timestamp_end_j = chVTGetSystemTime();
                if(timestamp_end_j - timestamp_start_j >= TIME_MS2I(time_delay_jump)) {
                    // move player
                    is_jump = true;
                    // restart jump time
                    timestamp_start_j = chVTGetSystemTime();
                }
                if(is_jump) {
                    // increment bot y position
                    unit[1].y++;
                    temp++;
                    if(temp >= 25) {
                        is_jump = false;
                        temp = 0;
                    }
                }
                timestamp_end_s = chVTGetSystemTime();
                if ((timestamp_end_s - timestamp_start_s >= TIME_MS2I(time_delay_speed)) && (alien_speed <= 10)) {
                    alien_speed++;
                    if(time_delay_bullet > 50) {
                        time_delay_bullet -= 5;
                    }
                    timestamp_start_s = chVTGetSystemTime();
                }
                switch(is_left){
                    // change direction at edges of screen
                    case 0:
                    unit[1].x -= alien_speed;
                    break;
                    case 1:
                    unit[1].x += alien_speed;
                    break;
                }
                
                // constrain x position of bot
                unit[1].x = constrain(unit[1].x, size*SCALE, WIDTH - size*SCALE);
                if(unit[1].x <= size*SCALE && !is_left) {
                    is_left = 1;
                }
                else if(unit[1].x >= WIDTH - size*SCALE && is_left) {
                    is_left = 0;
                }
                // constrain y position of bot
                if (unit[1].y >= HEIGHT - 95) {
                    // put game over here?
                    unit[1].y = 80;
                    unit[0].lives--;
                }
            }
        }
    }
}