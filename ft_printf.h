#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct	s_info
{
	long long	value;
	int			flag;
	int			width;
	int			precision;
	int			sign;
}				t_info;

int	g_ret;

int	ft_printf(const char *format, ...);

int ft_parse_flag(const char** format);
int	ft_parse_number(const char** format, va_list* ap, char option);
long long ft_parse_specifier(const char** format, va_list* ap);

int	ft_print_value(t_info info);
int print_write(int gap, char* str);

void	put_number(long long n, char* base, int len);
void	ft_bzero(void* s, size_t n);
size_t	ft_strlen(const char* s);
int		ft_get_number_len(long long n, int len);

#endif
