#include "ft_printf.h"

void	init_struct(t_info* info)
{
	info->flag = 0;
	info->sign = 0;
	info->width = 0;
	info->value = 0;
	info->precision = 0;
}

int	ft_printf(const char * format, ...)
{
	va_list ap;
	t_info		info;
	va_start(ap, format);

	int pre = 0;

	g_ret = 0;
	while (*format != '\0')
	{
		init_struct(&info);
		if (*format == '%' && format++)
		{
			info.flag = ft_parse_flag(&format);
			if ((info.width = ft_parse_number(&format, &ap)) < 0)
			{
				info.width = -(info.width);
				info.flag = '-';

			}

			if (*format == '.' && format++)
			{
				pre = ft_parse_number(&format, &ap);
				info.precision = (pre > 0 ? pre : 0);
			}

			if ((info.value = ft_parse_specifier(&format, &ap)) < 0 && (info.sign = 1))
			{
				 info.value = info.value * -1;
			}

			ft_print_value(&info);
		}
		else
			write(1, format++, 1);
	}
	return g_ret;
}
