#include "entity.h"

// ----------------------------------------------------------------------------
// Variables
// ----------------------------------------------------------------------------

#define MAX_ENTITIES 30

// Array of entities
// Last entity will be left empty to mark end of array
// All valid entities should be at the beginning of the array
// After init, array look like
// [E1][E2][E3][E4][E5][F]
// where [F] is next_free_entity
Entity entities[MAX_ENTITIES + 1];

// points to next free entity, starts pointing to entities[0]
Entity *next_free_entity;
// number of entities we have created
u8 num_entities;

// ----------------------------------------------------------------------------
// Public interface
// ----------------------------------------------------------------------------

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

   num_entities = 0;
}

// creates a new uninitialized entity
// returns a new entity, containing garbage!
Entity *manager_entity_create() {
   Entity *e = next_free_entity;
   next_free_entity = e + 1;

   ++num_entities;
   
   return e;
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

   --num_entities;
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

// returns the number of free entities available
// return: 
//    u8 number of free entities
u8 manager_entity_free_space() {
   return MAX_ENTITIES - num_entities;
}