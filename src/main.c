#include <cpctelera.h>

#include "managers/entity.h"
#include "system/physics.h"
#include "system/render.h"

void wait(u8 n) {
   do {
      cpct_waitHalts(2);
      cpct_waitVSYNC();
   } while (--n);
}

void main(void) {
   cpct_disableFirmware();
   cpct_setVideoMode(0);
   cpct_setBorder(HW_BLACK);
   cpct_setPALColour(0, HW_BLACK);

   manager_entity_init();

   create_init_entities();   

   while (1) {
      sys_physics_update();
      sys_render_update();
      wait(20); // wait 10 times each frame, instead of 50 frames / sec we go for 5 frames / sec 
   }
}
