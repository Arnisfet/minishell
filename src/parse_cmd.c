/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmacmill <jmacmill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 17:57:10 by mrudge            #+#    #+#             */
/*   Updated: 2022/01/12 20:32:00 by mrudge           ###   ########.fr       */
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

char	**split_string(char **commands, t_struct *p)
{
	int		i;
	char	**new_arr;

	i = 0;
	while (commands[i])
	{
		new_arr = ft_split_quotes(commands[i], ' ');
		new_arr = parse_strings(new_arr, p);
		printr(new_arr);
		i++;
	}
	ft_free(commands);
	return (new_arr);
}

int	parse_cmd(char *line, t_struct *p)
{
	char	**commands;

	p->error = 0;
	if (check_string(line, p) != 0)
		return (2);
	commands = parse_pipe(line, p);
	if (p->error != 0)
	{
		if (commands)
			ft_free(commands);
		return (1);
	}
	commands = parse_redirect(commands, p);
	if (p->error != 0)
	{
		ft_free(commands);
		return (2);
	}
	commands = split_string(commands, p);
	if (p->redirect)
		print_list(p);
	ft_free(commands);
	return (0);
}
