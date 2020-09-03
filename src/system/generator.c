#include "generator.h"
#include "managers/entity.h"

// ----------------------------------------------------------------------------
// Variables
// ----------------------------------------------------------------------------

// template for new entities, quicker to copy this memory chunk
const Entity init_entity = {
   ENTITY_TYPE_DEFAULT, // type
   79, 1,               // x,y
   -1,                  // x speeed
   0x80,                // color
   0x00                 // prevptr
};

u8 start_x;
u8 start_y;

direction movement_direction;

// ----------------------------------------------------------------------------
// Private interface
// ----------------------------------------------------------------------------

// sets some init random values for our entities
void set_init_star_values(Entity *e) {
   i8 sign = -1;
   u8 abs_speed;

   e->type = ENTITY_TYPE_DEFAULT;

   if ( (movement_direction == TO_LEFT) || (movement_direction == TO_RIGHT) ) {
      e->x = start_x;
      e->y = cpct_rand() % 200;
   } else {
      e->x = cpct_rand() % 160;
      e->y = start_y;
   }
   if ( (movement_direction == TO_DOWN) || (movement_direction == TO_RIGHT) ) {
      sign = 1;
   }
   abs_speed = (cpct_rand() & 0x03);
   e->x_speed = sign + (sign*abs_speed); // we do a bitwise AND with 0b00000011. Any bits other than 11 are discarded 
   if (abs_speed == 0 ) {
      e->color = cpct_px2byteM0(2, 0); 
   } else if (abs_speed == 1) { 
      e->color = cpct_px2byteM0(3, 0); 
   } else {
      e->color = cpct_px2byteM0(1, 1); 
   }
}

// ----------------------------------------------------------------------------
// Public interface
// ----------------------------------------------------------------------------

void sys_generator_init() {
   start_x = 79;
   start_y = 0;
   movement_direction = TO_LEFT;
}

// Initializes all entities in the global array
// creates them and initialized them
void create_init_entities(int num_entities) {
   for (u8 i = 0; i < num_entities; i++) {
      Entity *e = manager_entity_create();            // create all entities
      cpct_memcpy(e, &init_entity, sizeof(Entity));   // copy from template
      set_init_star_values(e);              // choose some random values
   }
}

// Creates and initializes a new star entity
// Precondition:
//  there must be memory space available for new entities
void generate_new_star() {
    Entity *e = manager_entity_create();            // create all entities
    cpct_memcpy(e, &init_entity, sizeof(Entity));   // copy from template
    set_init_star_values(e);              // choose some random values
}

// creates new entities
void sys_generator_update() {
    // is there enough space?
    if (manager_entity_free_space() > 0) {
        generate_new_star();
    }
}

// generates entities from the right
void sys_generator_right() {
   start_x = 79;
   movement_direction = TO_LEFT;
}

// generates entities from the left
void sys_generator_left() {
   start_x = 1;
   movement_direction = TO_RIGHT;
}

// generates entities from the bottom
void sys_generator_bottom() {
   start_y = 199;
   movement_direction = TO_UP;
}

// generates entities from the top
void sys_generator_top() {
   start_y = 1;
   movement_direction = TO_DOWN;
}