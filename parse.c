#include "ft_printf.h"

int ft_parse_flag(const char** format)
{
	int flag;

	flag = 0;
	while (**format == '-' || **format == '0')
	{
		if (**format == '0' && (*format)++)
			flag = '0';
		else if (**format == '-' && (*format)++)
			flag = (**format == '0' && (*format)++ ? '-' : '-');
	}
	return flag;
}

int	ft_parse_number(const char** format, va_list* ap, char option)
{
	int	ret;

	ret = 0;

	while (**format == ' ' && option == 'w')
		write(1, " ", 1) && (*format)++;
	if (**format == '*')
	{
		(*format)++;
		ret = va_arg(*ap, int);
		if (option == 'p' && ret == 0)
			ret = -3;
		else if (option == 'p' && ret < 0)
			ret = -2;
		return (ret);
	}
	while ('0' <= **format && **format <= '9')
		ret = ret * 10 + *((*format)++) - '0';
	if (option == 'p')
		ret = (ret > 0 ? ret : -1);
	return (ret);
}

long long ft_parse_specifier(const char** format, va_list* ap, t_info *info)
{
	long long	value;

	value = 0;
	if (**format == 'd' || **format == 'i' || **format == 'c' || **format == 'o')
		value = (long long)va_arg(*ap, int);
	else if (**format == '%')
		(value = '%') && (info->precision = 0);
	else if (**format == 's')
		value = (long long)va_arg(*ap, char*);
	else if (**format == 'u' || **format == 'x' || **format == 'X')
		value = (long long)va_arg(*ap, unsigned int);
	else if (**format == 'p')
		value = (unsigned long)va_arg(*ap, void*);
	else
	{
		info->type = 'e';
		return 0;
	}

	info->type = **format;
	(*format)++;
	return value;
}
