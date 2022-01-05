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

int	parse_cmd(char *line, t_struct *p)
{
	char	**commands;
	int		i;
	
	p->trim_env = NULL;
	commands = parse_pipe(line, p);
	commands = parse_redirect(commands, p);
	commands = parse_strings(commands, p);
	
	print_list(p);
	printr(commands);
	return (launch(commands, p));
}
