// 创建于20224.12.22
// NUllPotOS BMP位图图像解析头文件

#include <types.hpp>

typedef struct 
{
	uint16_t magic;
	uint32_t fileSize;
	uint32_t reserved;
	uint32_t bmpDataOffset;

	
	uint32_t bmpInfoSize;
	uint32_t frameWidth;
	uint32_t frameHeight;
	uint16_t reservedValue;
	uint16_t bitsPerPixel;
	uint32_t compressionMode;
	uint32_t frameSize;
	uint32_t horizontalResolution;
	uint32_t verticalResolution;
	uint32_t usedColorCount;
	uint32_t importantColorCount;
} __attribute__((packed)) Bmp;

void bmp(Bmp *bmp,uint32_t x,uint32_t y,bool isTransparent);