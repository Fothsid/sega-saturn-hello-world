#include "vdp1.h"

int vdp1_cmd_idx;
void vdp1_init()
{
	memset((void*)VDP1, 0, sizeof(_VDP1REGS));
	memset((void*)VDP1_VRAM, 0, 512*1024);

	vdp1_cmd_idx = 0;

	/* Interrupts should be disabled. */
    VDP1->TVMR = 0;
    VDP1->PTMR = 2; /* Immediately start drawing. */
    VDP1->FBCR = 0;
    VDP1->EWDR = 0; /* Set the frame buffer to black. */

    /* Erase the entire screen using a rectangle ranging from (0,0) to (320,240) */
    VDP1->EWLR = 0;
    VDP1->EWRR = ((TV_WIDTH >> 3) << 9) | TV_HEIGHT;
}

void vdp1_set_user_clipping(s16 x0, s16 y0, s16 x1, s16 y1)
{
	VDP1CMD* cmd = &VDP1_CMDLIST[vdp1_cmd_idx++];
	cmd->CTRL = CMD_USRCLIP;
	cmd->LINK = 0;
	cmd->XA = x0;
	cmd->YA = y0;
	cmd->XC = x1;
	cmd->YC = y1;
}

void vdp1_set_system_clipping(s16 x0, s16 y0, s16 x1, s16 y1)
{
	VDP1CMD* cmd = &VDP1_CMDLIST[vdp1_cmd_idx++];
	cmd->CTRL = CMD_SYSCLIP;
	cmd->LINK = 0;
	cmd->XA = x0;
	cmd->YA = y0;
	cmd->XC = x1;
	cmd->YC = y1;
}

void vdp1_set_local_coords(s16 x, s16 y)
{
	VDP1CMD* cmd = &VDP1_CMDLIST[vdp1_cmd_idx++];
	cmd->CTRL = CMD_LCOORD;
	cmd->LINK = 0;
	cmd->XA = x;
	cmd->YA = y;
}

void vdp1_draw_sprite(s16 x, s16 y, u16 w, u8 h, void* texture, u16 pmod)
{
	VDP1CMD* cmd = &VDP1_CMDLIST[vdp1_cmd_idx++];
	cmd->CTRL = CMD_SPRITE;
	cmd->LINK = 0;
	cmd->XA = x;
	cmd->YA = y;
	cmd->SRCA = ((u32)texture >> 3);
	cmd->SIZE = (((w >> 3) << 8) | h ) & 0x3FFF;
	cmd->PMOD = pmod;
}

void vdp1_draw_end()
{
	VDP1CMD* cmd = &VDP1_CMDLIST[vdp1_cmd_idx++];
	cmd->CTRL = CMD_DRAWEND;
}

void vdp1_clear_list()
{
	vdp1_cmd_idx = 0;
}

void vdp1_swap_buffers()
{
	VDP1->FBCR = 0;
}