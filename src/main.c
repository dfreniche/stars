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
   sys_physics_init();
   sys_generator_init();
   sys_render_init();
   manager_entity_init();

   while (1) {
      sys_physics_update();
      sys_generator_update();
      sys_render_update();
      manager_entity_update();

      cpct_scanKeyboard_f();

      if (cpct_isKeyPressed(Key_CursorRight)) {
         sys_physics_change_x_axis_movement_left_to_right();
         sys_generator_left();
      } else if (cpct_isKeyPressed(Key_CursorLeft)) {
         sys_physics_change_x_axis_movement_right_to_left();
         sys_generator_right();
      } else if (cpct_isKeyPressed(Key_CursorUp)) {
         sys_physics_change_y_axis_movement_bottom_to_top();
         sys_generator_bottom();
      } else if (cpct_isKeyPressed(Key_CursorDown)) {
         sys_physics_change_y_axis_movement_top_to_bottom();
         sys_generator_top();
      }

      cpct_waitVSYNC();

      // wait(1); // wait 10 times each frame, instead of 50 frames / sec we go for 5 frames / sec 
   }
}
