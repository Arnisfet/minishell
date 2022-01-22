/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmacmill <jmacmill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 16:35:33 by jmacmill          #+#    #+#             */
/*   Updated: 2022/01/21 20:55:48 by jmacmill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ctrl_c_parent(int status)
{
	status++;
	// write(2, "ctrl+c parent\n", 14);
	// g_question = 130;
	rl_on_new_line();
	rl_redisplay();
	ft_putstr_fd("  \b\b\n", 1);
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
}

void	ctrl_slash_parent(int status)
{
	// write(2, "ctrl+slash parent\n", 18);
	rl_on_new_line();
	rl_redisplay();
	ft_putstr_fd("  \b\b", 1);
	rl_redisplay();
}

void	ctrl_c_heredoc(int status)
{
	int		file;

	(void)status;
	write(1, "\n", 1);
	// rl_on_new_line();
	exit(130);
}

void	ctrl_c_child(int status)
{
	// write(2, "ctrl+c\n", 7);
	status++;


	// exit(1);
	printf("\n");
	// g_question = 130;
	// rl_on_new_line();
	// rl_redisplay();
	// ft_putstr_fd("  \b\b\n", 1);
	// rl_on_new_line();
	// rl_replace_line("", 1);
	// rl_redisplay();
	//exit(300);
}

void	ctrl_slash_child(int status)
{
	// write(2, "slash\n", 6);
	// rl_on_new_line();
	// rl_redisplay();
	ft_putstr_fd("Quit: 3\n", 1);
	// ft_putendl_fd("", 1);
	// rl_redisplay();
	// exit(1);
}

// void	ctrl_c_redirect_heredoc(int status)
// {
// 	int		file;

// 	status++;
// 	write(1, "\n", 1);
// 	file = open(".heredoc_error", O_CREAT | O_TRUNC | O_RDWR, 0644);
// 	write(file, "ctrl_c_redirect_heredoc",
// 		ft_strlen("ctrl_c_redirect_heredoc"));
// 	rl_on_new_line();
// 	close(file);
// 	exit(130);
// }

void	ctrl_c_pipe_heredoc(int status)
{
	status++;
	write(1, "\n", 1);
	rl_on_new_line();
	exit(130);
}

void	ctrl_c_fork(int status)
{
	status++;
	write(1, "\b\b  \b\b\n", 7);
}