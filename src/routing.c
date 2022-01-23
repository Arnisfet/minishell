/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmacmill <jmacmill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 14:17:39 by jmacmill          #+#    #+#             */
/*   Updated: 2022/01/23 15:35:02 by jmacmill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	make_pids(t_struct *p)
{
	if (p->total_cmd != 0)
	{
		p->pid = (pid_t *)malloc((p->total_cmd) * sizeof(pid_t));
		if (!(p->pid))
		{
			ft_putendl_fd("Error: unable to allocate memory", 2);
			return (2);
		}
	}
	return (0);
}

void	preparation(t_struct *p)
{
	ignore_signals();
	p->tmpin = dup(0);
	p->tmpout = dup(1);
	p->here_doc = 0;
	p->idx = 0;
}

void	check_minishell(char **new_arr, t_struct *p)
{
	int	a;

	a = 0;
	if (find_str(new_arr[0], "exit"))
	{
		build_exit(new_arr, p);
		return ;
	}
	if (p->total_cmd == 1)
	{
		a = 0;
		a = check_bultin(new_arr, p);	
	}
	if (a == 1)
		return ;
	if (ft_strncmp(new_arr[0], "./minishell", 12))
		on_chld_signals();
	child(new_arr, p);
}

void	minishell_wo_pipes(char **array, t_struct *p)
{
	int	i;
	int	a;

	i = 0;
	dup2(p->fdin, 0);
	close(p->fdin);
	check_out(p);
	redirect_out(p);
	a = 0;
	if (find_str(array[0], "exit"))
	{
		build_exit(array, p);
		return ;
	}
	i = check_bultin(array, p);
	if (i == 0)
	{
		if (access(array[0], (F_OK & X_OK)) == 0)
			execute(array[0], array, p);
		else
			check_execve(array, p);
	}
}

void	route_minishell(char **array, t_struct *p)
{
	if (p->total_cmd == 1)
	{
		// if (!ft_strncmp(array[0], "./minishell", 12))
		// {
		// 	ignore_signals();
		// 	write(2, "mini\n", 5);
		// 	start_execve(array[0], array, p);
		// }

			if (p->fdin == -1)
			return ;
		minishell_wo_pipes(array, p);
	
	}
	else
	{
		if (ft_strncmp(array[0], "./minishell", 12))
			on_chld_signals();
		child(array, p);
	}
}