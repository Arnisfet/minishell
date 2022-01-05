/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmacmill <jmacmill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 21:51:41 by mrudge            #+#    #+#             */
/*   Updated: 2022/01/05 15:46:24 by jmacmill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_bultin(char **str, t_struct *p)
{
	if (find_str(str[0], "cd"))
		build_cd(str, p);
	if (find_str(str[0], "pwd"))
		build_pwd(str);
	if (find_str(str[0], "echo"))
	{
		if (builtin_echo(str + 1, p))
			return (1);
	}
	if (find_str(str[0], "env"))
		builtin_env(p);
	if (find_str(str[0], "unset"))
		build_unset(str, p);
	if (find_str(str[0], "export"))
			build_export(str, p);
	if (find_str(str[0], "exit"))
		return (-1);
	return (0);
}

int	execute(char *path, char **str, t_struct *p)
{
	pid_t	child;
	
	child = fork();
	if (child == -1)
	{
		ft_putstr_fd("Error creating a process\n", 2);
		return (-1);
	}
	if (child == 0)
	{
		if (execve(path, str, p->arr_env) == -1)
			perror("Could not execute execve");
	}
	waitpid(child, NULL, 0);
	return (1);
}

void	free_array(char **str)
{
	int	i;

	if (str)
	{
		i = 0;
		while (str[i])
		{
			free(str[i]);
			i++;
		}
		free(str);
	}
}

int	start_execve(char *path, char **str, struct stat s, t_struct *p)
{
	if (s.st_mode & S_IFREG)
	{
		if (s.st_mode & S_IXUSR)
			return (execute(path, str, p));
		else
		{
			ft_putstr_fd("minishell: permission denied: ", 2);
			ft_putendl_fd(path, 2);
		}
		free(path);
		return (1);
	}
	free(path);
	return (0);
}

int	check_execve(char **str, t_struct *p)
{
	struct stat	s;
	char		*path;
	char		*execve_path;
	char		**spl_path;
	int			i;

	path = get_env_var("PATH", p);
	if (path)
	{
		i = 0;
		spl_path = ft_split(path, ':');
		while (spl_path[i])
		{
			if (find_str(str[0], spl_path[i]))
				execve_path = ft_strdup(str[0]);
			if (lstat(execve_path, &s) == -1)
				free(execve_path);
			else
			{
				free_array(spl_path);
				return (start_execve(execve_path, str, s, p));
			}
			i++;
		}
		free_array(spl_path);
	}
	return (0);	
}

int	parse_cmd(char **str, t_struct *p)
{
	int	result;
	
	result = check_bultin(str, p);
	if (result == 1)
		return (0);
	if (result == -1)
		return (-1);
	if (check_execve(str, p))
		return (0);
	//execute(str[0], str, p);
	return (1);
}
