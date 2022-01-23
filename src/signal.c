/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmacmill <jmacmill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 16:35:33 by jmacmill          #+#    #+#             */
/*   Updated: 2022/01/23 12:53:39 by jmacmill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ctrl_c_parent(int status)
{
	status++;
	rl_on_new_line();
	rl_redisplay();
	ft_putstr_fd("  \b\b\n", 1);
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
}

void	ctrl_slash_parent(int status)
{
	rl_on_new_line();
	rl_redisplay();
	ft_putstr_fd("  \b\b", 1);
	rl_redisplay();
}

void	ctrl_c_child(int status)
{
	status++;
	g_status = 130;
	printf("\n");
}

void	ctrl_slash_child(int status)
{
	ft_putstr_fd("Quit: 3\n", 1);
}

void	ctrl_c_fork(int status)
{
	status++;
	write(1, "\b\b  \b\b\n", 7);
}
