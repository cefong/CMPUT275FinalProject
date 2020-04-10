/*
Names: Claire Martin (1571140), Celine Fong, Minh Dang, Zi Xue Lim
CMPUT 275, Winter 2020

Final Project: A Variation on 'Galaga'
high_score.cpp: Handles storing and updating high scores on Arduino permanent memory
*/

#include "high_score.h"

static int eeAdr = 0;


void high_score_get(high_score* h) {
    /* 
    Gets the high score for a given level from permanent memory

    PARAMETERS:
        h: the chosen level
    */
    high_score temp;
    // get score from EEPROM
    EEPROM.get(eeAdr, temp);
    // update scores for each level
    h->rookie = temp.rookie;
    h->intermediate = temp.intermediate;
    h->advanced = temp.advanced;
}


uint32_t high_score_init(int lives) {
    /* 
    Initialize high scores for given level

    PARAMETERS:
        lives: level chosen (1,3,5)
    */
    high_score temp;
    // get high score for level
    high_score_get(&temp);
    // update scores accordingly
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
    /* 
    Puts a high score into the permanent memory

    PARAMETERS:
        h: given high score to be added
    */
    EEPROM.put(eeAdr, h);
}


void high_score_clear() {
    /* 
    Trigger mass clearing of EEPROM
    */
    high_score clear = {0, 0, 0};
    high_score_put(clear);
}