#include "common.h"
#include "gfx.h"

char* itoa(int num, char* buffer)
{
    char* t = buffer;
	if (num == 0)
	{
		t[0] = '0';
		t[1] = 0;
		return t;
	}

    int isNegative = num < 0;
    if (isNegative)
    {
        num = -num;
        *buffer++ = '-';
    }

    int n = 0;
    int b = num;
    while (b > 0)
    {
        n++;
        b /= 10;
    }

    for (int i = 0; i < n; i++)
    {
        buffer[n-i-1] = 0x30 + num % 10;
        num /= 10; 
    }
    buffer += n;
    *buffer = 0;
    return t;
}

void ss_main()
{
	char textBuffer[10];

	gfx_init();

	VDP2->BKTAU = 0;

	// Setup layer priorities
	VDP2->PRISA = 0x0101;
	VDP2->PRISB = 0x0101;
	VDP2->PRISC = 0x0101;
	VDP2->PRISD = 0x0101;

	gfx_load_font();
	
	// Set palette for the font
	VDP2_CRAM[0] = 0;
	VDP2_CRAM[1] = 0xFFFF;

	vdp1_draw_end();

	vdp2_screen_on(TV_320_240_NI);
	int frameCounter = 0;
	while (1)
	{
		vdp2_wait_vblank();

		vdp1_clear_list();
		vdp1_set_system_clipping(0, 0, 319, 239);
		vdp1_set_user_clipping(0, 0, 319, 239);
		vdp1_set_local_coords(0, 0);
		gfx_print("Hello world on SEGA Saturn! :)\n\nNo libc or SGL :P", 16, 16);
		gfx_print("Wow! Moving text!", 16, 64 + frameCounter % 90);
		
		itoa(frameCounter, textBuffer);
		gfx_print("Frame counter: ", 16, 164);
		gfx_print(textBuffer, 132, 164);
		
		vdp1_draw_end();
		
		frameCounter++;
	}
}