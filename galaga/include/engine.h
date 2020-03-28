#ifndef __ENGINE_H
#define __ENGINE_H

#include <Adafruit_GFX.h>
#include <MCUFRIEND_kbv.h>
#include <SPI.h>
#include "common.h"
extern thread_t *engine_thread;
extern thread_t *player_thread;
extern thread_t *bot_thread;
void engine();
#endif