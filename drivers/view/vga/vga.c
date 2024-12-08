// 创建于2024.12.8
// NullPotOS vga驱动

#include <drivers/view/vga/vga.h>
#include <stdint.h>
#include <libs/libc/string.h>

#define TTY_WIDTH 80
#define TTY_HEIGHT 25

VGA *buffer = (VGA *)0xB8000;

VGA theme_color = VGA_COLOR_BLACK;

uint32_t VGA_COLUMN = 0;
uint16_t VGA_ROW = 0;



void VGA_set_theme(VGA fg, VGA bg)
{
    theme_color = (bg << 4 | fg) << 8;
}

void VGA_put_char(char chr)
{
    if (chr == '\n') 
    {
        VGA_COLUMN = 0;
        VGA_ROW++;
    }
    else if (chr == '\r') 
    {
        VGA_COLUMN = 0;
    }
    else 
    {
        *(buffer + VGA_COLUMN + VGA_ROW * TTY_WIDTH) = (theme_color | chr);
        VGA_COLUMN++;
        if (VGA_COLUMN >= TTY_WIDTH) 
        {
            VGA_COLUMN = 0;
            VGA_ROW++;
        }
    }

    if (VGA_ROW >= TTY_HEIGHT) 
    {
        VGA_scroll_up();
        VGA_ROW--;
    } 

}

void VGA_put_str(char* str)
{
    while (*str != '\0') 
    {
        VGA_put_char(*str);
        str++;
    }
}

void VGA_scroll_up()
{
    size_t last_line = TTY_WIDTH * (TTY_HEIGHT - 1);
    memcpy(buffer, buffer + TTY_WIDTH, last_line);
    for (size_t i = 0; i < TTY_WIDTH; i++) {
        *(buffer + i + last_line) = theme_color;
    }
    VGA_ROW = VGA_ROW == 0 ? 0 : VGA_ROW - 1;

}

void VGA_clear()
{
    for (uint32_t x = 0; x < TTY_WIDTH; x++) 
    {
        for (uint32_t y = 0; y < TTY_HEIGHT; y++) 
        {
            *(buffer + x + y * TTY_WIDTH) = theme_color;
        }
    }
}