#include "world.h"

#include "loadMem.h"

worldBlock player1;

joypad_input joypad_value;

void player_tick( worldBlock *pPlayer, joypad_input *pJoypad );

void world_init( void )
{
    loadMem_init();

    player1.spriteID = 0;
    player1.x = 8;
    player1.y = 16;

    joypad_value.joypad_val = 0;

    SHOW_SPRITES;
}

void world_draw( void )
{
    move_sprite( player1.spriteID, (UINT8)player1.x, (UINT8)player1.y );
    
}


void world_tick( void )
{
    world_getJoyPad();
    player_tick( &player1, &joypad_value );
}


void world_getJoyPad( void )
{
    joypad_value.joypad_val |= joypad();
}

#define MOVE_SIZE 8
void player_tick( worldBlock *pPlayer, joypad_input *pJoypad )
{
    UINT8 JOY_VALUE = pJoypad->joypad_val;
    UINT8 NEXT_Y = 0;
    UINT8 NEXT_X = 0;

    switch ( JOY_VALUE )
    {
        case (J_UP):
            pPlayer->yVel = -MOVE_SIZE;
            pPlayer->xVel = 0;
            break;
        case (J_DOWN):
            pPlayer->yVel = MOVE_SIZE;
            pPlayer->xVel = 0;
            break;
        case (J_RIGHT):
            pPlayer->xVel = MOVE_SIZE;
            pPlayer->yVel = 0;
            break;
        case (J_LEFT):
            pPlayer->xVel = -MOVE_SIZE;
            pPlayer->yVel = 0;
            break;
    }

    disable_interrupts();
    joypad_value.joypad_val = 0;
    enable_interrupts();

    NEXT_Y = ((UINT8)pPlayer->y + (UINT8)pPlayer->yVel);
    NEXT_X = ((UINT8)pPlayer->x + (UINT8)pPlayer->xVel);


    if ( 16 <= NEXT_Y && NEXT_Y <= 152 )
        pPlayer->y += pPlayer->yVel;

    if ( 8 <= NEXT_X && NEXT_X <= 160 )
        pPlayer->x += pPlayer->xVel;

    //printf("X: %u Y: %u\n", (unsigned int)NEXT_X, (unsigned int)NEXT_Y);
}