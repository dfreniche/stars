#include <cpctelera.h>

#include "managers/entity.h"
#include "system/physics.h"
#include "system/render.h"
#include "system/generator.h"

void wait(u8 n) {
   do {
      cpct_waitHalts(2);
      cpct_waitVSYNC();
   } while (--n);
}

void main(void) {
   sys_render_init();

   manager_entity_init();

   // create_init_entities();   

   while (1) {
      sys_physics_update();
      sys_generator_update();
      sys_render_update();
      manager_entity_update();

      wait(10); // wait 10 times each frame, instead of 50 frames / sec we go for 5 frames / sec 
   }
}
