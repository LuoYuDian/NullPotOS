// 创建于2024.12.8
// NullPotOS multiboot规范定义

#ifndef __MULTIBOOT_H__
#define __MULTIBOOT_H__

#define MAGIC   0x1BADB002
#define ALI     0x03
#define CHECKSUM(flags)     -(MAGIC + flags)

#define WIDTH 1280
#define HEIGHT 720
#define DEPTH 32

#endif