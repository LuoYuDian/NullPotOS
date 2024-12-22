// 创建于2024.12.22
// NullPotOS 基础内存操作和字符串处理的内联函数库

#include <libs/string.hpp>
#include <types.hpp>

int memcmp(const void* buffer1,const void* buffer2,size_t count)
{
	if(!count) 
	{
		return 0;
	}

	while(count-- && *(char*)buffer1 == *(char*)buffer2) 
	{
		buffer1 = (char*)buffer1 + 1;
		buffer2 = (char*)buffer2 + 1;
	}

	
	return( *((uint8_t *)buffer1) - *((uint8_t *)buffer2) );    
}


void memcpy(uint8_t *dest,const uint8_t *src,uint32_t len)
{
	uint8_t *sr = (uint8_t *)src;
	uint8_t *dst = dest;

	while (len != 0) 
	{
		*dst++ = *sr++;
		len--;
	}
}

void memset(void *dest,uint8_t val,uint32_t len)
{
	for (uint8_t *dst = (uint8_t *)dest; len != 0; len--) 
	{
		*dst++ = val;
	}
}
void bzero(void *dest,uint32_t len)
{
	memset(dest, 0, len);
}

void memclean(char *s,int len)
{
	int i;
	for (i = 0; i != len; i++) 
	{
		s[i] = 0;
	}
	return;
}

int strcmp(const char *dest,const char *src)
{
	int ret = 0 ;

	while(!(ret = *(unsigned char *)src - *(unsigned char *)dest) && *dest) 
	{
		++src;
		++dest;
	}
	if (ret < 0) 
	{
		ret = -1;
	}
	else if (ret > 0) 
	{
		ret = 1;
	}
	return ret;
}

char *strcpy(char *dest,const char *src)
{
	char *tmp = dest;

	while (*src) 
	{
		*dest++ = *src++;
	}
	*dest = '\0';	
	return tmp;
}

char *strncpy(char *dest,const char *src,uint32_t len)
{
	char *dst = dest;

	while (len > 0) 
	{
		while (*src)
		{
			*dest++ = *src++;
		}
		len--;
	}
	*dest = '\0';
	return dst;
}

char *strcat(char *dest,const char *src)
{
	char *cp = dest;

	while (*cp) 
	{
		cp++;
	}
	while ((*cp++ = *src++))
	{

	}
	return dest;
}

char *strchr(char *str,int c)
{
	for (; *str != 0; ++str) 
	{
		if (*str == c) 
		{
			return str;
		}
	}
	return 0;
}

int strlen(const char *src)
{
	const char *eos = src;

	while (*eos++)
	{

	}
	return (eos - src - 1);
}

void delete_char(char *str,int pos)
{
	int i;
	for (i = pos; i < strlen(str); i++) 
	{
		str[i] = str[i + 1];
	}
}

void insert_char(char *str,int pos, char ch)
{
	int i;
	for (i = strlen(str); i >= pos; i--) 
	{
		str[i + 1] = str[i];
	}
	str[pos] = ch;
}

void insert_str(char *str,char *insert_str,int pos)
{
	for (int i = 0; i < strlen(insert_str); i++) 
	{
		insert_char(str, pos + i, insert_str[i]);
	}
}

char *strupr(char *src)
{
	while (*src != '\0')
	{
		if (*src >= 'a' && *src <= 'z')
		{
			*src -= 32;
		}
		src++;
	}
	return src;
}

char *strlwr(char *src)
{
	while (*src != '\0')
	{
		if (*src > 'A' && *src <= 'Z')
		{ 
			*src += 32;
		}
		src++;
	}
	return src;
}
