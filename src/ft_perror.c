#include "malloc.h"

void	ft_perror(const char *msg)
{
	extern const int			errno;
	extern const char	* const sys_errlist[];

	if (msg)
	{
		ft_putstr_fd(msg, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(sys_errlist[errno], 2);
}

void	malloc_err(const char *msg, void *ptr)
{
	ft_printf("malloc: *** error for object %p : %s\n", ptr, msg);
}