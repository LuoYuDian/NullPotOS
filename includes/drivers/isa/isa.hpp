// 创建于2024.12.22
// NullPotOS ISA设备驱动程序头文件

#include <types.hpp>

#define DMA_MODE_CHECK		0x00
#define DMA_MODE_READ		0x04
#define DMA_MODE_WRITE		0x08
#define DMA_MODE_AUTO		0x10
#define DMA_MODE_DOWN		0x20
#define DMA_MODE_DEMAND		0x00
#define DMA_MODE_SINGLE		0x40
#define DMA_MODE_BLOCK		0x80
#define DMA_MODE_CASCADE	0xC0

void isa_dma_mask(uint8_t channel,bool mask);

void isa_dma_addr(uint8_t channel,void *addr);

void isa_dma_size(uint8_t channel,uint32_t size);

void isa_dma_reset(uint8_t channel);

void isa_dma_mode(uint8_t channel,uint8_t mode);