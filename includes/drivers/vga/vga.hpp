// 创建于2024.12.22
// NullPotOS 图像显示驱动头文件

extern "C" 
{
	#include <firmware/UEFI.hpp>
}

void GetVInfo(FrameBufferConfig &fbc);

void VGA_clear(void);

void VGA_clear_color(int color);

void VGA_write_newline(void);

void VGA_scroll(void);

void VGA_draw_pixel(uint32 x,uint32 y,uint32 color);

void VGA_draw_rect(int x0,int y0,int x1,int y1,int color);

void VGA_draw_char(char c,int32 x,int32 y,int color);

void VGA_put_char(char c,int color);

void VGA_put_string(const char *str);

void VGA_put_string_color(const char *str,int color);

void VGA_to_serial(int op);

void set_fore_color(int color);

void set_back_color(int color);