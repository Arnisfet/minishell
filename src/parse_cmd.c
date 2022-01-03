/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmacmill <jmacmill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 21:51:41 by mrudge            #+#    #+#             */
/*   Updated: 2022/01/03 17:44:17 by jmacmill         ###   ########.fr       */
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

int	execute(char **str, t_struct *p)
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
		if (execve(str[0], str, p->arr_env) == -1)
			perror("Could not execute execve");
	}
	waitpid(child, NULL, 0);
	return (1);
}

int	check_execve(char *str, t_struct *p)
{
	
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
	execute(str, p);
	return (1);
}
