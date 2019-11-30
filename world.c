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
    joypad_value.joypad_val = joypad();
}

void player_tick( worldBlock *pPlayer, joypad_input *pJoypad )
{
    UINT8 JOY_VALUE = pJoypad->joypad_val;
    int NEXT_Y = 0;
    int NEXT_X = 0;

    if ( JOY_VALUE & J_UP )
    {
        pPlayer->yVel = -2;
    }
    else if ( JOY_VALUE & J_DOWN )
    {
        pPlayer->yVel = 2;
    }
    else
        pPlayer->yVel = 0;

    if ( JOY_VALUE & J_RIGHT )
    {
        pPlayer->xVel = 2;
    }
    else if ( JOY_VALUE & J_LEFT )
    {
        pPlayer->xVel = -2;
    }
    else
        pPlayer->xVel = 0;

    NEXT_Y = (pPlayer->y + pPlayer->yVel);
    NEXT_X = (pPlayer->x + pPlayer->xVel);

    if ( MINWNDPOSY <= NEXT_Y && NEXT_Y <= MAXWNDPOSY )
        pPlayer->y += pPlayer->yVel;
    else if ( MINWNDPOSY <= NEXT_Y )
        pPlayer->y = MINWNDPOSY;
    else if ( MAXWNDPOSY >= NEXT_Y )
        pPlayer->y = MAXWNDPOSY;
    
    if ( MINWNDPOSX <= NEXT_X && NEXT_X <= MAXWNDPOSX )
        pPlayer->x += pPlayer->xVel;
    else if ( MINWNDPOSX <= NEXT_X )
        pPlayer->x = MINWNDPOSX;
    else if ( MAXWNDPOSX >= NEXT_X )
        pPlayer->x = MAXWNDPOSX;
}