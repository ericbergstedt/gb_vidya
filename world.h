
#include <gb/gb.h>
#include <stdio.h>

#include "loadMem.h"

typedef struct world_block_ {
    UINT8 spriteID;
    UINT8 x;
    UINT8 y;
    UINT8 xVel;
    UINT8 yVel;

    UINT8 xAnim;
    UINT8 yAnim;
    UINT8 anim_step;
} worldBlock;


typedef struct joypad_input_ {
    UINT8 joypad_val;
} joypad_input;

void world_init( void );

// game Logic
void world_tick( void );

// draw game
void world_draw( void );

void world_setJoyPad( UBYTE joypadVal );

