// 创建于2024.12.14
// NullPotOS 错误处理

#include <stdint.h>
#include <kernel/error/error.h>

void put_error(int error_code)
{
    // 将背景色设置为蓝色
    VGA_set_theme(VGA_COLOR_WHITE, VGA_COLOR_BLUE);
    VGA_clear();
    VGA_scroll_up();
    printf("Your device has a error!\nNullPotOS is exit!");
    printf("Error code: %d\n", error_code);
}