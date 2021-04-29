#include "ft_printf.h"

int	ft_print_value(t_info info)
{
	int gap;
	int zero;

	zero = 0;
	gap = 0;

	if (info.precision > 0)
		zero = info.precision - ft_get_number_len(info.value, 10);
	else if (info.precision != -3 && (info.flag == '0' && (info.precision > -1 || info.precision == -2)))
		zero = info.width - ft_get_number_len(info.value, 10) - info.sign;
	zero = zero > 0 ? zero : 0;
	if ((info.width > info.precision && info.width > ft_get_number_len(info.value, 10)) || info.value == 0)
		if (info.value == 0 && (info.precision == -1 || info.precision == -3))
			gap = info.width;
		else
			gap = (info.precision > info.width ? info.width - info.precision : info.width - ft_get_number_len(info.value, 10) - zero) - info.sign;
	if (!(info.flag == '-'))
		print_write(gap, " ");
	print_write(info.sign, "-");
	print_write(zero, "0");
	if (!(info.value == 0 && (info.precision == -1 || info.precision == -3)))
		put_number(info.value, (char*)"0123456789", 10);
	if (info.flag == '-')
		print_write(gap, " ");

	return 1;
}

int print_write(int gap, char* str)
{
	int i = 0;
	while (i++ < gap)
		g_ret += write(1, str, 1);

	return i;
}
