
#ifndef LOADMEM_
#define LOADMEM_

#include <gb/gb.h>
#include <stdio.h>

#include "loadMem.h"


void loadMem_init( void )
{
    set_sprite_data( 0, 12, gameTitles );
    set_sprite_tile( 0, 1 );

    set_bkg_data( 0, 12, gameTitles );
    set_bkg_tiles( 0,0, gameBgWidth, gameBgHeight, gameBg );

    SHOW_BKG;
    SHOW_SPRITES;
    DISPLAY_ON;
}




#endif 
