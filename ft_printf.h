/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohykim <dohykim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 07:19:31 by dohykim           #+#    #+#             */
/*   Updated: 2021/05/03 18:56:40 by dohykim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct	s_info
{
	long long	value;
	int			type;
	int			flag;
	int			width;
	int			precision;
	int			sign;
}				t_info;

int	g_ret;

int				ft_printf(const char *format, ...);
void			init_struct(t_info *info);

int				ft_parse_flag(const char **format);
int				ft_parse_number(const char **format, va_list *ap, char option);
long long		ft_parse_specifier
					(const char **format, va_list *ap, t_info *info);

void				ft_print_value(t_info info);
int				print_write(int gap, char *str);
void			put_number(long long n, char *base, int len);
int				put_string(int len, char *buf);
int	calcualte_option (t_info info, int len, int zero, char option);
void calc_base(int *base, char** note, t_info info);
int		calc_gap(t_info info, int len, int zero);

size_t			ft_strlen(long long n, t_info *info);
size_t			ft_typelen(const char **s, long long n, int len, t_info *info);

#endif
