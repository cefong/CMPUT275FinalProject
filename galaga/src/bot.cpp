#include "bot.h"
static int is_left = 0;
static loc bot_loc;
int timestamp_start, timestamp_end;
void bot() {
    bot_loc.x = WIDTH/2;
    bot_loc.y = 70;
    timestamp_start = chVTGetSystemTime();
    while(1) {
        chMsgWait();
        msg_t stat = chMsgGet(engine_thread);
        chMsgRelease(engine_thread, stat);
        if(!stat) {
            timestamp_end = chVTGetSystemTime();
            if(timestamp_end - timestamp_start >= TIME_MS2I(2000)) {
                bot_loc.is_fire = true;
                timestamp_start = chVTGetSystemTime();
            }
            else {
                bot_loc.is_fire = false;
            }
            switch(is_left){
                case 0:
                bot_loc.x -= 2;
                break;
                case 1:
                bot_loc.x += 2;
                break;
            }
            
            chMsgSend(engine_thread, (msg_t)&bot_loc);
            bot_loc.x = constrain(bot_loc.x, bot_size, WIDTH - bot_size);
            if(bot_loc.x <= bot_size && !is_left) {
                is_left = 1;
            }
            else if(bot_loc.x >= WIDTH - bot_size && is_left) {
                is_left = 0;
            }
        }
    }
}