#include "world.h"

#include <string.h>

worldBlock player1;

joypad_input joypad_value;

BYTE isDEAD = 0;

const char blankmap = 0x00;

BYTE player_tick( worldBlock *pPlayer, joypad_input *pJoypad );
BYTE player_checkCollision( worldBlock *pPlayer );

void world_init( void )
{
    loadMem_init();

    player1.spriteID = 0;
    player1.x = 8*10;
    player1.y = 8*9;
    player1.xAnim = 8*10;
    player1.yAnim = 8*9;
    player1.anim_step = 1;

    joypad_value.joypad_val = 0;
    SHOW_SPRITES;
    
}

void world_draw( void )
{
    static BYTE firstTick = 0;
    UINT8 X = 0;
    UINT8 Y = 0;

    if ( firstTick == 0 )
    {
        firstTick = 1;
        set_sprite_tile( 0, 1 );
        move_sprite( player1.spriteID, (UINT8)player1.xAnim, (UINT8)player1.yAnim );
    }

    if ( player1.xAnim != player1.x || player1.yAnim != player1.y )
    {
        if ( player1.x > player1.xAnim )
        {
            set_sprite_tile( 0, 13 );
            player1.xAnim += player1.anim_step;
            set_sprite_prop( player1.spriteID, get_sprite_prop(player1.spriteID) & ~S_FLIPX );
        }
        else if ( player1.x < player1.xAnim )
        {
            set_sprite_tile( 0, 13 );
            player1.xAnim -= player1.anim_step;
            set_sprite_prop( player1.spriteID, get_sprite_prop(player1.spriteID) | S_FLIPX );
        }
        
        if ( player1.y > player1.yAnim )
        {
            set_sprite_tile( 0, 1 );
            player1.yAnim += player1.anim_step;
            set_sprite_prop( player1.spriteID, get_sprite_prop(player1.spriteID) | S_FLIPY );
        }
        else if ( player1.y < player1.yAnim )
        {
            set_sprite_tile( 0, 1 );
            player1.yAnim -= player1.anim_step;
            set_sprite_prop( player1.spriteID, get_sprite_prop(player1.spriteID) & ~S_FLIPY );
        }

        move_sprite( player1.spriteID, (UINT8)player1.xAnim, (UINT8)player1.yAnim );
    }
}


void world_tick( void )
{
    BYTE x = player1.x;
    BYTE y = player1.y;

    if ( player_tick( &player1, &joypad_value ) )
    {
        loadMem_setTile( x , y, 0x02 );
    }
}


void world_setJoyPad( UBYTE joypadVal )
{
    joypad_value.joypad_val |= joypadVal;
}


#define MOVE_SIZE 8
BYTE player_tick( worldBlock *pPlayer, joypad_input *pJoypad )
{
    UINT8 JOY_VALUE = pJoypad->joypad_val;
    UINT8 NEXT_Y = 0;
    UINT8 NEXT_X = 0;
    BYTE ret = 0;

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

    joypad_value.joypad_val = 0;

    NEXT_Y = ((UINT8)pPlayer->y + (UINT8)pPlayer->yVel);
    NEXT_X = ((UINT8)pPlayer->x + (UINT8)pPlayer->xVel);

    if ( 40 <= NEXT_Y && NEXT_Y <= 128 )
    {
        pPlayer->y += pPlayer->yVel;
        ret |= 0x01;
    }

    if ( 32 <= NEXT_X && NEXT_X <= 136 )
    {
        pPlayer->x += pPlayer->xVel;
        ret |= 0x02;
    }

    

/*
    if ( 16 <= NEXT_Y && NEXT_Y <= 152 )
        pPlayer->y += pPlayer->yVel;

    if ( 8 <= NEXT_X && NEXT_X <= 160 )
        pPlayer->x += pPlayer->xVel;
*/
    //printf("X: %u Y: %u\n", (unsigned int)NEXT_X, (unsigned int)NEXT_Y);
    return ret;
}

BYTE player_checkCollision( worldBlock *pPlayer )
{


}

