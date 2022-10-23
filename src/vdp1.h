#pragma once
#include "common.h"

#define VDP1_VRAM	 ((u8*) 0x25c00000)
#define VDP1_CMDLIST ((VDP1CMD*) 0x25c00000)
#define VDP1_REG	 ((volatile s16*) 0x25d00000)
#define VDP1_BACKBUF ((volatile s16*) 0x25c80000)

extern int vdp1_cmd_idx;
void vdp1_init();
void vdp1_set_user_clipping(s16 x0, s16 y0, s16 x1, s16 y1);
void vdp1_set_system_clipping(s16 x0, s16 y0, s16 x1, s16 y1);
void vdp1_set_local_coords(s16 x, s16 y);
void vdp1_draw_sprite(s16 x, s16 y, u16 w, u8 h, void* texture, u16 pmod);
void vdp1_draw_end();
void vdp1_clear_list();
void vdp1_swap_buffers();

enum
{
	CMD_SPRITE	= 0, // Normal sprite
	CMD_SSPRITE	= 1, // Scaled sprite 
	CMD_DSPRITE	= 2, // Distorted sprite
	CMD_POLY	= 4, // Polygon
	CMD_PLINE	= 5, // Polylines
	CMD_LINE	= 6, // Line
	CMD_USRCLIP	= 8, // Set User Clipping
	CMD_SYSCLIP	= 9, // Set System Clipping
	CMD_LCOORD	= 10, // Set Local Coordinates
	CMD_DRAWEND = 0x8000 // Draw end
};

#define PMOD_SET_PXL_MSB		(1 << 15)
#define PMOD_HIGH_SPEED_SHRINK	(1 << 12)
#define PMOD_DISABLE_PRECLIP	(1 << 11)
#define PMOD_CLIP				(1 << 10)
#define PMOD_CMOD				(1 << 9)
#define PMOD_MESH				(1 << 8)
#define PMOD_TEXTURE_ECD_OFF	(1 << 7)
#define PMOD_TRANSPARENCY_PIXEL (1 << 6)
#define PMOD_COLOR_MODE(X)		(((X) & 7) << 3)
#define PMOD_COLOR_CALC(X)		((X) & 7)

/*
	Color modes:
	0 - 4bpp, color bank
	1 - 4bpp, lookup table
	2 - 8bpp, 64 colors 
	3 - 8bpp, 128 colors
	4 - 8bpp, 256 colors
	5 - 16bpp
 */

#define PMOD_DEFAULT (PMOD_TEXTURE_ECD_OFF | PMOD_COLOR_MODE(2))

typedef struct
{
	u16 CTRL;
	u16 LINK;
	u16 PMOD;
	u16 COLR;
	u16 SRCA;
	u16 SIZE;
	s16 XA, YA;
	s16 XB, YB;
	s16 XC, YC;
	s16 XD, YD;
	u16 GRDA;
	u16 dummy;
} VDP1CMD;

typedef struct
{
	u16 TVMR; // TV mode
	u16 FBCR; // Framebuffer clear
	u16 PTMR; // Plot trigger
	u16 EWDR; // Erase/write color
	u16 EWLR; // Erase/write upper-left position
	u16 EWRR; // Erase/write lower-right position
	u16 ENDR; // Force draw end
	u16 EDSR; // Transfer end status
	u16 LOPR; // Return to the last command table processed
	u16 COPR; // Return to the current command table processed
	u16 MODR; // Mode status
} _VDP1REGS;
#define VDP1 ((volatile _VDP1REGS*) 0x25d00000)