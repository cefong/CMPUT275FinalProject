#include "bot.h"

// define initial variables
static int is_left = 0;
player_alien bot_loc[BOT_NUM];
static bool is_jump = false;
static int temp = 0;
int speed = 2;
// define variables for start and end times
systime_t timestamp_start_b, timestamp_end_b, timestamp_start_j, timestamp_end_j,
timestamp_start_s, timestamp_end_s;
void bot() {
    /*
    Controls the movement of the bot based on time and player movement
    */
    // define initial position of bot
    bot_loc[0].x = WIDTH/2;
    bot_loc[0].y = 80;
    // define time delays for bullet and bot jump
    int time_delay_bullet = 2000;
    int time_delay_jump = 5000;
    int time_delay_speed = 10000;
    // get both start times
    timestamp_start_b = chVTGetSystemTime();
    timestamp_start_j = chVTGetSystemTime();
    timestamp_start_s = chVTGetSystemTime();
    bot_loc[0].lives = 3;
    while(1) {
        // get engine thread
        chMsgWait();
        msg_t stat = chMsgGet(engine_thread);
        chMsgRelease(engine_thread, stat);
        if(!stat) {
            // get end time for bullet
            if(bot_loc->is_active) {
                timestamp_end_b = chVTGetSystemTime();
                if(timestamp_end_b - timestamp_start_b >= TIME_MS2I(time_delay_bullet)) {
                    // fire bullet
                    bot_loc[0].is_fire = true;
                    // restart bullet time
                    timestamp_start_b = chVTGetSystemTime();
                }
                else {
                    // don't fire
                    bot_loc[0].is_fire = false;
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
                    bot_loc[0].y++;
                    temp++;
                    if(temp >= 25) {
                        is_jump = false;
                        temp = 0;
                    }
                }
                timestamp_end_s = chVTGetSystemTime();
                if ((timestamp_end_s - timestamp_start_s >= TIME_MS2I(time_delay_speed)) && (alien_speed <= 10)) {
                    alien_speed ++;
                    timestamp_start_s = chVTGetSystemTime();
                }
                switch(is_left){
                    // change direction at edges of screen
                    case 0:
                    bot_loc[0].x -= speed;
                    break;
                    case 1:
                    bot_loc[0].x += speed;
                    break;
                }
                
                // constrain x position of bot
                bot_loc[0].x = constrain(bot_loc[0].x, size*SCALE, WIDTH - size*SCALE);
                if(bot_loc[0].x <= size*SCALE && !is_left) {
                    is_left = 1;
                }
                else if(bot_loc[0].x >= WIDTH - size*SCALE && is_left) {
                    is_left = 0;
                }
                // constrain y position of bot
                if (bot_loc[0].y >= HEIGHT - 95) {
                    bot_loc[0].y = 80;
                }
            }
        }
    }
}