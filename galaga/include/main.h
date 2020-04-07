/*
Names: Claire Martin (1571140), Celine Fong, Minh Dang, Zi Xue Lim
CMPUT 275, Winter 2020

Final Project: A Variation on 'Galaga'
main.h: Includes all necessary libraries as well as linking all threads together
*/

#ifndef __MAIN_H
#define __MAIN_H

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include "MCUFRIEND_kbv.h"
#include <SPI.h>
#include "common.h"
#include "player.h"
#include "engine.h"
#include "bot.h"
#include "multiplayer.h"

// include threads
thread_t *player_thread;
thread_t *player2_thread;
thread_t *engine_thread;
thread_t *bot_thread;

// include tft display
MCUFRIEND_kbv tft;


#endif