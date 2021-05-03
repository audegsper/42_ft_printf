/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohykim <dohykim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 08:07:40 by dohykim           #+#    #+#             */
/*   Updated: 2021/05/03 22:54:35 by dohykim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		calc_zero(t_info info, int len)
{
	int			num;

	num = 0;
	if (info.precision > 0 && !(info.type == 'c' || info.type == 's'))
		num = info.precision - len;
	else if (info.precision != -3 &&
		(info.flag == '0' && (info.precision > -1 || info.precision == -2)))
		num = info.width - len - info.sign - (info.type == 'p' ? 2 : 0);
	num = num > 0 ? num : 0;
	return (num);
}

static int		calc_gap(t_info info, int len, int zero)
{
	int			num;

	num = 0;
	if ((info.width >= info.precision && info.width > len) || info.value <= 0
		|| (info.type == 's' && info.width < info.precision))
	{
		if ((!(info.type == 'c' || info.type == 's') && info.value == 0 &&
		(info.precision == -1 || info.precision == -3)) ||
		(info.type == 's' && info.width < info.precision))
		{
			num = info.width - (info.type == 'p' ? 2 : 0);
			if (info.type == 's' && info.precision > len)
				num = num - len;
			else if (info.type == 's')
				num = num - info.precision;
		}
		else
		{
			num = (info.precision > info.width ? info.width - info.precision :
			info.width - len - zero) - info.sign;
			if (info.type == 'p')
				num = num - 2;
		}
	}
	return (num);
}

static void		calc_base(int *base, char **note, t_info info)
{
	if (info.type == 'p' || info.type == 'x' || info.type == 'X')
	{
		*base = 16;
		*note = (info.type == 'x' || info.type == 'p' ?
		"0123456789abcdef" : "0123456789ABCDEF");
	}
	else if (info.type == 'o')
	{
		*base = 8;
		*note = "01234567";
	}
	else
	{
		*base = 10;
		*note = "0123456789";
	}
}

void			ft_print_value(t_info info)
{
	int			gap;
	int			zero;
	int			len;
	int			base;
	char		*note;

	calc_base(&base, &note, info);
	len = ft_typelen((char **)(&info.value), info.value, base, &info);
	zero = calc_zero(info, len);
	gap = calc_gap(info, len, zero);
	if (!(info.flag == '-'))
		print_write(gap, " ");
	print_write(info.sign, "-");
	info.type == 'p' ? g_ret += write(1, &"0x", 2) : 0;
	if (!(info.type == 'c'))
		print_write(zero, "0");
	if (info.type == '%' && info.value != 0)
		g_ret += write(1, &info.value, 1);
	else if (!(info.type == 'c' || info.type == 's' || info.type == '%') &&
	!(info.value == 0 && (info.precision == -1 || info.precision == -3)))
		put_number(info.value, note, base);
	else if (info.type == 'c' || info.type == 's')
		put_string(len, (char *)(&info.value));
	if (info.flag == '-')
		print_write(gap, " ");
}
