#include "render.h"

void sys_render_one_entity( Entity *e) {
    u8 *pvmem;

    if (e->prevptr != 0) {
        // paint previous position with background color
        *(e->prevptr) = 0x00;
    }
    if (!(e->type & ENTITY_TYPE_DEAD)) {
        // paint star in new position
        pvmem = cpct_getScreenPtr(CPCT_VMEM_START, e->x, e->y);
        *pvmem = e->color;
        e->prevptr = pvmem;
    }
}

void sys_render_deleted_entity( Entity *e) {
    u8 *pvmem = cpct_getScreenPtr(CPCT_VMEM_START, e->x, e->y);
    *pvmem = 0x00;
}

void sys_render_update() {
    manager_entity_forall( sys_render_one_entity );
}