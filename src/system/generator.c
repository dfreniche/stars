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

// ----------------------------------------------------------------------------
// Private interface
// ----------------------------------------------------------------------------

// sets some init random values for our entities
void set_init_star_values(Entity *e) {
   e->type = ENTITY_TYPE_DEFAULT;
   e->x = 79;
   e->y = cpct_rand() % 200;
   e->color = cpct_px2byteM0(1, 0); // this gets 0x80
   e->x_speed = -1-(cpct_rand() & 0x03); // we do a bitwise AND with 0b00000011. Any bits other than 11 are discarded 
}

// ----------------------------------------------------------------------------
// Public interface
// ----------------------------------------------------------------------------

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
