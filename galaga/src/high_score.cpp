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
    for(int i = 0; i < EEPROM.length(); i++) {
        EEPROM.write(i, 0);
    }
}