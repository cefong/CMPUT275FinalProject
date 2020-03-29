#ifndef __COMMON_H
#define __COMMON_H

#include "ChRt.h"
#include "Arduino.h"

struct loc {
    int x;
    int y;
};
#define WIDTH           320
#define HEIGHT          480

#define JOY_CENTER      512
#define JOY_DEADZONE    64

#define JOY_HORZ        A10
#define JOY_VERT        A8
#define BUTT            21

#define speed           4
#define player_size     8

#endif