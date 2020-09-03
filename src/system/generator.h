// star generator: generates stars

#pragma once
#include <cpctelera.h>
#include "directions.h"

void sys_generator_init();
void create_init_entities(int num_entities);
void sys_generator_update();

void sys_generator_right();
void sys_generator_left();
void sys_generator_bottom();
void sys_generator_top();
