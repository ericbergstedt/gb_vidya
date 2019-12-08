
#include <gb/gb.h>
#include <stdio.h>

#include <gb/gb.h>
#include <gb/console.h>
#include <stdio.h>
#include <string.h>


#include "world.h"

volatile UBYTE vbl_cnt, tim_cnt, joy_active;


void vbl()
{
  /* Upon IRQ, interrupts are automatically disabled */
  vbl_cnt++;
}

void tim()
{
  /* Upon IRQ, interrupts are automatically disabled */
  tim_cnt++;
}

void joy()
{
  joy_active++;
}

void print_counter()
{
  static UBYTE cnt_last = 0;
  static UBYTE cntDraw = 0;

  //static UBYTE lastJoypad = 0;

  UBYTE cnt = 0;
  UBYTE joypad_get = 0x00;
  UINT8 worldDraw = 0;

  /* Ensure mutual exclusion (not really necessary in this example)... */
  disable_interrupts();
  cnt = tim_cnt;
  joypad_get = joy_active;
  enable_interrupts();

  if ( joypad_get != 0x00 )
  {
    joypad_get = joypad();
    world_setJoyPad( joypad_get );
    disable_interrupts();
    joy_active = 0;
    enable_interrupts();
  }

  if ( cnt != cnt_last )
  {
    cnt_last = cnt;
    cntDraw++;
    

    /* interrupt based user input is just going to have to wait for now
    if ( joypad != lastJoypad )
    {
      world_setJoyPad(joypad);
      lastJoypad = joypad;
    }
    */
  }

  if ( cnt >= 16  )
  {
    disable_interrupts();
    tim_cnt = 0;
    enable_interrupts();
    worldDraw = 1;
  }

  if ( worldDraw > 0 )
  {
    world_tick();
  }

  if ( cntDraw >= 1  )
  {
    world_draw();
    cntDraw = 0;
  }
  

  /* Ensure mutual exclusion (not really necessary in this example)... */
  disable_interrupts();
  cnt = vbl_cnt;
  enable_interrupts();

  //printf("- VBL %u\n", (unsigned int)cnt);
}

void main()
{
  /* Ensure mutual exclusion (not really necessary in this example)... */
  disable_interrupts();
  vbl_cnt = tim_cnt = 0;
  add_VBL(vbl);
  add_TIM(tim);
  //add_JOY(joy);
  enable_interrupts();

  /* Set TMA to divide clock by 128 */
  TMA_REG = 0x80U;
  /* Set clock to 4096 Hertz */
  TAC_REG = 0x04U;
   // Timer will trigger 32 times a second


  /* Handle VBL and TIM interrupts */
  //set_interrupts( VBL_IFLAG | TIM_IFLAG | JOY_IFLAG );
  set_interrupts( VBL_IFLAG | TIM_IFLAG );


  world_init();
  world_draw();

  while(1) {
    print_counter();
    wait_vbl_done();
    world_setJoyPad( joypad() );
  }
}
