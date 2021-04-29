#include "ft_printf.h"

size_t	ft_strlen(const char* s)
{
	size_t i;

	i = 0;
	while (*s++)
		i++;
	return (i);
}

int		ft_get_number_len(long long n, int len)
{
	int	i;

	i = 1;
	while ((n /= len) > 0)
		++i;
	return (i);
}

void	put_number(long long n, char* base, int len)
{
	if (n > len - 1)
		put_number(n / len, base, len);
	write(1, &(base[n % len]), 1) && g_ret++;
}

void	ft_bzero(void* s, size_t n)
{
	char* ptr;

	ptr = (char*)s;
	while (n--)
	{
		*ptr = 0;
		ptr++;
	}
}
