/*
Names: Claire Martin (1571140), Celine Fong, Minh Dang, Zi Xue Lim
CMPUT 275, Winter 2020

Final Project: A Variation on 'Galaga'
engine.h: Header for engine.cpp, links to other threads
*/

#ifndef __ENGINE_H
#define __ENGINE_H

#include <Adafruit_GFX.h>
#include "MCUFRIEND_kbv.h"
#include <SPI.h>
#include "common.h"

// include threads
extern thread_t *engine_thread;
extern thread_t *player_thread;
extern thread_t *bot_thread;

// include tft display
extern MCUFRIEND_kbv tft;
void engine();

#endif