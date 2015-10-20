# include <unistd.h>
# include "malloc.h"

void	ft_putnbr(int n)
{
	if (n == -2147483648)
	{
		ft_putstr("-2147483648");
		return ;
	}
	if (n < 0)
	{
		ft_putchar('-');
		n *= -1;
	}
	if (n / 10 != 0)
	{
		ft_putnbr(n / 10);
	}
	ft_putchar((n % 10) + '0');
}

size_t	ft_strlen(char *s)
{
	char	*tmp;

	if (!s)
		return (0);
	tmp = s;
	while (*tmp)
		tmp++;
	return (tmp - s);
}