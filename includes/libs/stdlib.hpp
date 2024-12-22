// 创建于2024.12.22
// NullPotOS 通用工具内联函数库头文件

#include <types.hpp>

#define MAX_PRECISION (10)

static const double rounders[MAX_PRECISION + 1] = 
{
	0.5,
	0.05,
	0.005,
	0.0005,
	0.00005,
	0.000005,
	0.0000005,
	0.00000005,
	0.000000005,
	0.0000000005,
	0.00000000005
};

void delay(uint32_t count);

void hang(void);

bool isdigit(int c);

int atoi(char* pstr);

char *get_filename(char *path);

char *ftoa(double f,char *buf,int precision);