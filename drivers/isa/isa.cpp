// 创建于2024.12.22
// NullPotOS ISA设备驱动程序

#include <drivers/isa/isa.hpp>
#include <drivers/serial/serial.hpp>
#include <drivers/common/common.hpp>

#define ISA_DMA_CHAN2_READ	0x46
#define ISA_DMA_CHAN2_WRITE	0x4A
#define ISA_DMA0_CHAN2_PAGE	0x81

enum
{
	DMA0_CHAN0_ADDR		= 0x00,
	DMA0_CHAN0_COUNT	= 0x01,
	DMA0_CHAN1_ADDR		= 0x02,
	DMA0_CHAN1_COUNT	= 0x03,
	DMA0_CHAN2_ADDR		= 0x04,
	DMA0_CHAN2_COUNT	= 0x05,
	DMA0_CHAN3_ADDR		= 0x06,
	DMA0_CHAN3_COUNT	= 0x07,

	DMA0_STATUS			= 0x08,
	DMA0_COMMAND		= 0x08,
	DMA0_REQUEST		= 0x09,
	DMA0_MASK1			= 0x0A,
	DMA0_MODE			= 0x0B,
	DMA0_RESET			= 0x0C,
	DMA0_TEMP			= 0x0d,
	DMA0_MASTER_CLEAR	= 0x0d,
	DMA0_MASK_CLEAR		= 0x0E,
	DMA0_MASK2			= 0x0F,

	DMA1_CHAN4_ADDR		= 0XC0,
	DMA1_CHAN4_COUNT	= 0XC2,
	DMA1_CHAN5_ADDR		= 0XC4,
	DMA1_CHAN5_COUNT	= 0XC6,
	DMA1_CHAN6_ADDR		= 0XC8,
	DMA1_CHAN6_COUNT	= 0XCA,
	DMA1_CHAN7_ADDR		= 0XCC,
	DMA1_CHAN7_COUNT	= 0XCE,

	DMA1_STATUS			= 0xD0,
	DMA1_COMMAND		= 0xD0,
	DMA2_REQUEST		= 0xD2,
	DMA1_MASK1			= 0xD4,
	DMA1_MODE			= 0xD6,
	DMA1_RESET			= 0xD8,
	DMA1_TEMP			= 0xDA,
	DMA1_MASTER_CLEAR	= 0xDA,
	DMA1_MASK_CLEAR		= 0xDC,
	DMA1_MASK2			= 0xDE,

	DMA0_CHAN1_PAGE		= 0x83,
	DMA0_CHAN2_PAGE		= 0x81, 
	DMA0_CHAN3_PAGE		= 0x82,

	DMA1_CHAN5_PAGE		= 0x8B,
	DMA1_CHAN6_PAGE		= 0x89,
	DMA1_CHAN7_PAGE		= 0x8A,
};

static uint8_t DMA_MASK1[] = 
{
	DMA0_MASK1,
	DMA0_MASK1,
	DMA0_MASK1,
	DMA0_MASK1,
	DMA1_MASK1,
	DMA1_MASK1,
	DMA1_MASK1,
	DMA1_MASK1,
};

static uint8_t DMA_MODE[] =
{
	DMA0_MODE,
	DMA0_MODE,
	DMA0_MODE,
	DMA0_MODE,
	DMA1_MODE,
	DMA1_MODE,
	DMA1_MODE,
	DMA1_MODE,
};

static uint8_t DMA_RESET[] =
{
	DMA0_RESET,
	DMA0_RESET,
	DMA0_RESET,
	DMA0_RESET,
	DMA1_RESET,
	DMA1_RESET,
	DMA1_RESET,
	DMA1_RESET,
};

static uint8_t DMA_ADDR[] = 
{
	DMA0_CHAN0_ADDR,
	DMA0_CHAN1_ADDR,
	DMA0_CHAN2_ADDR,
	DMA0_CHAN3_ADDR,
	DMA1_CHAN4_ADDR,
	DMA1_CHAN5_ADDR,
	DMA1_CHAN6_ADDR,
	DMA1_CHAN7_ADDR,
};


static uint8_t DMA_COUNT[] =
{
	DMA0_CHAN0_COUNT,
	DMA0_CHAN1_COUNT,
	DMA0_CHAN2_COUNT,
	DMA0_CHAN3_COUNT,
	DMA1_CHAN4_COUNT,
	DMA1_CHAN5_COUNT,
	DMA1_CHAN6_COUNT,
	DMA1_CHAN7_COUNT,
};

static uint8_t DMA_PAGE[] = 
{
	0,
	DMA0_CHAN1_PAGE,
	DMA0_CHAN2_PAGE,
	DMA0_CHAN3_PAGE,
	0,
	DMA1_CHAN5_PAGE,
	DMA1_CHAN6_PAGE,
	DMA1_CHAN7_PAGE,
};

void isa_dma_mask(uint8_t channel,bool mask)
{
	uint16_t port = DMA_MASK1[channel];
	uint8_t data = channel % 4;
	if (!mask)
	{
		data |= 0x4;
	}
	outb(port, data);
}

void isa_dma_addr(uint8_t channel,void *addr)
{
	uint16_t port = DMA_ADDR[channel];

	uint32_t offset = ((uint32_t)(uintptr_t)addr) % 0x10000;
	if (channel >= 5)
	{
		offset >>= 1;
	}
	outb(port, offset & 0xFF);
	outb(port, (offset >> 8) & 0xFF);

	port = DMA_PAGE[channel];
	outb(port, (uint32_t)(uintptr_t)addr >> 16);
}

void isa_dma_size(uint8_t channel,uint32_t size)
{
	uint16_t port = DMA_COUNT[channel];
	if (channel >= 5)
	{
		size >>= 1;
	}
	outb(port, (size - 1) & 0xFF);
	outb(port, ((size - 1) >> 8) & 0xFF);
}

void isa_dma_mode(uint8_t channel,uint8_t mode)
{
	uint16_t port = DMA_MODE[channel];
	outb(port, mode | (channel % 4));
}

void isa_dma_reset(uint8_t channel)
{
	uint16_t port = DMA_RESET[channel];
	outb(port, 0);
}
