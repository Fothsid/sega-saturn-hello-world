#pragma once

#include "types.h"
#include "vdp1.h"
#include "vdp2.h"

void gfx_init();
void gfx_load_font();
void gfx_print(const char* str, int x, int y);