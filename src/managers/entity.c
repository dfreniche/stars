#include "entity.h"

#define NUM_ENTITIES 5

// Array of entities
// Last entity will be left empty to mark end of array
// All valid entities should be at the beginning of the array
// After init, array look like
// [E1][E2][E3][E4][E5][F]
// where [F] is next_free_entity
Entity entities[NUM_ENTITIES + 1];

// points to next free entity, starts pointing to entities[0]
Entity *next_free_entity;

// template for new entities, quicker to copy this memory chunk
const Entity init_entity = {
   ENTITY_TYPE_DEFAULT, // type
   79, 1,               // x,y
   -1,                  // x speeed
   0xFF,                // color
   0x00                 // prevptr
};

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
   for (u8 i = 0; i < NUM_ENTITIES; i++) {
      Entity *e = manager_entity_create();            // create all entities
      cpct_memcpy(e, &init_entity, sizeof(Entity));   // copy from template
      manager_set_init_entity_values(e);              // choose some random values
   }
}

// sets some init random values for our entities
void manager_set_init_entity_values(Entity *e) {
   e->type = ENTITY_TYPE_DEFAULT;
   e->x = 79;
   e->y = cpct_rand() % 200;
   e->color = 2;
   e->x_speed = -1-(cpct_rand() & 0x03); // we do a bitwise AND with 0b00000011. Any bits other than 11 are discarded 
}

// mark an entity for later destruction
// we just activate the "dead bit" on that entity
void manager_entity_set4destruction(Entity *dead_entity) {
   dead_entity->type |= ENTITY_TYPE_DEAD;
}

// destroys an entity
void manager_entity_destroy(Entity *dead_entity) {
   Entity *de = dead_entity;
   Entity *last = next_free_entity;
   --last;

   if (de != last) {
      cpct_memcpy(de, last, sizeof(Entity));
   } 

   last->type = ENTITY_TYPE_INVALID;
   next_free_entity = last;
}

// Applies function to all Entitites
void manager_entity_forall( void (*update_function)(Entity *) ) {
   Entity *e = entities;

   while (e != next_free_entity) {
      update_function(e);
      ++e;
   }
}

// Updates entity manager by deleting all marked for deletion entities
void manager_entity_update() {
   Entity *e = entities;
   while (e->type != ENTITY_TYPE_INVALID) {
      if (e->type & ENTITY_TYPE_DEAD) {
         manager_entity_destroy(e);
      } else {
         ++e;
      }
   }
}