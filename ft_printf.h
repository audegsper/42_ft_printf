/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohykim <dohykim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 07:19:31 by dohykim           #+#    #+#             */
/*   Updated: 2021/05/03 22:18:02 by dohykim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

typedef struct		s_info
{
	long long		value;
	int				type;
	int				flag;
	int				width;
	int				precision;
	int				sign;
}					t_info;

int					g_ret;

/*
********** ft_printf.c **************
*/
int					ft_printf(const char *format, ...);
void				init_struct(t_info *info);
/*
********** parse.c **************
*/
int					ft_parse_flag(const char **format);
int					ft_parse_number(const char **format, va_list *ap, char option);
long long			ft_parse_specifier
					(const char **format, va_list *ap, t_info *info);
/*
********** print.c **************
*/
void				ft_print_value(t_info info);
/*
********** utils.c **************
*/
int					put_string(int len, char *buf);
int					print_write(int gap, char *str);
void				put_number(long long n, char *base, int len);
size_t				ft_typelen(char **s, long long n, int len, t_info *info);

#endif
