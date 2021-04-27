#include "ft_printf.h"

int	ft_print_value(t_info* info)
{
	int gap;
	gap = 0;

	if (info->flag == 0 && info->width > info->precision && info->width - info->sign > ft_get_number_len(info->value, 10))
	{
		gap = (info->precision > 0 ? info->width - info->precision : info->width - ft_get_number_len(info->value, 10)) - info->sign;
		print_write(gap, " ");
	}

	if (info->sign == 1)
	{
		print_write(1, "-");
		info->width = info->width - 1;
	}
	if (info->precision > 0 || info->flag == '0')
	{
		gap = (info->precision > 0 ? info->precision : info->width) - ft_get_number_len(info->value, 10);
		print_write(gap, "0");
	}

	put_number(info->value, (char*)"0123456789", 10);

	if (info->flag == '-' && info->width > info->precision && info->width > ft_get_number_len(info->value, 10))
	{
		gap = (info->precision > 0 ? info->width - info->precision : info->width - ft_get_number_len(info->value, 10) - info->sign);
		print_write(gap, " ");
	}

	return 1;
}

int print_write(int gap, char* str)
{
	int i = 0;
	while (i++ < gap)
		g_ret += write(1, str, 1);

	return i;
}
