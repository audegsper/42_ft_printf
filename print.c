/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohykim <dohykim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 08:07:40 by dohykim           #+#    #+#             */
/*   Updated: 2021/05/03 08:07:42 by dohykim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

	i = 0;
	if (len == 1)
		g_ret += write(1, buf, 1);
	else
		g_ret += write(1, *(char**)buf, len);
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
	int len;
	int base;
	char* note;

	zero = 0;
	gap = 0;
	if (info.type == 'p' || info.type == 'x' || info.type == 'X')
	{
		base = 16;
		note = (info.type == 'x' || info.type == 'p' ? "0123456789abcdef" : "0123456789ABCDEF");
	}
	else if (info.type == 'o')
	{
		base = 8;
		note = "01234567";
	}
	else
	{
		base = 10;
		note = "0123456789";
	}
	len = ft_typelen(&info.value, info.value, base, &info);

	if (info.precision > 0 && !(info.type == 'c' || info.type == 's'))
		zero = info.precision - len;
	else if (info.precision != -3 && (info.flag == '0' && (info.precision > -1 || info.precision == -2)))
		zero = info.width - len - info.sign - (info.type == 'p' ? 2 : 0);
	zero = zero > 0 ? zero : 0;
	if ((info.width >= info.precision && info.width > len) || info.value <= 0 || (info.type == 's' && info.width < info.precision))
		if (!(info.type == 'c' || info.type == 's') && info.value == 0 && (info.precision == -1 || info.precision == -3) || (info.type == 's' && info.width < info.precision))
			gap = info.width - (info.type == 'p' ? 2 : 0) - (info.type == 's' && info.precision > len ? len : info.type == 's' ? info.precision : 0);
		else
			gap = (info.precision > info.width ? info.width - info.precision : info.width - len - zero) - info.sign - (info.type == 'p' ? 2 : 0);
	if (!(info.flag == '-'))
		print_write(gap, " ");
	print_write(info.sign, "-");
	if (info.type == 'p' ? g_ret += write(1, &"0x", (info.type == 'p' ? 2 : 0)) : 0);
	if (!(info.type == 'c'))
		print_write(zero, "0");
	if (info.type == '%' && info.value != 0)
		g_ret += write(1, &info.value, 1);
	else if (!(info.type == 'c' || info.type == 's' || info.type == '%') && !(info.value == 0 && (info.precision == -1 || info.precision == -3)))
		put_number(info.value, note, base);
	else if (info.type == 'c' || info.type == 's')
		put_string(len, &info.value);
	if (info.flag == '-')
		print_write(gap, " ");

	return 1;
}
