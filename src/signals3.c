/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmacmill <jmacmill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 14:15:54 by jmacmill          #+#    #+#             */
/*   Updated: 2022/01/23 14:18:51 by jmacmill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ignore_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	on_chld_signals(void)
{
	signal(SIGINT, ctrl_c_child);
	signal(SIGQUIT, ctrl_slash_child);
}

void	on_parent_signals(void)
{
	signal(SIGQUIT, ctrl_slash_parent);
	signal(SIGINT, ctrl_c_parent);
}

void	restore_std(t_struct *p)
{
	dup2(p->tmpin, 0);
	dup2(p->tmpout, 1);
	close(p->tmpin);
	close(p->tmpout);
}

void	global_wait(t_struct *p)
{
	int	i;

	i = 0;
	while (i < p->total_cmd)
	{
		waitpid(p->pid[i], NULL, 0);
		i++;
	}
}