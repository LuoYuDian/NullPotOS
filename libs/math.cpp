// 创建于20224.12.22
// NullPotOS 数学处理的内联函数库

#include <libs/math.hpp>

double sin(double x)
{
	asm volatile("fldl %0 \n"
                 "fsin \n"
                 "fstpl %0\n"
                 : "+m"(x)
				);
	return x;
}

double cos(double x)
{
	asm volatile("fldl %0 \n"
                 "fcos \n"
                 "fstpl %0\n"
                 : "+m"(x)
				 );
	return x;
}

double tan(double x)
{
	asm volatile("fldl %0 \n"
                 "fptan \n"
                 "fstpl %0\n"
                 "fstpl %0\n"
                 : "+m"(x)
				 );
	return x;
}

double sqrt(double x)
{
	asm volatile("fldl %0 \n"
                 "fsqrt \n"
                 "fstpl %0\n"
                 : "+m"(x)
				 );
	return x;
}

double log2(double x)
{
	asm volatile("fld1 \n"
                 "fldl %0 \n"
                 "fyl2x \n"
                 "fwait \n"
                 "fstpl %0\n"
                 : "+m"(x)
				 );
	return x;
}
