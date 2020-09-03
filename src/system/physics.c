#include "physics.h"
#include "render.h"
#include <managers/entity.h>

void (*sys_physics_update_one_entity)(Entity *);


// ----------------------------------------------------------------------------
// Private functions
// ----------------------------------------------------------------------------

// updates one entity
// changes position based on x velocity
void sys_physics_update_one_entity_right_to_left(Entity *e) {
    u8 newx = e->x + e->x_speed;
    // we assume our movement is from right to left
    // with a velocity of -5 x will be 15, 10, 5, 0, 250, 245
    // at some point when x < 0 it gets 255, so it's >
    if (newx > e->x) {
        // sys_render_deleted_entity( e );
        manager_entity_set4destruction(e);
        // manager_entity_destroy(e);
        // {
        // Entity * new_e = manager_entity_create();
        // manager_set_init_entity_values(new_e);
        // }
    } else {
        e->x = newx;
    }
}

void sys_physics_update_one_entity_left_to_right(Entity *e) {
    u8 newx = e->x + e->x_speed;
    // we assume our movement is from right to left
    // with a velocity of -5 x will be 15, 10, 5, 0, 250, 245
    // at some point when x < 0 it gets 255, so it's >
    if (newx > 80) {
        // sys_render_deleted_entity( e );
        manager_entity_set4destruction(e);
        // manager_entity_destroy(e);
        // {
        // Entity * new_e = manager_entity_create();
        // manager_set_init_entity_values(new_e);
        // }
    } else {
        e->x = newx;
    }
}

void change_x_axis_movement_one_entity_left_to_right(Entity *e) {
    i8 speed = e->x_speed;
    if (speed < 0) {
        e->x_speed = -1 * speed;
    }
}

void change_x_axis_movement_one_entity_right_to_left(Entity *e) {
    i8 speed = e->x_speed;
    if (speed > 0) {
        e->x_speed = -1 * speed;
    }
}

//-->
void sys_physics_change_x_axis_movement_left_to_right() {
    sys_physics_update_one_entity = sys_physics_update_one_entity_left_to_right;
    manager_entity_forall( change_x_axis_movement_one_entity_left_to_right );
}

// <--
void sys_physics_change_x_axis_movement_right_to_left() {
    sys_physics_update_one_entity = sys_physics_update_one_entity_right_to_left;
    manager_entity_forall( change_x_axis_movement_one_entity_right_to_left );
}

// ----------------------------------------------------------------------------
// Public interface
// ----------------------------------------------------------------------------

void sys_physics_init() {
    sys_physics_update_one_entity = sys_physics_update_one_entity_right_to_left;
}

// updates physics for all entities
void sys_physics_update() {
    // for all entities
    manager_entity_forall( sys_physics_update_one_entity );
}
