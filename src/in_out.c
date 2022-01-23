/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_out.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmacmill <jmacmill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 14:24:06 by jmacmill          #+#    #+#             */
/*   Updated: 2022/01/23 14:25:41 by jmacmill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	check_in(t_struct *p)
{
	if (check_infile(p, p->idx))
	{
		p->fdin = open(get_infile(p, p->idx), O_RDONLY, 0644);
		if (p->fdin == -1)
			perror("minishell");
	}
}

void	redirect_in(t_struct *p)
{
	dup2(p->fdin, 0);
	close(p->fdin);
}

void	redirect_out(t_struct *p)
{
	dup2(p->fdout, 1);
	close(p->fdout);
}

void	check_out(t_struct *p)
{
	if (check_outfile(p, p->idx))
		p->fdout = get_outfile(p, p->idx);
	else
		p->fdout = dup(p->tmpout);
}

void	child(char **commands, t_struct *p)
{
	if (p->idx != 0)
		check_in(p);
	redirect_in(p);
	if (p->idx == p->total_cmd - 1)
		check_out(p);
	else
	{
		pipe(p->fdpipe);
		if (check_outfile(p, p->idx))
		{
			p->fdout = get_outfile(p, p->idx);
			dup2(p->fdout, p->fdpipe[1]);
		}
		else
			p->fdout = p->fdpipe[1];
		p->fdin = p->fdpipe[0];
	}
	redirect_out(p);
	p->pid[p->idx] = fork();
	if (p->pid[p->idx] == 0)
	{
		if (p->fdin != -1)
			choose_func(commands, p);
		exit(1);
	}
}