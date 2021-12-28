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

void	switch_dir(char *path, t_struct *p)
{
	char	*pwd;
	char	buf[4096 + 1];
	t_env	*tmp;

	pwd = getcwd(buf, 4096);
	if (chdir(path) == 0)
		return ;
	else
	{
		ft_putstr_fd("cd: string not in pwd: ", 2);
		return ;
	}
	tmp = p->my_env;
	while (tmp != NULL)
	{
		if (find_str("OLDPWD", tmp->var))
		{
			free(tmp->value);
			tmp->value = ft_strdup(pwd);
			break ;
		}
		tmp = tmp->next;
	}
}

void	update_var(char *s1, char *s2, t_struct *p)
{
	t_env	*tmp;

	tmp = p->my_env;
	while (tmp != NULL)
	{
		if (find_str(s1, tmp->var))
		{
			if (tmp->value)
				free(tmp->value);
			tmp->value = ft_strdup(s2);
			break ;
		}
		tmp = tmp->next;
	}
}

void	go_to_dir(char *path, t_struct *p)
{
	t_env	*tmp;
	char	*cwd;
	char	buff[4096 + 1];

	cwd = getcwd(buff, 4096);
	if (chdir(path) != 0)
	{
		ft_putstr_fd("cd: string not in pwd: ", 2);
		return ;
	}
	update_var("OLDPWD", cwd, p);
	update_var("PWD", path, p);
}

int	build_cd(char **str, t_struct *p)
{
	char	*home_path;
	char	*old_path;
	
	home_path = get_env_var("HOME", p);
	old_path = get_env_var("OLDPWD", p);
	
	if (!str[1])
	{
		go_to_dir(home_path, p);
		return (1);
	}
	else
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
			switch_dir(old_path, p);
			return (1);
		}
	}
	return (1);
}
