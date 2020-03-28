#ifndef __PLAYER_H
#define __PLAYER_H

#include "Arduino.h"
#include "ChRt.h"

#define WIDTH           480
#define HEIGHT          320

#define JOY_CENTER      512
#define JOY_DEADZONE    64

#define JOY_VERT        A9
#define JOY_HORZ        A8

void player();
#endif