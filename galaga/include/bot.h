/*
Names: Claire Martin (1571140), Celine Fong, Minh Dang, Zi Xue Lim
CMPUT 275, Winter 2020

Final Project: A Variation on 'Galaga'
bot.h: Links engine thread to bot thread
*/


#ifndef __BOT_H
#define __HOT_H

#include "common.h"

// include engine thread
extern thread_t *engine_thread;
void bot();
void bot2();

#endif