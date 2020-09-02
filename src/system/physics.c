#include "physics.h"
#include "render.h"
#include <managers/entity.h>

// ----------------------------------------------------------------------------
// Public interface
// ----------------------------------------------------------------------------

// updates one entity
// changes position based on x velocity
void sys_physics_update_one_entity(Entity *e) {
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

// updates physics for all entities
void sys_physics_update() {
    // for all entities
    manager_entity_forall( sys_physics_update_one_entity );
}