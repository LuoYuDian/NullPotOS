// 创建于2024.12.13
// NullPotOS 标准库
// 在中国，这一天是南京大屠杀死难者国家公祭日
// 为死者默哀!!!

#ifdef _LIBC
char* __uitoa_internal(unsigned int value, char* str, int base, unsigned int* size);
char* __itoa_internal(int value, char* str, int base, unsigned int* size);
#endif
char* itoa(int value, char* str, int base);