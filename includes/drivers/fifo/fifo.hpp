// 创建于2024.12.22
// NullPotOS FIFO先进先出结构头文件

#include <drivers/common/common.hpp>
#include <types.hpp>

#define FIFO_FLAGS_OVERRUN 1

typedef struct FIFO 
{
	uint32_t *buf;
	int p, q, size, free, flags;
} fifo_t;

void fifo_init(fifo_t *fifo,int size,uint32_t *buf); 

int fifo_put(fifo_t *fifo,uint32_t data);

int fifo_get(fifo_t *fifo);
int fifo_status(fifo_t *fifo);