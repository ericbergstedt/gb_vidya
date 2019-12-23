#ifndef LOADMEM__
#define LOADMEM__

#include "gameTitles.h"
#include "gameBG.h"

#define TILE_EMPTY 0x00

void loadMem_init( void );

void loadMem_setTile( BYTE x , BYTE y, BYTE tile );

BYTE loadMem_getTile( BYTE x, BYTE y );

void loadMem_clearAllTileID( BYTE tileID );

#endif



