/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohykim <dohykim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 07:19:27 by dohykim           #+#    #+#             */
/*   Updated: 2021/05/03 18:35:57 by dohykim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t		ft_strlen(long long n, t_info *info)
{
	size_t	i;

	i = 0;
	if (info->value != 0)
		while (*((char*)n + i) != '\0')
			i++;
	else
		(i = 6) &&
		(info->value = "(null)");
	if (info->precision < 0 && !(info->precision == -2))
		i = 0;
	else
		i = (i > info->precision &&
		info->precision != 0 ? info->precision : i);
	return (i);
}

size_t		ft_typelen(const char **s, long long n, int len, t_info *info)
{
	size_t	i;

	i = 0;
	if (info->type == 'c' || info->type == '%')
	{
		i = ((char)n == '\0' || (char)n < 0 ? 1 : 0);
		if ((char)n > 0 && (char)n < 128)
			i++;
	}
	else if (info->type == 's')
	{
		i = ft_strlen(n, info);
		if (i == 1)
			*s = **s;
	}
	else
	{
		i = 1;
		while ((n /= len) > 0)
			++i;
	}
	return (i);
}

void		put_number(long long n, char *base, int len)
{
	if (n > (unsigned long long)len - 1)
		put_number(n / len, base, len);
	g_ret += write(1, &(base[n % len]), 1);
}

int			put_string(int len, char *buf)
{
	int		i;

	i = 0;
	if (len == 1)
		g_ret += write(1, buf, 1);
	else
		g_ret += write(1, *(char**)buf, len);
	return (i);
}

int			print_write(int len, char *buf)
{
	int		i;

	i = 0;
	while (i++ < len)
		g_ret += write(1, buf, 1);
	return (i);
}
