#include "render.h"

// ----------------------------------------------------------------------------
// Public interface
// ----------------------------------------------------------------------------

const u8 palette[] = {
    HW_BLACK,        HW_BRIGHT_WHITE, HW_WHITE,        HW_PASTEL_YELLOW,
    HW_BRIGHT_WHITE, HW_BRIGHT_WHITE, HW_BRIGHT_WHITE, HW_BRIGHT_WHITE,
    HW_BRIGHT_WHITE, HW_BRIGHT_WHITE, HW_BRIGHT_WHITE, HW_BRIGHT_WHITE,
    HW_BRIGHT_WHITE, HW_BRIGHT_WHITE, HW_BRIGHT_WHITE, HW_BRIGHT_WHITE
};

u8 hyperspace_enabled;

void sys_render_one_entity( Entity *e) {
    u8 *pvmem;

    if (e->prevptr != 0 && !hyperspace_enabled) {
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

void sys_render_init() {
    cpct_disableFirmware();
    cpct_setVideoMode(0);
    cpct_setBorder(HW_BLACK);
    cpct_setPalette(palette, 16);
    hyperspace_enabled = 0;
}

void sys_render_hyperspace_toggle() {
    cpct_setBorder(HW_BRIGHT_WHITE);
    cpct_clearScreen(0x00);
    cpct_setBorder(HW_BLACK);
    if (hyperspace_enabled == 0) {
        hyperspace_enabled = 1;
    } else {
        hyperspace_enabled = 0;
    }
}