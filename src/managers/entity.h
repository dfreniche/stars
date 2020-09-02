#pragma once
#include <cpctelera.h>

// Types of entities

#define ENTITY_TYPE_INVALID   0x00 // all zeroes                     0000 0000
#define ENTITY_TYPE_STAR      0x01 // lower bit signals star entity  0000 0001
#define ENTITY_TYPE_DEAD      0x80 // upper bit signals death entity 1000 0000
#define ENTITY_TYPE_DEFAULT   0x7F // Default entity                 0111 1111

// Entity type
typedef struct te {
   u8 type;             // entity type: one of the constants above
   u8 x, y;             // x, y position
   i8 x_speed;          // speed in x axis
   u8 color;            // star color
   u8 *prevptr;         // previous screen pointer where this entity was rendered
} Entity;

// ----------------------------------------------------------------------------
// Public interface
// ----------------------------------------------------------------------------

void manager_entity_init();
Entity *manager_entity_create();
void manager_entity_set4destruction(Entity *dead_entity);
void manager_entity_destroy(Entity *dead_entity);
void manager_entity_forall( void (*update_function)(Entity *) );
void manager_entity_update();
u8 manager_entity_free_space();