
#include <gb/gb.h>
#include <stdio.h>

#include "loadMem.h"

typedef enum faceDirection_
{
    DIR_RIGHT,
    DIR_LEFT,
    DIR_UP,
    DIR_DOWN,
    DIR_UNDEF
} faceDirection;

typedef enum anim_type
{
    ANIMATE_SLIDE,      // Slides into position
    ANIMATE_JUMP       // Has no in between frames, jumps to the location
};

typedef struct world_block_ {
    UINT8 isActive;

    UINT8 spriteID;
    UINT8 x;
    UINT8 y;
    UINT8 xVel;
    UINT8 yVel;

    UINT8 xAnim;
    UINT8 yAnim;
    UINT8 anim_step;

    struct worldBlock *pNextBlock;
} worldBlock;



typedef struct character_
{
    UINT8 lastPosX;
    UINT8 lastPoxY;
    faceDirection direction;
    worldBlock drawData;
} character;


typedef struct joypad_input_ {
    UINT8 joypad_val;
} joypad_input;

void world_init( void );

// game Logic
void world_tick( void );

// draw game
void world_draw( void );

void world_setJoyPad( UBYTE joypadVal );

