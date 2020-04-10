/*
Names: Claire Martin (1571140), Celine Fong, Minh Dang, Zi Xue Lim
CMPUT 275, Winter 2020

Final Project: A Variation on 'Galaga'
bot.cpp: Controls bot movement
*/

#include "bot.h"

// define initial variables
static int is_left = 0;
extern player_alien unit[BOT_NUM];
extern bullet ammo[PLAY_NUM_BULLET];
static bool is_jump = false;
static int temp = 0;
int alien_speed = 2;
// define time delays for bullet, bot jump, and speed
int time_delay_bullet = 200;
int time_delay_jump = 5000;
int time_delay_speed = 10000;
// define variables for start and end times
systime_t timestamp_start_b, timestamp_end_b, timestamp_start_j, timestamp_end_j,
timestamp_start_s, timestamp_end_s;


void bot() {
    /*
    Controls the movement of the bot based on time and player movement
    */
    // define initial position of bot and num lives
    unit[1].x = WIDTH/2;
    unit[1].y = 90 ;
    unit[1].lives = 3;
    // get all initial start times
    timestamp_start_b = chVTGetSystemTime();
    timestamp_start_j = chVTGetSystemTime();
    timestamp_start_s = chVTGetSystemTime();

    while(1) {
        // get engine thread
        chMsgWait();
        msg_t stat = chMsgGet(engine_thread);
        chMsgRelease(engine_thread, stat);
        if(!stat) {
            // if alien is active
            if(unit->is_active) {
                // get end time for bullet
                timestamp_end_b = chVTGetSystemTime();
                if(unit[1].x <= unit[0].x + 15 && unit[1].x >= unit[0].x - 15 
                    && timestamp_end_b - timestamp_start_b >= TIME_MS2I(time_delay_bullet)) {
                    // fire bullet when in line with player and if time delay has passed
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
                    // alien jumps if time delay has passed
                    is_jump = true;
                    // restart jump time
                    timestamp_start_j = chVTGetSystemTime();
                }

                if(is_jump) {
                    // if alien is jumping, increment y position
                    unit[1].y++;
                    temp++;
                    if(temp >= 25) {
                        // allows for smooth movement, alien jumps 1 pixel per loop
                        // for 25 loops, instead of jumping 25 pixels at once
                        is_jump = false;
                        temp = 0;
                    }
                }

                // get end time for speed change
                timestamp_end_s = chVTGetSystemTime();
                if ((timestamp_end_s - timestamp_start_s >= TIME_MS2I(time_delay_speed)) && (alien_speed <= 10)) {
                    // if speed delay has passed, increment speed (up to 10)
                    alien_speed++;
                    if(time_delay_bullet > 50) {
                        // make alien shoot faster
                        time_delay_bullet -= 5;
                    }
                    // reset start time for speed
                    timestamp_start_s = chVTGetSystemTime();
                }

                for(int i = 0; i < PLAY_NUM_BULLET; i++) {
                    // iterate through bullets
                    if (ammo[i].active && ammo[i].player 
                    && ammo[i].x >= unit[1].x - 15 && ammo[i].x <= unit[1].x + 15
                    && ammo[i].y <= unit[1].y + 50 && ammo[i].y >= unit[1].y + 10) {
                        // if bullet is active and within range, bot changes direction
                        if(is_left == 1) is_left = 0;
                        else is_left = 1;
                    }
                }

                // move alien back and forth
                switch(is_left){
                    case 0:
                    unit[1].x -= alien_speed;
                    break;
                    case 1:
                    unit[1].x += alien_speed;
                    break;
                }
                
                // constrain x position of bot and change direction at each edge
                unit[1].x = constrain(unit[1].x, size*SCALE, WIDTH - size*SCALE);
                if(unit[1].x <= size*SCALE && !is_left) {
                    is_left = 1;
                }
                else if(unit[1].x >= WIDTH - size*SCALE && is_left) {
                    is_left = 0;
                }
                // constrain y position of bot
                if (unit[1].y >= HEIGHT - 95) {
                    // if alien reaches bottom, respawn and remove a player life
                    unit[1].is_active = false;
                    unit[0].lives--;
                }
            }
        }
    }
}
