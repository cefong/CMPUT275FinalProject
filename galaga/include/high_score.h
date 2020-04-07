#ifndef __HIGH_SCORE_H
#define __HIGH_SCORE_H

#include "common.h"
#include <EEPROM.h>


void high_score_put(high_score h);
void high_score_clear();
void high_score_get(high_score* h);
uint32_t high_score_init(int lives);



#endif