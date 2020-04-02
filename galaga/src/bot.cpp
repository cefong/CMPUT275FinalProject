#include "bot.h"
static int is_left = 0;
static alien bot_loc;
static bool is_jump = false;
static int temp = 0;
systime_t timestamp_start_b, timestamp_end_b, timestamp_start_j, timestamp_end_j;
void bot() {
    bot_loc.x = WIDTH/2;
    bot_loc.y = 80;
    int time_delay_bullet = 2000;
    int time_delay_jump = 5000;
    timestamp_start_b = chVTGetSystemTime();
    timestamp_start_j = chVTGetSystemTime();
    while(1) {
        chMsgWait();
        msg_t stat = chMsgGet(engine_thread);
        chMsgRelease(engine_thread, stat);
        if(!stat) {
            timestamp_end_b = chVTGetSystemTime();
            if(timestamp_end_b - timestamp_start_b >= TIME_MS2I(time_delay_bullet)) {
                // fire bullet
                bot_loc.is_fire = true;
                timestamp_start_b = chVTGetSystemTime();
            }
            else {
                // don't fire
                bot_loc.is_fire = false;
            }

            timestamp_end_j = chVTGetSystemTime();
            if(timestamp_end_j - timestamp_start_j >= TIME_MS2I(time_delay_jump)) {
                // move player
                is_jump = true;
                timestamp_start_j = chVTGetSystemTime();
            }
            if(is_jump) {
                bot_loc.y++;
                temp++;
                if(temp >= 25) {
                    is_jump = false;
                    temp = 0;
                }
            }
            switch(is_left){
                case 0:
                bot_loc.x -= 2;
                break;
                case 1:
                bot_loc.x += 2;
                break;
            }
            
            // constrain x position of bot
            bot_loc.x = constrain(bot_loc.x, size*SCALE, WIDTH - size*SCALE);
            if(bot_loc.x <= size*SCALE && !is_left) {
                is_left = 1;
            }
            else if(bot_loc.x >= WIDTH - size*SCALE && is_left) {
                is_left = 0;
            }
            // constrain y position of bot
            if (bot_loc.y >= HEIGHT - 95) {
                bot_loc.y = 80;
            }
            // send new bot info to engine
            chMsgSend(engine_thread, (msg_t)&bot_loc);
        }
    }
}