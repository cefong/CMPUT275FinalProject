/*
Names: Claire Martin (1571140), Celine Fong (1580124), Minh Dang, Zi Xue Lim
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

#endif