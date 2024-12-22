// 创建于2024.12.22
// NullPotOS cmos存储器驱动

#include <drivers/cmos/cmos.hpp>
#include <drivers/common/common.hpp>

unsigned char read_cmos(unsigned char p)
{
	unsigned char data;

	outb(cmos_index, p);

	data = inb(cmos_data);

	outb(cmos_index, 0x80);
	return data;
}

unsigned int get_hour_hex(void)
{
	return BCD_HEX(read_cmos(CMOS_CUR_HOUR));
}

unsigned intget_min_hex(void)
{
	return BCD_HEX(read_cmos(CMOS_CUR_MIN));
}

unsigned int get_sec_hex(void)
{
	return BCD_HEX(read_cmos(CMOS_CUR_SEC));
}

unsigned int get_day_of_month(void)
{
	return BCD_HEX(read_cmos(CMOS_MON_DAY));
}

unsigned int get_day_of_week(void)
{
	return BCD_HEX(read_cmos(CMOS_WEEK_DAY));
}

unsigned int get_mon_hex(void)
{
	return BCD_HEX(read_cmos(CMOS_CUR_MON));
}

unsigned int get_year(void)
{
	return (BCD_HEX(read_cmos(CMOS_CUR_CEN)) * 100) + BCD_HEX(read_cmos(CMOS_CUR_YEAR)) - 30 + 2010;
}
