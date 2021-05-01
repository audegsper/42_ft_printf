#include "ft_printf.h"

void	init_struct(t_info* info)
{
	info->flag = 0;
	info->sign = 0;
	info->width = 0;
	info->value = 0;
	info->precision = 0;
	info->type = 0;
}

int	ft_printf(const char* format, ...)
{
	va_list ap;
	t_info		info;
	va_start(ap, format);

	int prec = 0;

	g_ret = 0;
	while (*format != '\0')
	{
		init_struct(&info);
		if (*format == '%' && format++)
		{
			info.flag = ft_parse_flag(&format);
			if ((info.width = ft_parse_number(&format, &ap, 'w')) < 0)
			{
				info.width = -(info.width);
				info.flag = '-';
			}

			if (*format == '.' && format++)
			{
				prec = ft_parse_number(&format, &ap, 'p');
				info.precision = prec;
			}

			if ((info.value = ft_parse_specifier(&format, &ap, &info)) < 0 && !(info.type == 'c' || info.type == 's') && (info.sign = 1))
				info.value = info.value * -1;

			if (!(info.type == 'e'))
				ft_print_value(info);
		}
		else
			g_ret += write(1, format++, 1);
	}
	return g_ret;
}

/*
int main()
{
	ft_printf("-->|%0*.d|<--\n", 4, -135);
	printf("-->|%0*.d|<--\n", 4, -135);
	ft_printf("-->|%-4.4d|<--\n", 198);
	printf("-->|%-4.4d|<--\n", 198);
	ft_printf("-->|%-4.*d|<--\n", 4, -135);
	printf("-->|%-4.*d|<--\n", 4, -135);
	ft_printf("-->|%-4.1d|<--\n", 198);
	printf("-->|%-4.1d|<--\n", 198);
	ft_printf("-->|%-4.*d|<--\n", 3, -12);
	printf("-->|%-4.*d|<--\n", 3, -12);
	ft_printf("-->|%04d|<--\n", 198);
	printf("-->|%04d|<--\n", 198);
	ft_printf("-->|%*.*d|<--\n", 4, -4, -12);
	printf("-->|%*.*d|<--\n", 4, -4, -12);
	ft_printf("-->|%*.*d|<--\n", 4, 1, -13);
	printf("-->|%*.*d|<--\n", 4, 1, -13);
	ft_printf("-->|%*.*d|<--\n", 4, 3, -14);
	printf("-->|%*.*d|<--\n", 4, 3, -14);
	ft_printf("-->|%0*.d|<--\n", 4, -18);
	printf("-->|%0*.d|<--\n", 4, -18);
	ft_printf("-->|%0*.1d|<--\n", -4, -12);
	printf("-->|%0*.1d|<--\n", -4, -12);
	ft_printf("-->|%0*.*d|<--\n", 4, 0, -12);
	printf("-->|%0*.*d|<--\n", 4, 0, -12);


	ft_printf("-->|%-16.s|<--\n", "abc");
	printf("-->|%-16.s|<--\n", "abc");

	ft_printf("-->|%*.5s|<--\n", 0, "abc");
	printf("-->|%*.5s|<--\n", 0, "abc");

	ft_printf("-->|%1.*s|<--\n", 2, "abc");
	printf("-->|%1.*s|<--\n", 2, "abc");

	ft_printf("-->|%-*.4s|<--\n", 4, "abc");
	printf("-->|%-*.4s|<--\n", 4, "abc");

	ft_printf("-->|%-1.2s|<--\n", "abc");
	printf("-->|%-1.2s|<--\n", "abc");
}
*/