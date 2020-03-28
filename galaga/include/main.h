#include <Arduino.h>
#ifndef __MAIN_H
#define __MAIN_H

#include <Adafruit_GFX.h>
#include <MCUFRIEND_kbv.h>
#include <SPI.h>
#include "common.h"
#include "player.h"
#include "engine.h"

thread_t *player_thread;
thread_t *bot_thread;
thread_t *engine_thread;

MCUFRIEND_kbv tft;


#endif