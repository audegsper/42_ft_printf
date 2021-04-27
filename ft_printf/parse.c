#include "ft_printf.h"

int ft_parse_flag(const char** format)
{
	int flag;

	while (**format == '-' || **format == '0')
	{
		if (**format == '0' && (*format)++)
			flag = '0';
		else if (**format == '-' && (*format)++)
			flag = '-';
	}
	return flag;
}

int	ft_parse_number(const char** format, va_list* ap)
{
	int	ret;

	ret = 0;
	if (**format == '*')
	{
		(*format)++;
		ret = va_arg(*ap, int);
		return (ret);
	}
	while ('0' <= **format && **format <= '9')
		ret = ret * 10 + *((*format)++) - '0';
	return (ret);
}

long long ft_parse_specifier(const char **format, va_list *ap)
{
	long long	value;

	value = 0;
	if (**format == 'd' || **format == 'i' || **format == 'c')
	{
		(value = (long long)va_arg(*ap, int));
		(*format)++;
	}
	else if (**format == '%')
		value = '%';
	else if (**format == 's')
		value = (long long)va_arg(*ap, char*);
	else if (**format == 'u' || **format == 'x' || **format == 'X')
		value = (long long)va_arg(*ap, unsigned int);
	else if (**format == 'p')
		value = (long long)va_arg(*ap, void*);

	return value;
}
