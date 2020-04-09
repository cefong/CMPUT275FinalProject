/*
Names: Claire Martin (1571140), Celine Fong (1580124), Minh Dang, Zi Xue Lim
CMPUT 275, Winter 2020

Final Project: A Variation on 'Galaga'
high_score.h: Header for high_score.cpp, includes EEPROM library
*/

#ifndef __HIGH_SCORE_H
#define __HIGH_SCORE_H

#include "common.h"
#include <EEPROM.h>


void high_score_put(high_score h);
void high_score_clear();
void high_score_get(high_score* h);
uint32_t high_score_init(int lives);



#endif