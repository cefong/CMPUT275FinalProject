#include "engine.h"
#include "character.h"
#include "multiplayer.h"
static int start = 1;
static int selection = 0;
static int lives_select = 0;
static int player_lives = 3;
static int cur_score = 0;
static player_stats *player1;
static player_stats *player2;  

// drawing a heart to display lives stat
static void drawHeart(int16_t anchorX, int16_t anchorY, int16_t scale, int16_t color = TFT_RED) {
    // anchor point in upper left corner
    tft.drawRect(anchorX, anchorY+2*scale, scale, 3*scale, color);
    tft.drawRect(anchorX+1*scale, anchorY+1*scale, scale, 5*scale, color);
    tft.drawRect(anchorX+2*scale, anchorY+1*scale, scale, 6*scale, color);
    tft.drawRect(anchorX+3*scale, anchorY+2*scale, scale, 6*scale, color);
    tft.drawRect(anchorX+4*scale, anchorY+3*scale, scale, 6*scale, color);
    tft.drawRect(anchorX+8*scale, anchorY+2*scale, scale, 3*scale, color);
    tft.drawRect(anchorX+7*scale, anchorY+1*scale, scale, 5*scale, color);
    tft.drawRect(anchorX+6*scale, anchorY+1*scale, scale, 6*scale, color);
    tft.drawRect(anchorX+5*scale, anchorY+2*scale, scale, 6*scale, color);   
}

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
    tft.setCursor(10, HEIGHT - 40);
    tft.print("LIVES");
    for (int i = 0; i < player_lives; i++) {
        drawHeart(10+i*30, HEIGHT - 20, 2);
    }
}

// for multiplayer
static void multi_screen_init() {
    // initialize basic screen
    tft.fillScreen(TFT_BLACK);
    tft.fillRect(0, 50, WIDTH, 5, TFT_PURPLE);
    tft.fillRect(0, HEIGHT - 50, WIDTH, 5, TFT_PURPLE);

}
static void high_score_show() {
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
    player1->lives = 1;
    player2->lives = 1;
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
    switch(selection){
        // toggle between PLAY and HIGH SCORE options
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

// lives selection for single player
void show_lives_selection() {
    tft.fillScreen(TFT_BLACK);
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
}

void engine() {
    if(start == 1) {
        // if we are just starting, display main screen
        chMsgSend(player_thread, start);
        tft.setCursor(35, 100);
        tft.setTextSize(7);
        tft.setTextColor(TFT_RED, TFT_BLACK);
        tft.print("GALAGA");
        tft.setTextSize(3);
        show_selection();
        chMsgWait();
        msg_t mess = chMsgGet(player_thread);
        selection -= mess;
        if(selection > 2) selection = 0;
        else if(selection < 0) selection = 2;
        chMsgRelease(player_thread, mess);
        eventmask_t butt_trig = chEvtWaitAnyTimeout(ALL_EVENTS, 0);
        if(butt_trig && selection == 0) {
            // if button is pressed and selected PLAY
            start = 0;
        }
        else if(butt_trig && selection == 1) {
            start = 2;
        }
    }
    else if(start == 0) {
        /* i messed something up here lol minh help
        show_lives_selection();
        chMsgWait();
        msg_t mess = chMsgGet(player_thread);
        lives_select -= mess;
        if(lives_select > 2) lives_select = 0;
        else if(lives_select < 0) lives_select = 2;
        chMsgRelease(player_thread, mess);
        eventmask_t butt_trig = chEvtWaitAnyTimeout(ALL_EVENTS, 0);
        if(butt_trig && lives_select == 0) {
            // if button is pressed and selected beginner
            player_lives = 5;
        }
        else if(butt_trig && lives_select == 1) {
            // if button is pressed and selected intermediate
            player_lives = 3;
        }
        else if (butt_trig && lives_select == 2) {
            // if button is pressed and selected advanced
            player_lives = 1;
        }
        */
        main_screen_init();
        // initialize player and bot
        player_stats *player;
        alien *bot;
        player->x = WIDTH/2;
        player->y = HEIGHT-70;
        player->lives = player_lives;
        bot->x = WIDTH/2;
        bot->y = 70;
        int x_temp_p, x_temp_b, y_temp_b;
        while(start == 0){
            chMsgSend(player_thread, start);
            chMsgSend(bot_thread, start);
            drawSpaceship(player->x, player->y, x_temp_p, player->y, SCALE, true);
            drawSpaceship(bot->x, bot->y, x_temp_b, y_temp_b, SCALE, false);
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
        tft.fillScreen(TFT_BLACK);
        while(!multiplayer_init()) {
            tft.setTextColor(TFT_WHITE, TFT_BLACK);
            tft.setCursor(30, 200);
            tft.setTextSize(2);
            tft.print("Waiting to connect...");
            eventmask_t butt_trig = chEvtWaitAnyTimeout(ALL_EVENTS, 0);
            if(butt_trig) {
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
            chMsgSend(player_thread, start);
            chMsgSend(player2_thread, start);
            drawSpaceship(player1->x, player1->y, x_temp_1, player1->y, SCALE, true);
            drawSpaceship(player2->x, player2->y, x_temp_2, player2->y, SCALE, false);
            bullet_update();
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
            // update player2

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
