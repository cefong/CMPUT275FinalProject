/*
Names: Claire Martin (1571140), Celine Fong, Minh Dang, Zi Xue Lim
CMPUT 275, Winter 2020

Final Project: A Variation on 'Galaga'
engine.cpp: Main engine thread, controls organization of game
*/

#include "engine.h"
#include "character.h"
#include "high_score.h"

// define structs and initial variables
#include <TouchScreen.h>

extern bullet ammo[PLAY_NUM_BULLET];
player_alien unit[BOT_NUM];
extern int alien_speed;
extern int time_delay_bullet;
extern int time_delay_jump;
extern int time_delay_speed;
static int start = 1;
static int selection = 0;

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

static void processTouchScreen(int16_t *screen_x, int16_t *screen_y) {
    TSPoint touch  = ts.getPoint();
    pinMode(YP, OUTPUT);
    pinMode(XM, OUTPUT);
    if(touch.z < MINPRESSURE || touch.z > MAXPRESSURE) return;
    *screen_x = map(touch.y, TS_MINX, TS_MAXX, HEIGHT - 1, 0);
    *screen_y = map(touch.x, TS_MINY, TS_MAXY, WIDTH - 1, 0);
    chThdSleepMilliseconds(5);
}


static void update_health(int lives) {
    /*
    Updates health of player.

    PARAMETERS:
        lives: number of lives left for player
    */
    for (int i = 0; i < lives; i++) {
        drawHeart(10+i*30, HEIGHT - 20, 2);
    }
}


static void main_screen_init(player_alien* player, int highscore) {
    /*
    Initializes gameplay screen.

    PARAMETERS:
        player: updated player struct with lives based on level
        highscore: current high score for chosen level
    */

    // initialize basic screen
    tft.fillScreen(TFT_BLACK);
    tft.fillRect(0, 50, WIDTH, 5, TFT_PURPLE);
    tft.fillRect(0, HEIGHT - 50, WIDTH, 5, TFT_PURPLE);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);

    // display high score
    tft.setCursor(10, 10);
    tft.setTextSize(2);
    tft.print("HIGH SCORE");
    tft.setCursor(10, 30);
    tft.setTextSize(2);
    tft.print(highscore);

    // display current score
    tft.setCursor(200, 10);
    tft.setTextSize(2);
    tft.print("SCORE");
    tft.setCursor(200, 30);
    tft.print(player->score);
    // display number of lives (5, 3 or 1)
    tft.setCursor(10, HEIGHT - 40);
    tft.print("LIVES");
    update_health(player->lives);
    // main menu button
    tft.fillRect(170, HEIGHT - 50, 2, 50, TFT_PURPLE);
    tft.setCursor(192, HEIGHT - 28);
    tft.print("MAIN MENU");
}

static void high_score_show() {
    /*
    Shows high score screen
    */

    // get current high score
    high_score temp;
    high_score_get(&temp);
    int selection = 0;
    tft.fillScreen(TFT_BLACK);
    while(start == 3) {
        // start player thread
        chMsgSend(player_thread, start);
        chMsgWait();
        msg_t stat = chMsgGet(player_thread);
        // wait for button press
        eventmask_t butt_trig = chEvtWaitAnyTimeout(ALL_EVENTS, 0);
        selection += stat;
        // constrain joystick selections
        if(selection > 1) selection = 0;
        else if(selection < 0) selection = 1;
        chMsgRelease(player_thread, MSG_OK);

        // display high score title
        tft.setCursor(35, 60);
        tft.setTextSize(7);
        tft.setTextColor(TFT_RED, TFT_BLACK);
        tft.print("GALAGA");
        tft.setTextSize(4);
        tft.setTextColor(TFT_RED, TFT_BLACK);
        tft.setCursor(25, 120);
        tft.print("HIGH SCORES");
        // display rookie high score
        tft.setTextSize(3);
        tft.setTextColor(TFT_WHITE, TFT_BLACK);
        tft.setCursor(0, 180);
        tft.println("ROOKIE: ");
        tft.print(temp.rookie);
        // display intermediate high score
        tft.setCursor(0, 250);
        tft.println("INTERMEDIATE: ");
        tft.print(temp.intermediate);
        // display advanced high score
        tft.setCursor(0, 320);
        tft.println("ADVANCED: ");
        tft.print(temp.advanced);

        // allow users to go back or clear scores
        switch (selection) {
            case 0:
                tft.setTextSize(3);
                tft.setTextColor(TFT_BLACK, TFT_WHITE);
                tft.setCursor(10, 400);
                tft.print("BACK");
                tft.setTextColor(TFT_WHITE, TFT_BLACK);
                tft.setCursor(210, 400);
                tft.print("CLEAR");
                break;
            
            case 1:
                tft.setTextSize(3);
                tft.setTextColor(TFT_WHITE, TFT_BLACK);
                tft.setCursor(10, 400);
                tft.print("BACK");
                tft.setTextColor(TFT_BLACK, TFT_WHITE);
                tft.setCursor(210, 400);
                tft.print("CLEAR");
                break;
        }
        // if user pressed a button
        if(butt_trig && selection == 0) {
            // if selected go back
            start = 1;
            tft.fillScreen(TFT_BLACK);
        }
        else if (butt_trig && selection == 1) {
            // if selected clear
            high_score_clear();
            high_score_get(&temp);
            tft.fillRect(0, 140, WIDTH, 90, TFT_BLACK);
        }
    }
}

static void endScreen(int currentScore, int highScore, int mode){
    /*
    Display end screen
    PARAMETERS:
        currentScore: player's score
        highScore: current high score for player's level
        mode: current level (5,3, or 1 for number of lives)
    */
    high_score temp;
    bool is_highscore = false;
    // get high score
    high_score_get(&temp);
    
    while(start != 1) {
        // continue while player has not chosen to go back to main
        chThdSleepMilliseconds(10);
        eventmask_t butt_trig = chEvtWaitAnyTimeout(ALL_EVENTS, 0);

        // print "GALAGA" and "GAME OVER"
        tft.setCursor(35, 100);
        tft.setTextSize(7);
        tft.setTextColor(TFT_RED);
        tft.print("GALAGA");
        tft.setTextSize(5);
        tft.setTextColor(TFT_WHITE);
        tft.setCursor(30,200);
        tft.print("GAME OVER");
        if(currentScore > highScore){
            // if player beat high score
            is_highscore = true;
            tft.setCursor(35,250);
            tft.setTextSize(3);
            tft.print("NEW HIGH SCORE");
        }
        // print current high score
        tft.setCursor(35,300);
        tft.setTextSize(2);
        tft.print("Current High Score: ");
        tft.setCursor(35,330);

        tft.setTextColor(TFT_CYAN);
        tft.print(highScore);
        tft.setTextColor(TFT_WHITE);
        // print player's score
        tft.setCursor(35,360);
        tft.print("Your Score: ");
        tft.print(currentScore);

        // return to Menu button
        tft.setCursor(35,380);
        tft.setTextSize(3);
        tft.setTextColor(TFT_BLACK,TFT_WHITE);
        tft.print("RETURN TO MENU");
        if(butt_trig == 1) {
            // return when player presses joystick button
            start = 1;
            if(is_highscore) {
                switch(mode) {
                    // update high scores if player beat one
                    case 5:
                    temp.rookie = currentScore;
                    high_score_put(temp);
                    break;
                    case 3:
                    temp.intermediate = currentScore;
                    high_score_put(temp);
                    break;
                    case 1:
                    temp.advanced = currentScore;
                    high_score_put(temp);
                    break;
                }
            }
            tft.fillScreen(TFT_BLACK);
        } 
    }
}

static void show_selection() {
    /*
    Toggle between PLAY and HIGH SCORE options, and highlight
    the current selected options.
    */

    switch(selection){
        // highlight selected button
        case 0:
            tft.setTextColor(TFT_BLACK, TFT_WHITE);
            tft.setCursor(110, 200);
            tft.print("PLAY");
            tft.setTextColor(TFT_WHITE, TFT_BLACK);
            tft.setCursor(65, 240);
            tft.print("HIGH SCORE");
            break;
        case 1:
            tft.setTextColor(TFT_WHITE, TFT_BLACK);
            tft.setCursor(110, 200);
            tft.print("PLAY");
            tft.setTextColor(TFT_BLACK, TFT_WHITE);
            tft.setCursor(65, 240);
            tft.print("HIGH SCORE");
            break;
    }
}


static void asset_init() {
    /*
    Resets assets such as time delays, speed, and score. This will be used after a game ends
    to reset game statistics.
    */

    time_delay_bullet = 200;
    time_delay_jump   = 5000;
    time_delay_speed  = 10000;
    alien_speed = 2;

    // reset scores
    unit[0].score = 0;
    unit[1].score = 0;
    
    for(int i = 0; i < PLAY_NUM_BULLET; i++) {
        // deactivate all bullets
        ammo[i].active = false;
    }

    // reset player position and reactivate it
    unit[0].x = WIDTH/2;
    unit[0].y = HEIGHT- 85;
    unit[0].x_temp = WIDTH/2;
    unit[0].y_temp = HEIGHT- 85;
    unit[0].is_active = true;
    unit[0].is_player = true;
    // reset alien position and reactivate it
    unit[1].x = WIDTH/2;
    unit[1].y = 90;
    unit[1].x_temp = WIDTH/2;
    unit[1].y_temp = 90;
    unit[1].is_active = true;
    unit[1].is_player = false;
    unit[1].lives = 3;
}

static int show_lives_selection() {
    tft.fillScreen(TFT_BLACK);
    int lives_select = 0;
    tft.setCursor(35, 100);
    tft.setTextSize(7);
    tft.setTextColor(TFT_RED);
    tft.print("GALAGA");
    while(1) {
        tft.setTextSize(3);
        chMsgSend(player_thread, 1);
        chMsgWait();
        msg_t mess = chMsgGet(player_thread);
        lives_select -= mess;
        // handle level selection from joystick
        if(lives_select > 2) lives_select = 0;
        else if(lives_select < 0) lives_select = 2;
        chMsgRelease(player_thread, mess);
        // check for button press
        eventmask_t butt_trig = chEvtWaitAnyTimeout(ALL_EVENTS, 0);

        switch(lives_select){
            // toggle between lives selection
            case 0:
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

static void menu() {
    // if we are just starting, display main screen
    chMsgSend(player_thread, start);
    tft.setCursor(35, 100);
    tft.setTextSize(7);
    tft.setTextColor(TFT_RED, TFT_BLACK);
    tft.print("GALAGA");
    tft.setTextSize(3);
    // show selection between PLAY and HIGH SCORE
    show_selection();
    // get player thread to search for joystick movement
    chMsgWait();
    msg_t mess = chMsgGet(player_thread);
    selection -= mess;
    // constrain joystick selections
    if(selection > 1) selection = 0;
    else if(selection < 0) selection = 1;
    chMsgRelease(player_thread, mess);
    // check for button press
    eventmask_t butt_trig = chEvtWaitAnyTimeout(ALL_EVENTS, 0);
    if(butt_trig && selection == 0) {
        // if button is pressed and selected PLAY
        start = 0;
    }
    else if(butt_trig && selection == 1) {
        // if button is pressed and selected MULTIPLAYER
        // change this to high score
        start = 3;
    }
    // else if(butt_trig && selection == 2) {
    //     // if button is pressed and selected HIGH SCORE
    //     start = 3;
    // }
}
static void singleplayer() {
    // user selected PLAY
    // initialize screen and reset player stats
    unit[0].lives = show_lives_selection();
    int mode = unit[0].lives;
    asset_init();
    uint32_t high_score = high_score_init(unit[0].lives);
    main_screen_init(&unit[0], high_score);
    //int live_temp_player = unit[0].lives;
    // loop while game is still in play (player is alive)
    while(start == 0){
        int16_t touch_x = 0, touch_y = 0;
        // start player and bot threads
        chMsgSend(player_thread, start);
        chMsgSend(bot_thread, start);

        // draw the purple lines for edge of playing area
        tft.fillRect(0, 50, WIDTH, 5, TFT_PURPLE);
        tft.fillRect(0, HEIGHT - 50, WIDTH, 5, TFT_PURPLE);
        // draw spaceships for player and alien
        drawSpaceship(&unit[0], SCALE);
        drawSpaceship(&unit[1], SCALE);
        // handle bullets      
        bullet_update(&unit[1],&unit[0], high_score);
        chMsgWait();
        // update player
        msg_t stat = chMsgGet(player_thread);
        chMsgRelease(player_thread, MSG_OK);
        // change player position based on joystick reading
        unit[0].x += stat;
        // constrain player position
        unit[0].x = constrain(unit[0].x, size*SCALE, WIDTH - size*SCALE);
        // check for button press
        eventmask_t butt_trig = chEvtWaitAnyTimeout(ALL_EVENTS, 0);

        if(butt_trig) {
            // if player is firing, fire a bullet from player position
            fire_bullet(&unit[0]);
        }

        if(unit[1].is_active) {
            // if bot is alive
            if(unit[1].is_fire) {
                // if bot is firing, fire a bullet from bot position
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
        processTouchScreen(&touch_x, &touch_y);
        if(touch_y >= 0 && touch_y <= WIDTH - 170 && touch_x >= HEIGHT - 50 && touch_x <= HEIGHT) {
            tft.fillScreen(TFT_BLACK);
            endScreen(unit[0].score, high_score, mode);

        }
        else if(!unit[0].is_active) {
            // if player died, display game over screen
            tft.fillScreen(TFT_BLACK);
            endScreen(unit[0].score, high_score, mode);
        }
    }
}

void engine() {
    /*
    Runs main engine thread, calls and controls other threads
    */
    if(start == 1) {
        menu();
    }
    else if(start == 0) {
        singleplayer();
    }
    else if(start == 3) {
        // if player chose high score
        high_score_show();
    }
}
