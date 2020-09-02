#include "render.h"

void sys_render_one_entity( Entity *e) {
    // paint star in new position
    u8 *pvmem = cpct_getScreenPtr(CPCT_VMEM_START, e->x, e->y);
    *pvmem = e->color;
    
    // paint previous position with background color
    pvmem = cpct_getScreenPtr(CPCT_VMEM_START, e->prev_x, e->prev_y);
    *pvmem = 0x00;
}

void sys_render_deleted_entity( Entity *e) {
    u8 *pvmem = cpct_getScreenPtr(CPCT_VMEM_START, e->x, e->y);
    *pvmem = 0x00;
}

void sys_render_update() {
    manager_entity_forall( sys_render_one_entity );
}