#include "minitalk.h"

int ft_error(char *str)
{
	ft_putendl_fd(str, 2);
	return (0);
}

void	ft_putendl_fd(char *s, int fd)
{
	if (s)
	{
		while (*s)
			write(fd, s++, 1);
		write(fd, "\n", 1);
	}
}

int	ft_isdigit(char *str)
{
	while (*str)
	{
		if (!(*str >= '0' && *str <= '9'))
			return (1);
		str++;
	}
	return (0);
}


void	ft_putnbr_fd(int n, int fd)
{
	long long	x;

	x = n;
	if (x < 0)
	{
		x = -x;
		write(fd, "-", 1);
	}
	if (x / 10)
		ft_putnbr_fd(x / 10, fd);
	x %= 10;
	x += '0';
	write(fd, &x, 1);
}

int	ft_atoi(const char *str)
{
	long	nmb;
	int		sign;

	nmb = 0;
	sign = 1;
	while (*str == '\t' || *str == '\n'
		   || *str == '\v' || *str == '\f'
		   || *str == '\r' || *str == ' ')
		++str;
	if (*str == '-')
	{
		sign = -1;
		++str;
	}
	else if (*str == '+')
		++str;
	while (*str >= '0' && *str <= '9')
	{
		nmb += *str - 48;
		nmb *= 10;
		++str;
	}
	nmb /= 10;
	return ((int)(nmb * sign));
}