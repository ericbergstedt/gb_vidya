#include "world.h"

#include <string.h>
#include <rand.h>

character player1;

joypad_input joypad_value;

BYTE isDEAD = 0;

const char blankmap = 0x00;

BYTE player_tick( character *pPlayer, joypad_input *pJoypad );
BYTE player_checkCollision( character *pPlayer );
void world_restart( void );

void world_setApple( void );

void world_init( void )
{
    loadMem_init();

    player1.drawData.spriteID = 0;
    player1.drawData.x = 8*10;
    player1.drawData.y = 8*9;
    player1.drawData.xAnim = 8*10;
    player1.drawData.yAnim = 8*9;
    player1.drawData.anim_step = 1;

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
        move_sprite( player1.drawData.spriteID, (UINT8)player1.drawData.xAnim, (UINT8)player1.drawData.yAnim );
    }

    if ( player1.drawData.xAnim != player1.drawData.x || player1.drawData.yAnim != player1.drawData.y )
    {
        if ( player1.drawData.x > player1.drawData.xAnim )
        {
            set_sprite_tile( 0, 1);
            player1.drawData.xAnim += player1.drawData.anim_step;
            set_sprite_prop( player1.drawData.spriteID, get_sprite_prop(player1.drawData.spriteID) & ~S_FLIPX );
        }
        else if ( player1.drawData.x < player1.drawData.xAnim )
        {
            set_sprite_tile( 0, 1 );
            player1.drawData.xAnim -= player1.drawData.anim_step;
            set_sprite_prop( player1.drawData.spriteID, get_sprite_prop(player1.drawData.spriteID) | S_FLIPX );
        }
        
        if ( player1.drawData.y > player1.drawData.yAnim )
        {
            set_sprite_tile( 0, 1 );
            player1.drawData.yAnim += player1.drawData.anim_step;
            set_sprite_prop( player1.drawData.spriteID, get_sprite_prop(player1.drawData.spriteID) | S_FLIPY );
        }
        else if ( player1.drawData.y < player1.drawData.yAnim )
        {
            set_sprite_tile( 0, 1 );
            player1.drawData.yAnim -= player1.drawData.anim_step;
            set_sprite_prop( player1.drawData.spriteID, get_sprite_prop(player1.drawData.spriteID) & ~S_FLIPY );
        }

        move_sprite( player1.drawData.spriteID, (UINT8)player1.drawData.xAnim, (UINT8)player1.drawData.yAnim );
    }
}

void world_setApple( void )
{
    INT16 randX = (rand() * (UINT16)gameBgWidth) / (char)0xFF;
    INT16 randY = (rand() * (UINT16)gameBgHeight) / (char)0xFF;

    while( 1 )
    {
        if ( gameBg[ randX * randY ] = 0x00 )
        {
            gameBg[ randX * randY ] = 14;
            break;
        }
        else
        {
            randX = (rand() * gameBgWidth) / (char)0xFF;
            randY = (rand() * gameBgWidth) / (char)0xFF;
        }
        
    }
}

void world_restart( void )
{
    loadMem_clearAllTileID( 0x02 );
}

void world_tick( void )
{
    BYTE x = player1.drawData.x;
    BYTE y = player1.drawData.y;

    if ( player_tick( &player1, &joypad_value ) )
    {
        loadMem_setTile( x , y, 0x02 );
    }
    else 
    {
        // reload the world
        world_restart();
    }
}


void world_setJoyPad( UBYTE joypadVal )
{
    joypad_value.joypad_val = joypadVal;
}


#define MOVE_SIZE 8
BYTE player_tick( character *pPlayer, joypad_input *pJoypad )
{
    UINT8 JOY_VALUE = pJoypad->joypad_val;
    UINT8 NEXT_Y = 0;
    UINT8 NEXT_X = 0;
    BYTE ret = 0;

    switch ( JOY_VALUE )
    {
        case (J_UP):
            pPlayer->drawData.yVel = -MOVE_SIZE;
            pPlayer->drawData.xVel = 0;
            break;
        case (J_DOWN):
            pPlayer->drawData.yVel = MOVE_SIZE;
            pPlayer->drawData.xVel = 0;
            break;
        case (J_RIGHT):
            pPlayer->drawData.xVel = MOVE_SIZE;
            pPlayer->drawData.yVel = 0;
            break;
        case (J_LEFT):
            pPlayer->drawData.xVel = -MOVE_SIZE;
            pPlayer->drawData.yVel = 0;
            break;
    }

    //joypad_value.joypad_val = 0;

    ret = player_checkCollision( pPlayer );

    return ret;
}

BYTE player_checkCollision( character *pPlayer )
{
    BYTE ret = 0;
    UINT8 NEXT_Y = ((UINT8)pPlayer->drawData.y + (UINT8)pPlayer->drawData.yVel);
    UINT8 NEXT_X = ((UINT8)pPlayer->drawData.x + (UINT8)pPlayer->drawData.xVel);

    if ( pPlayer != 0 )
    {
        if ( loadMem_getTile( NEXT_X, NEXT_Y ) == TILE_EMPTY )
        {
            ret = 0x01;
            pPlayer->drawData.y += pPlayer->drawData.yVel;
            pPlayer->drawData.x += pPlayer->drawData.xVel;
        }
    }

    return ret;
}

