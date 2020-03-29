#include "engine.h"
static int start = 1;
static int selection = 0;
struct player_stats {
    int health = 3;
    int x;
    int y;
};

void main_screen_init() {
    tft.fillScreen(TFT_BLACK);
    tft.drawLine(0, 30, WIDTH, 30, TFT_RED);
    tft.drawLine(0, HEIGHT - 50, WIDTH, HEIGHT - 50, TFT_RED);
    tft.setCursor(10, 10);
    tft.setTextSize(2);
    tft.print("HIGH SCORE: ");
}






void engine() {
    while(1) {
        if(start == 1) {
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
                start = 0;
            }
            
        }
        else {
            main_screen_init();
            loc *player;
            Serial.println(start);
            while(start == 0){
                chMsgSend(player_thread, start);
                chMsgWait();       
                player = (loc*)chMsgGet(player_thread);
                chMsgRelease(player_thread, (msg_t)&player);
                Serial.println(player->x);
                eventmask_t butt_trig = chEvtWaitAnyTimeout(ALL_EVENTS, 0);
                if(butt_trig) {
                    Serial.println("fire triggered");
                }
                //Serial.println(player->y);
            }
        }
    }
}