/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmacmill <jmacmill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 17:57:10 by mrudge            #+#    #+#             */
/*   Updated: 2022/01/05 20:04:37 by jmacmill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

int	check_bultin(char **str, t_struct *p)
{
	if (find_str(str[0], "cd"))
		return (build_cd(str, p));
	if (find_str(str[0], "pwd"))
	{
		build_pwd(str);
		return (1);
	}
	if (find_str(str[0], "echo"))
	{
		if (builtin_echo(str + 1, p))
			return (1);
	}
	if (find_str(str[0], "env"))
		return (builtin_env(p));
	if (find_str(str[0], "unset"))
		return (build_unset(str, p));
	if (find_str(str[0], "export"))
		return (build_export(str, p));
	if (find_str(str[0], "exit"))
	{
		build_exit(str, p);
		return (-1);
	}
	return (0);
}

int	launch(char **commands, t_struct *p)
{
	int	i;
	int	result;
	char	**spl_str;

	i = 0;
	while (commands[i])
	{
		spl_str = ft_split(commands[i], ' ');
		if (spl_str)
		{
			result = check_bultin(spl_str, p);
			if (result == 1)
				return (0);
			if (result == -1)
				return (-1);
			if (check_execve(spl_str, p))
				return (0);
		}
		i++;
	}
	return (1);
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
