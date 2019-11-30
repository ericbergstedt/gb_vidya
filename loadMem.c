
#ifndef LOADMEM_
#define LOADMEM_

#include <gb/gb.h>
#include <stdio.h>

#include "gameSprites.h"

void loadMem_init( void )
{
    set_sprite_data( 0, blockBank, block );
    set_sprite_tile( 0, 0 );
}




#endif 
