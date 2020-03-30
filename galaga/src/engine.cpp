#include "engine.h"
#include "character.h"

static bool start = true;
static int selection = 0;
static int cur_score = 0;
static void main_screen_init() {
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


void engine() {
    if(start) {
        chMsgSend(player_thread, start);
        tft.setCursor(35, 100);
        tft.setTextSize(7);
        tft.setTextColor(TFT_RED, TFT_BLACK);
        tft.print("GALAGA");
        tft.setTextSize(3);
        switch(selection){
            case 0:
            tft.setTextColor(TFT_BLACK, TFT_WHITE);
            tft.setCursor(110, 200);
            tft.print("PLAY");
            tft.setTextColor(TFT_WHITE, TFT_BLACK);
            tft.setCursor(80, 240);
            tft.print("HIGH SCORE");
            break;
            case 1:
            tft.setTextColor(TFT_WHITE, TFT_BLACK);
            tft.setCursor(110, 200);
            tft.print("PLAY");
            tft.setTextColor(TFT_BLACK, TFT_WHITE);
            tft.setCursor(80, 240);
            tft.print("HIGH SCORE");
            break;
            case 2:
            break;
        }
        chMsgWait();
        msg_t mess = chMsgGet(player_thread);
        selection += mess;
        if(selection > 1) selection = 0;
        if(selection < 0) selection = 1;
        chMsgRelease(player_thread, mess);
        eventmask_t butt_trig = chEvtWaitAnyTimeout(ALL_EVENTS, 0);
        if(butt_trig && selection == 0) {
            start = false;
        }
        
    }
    else {
        main_screen_init();
        loc *player;
        loc *bot;
        int x_temp_p, x_temp_b;
        while(start == 0){
            chMsgSend(player_thread, start);
            chMsgSend(bot_thread, start);
            draw_player(player->x, player->y, x_temp_p, player->y);
            draw_bot(bot->x, bot->y, x_temp_b, bot->y);
            x_temp_b = bot->x;
            x_temp_p = player->x;   
            bullet_update();
            chMsgWait();
            player = (loc*)chMsgGet(player_thread);
            chMsgRelease(player_thread, (msg_t)&player);
            chMsgWait();
            bot = (loc*)chMsgGet(bot_thread);
            chMsgRelease(bot_thread, (msg_t)&bot);
            if(player->is_fire) {
                fire_bullet(true, player->x, player->y);
            }
            if(bot->is_fire) {
                fire_bullet(false, bot->x, bot->y);
            }
        }
    }
}