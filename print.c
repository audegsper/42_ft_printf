#include "ft_printf.h"

void	put_number(long long n, char* base, int len)
{
	if (n > (long long)len - 1)
		put_number(n / len, base, len);
	g_ret += write(1, &(base[n % len]), 1);
}

int	put_string(int len, char* buf)
{
	int i;

	//printf("{len : %d, buf : %s}\n", len, buf);
	i = 0;
	if (len == 1)
		g_ret += write(1, buf, 1);
	else
		g_ret += write(1, *(char **)buf, len);
	//g_ret += _write(1, buf, len);
	/*while (i++ < len)
	{
		g_ret += _write(1, buf, 1);
		buf++;
	}*/
	return i;
}

int print_write(int len, char* buf)
{
	int i;

	i = 0;
	while (i++ < len)
		g_ret += write(1, buf, 1);
	return i;
}

int	ft_print_value(t_info info)
{
	int gap;
	int zero;
	int prefix;
	int base;
	char* note;

	zero = 0;
	gap = 0;
	prefix = 0;
	if (info.type == 'p' || info.type == 'x' || info.type == 'X')
	{
		base = 16;
		note = (info.type == 'x' || info.type == 'p' ? "0123456789abcdef" : "0123456789ABCDEF");
		prefix = (info.type == 'p' ? 2 : 0);
	}
	else
	{
		base = 10;
		note = "0123456789";
	}

	if (info.precision > 0)
		zero = info.precision - ft_typelen(&info.value,info.value, base, info);
	else if (info.precision != -3 && (info.flag == '0' && (info.precision > -1 || info.precision == -2)))
		zero = info.width - ft_typelen(&info.value, info.value, base, info) - info.sign - prefix;
	zero = zero > 0 ? zero : 0;
	if ((info.width > info.precision && info.width > ft_typelen(&info.value, info.value, base, info)) || info.value <= 0)
		if (!(info.type == 'c' || info.type == 's') && info.value == 0 && (info.precision == -1 || info.precision == -3))
			gap = info.width - prefix;
		else
			gap = (info.precision > info.width ? info.width - info.precision : info.width - ft_typelen(&info.value, info.value, base, info) - zero) - info.sign - prefix;
	if (!(info.flag == '-'))
		print_write(gap, " ");
	print_write(info.sign, "-");
	if (info.type == 'p' ? g_ret += write(1, &"0x", prefix) : 0);
	print_write(zero, "0");
	if (!(info.type == 'c' || info.type == 's') && !(info.value == 0 && (info.precision == -1 || info.precision == -3)))
		put_number(info.value, note, base);
	else if (info.type == 'c' || info.type == 's')
		put_string(ft_typelen(&info.value, info.value, base, info), &info.value);
	if (info.flag == '-')
		print_write(gap, " ");

	return 1;
}
