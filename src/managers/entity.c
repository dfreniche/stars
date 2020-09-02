#include "entity.h"

#define NUM_STARS 5

// Array of entities
Entity entities[NUM_STARS + 1];

// points to next free entity, starts pointing to entities[0]
Entity *next_free_entity;

// template for new entities, quicker to copy this memory chunk
const Entity init_entity = {
   ENTITY_TYPE_DEFAULT,    // type
   79, 1,               // x,y
   79, 0,                 // previous positions
   -1,                  // x speeed
   0xFF                 // color
};

u8 y_global;

// init: initializes all global vars
// sdcc will initialize them in ROM if we init directly
// so we 1st reserve space, then init it
// in asm it'll be 	.ds 50 that reserves 50 bytes. DS == define space. DB == define bytes
void manager_entity_init() {
    // memset: loads with 0s starting at entities the size of entities
    // this is an array, so it's 10 * sizeof(Entity) == 10 * 5
    // beware sizeof(Entity *) is 2 bytes
   cpct_memset(entities, 0, sizeof(entities));
   next_free_entity = entities;
   y_global = 10;
}

// creates a new uninitialized entity
// returns a new entity, containing garbage!
Entity *manager_entity_create() {
   Entity *e = next_free_entity;
   next_free_entity = e + 1;
   
   return e;
}

// Initializes all entities in the global array
// creates them and initialized them
void create_init_entities(void) {
   for (u8 i = 0; i < NUM_STARS; i++) {
      Entity *e = manager_entity_create();            // create all entities
      cpct_memcpy(e, &init_entity, sizeof(Entity));   // copy from template
      manager_set_init_entity_values(e);              // choose some random values
   }
}

// sets some init random values for our entities
void manager_set_init_entity_values(Entity *e) {
   y_global += 10;
   e->type = ENTITY_TYPE_DEFAULT;
   e->x = 79;
   // e->y = y_global;
   e->prev_x = 79;
   e->y = 1 + (u8)(cpct_rand() & 0xC8);
   e->prev_y = e->y;
   // e->color = 4; //(cpct_rand() & 0xF);
   e->x_speed = -1; //-(cpct_rand() & 0x03); // % 4
}

// destroys an entity
void manager_entity_destroy(Entity *dead_entity) {
    dead_entity->type = ENTITY_TYPE_INVALID;
}

// Applies function to all Entitites
void manager_entity_forall( void (*update_function)(Entity *) ) {
   Entity *e = entities;
   // for (int i=0; i<NUM_STARS; i++) {
   //    Entity *e = &entities[i];
   //    if (e->type != ENTITY_TYPE_INVALID) {
   //       update_function(e);
   //    }
   // }
   while (e != next_free_entity) {
      update_function(e);
      ++e;
   }
}