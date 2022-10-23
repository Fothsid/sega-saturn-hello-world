#include "vdp2.h"

void vdp2_init()
{
    memset((void*) VDP2, 0, sizeof(_VDP2REGS));

    VDP2->TVMD = 0; // Disable TV
    VDP2->RAMCTL &= ~0x3000; // Color RAM mode 0
    VDP2->MPOFN = 0; // NGB0 map offset
    VDP2->CHCTLA = 0x12 | 8; // Bitmap 256 color mode for NBG0
    VDP2->SCXIN0 = 0;
    VDP2->SCXDN0 = 0;
    VDP2->SCYIN0 = 0;
    VDP2->SCYDN0 = 0;
    VDP2->BGON = 1; // Enable NBG1

    memset_w((void*)VDP2_VRAM, 0, 0x40000);
    memset_w((void*)VDP2_CRAM, 0, 0x800);
}

void vdp2_screen_on(u16 mode)
{
    VDP2->TVMD = mode;
}

void vdp2_screen_off()
{
    VDP2->TVMD = 0;
}

void vdp2_wait_vblank()
{
    while ((VDP2->TVSTAT & 8));
    while ((VDP2->TVSTAT & 8) == 0);
}