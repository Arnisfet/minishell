#include "minishell.h"

char	*build_pwd(char **str)
{
	char	*cwd;
	char	buf[4096 + 1];

	if (str[1])
	{
		ft_putstr_fd("pwd: too many arguments", 2);
		return (NULL);
	}
	else
	{
		cwd = getcwd(buf, 4096);
		printf("pwd: %s\n", cwd);
	}
	return (cwd);
}
