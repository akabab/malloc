#include <unistd.h>

void		ft_putchar(const char c)
{
	write(1, &c, 1);
}

void		ft_putchar_fd(const char c, int fd)
{
	write(fd, &c, 1);
}

void		ft_putstr(const char *str)
{
	while (*str)
	{
		ft_putchar(*str);
		str++;
	}
}

void		ft_putstr_fd(const char *str, int fd)
{
	while (*str)
	{
		ft_putchar_fd(*str, fd);
		str++;
	}
}

void		ft_putendl_fd(const char *s, int fd)
{
	ft_putstr_fd(s, fd);
	ft_putchar_fd('\n', fd);
}
