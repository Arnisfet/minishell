/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmacmill <jmacmill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 18:36:20 by jmacmill          #+#    #+#             */
/*   Updated: 2022/01/23 18:19:57 by jmacmill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	execute(char *path, char **str, t_struct *p)
{
	int	ret;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	ret = fork();
	if (ret == -1)
		ft_putendl_fd("Unable to create a fork", 2);
	if (ret == 0)
	{
		signal(SIGINT, ctrl_c_child);
		signal(SIGQUIT, ctrl_slash_child);
		if (execve(path, str, p->arr_env) == -1)
			perror("Could not execute execve");
	}
	else
		waitpid(ret, NULL, 0);
	return (1);
}

int	execute_chld(char *path, char **str, t_struct *p)
{
	if (execve(path, str, p->arr_env) == -1)
		perror("Could not execute execve");
	return (1);
}

int	start_execve(char *path, char **str, t_struct *p)
{
	if (p->total_cmd == 1)
		execute(path, str, p);
	else
		execute_chld(path, str, p);
	free(path);
	return (0);
}
