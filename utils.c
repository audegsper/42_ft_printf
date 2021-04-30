#include "ft_printf.h"

size_t	ft_strlen(const char* s)
{
	size_t i;

	i = (*s == '\0' || *s < 0 ? 1 : 0);
	while (*s > 0 && *s < 128 && *s++)
		i++;
	return (i);
}

int		ft_numlen(long long n, int len)
{
	int	i;

	i = 1;
	while ((n /= len) > 0)
		++i;
	return (i);
}

size_t	ft_typelen(const char** s, long long n, int len, t_info info)
{
	size_t	i;

	i = 0;
	if (info.type == 'c')
	{
		i = ((char)n == '\0' || (char)n < 0 ? 1 : 0);
		if ((char)n > 0 && (char)n < 128)
			i++;
	}
	else if (info.type == 's')
	{
		while (*((char*)n + i) != '\0')
			i++;
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