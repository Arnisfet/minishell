#include "minishell.h"

int	build_cd(const char *str)
{
	char	*error;

	if (chdir(str) == 0)
	{
		return (0);
	}
	error = strerror(errno);
	ft_putstr_fd(error, 1);
	return (1);
}

