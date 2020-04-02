#include "engine.h"
#include "character.h"
#include "multiplayer.h"

// define structs and initial variables
static int start = 1;
static int selection = 0;
static int cur_score = 0;
static player_stats *player1;
static player_stats *player2;  

// for singleplayer
static void main_screen_init() {
    // initialize basic screen
    tft.fillScreen(TFT_BLACK);
    tft.fillRect(0, 50, WIDTH, 5, TFT_PURPLE);
    tft.fillRect(0, HEIGHT - 50, WIDTH, 5, TFT_PURPLE);
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
    player1->lives = 1;
    player2->lives = 1;
    Serial.end();
    Serial.begin(9600);
    Serial.println("R");
    if(wait_timeout(1,500)) {
        char r = Serial.read();
        if(r == 'A') {
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
        main_screen_init();
        // initialize player and bot structs and positions
        player_stats *player;
        alien *bot;
        player->x = WIDTH/2;
        player->y = HEIGHT-70;
        bot->x = WIDTH/2;
        bot->y = 70;
        int x_temp_p, x_temp_b, y_temp_b;
        while(start == 0){
            // start player and bot threads
            chMsgSend(player_thread, start);
            chMsgSend(bot_thread, start);
            // draw the spaceships for player and bot
            drawSpaceship(player->x, player->y, x_temp_p, player->y, SCALE, true);
            drawSpaceship(bot->x, bot->y, x_temp_b, y_temp_b, SCALE, false);
            // update bot and player positions
            x_temp_b = bot->x;
            x_temp_p = player->x;
            y_temp_b = bot->y;
            // handle bullets
            bullet_update();

            chMsgWait();
            // update player
            player = (player_stats*)chMsgGet(player_thread);
            chMsgRelease(player_thread, (msg_t)&player);

            chMsgWait();
            // update bot
            bot = (alien*)chMsgGet(bot_thread);
            chMsgRelease(bot_thread, (msg_t)&bot);

            if(player->is_fire) {
                // if player is firing, fire a bullet from player position
                fire_bullet(true, player->x, player->y);
            }
            if(bot->is_fire) {
                // if bot is firing, fire a bullet from alien position
                fire_bullet(false, bot->x, bot->y);
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
        int x_temp_1, x_temp_2;
        while(start == 2) {
            // start player threads
            chMsgSend(player_thread, start);
            chMsgSend(player2_thread, start);
            // draw Spaceships are player positions
            drawSpaceship(player1->x, player1->y, x_temp_1, player1->y, SCALE, true);
            drawSpaceship(player2->x, player2->y, x_temp_2, player2->y, SCALE, false);
            // handle bullets
            bullet_update();
            // update player positions
            x_temp_2 = player2->x;
            x_temp_1 = player1->x;

            chMsgWait();
            // update player1
            player1 = (player_stats*)chMsgGet(player_thread);
            chMsgRelease(player_thread, (msg_t)&player1);

            chMsgWait();
            // update player2
            player2 = (player_stats*)chMsgGet(player2_thread);
            chMsgRelease(player2_thread, (msg_t)&player2);

            if(player1->is_fire) {
                // if player1 is firing, fire a bullet from player1 position
                fire_bullet(true, player1->x, player1->y);
            }
            if(player2->is_fire) {
                // if player2 is firing, fire a bullet from player2 position
                fire_bullet(false, player2->x, player2->y);
            }
        }
    }
}
