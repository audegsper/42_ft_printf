/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohykim <dohykim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 07:19:01 by dohykim           #+#    #+#             */
/*   Updated: 2021/05/03 08:44:52 by dohykim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		init_struct(t_info *info)
{
	info->flag = 0;
	info->sign = 0;
	info->width = 0;
	info->value = 0;
	info->precision = 0;
	info->type = 0;
}

int			ft_printf(const char *format, ...)
{
	va_list ap;
	t_info	info;
	int		prec;

	va_start(ap, format);
	prec = 0;
	g_ret = 0;
	while (*format != '\0')
	{
		init_struct(&info);
		if (*format == '%' && format++)
		{
			info.flag = ft_parse_flag(&format);
			if ((info.width = ft_parse_number(&format, &ap, 'w')) < 0)
				(info.width = -(info.width)) &&
				(info.flag = '-');
			if (*format == '.' && format++)
				info.precision = ft_parse_number(&format, &ap, 'p');
			if ((info.value = ft_parse_specifier(&format, &ap, &info)) < 0 &&
			!(info.type == 'c' || info.type == 's') && (info.sign = 1))
				info.value = info.value * -1;
			ft_print_value(info);
		}
		else
			g_ret += write(1, format++, 1);
	}
	return (g_ret);
}
