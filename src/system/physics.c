#include "physics.h"
#include "render.h"
#include <managers/entity.h>

// updates one entity
// changes position based on x velocity
void sys_physics_update_one_entity(Entity *e) {
    u8 newx = e->x + e->x_speed;
    // we assume our movement is from right to left
    // with a velocity of -5 x will be 15, 10, 5, 0, 250, 245
    // at some point when x < 0 it gets 255, so it's >
    if (newx > e->x) {
        manager_entity_destroy(e);
        sys_render_deleted_entity( e );

        manager_set_init_entity_values(e);
    } else {
        e->prev_x = e->x;
        e->x = newx;
    }
}

// updates physics for all entities
void sys_physics_update() {
    // for all entities
    manager_entity_forall( sys_physics_update_one_entity );
}