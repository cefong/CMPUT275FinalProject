/*
Names: Claire Martin (1571140), Celine Fong (1580124), Minh Dang, Zi Xue Lim
CMPUT 275, Winter 2020

Final Project: A Variation on 'Galaga'
high_score.cpp: Makes use of the EEPROM to store high scores
*/
#include "high_score.h"

static int eeAdr = 0;

void high_score_get(high_score* h) {
    high_score temp;
    EEPROM.get(eeAdr, temp);
    h->rookie = temp.rookie;
    h->intermediate = temp.intermediate;
    h->advanced = temp.advanced;
}

uint32_t high_score_init(int lives) {
    high_score temp;
    high_score_get(&temp);
    if(lives == 1) {
        return temp.advanced;
    }
    else if(lives == 3) {
        return temp.intermediate;
    }
    else if(lives == 5) {
        return temp.rookie;
    }
}

void high_score_put(high_score h) {
    EEPROM.put(eeAdr, h);
}

// trigger mass clearing of eeprom
void high_score_clear() {
    high_score clear = {0, 0, 0};
    high_score_put(clear);
}