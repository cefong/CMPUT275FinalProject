#include "engine.h"
#include "character.h"
#include "multiplayer.h"
extern bullet ammo[PLAY_NUM_BULLET];
extern player_alien bot_loc[BOT_NUM];
// define structs and initial variables
static int start = 1;
static int selection = 0;
static int cur_score = 0;

// for singleplayer
static void main_screen_init() {
    // initialize basic screen
    tft.fillScreen(TFT_BLACK);
    tft.fillRect(0, 50, WIDTH, 5, TFT_PURPLE);
    tft.fillRect(0, HEIGHT - 50, WIDTH, 5, TFT_PURPLE);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.setCursor(10, 10);
    tft.setTextSize(2);
    tft.print("HIGH SCORE");
    tft.setCursor(200, 10);
    tft.setTextSize(2);
    tft.print("SCORE");
    tft.setCursor(200, 30);
    tft.print(cur_score);

}
// for multiplayer
static void multi_screen_init() {
    // initialize basic screen
    tft.fillScreen(TFT_BLACK);
    tft.fillRect(0, 50, WIDTH, 5, TFT_PURPLE);
    tft.fillRect(0, HEIGHT - 50, WIDTH, 5, TFT_PURPLE);

}

static void high_score_show() {
    /*
    Shows high schore on the top of the screen
    */
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
    tft.print(cur_score);

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

int show_lives_selection() {
    tft.fillScreen(TFT_BLACK);
    int lives_select = 0;
    while(1) {
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
            tft.setTextColor(TFT_BLACK, TFT_WHITE);
            tft.setCursor(110, 200);
            tft.print("ROOKIE");
            tft.setTextColor(TFT_WHITE, TFT_BLACK);
            tft.setCursor(50, 240);
            tft.print("INTERMEDIATE");
            tft.setTextColor(TFT_WHITE, TFT_BLACK);
            tft.setCursor(100, 280);
            tft.print("ADVANCED");
            break;
            case 1:
            tft.setTextColor(TFT_WHITE, TFT_BLACK);
            tft.setCursor(110, 200);
            tft.print("ROOKIE");
            tft.setTextColor(TFT_BLACK, TFT_WHITE);
            tft.setCursor(50, 240);
            tft.print("INTERMEDIATE");
            tft.setTextColor(TFT_WHITE, TFT_BLACK);
            tft.setCursor(100, 280);
            tft.print("ADVANCED");
            break;
            case 2:
            tft.setTextColor(TFT_WHITE, TFT_BLACK);
            tft.setCursor(110, 200);
            tft.print("ROOKIE");
            tft.setTextColor(TFT_WHITE, TFT_BLACK);
            tft.setCursor(50, 240);
            tft.print("INTERMEDIATE");
            tft.setTextColor(TFT_BLACK, TFT_WHITE);
            tft.setCursor(100, 280);
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

void cast(player_alien*player1, player_alien*player2) {
    player2->x = player1->x;
    player2->y = player1->y;
    player2->is_fire = player1->is_fire;
    player2->is_active = player1->is_active;
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
        player_alien player;
        player.lives = show_lives_selection();
        main_screen_init();
        // initialize player and bot structs and positions    
        player.x = WIDTH/2;
        player.y = HEIGHT-70;
        player.is_active = false;
        bot_loc[0].x = WIDTH/2;
        bot_loc[0].y = 80;
        bot_loc[0].is_active = true;
        int x_temp_p, x_temp_b, y_temp_b;
        int firstRun = 0;
        while(start == 0){
            // start player and bot threads
            chMsgSend(player_thread, start);
            chMsgSend(bot_thread, start);
            // draw the spaceships for player and bot
            drawSpaceship(&player, x_temp_p, player.y, SCALE);
            drawSpaceship(&bot_loc[0], x_temp_b, y_temp_b, SCALE);
            // update bot and player positions
            x_temp_b = bot_loc[0].x;
            x_temp_p = player.x;
            y_temp_b = bot_loc[0].y;
            // handle bullets      
            bullet_update(&bot_loc[0],&player);
            chMsgWait();
            // update player
            player_alien* player_temp = (player_alien*)chMsgGet(player_thread);
            cast(player_temp, &player);
            chMsgRelease(player_thread, (msg_t)&player_temp);
            if(player.is_fire) {
                // if player is firing, fire a bullet from player position
                Serial.println("fire");
                fire_bullet(&player);
            }
            if(bot_loc[0].is_active) {
                if(bot_loc[0].is_fire) {
                    // if bot is firing, fire a bullet from alien position
                    fire_bullet(&bot_loc[0]);
                }
            }

        }
    }
    else if(start == 2) {
        // multiplayer
        tft.fillScreen(TFT_BLACK);
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
            tft.print("Success!");
            multi_screen_init();
   
        }
        static player_alien *player1;
        static player_alien *player2;   
        int x_temp_1, x_temp_2;
        while(start == 2) {
            // start player threads
            chMsgSend(player_thread, start);
            chMsgSend(player2_thread, start);
            // draw Spaceships are player positions
            drawSpaceship(player1, x_temp_1, player1->y, SCALE);
            drawSpaceship(player2, x_temp_2, player2->y, SCALE);
            // handle bullets
            bullet_update(player1,player2);
            // update player positions
            x_temp_2 = player2->x;
            x_temp_1 = player1->x;

            chMsgWait();
            // update player1
            player1 = (player_alien*)chMsgGet(player_thread);
            chMsgRelease(player_thread, (msg_t)&player1);
            chMsgWait();
            // update player2
            player2 = (player_alien*)chMsgGet(player2_thread);
            chMsgRelease(player2_thread, (msg_t)&player2);

            if(player1->is_fire) {
                // if player1 is firing, fire a bullet from player1 position
                fire_bullet(player1);
            }
            if(player2->is_fire) {
                // if player2 is firing, fire a bullet from player2 position
                fire_bullet(player2);
            }
        }
    }
}
