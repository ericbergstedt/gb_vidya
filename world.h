
#include <gb/gb.h>
#include <stdio.h>

#include "loadMem.h"

typedef struct world_block_ {
    UINT8 spriteID;
    int x;
    int y;
    int xVel;
    int yVel;
} worldBlock;


typedef struct joypad_input_ {
    UINT8 joypad_val;
} joypad_input;

void world_init( void );

// game Logic
void world_tick( void );

// draw game
void world_draw( void );

void world_getJoyPad( void );
