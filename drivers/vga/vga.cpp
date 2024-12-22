// 创建于20224.12.22
// NullPotOS 图像显示驱动

#include <drivers/serial/serial.hpp>
#include <drivers/vga/vga.hpp>
#include <firmware/UEFI.hpp>
#include <libs/string.hpp>

extern uint8_t ascfont[];

uint32_t *VGA_mem;
uint32_t width, height;
uint32_t fore_color, back_color;
int32_t x, y;
int32_t cx, cy;
uint32_t c_width, c_height;

int VGA_serial = 0;

void GetVInfo(FrameBufferConfig &fbc)
{
	VGA_mem = (uint32_t *)fbc.frame_buffer;
	width = fbc.horizontal_resolution;
	height = fbc.vertical_resolution;;

	set_fore_color(0xffffff);
	set_back_color(0x000000);

	x = 2;
	y = cx = cy = 0;

	c_width = width / 9;
	c_height = height / 16;
}

void VGA_clear(void)
{
	for (uint32_t i = 0; i < (width * (height)); i++) 
	{
		VGA_mem[i] = back_color;
	}
	x = 2;
	y = 0;
	cx = cy = 0;
}

void VGA_clear_color(int color)
{
	set_back_color(color);
	for (uint32_t i = 0; i < (width * (height)); i++) 
	{
		VGA_mem[i] = color;
	}
	x = 2;
	y = 0;
	cx = cy = 0;
}

void VGA_write_newline(void)
{
	VGA_scroll();
	cx = 0;
	cy++;
}

void VGA_scroll(void)
{
	if ((uint32_t)cx > c_width) 
	{
		cx = 0;
		cy++;
	} 
	else 
	{
		cx++;
	}

	if ((uint32_t)cy >= c_height) 
	{
		cy = c_height - 1;
		memcpy(reinterpret_cast<uint8_t*>(VGA_mem), reinterpret_cast<uint8_t*>(VGA_mem + width * 16 * sizeof(uint32_t)), width * (height - 16) * sizeof(uint32_t));
		for (uint32_t i = (width * (height - 16)); i != (width * height); i++) 
		{
			VGA_mem[i] = back_color;
		}
	}
}

void VGA_draw_pixel(uint32_t x,uint32_t y,uint32_t color)
{
	if (x >= width || y >= height) 
	{
		return;
	}
	color = (color & 0xff) | (color & 0xff00) | (color & 0xff0000);
	uint32_t  *p = (uint32_t *)VGA_mem + y * width + x;
	*p = color;
}

void VGA_draw_rect(int x0,int y0,int x1,int y1,int color)
{
	int x, y;
	for (y = y0; y <= y1; y++) 
	{
		for (x = x0; x <= x1; x++) 
		{
			(VGA_mem)[y * width + x] = color;
		}
	}
}

void VGA_draw_char(char c,int32_t x,int32_t y,int color)
{
	uint8_t *font = ascfont;
	font += c * 16;

	for (int i = 0; i < 16; i++) 
	{
		for (int j = 0; j < 9; j++) 
		{
			if (font[i] & (0x80 >> j)) 
			{
				VGA_mem[(y + i) * width + x + j] = color;
			} 
			else
			{
				VGA_mem[(y + i) * width + x + j] = back_color;
			}
		}
	}
}

void VGA_put_char(char c,int color)
{
	if (c == '\n') 
	{
		VGA_scroll();
		cx = 0;
		cy++;
		return;
	} 
	else if (c == '\r') 
	{
		cx = 0;
		return;
	} 
	else if(c == '\t') 
	{
		for (int i = 0; i < 4; i++) VGA_put_char(' ', color);
		return;
	} 
	else if (c == '\b' && cx > 0) {
		cx -= 1;
		if (cx == 0) {
			cx = c_width - 1;
			if (cy != 0) cy -= 1;
			if (cy == 0) cx = 0, cy = 0;
		}
		int x = (cx+1) * 9 - 7;
		int y = cy * 16;
		VGA_draw_rect(x, y, x + 9, y + 16, back_color);
		return;
	}
	VGA_scroll();
	VGA_draw_char(c, cx * 9 - 7, cy * 16, color);
}

void VGA_put_string(const char *str)
{
	for (;*str; ++str) 
	{
		char c = *str;
		VGA_put_char(c, fore_color);
	}
}

void VGA_put_string_color(const char *str,int color)
{
	for (;*str; ++str) 
	{
		char c = *str;
		VGA_put_char(c, color);
	}
}

void VGA_to_serial(int op)
{
	if (op == 1)
	{
		VGA_serial = 1;
	}
	else
	{
		VGA_serial = 0;
	}
}

void set_fore_color(int color)
{
	fore_color = color;
}

void set_back_color(int color)
{
	back_color = color;
}
