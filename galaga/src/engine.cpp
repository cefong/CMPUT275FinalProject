#include "engine.h"
#include "character.h"
#include "multiplayer.h"
extern bullet ammo[PLAY_NUM_BULLET];
player_alien unit[BOT_NUM];
extern int alien_speed;
extern int time_delay_bullet;
extern int time_delay_jump;
extern int time_delay_speed;
// define structs and initial variables
static int start = 1;
static int selection = 0;

static void update_health(int lives) {
    for (int i = 0; i < lives; i++) {
        drawHeart(10+i*30, HEIGHT - 20, 2);
    }
}

// for singleplayer
static void main_screen_init(player_alien* player, int highscore) {
    // initialize basic screen
    tft.fillScreen(TFT_BLACK);
    tft.fillRect(0, 50, WIDTH, 5, TFT_PURPLE);
    tft.fillRect(0, HEIGHT - 50, WIDTH, 5, TFT_PURPLE);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.setCursor(10, 10);
    tft.setTextSize(2);
    tft.print("HIGH SCORE");
    tft.setCursor(10, 30);
    tft.setTextSize(2);
    tft.print(highscore);
    tft.setCursor(200, 10);
    tft.setTextSize(2);
    tft.print("SCORE");
    tft.setCursor(200, 30);
    tft.print(player->score);
    tft.setCursor(10, HEIGHT - 40);
    tft.print("LIVES");
    update_health(player->lives);
}

// for multiplayer
static void multi_screen_init() {
    // initialize basic screen
    tft.fillScreen(TFT_BLACK);
    tft.fillRect(0, 50, WIDTH, 5, TFT_PURPLE);
    tft.fillRect(0, HEIGHT - 50, WIDTH, 5, TFT_PURPLE);

}

static void high_score_show() {
    // Shows high schore on the top of the screen
    tft.fillScreen(TFT_BLACK);
    tft.drawLine(0, 50, WIDTH, 50, TFT_PURPLE);
    tft.drawLine(0, HEIGHT - 50, WIDTH, HEIGHT - 50, TFT_PURPLE);
    tft.setCursor(10, 10);
    tft.setTextSize(2);
    tft.print("HIGH SCORE");
    tft.setCursor(200, 10);
    tft.setTextSize(2);
    tft.print("SCORE");
    tft.setCursor(200, 30);

}

// multiplayer initialization
static bool multiplayer_init() {
    /*
    Initialize serial communication for multiplayer
    */
    Serial.end();
    Serial.begin(9600);
    Serial.println("R");
    if(wait_timeout(1,500)) {
        char r = Serial.read();
        if(r == 'A') {
            Serial.println("A");
            return 1;
        }
        else {
            return 0;
        }
    }
    else {
        return 0;
    }
}
static void endScreen(int currentScore, int highScore){
    while(start != 1) {
        chThdSleepMilliseconds(100);
        eventmask_t butt_trig = chEvtWaitAnyTimeout(ALL_EVENTS, 0);
        tft.setCursor(35, 100);
        tft.setTextSize(7);
        tft.setTextColor(TFT_RED);
        tft.print("GALAGA");
        tft.setTextSize(5);
        tft.setTextColor(TFT_WHITE);
        tft.setCursor(30,200);
        tft.print("GAME OVER");
        if(currentScore > highScore){
            tft.setCursor(35,250);
            tft.setTextSize(3);
            tft.print("NEW HIGH SCORE");
        }
        tft.setCursor(35,280);
        tft.setTextSize(2);
        tft.print("Current High Score: ");
        tft.print(highScore); // change this to hi-score
        tft.setCursor(35,330);
        tft.print("Your Score: ");
        tft.print(currentScore);
        tft.setCursor(35,380);
        tft.setTextSize(3);
        tft.setTextColor(TFT_BLACK,TFT_WHITE);
        tft.print("Return To Menu");
        if(butt_trig == 1) {
            start = 1;
            tft.fillScreen(TFT_BLACK);
        } 
    }

}

void show_selection() {
    /*
    Toggle between PLAY, MULTIPLAYER and HIGH SCORE options, and highlight
    the current selected option
    */
    switch(selection){
        case 0:
        tft.setTextColor(TFT_BLACK, TFT_WHITE);
        tft.setCursor(110, 200);
        tft.print("PLAY");
        tft.setTextColor(TFT_WHITE, TFT_BLACK);
        tft.setCursor(65, 240);
        tft.print("MULTIPLAYER");
        tft.setTextColor(TFT_WHITE, TFT_BLACK);
        tft.setCursor(65, 280);
        tft.print("HIGH SCORE");
        break;
        case 1:
        tft.setTextColor(TFT_WHITE, TFT_BLACK);
        tft.setCursor(110, 200);
        tft.print("PLAY");
        tft.setTextColor(TFT_BLACK, TFT_WHITE);
        tft.setCursor(65, 240);
        tft.print("MULTIPLAYER");
        tft.setTextColor(TFT_WHITE, TFT_BLACK);
        tft.setCursor(65, 280);
        tft.print("HIGH SCORE");
        break;
        case 2:
        tft.setTextColor(TFT_WHITE, TFT_BLACK);
        tft.setCursor(110, 200);
        tft.print("PLAY");
        tft.setTextColor(TFT_WHITE, TFT_BLACK);
        tft.setCursor(65, 240);
        tft.print("MULTIPLAYER");
        tft.setTextColor(TFT_BLACK, TFT_WHITE);
        tft.setCursor(65, 280);
        tft.print("HIGH SCORE");
        break;
    }
}
void asset_init() {
    time_delay_bullet = 200;
    time_delay_jump   = 5000;
    time_delay_speed  = 10000;
    alien_speed = 2;
    for(int i = 0; i < BOT_NUM; i++) {
        unit[i].is_active = false;
        unit[i].score = 0;
    }
    for(int i = 0; i < PLAY_NUM_BULLET; i++) {
        ammo[i].active = false;
    }
    unit[0].x = WIDTH/2;
    unit[0].y = HEIGHT- 85;
    unit[0].is_active = true;
    unit[0].is_player = true;
    unit[1].x = WIDTH/2;
    unit[1].y = 90;
    unit[1].is_active = true;
    unit[1].lives = 3;
}

int show_lives_selection() {
    tft.fillScreen(TFT_BLACK);
    int lives_select = 0;
    while(1) {
        tft.setCursor(35, 100);
        tft.setTextSize(7);
        tft.setTextColor(TFT_RED);
        tft.print("GALAGA");
        tft.setTextSize(5);
        chMsgSend(player_thread, 1);
        chMsgWait();
        msg_t mess = chMsgGet(player_thread);
        lives_select -= mess;
        if(lives_select > 2) lives_select = 0;
        else if(lives_select < 0) lives_select = 2;
        chMsgRelease(player_thread, mess);
        eventmask_t butt_trig = chEvtWaitAnyTimeout(ALL_EVENTS, 0);
        switch(lives_select){
            // toggle between lives selection
            case 0:
            tft.setTextSize(3);
            tft.setTextColor(TFT_BLACK, TFT_WHITE);
            tft.setCursor(105, 200);
            tft.print("ROOKIE");
            tft.setTextColor(TFT_WHITE, TFT_BLACK);
            tft.setCursor(55, 240);
            tft.print("INTERMEDIATE");
            tft.setTextColor(TFT_WHITE, TFT_BLACK);
            tft.setCursor(90, 280);
            tft.print("ADVANCED");
            break;
            case 1:
            tft.setTextColor(TFT_WHITE, TFT_BLACK);
            tft.setCursor(105, 200);
            tft.print("ROOKIE");
            tft.setTextColor(TFT_BLACK, TFT_WHITE);
            tft.setCursor(55, 240);
            tft.print("INTERMEDIATE");
            tft.setTextColor(TFT_WHITE, TFT_BLACK);
            tft.setCursor(90, 280);
            tft.print("ADVANCED");
            break;
            case 2:
            tft.setTextColor(TFT_WHITE, TFT_BLACK);
            tft.setCursor(105, 200);
            tft.print("ROOKIE");
            tft.setTextColor(TFT_WHITE, TFT_BLACK);
            tft.setCursor(55, 240);
            tft.print("INTERMEDIATE");
            tft.setTextColor(TFT_BLACK, TFT_WHITE);
            tft.setCursor(90, 280);
            tft.print("ADVANCED");
            break;
        }
        if(butt_trig && lives_select == 0) {
            // if button is pressed and selected beginner
            return 5;
        }
        else if(butt_trig && lives_select == 1) {
            // if button is pressed and selected intermediate
            return 3;
        }
        else if (butt_trig && lives_select == 2) {
            // if button is pressed and selected advanced
            return 1;
        }
        
    }

}

void cast(player_alien* player1, player_alien* player2) {
    player2->x = player1->x;
    player2->y = player1->y;
    player2->is_fire = player1->is_fire;
    player2->is_player = player1->is_player;
}


void engine() {
    /*
    Runs main engine thread, calls and controls other threads
    */
    if(start == 1) {
        // if we are just starting, display main screen
        chMsgSend(player_thread, start);
        tft.setCursor(35, 100);
        tft.setTextSize(7);
        tft.setTextColor(TFT_RED, TFT_BLACK);
        tft.print("GALAGA");
        tft.setTextSize(3);
        show_selection();
        // get player thread to search for joystick movement
        chMsgWait();
        msg_t mess = chMsgGet(player_thread);
        selection -= mess;
        // constrain joystick selections
        if(selection > 2) selection = 0;
        else if(selection < 0) selection = 2;
        chMsgRelease(player_thread, mess);
        eventmask_t butt_trig = chEvtWaitAnyTimeout(ALL_EVENTS, 0);
        if(butt_trig && selection == 0) {
            // if button is pressed and selected PLAY
            start = 0;
        }
        else if(butt_trig && selection == 1) {
            // if button is pressed and selected MULTIPLAYER
            start = 2;
        }
    }
    else if(start == 0) {
        unit[0].lives = show_lives_selection();
        asset_init();
        int high_score = 0;
        main_screen_init(&unit[0], high_score);
        int live_temp_player = unit[0].lives;
        while(start == 0){
            // start player and bot threads
            chMsgSend(player_thread, start);
            chMsgSend(bot_thread, start);
            // draw the spaceships for player and bot
            tft.fillRect(0, 50, WIDTH, 5, TFT_PURPLE);
            tft.fillRect(0, HEIGHT - 50, WIDTH, 5, TFT_PURPLE);
            for(int i = 0; i < BOT_NUM; i++) {
                drawSpaceship(&unit[i], SCALE);
            }
            // update bot and player positions
            if(live_temp_player != unit[0].lives) {
                live_temp_player = unit[0].lives;
                update_health(live_temp_player);
            }
            // handle bullets      
            bullet_update(&unit[1],&unit[0]);
            chMsgWait();
            // update player
            msg_t stat = chMsgGet(player_thread);
            chMsgRelease(player_thread, MSG_OK);
            unit[0].x += stat;
            unit[0].x = constrain(unit[0].x, size*SCALE, WIDTH - size*SCALE);
            eventmask_t butt_trig = chEvtWaitAnyTimeout(ALL_EVENTS, 0);
            if(butt_trig) {
                // if player is firing, fire a bullet from player position
                fire_bullet(&unit[0]);
            }
            if(unit[1].is_active) {
                if(unit[1].is_fire) {
                    // if bot is firing, fire a bullet from alien position
                    fire_bullet(&unit[1]);
                }
            } 
            else { 
                // respawn
                unit[1].is_active = true;
                unit[1].x = WIDTH/2;
                unit[1].y = 90;
                unit[1].lives = 3;
            }
            if(!unit[0].is_active) {
                tft.fillScreen(TFT_BLACK);
                endScreen(unit[0].score, 0);
            }
        }
    }
    else if(start == 2) {
        // multiplayer
        tft.fillScreen(TFT_BLACK);
        player_alien player1;
        player_alien player2;
        while(!multiplayer_init()) {
            tft.setTextColor(TFT_WHITE, TFT_BLACK);
            tft.setCursor(30, 200);
            tft.setTextSize(2);
            tft.print("Waiting to connect...");
            eventmask_t butt_trig = chEvtWaitAnyTimeout(ALL_EVENTS, 0);
            if(butt_trig) {
                // if connection is not successful, go back to main screen
                start = 1;
                tft.fillScreen(TFT_BLACK);
                break;
            }
        }
        if(start == 2) {
            tft.setTextColor(TFT_BLACK, TFT_BLACK);
            tft.setCursor(30, 200);
            tft.setTextSize(2);
            tft.print("Waiting to connect...");
            tft.setTextColor(TFT_WHITE, TFT_BLACK);
            tft.setCursor(100, 200);
            tft.print("Success!");
            multi_screen_init();   
        }
        while(start == 2) {
            // start player threads
            chMsgSend(player_thread, start);
            chMsgSend(player2_thread, start);
            // draw Spaceships are player positions
            drawSpaceship(&player1, SCALE);
            drawSpaceship(&player2, SCALE);
            // handle bullets
            bullet_update(&player1, &player2);
            // update player positions
            chMsgWait();
            // update player1
            player_alien* player_temp = (player_alien*)chMsgGet(player_thread);
            cast(player_temp, &player1);
            chMsgRelease(player_thread, (msg_t)&player_temp);
            chMsgWait();
            // update player2
            player_temp = (player_alien*)chMsgGet(player2_thread);
            cast(player_temp, &player2);
            chMsgRelease(player2_thread, (msg_t)&player_temp);

            if(player1.is_fire) {
                // if player1 is firing, fire a bullet from player1 position
                fire_bullet(&player1);
            }
            if(player2.is_fire) {
                // if player2 is firing, fire a bullet from player2 position
                fire_bullet(&player2);
            }
        }
    }
}
