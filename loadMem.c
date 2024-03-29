
#ifndef LOADMEM_
#define LOADMEM_

#include <gb/gb.h>
#include <stdio.h>

#include "loadMem.h"


void loadMem_init( void )
{
    set_sprite_data( 0, 15, gameTitles );
    set_sprite_tile( 0, 1 );

    set_bkg_data( 0, 13, gameTitles );
    set_bkg_tiles( 0, 0, gameBgWidth, gameBgHeight, gameBg );

    SHOW_BKG;
    SHOW_SPRITES;
    DISPLAY_ON;
}

void loadMem_setTile( BYTE x , BYTE y, BYTE tile )
{
    gameBg[ (((UINT16)x-8)/8) + (((UINT16)y-16)/8) * 20 ] = tile;

    set_bkg_tiles( 0, 0, gameBgWidth, gameBgHeight, gameBg );
}

BYTE loadMem_getTile( BYTE x, BYTE y )
{
    return gameBg[ (((UINT16)x-8)/8) + (((UINT16)y-16)/8) * 20 ];
}

void loadMem_clearAllTileID( BYTE tileID )
{
    UINT16 i = 0;
    UINT16 max = gameBgHeight * gameBgWidth;

    for ( i = 0 ; i < max ; i ++ )
    {
        if ( gameBg[ i ] == 0x02 )
        {
            gameBg[ i ] = 0x00;
        }
    }
    set_bkg_tiles( 0, 0, gameBgWidth, gameBgHeight, gameBg );
}

#endif 
