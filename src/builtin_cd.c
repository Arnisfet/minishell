#include "../inc/minishell.h"

void	get_error()
{
	char	*error;

	error = strerror(errno);
	ft_putstr_fd(error, 2);
}

int	find_str(const char *s1,const char *s2)
{
	int	result;

	if (!s1 || !s2)
		return (0);
	result = strcmp(s1, s2);
	if (result == 0)
		return (1);
	return (0);
}

int	build_cd(char **str, t_struct *p)
{
	char	*home_path;
	char	*old_path;
	
	home_path = get_env_var("HOME", p);
	old_path = get_env_var("OLDPWD", p);
	
	if (str[1])
	{
		if (str[2])
		{
			ft_putstr_fd("cd: string not in pwd: ", 2);
			return (-1);
		}
		else if (find_str(str[1], "--") || find_str(str[1], "~"))
		{
			chdir(home_path);
			return (1);
		}
		else if (find_str(str[1], "-"))
		{
			chdir(old_path);
			return (1);
		}
	}
	if (chdir(str[1]) == 0)
		return (1);
	else
	{
		ft_putstr_fd("cd: no such file or directory: ", 2);
		ft_putstr_fd(str[1], 2);
	}
	return (-1);
}
