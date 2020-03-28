#include "engine.h"
static int start = 1;
static int selection = 0;
struct player_stats {
    int health = 3;
    int x;
    int y;
};
void engine() {
    loc* player;
    loc bot[300];
    while(1) {
        if(start == 1) {
            tft.setCursor(50, 100);
            tft.setTextSize(10);
            tft.setTextColor(TFT_RED, TFT_BLACK);
            tft.print("GALAGA");
            tft.setTextSize(5);
            switch(selection){
                case 0:
                tft.setTextColor(TFT_BLACK, TFT_WHITE);
                tft.setCursor(120, 240);
                tft.print("Play");
                break;
                case 1:
                tft.setTextColor(TFT_WHITE, TFT_BLACK);
                tft.setCursor(120, 240);
                tft.print("Play");
                break;

                case 2:
                break;
            }
            tft.setTextColor(TFT_WHITE, TFT_BLACK);
            tft.setCursor(120, 240);
            tft.print("Play");
            thread_t *tp = chMsgWait();
            if(tp == player_thread) {
                chMsgSend(player_thread, (msg_t)&start);

            }
        }
        else {

        }
    }
}