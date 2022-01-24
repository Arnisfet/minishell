/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmacmill <jmacmill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 18:36:20 by jmacmill          #+#    #+#             */
/*   Updated: 2022/01/24 20:04:38 by jmacmill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	execute(char *path, char **str, t_struct *p)
{
	int	ret;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (ft_strncmp(path, "./minishell", 12))
		on_chld_signals();
	ret = fork();
	if (ret == -1)
		ft_putendl_fd("Unable to create a fork", 2);
	if (ret == 0)
	{
		if (execve(path, str, p->arr_env) == -1)
		{
			p->error = 126;
			perror("Could not execute execve");
		}
	}
	else
		waitpid(ret, NULL, 0);
	return (1);
}

int	execute_chld(char *path, char **str, t_struct *p)
{
	if (execve(path, str, p->arr_env) == -1)
	{
		p->error = 126;
		perror("Could not execute execve");
	}
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
