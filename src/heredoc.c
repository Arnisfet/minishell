/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmacmill <jmacmill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 14:26:27 by jmacmill          #+#    #+#             */
/*   Updated: 2022/01/23 14:27:19 by jmacmill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	act_signals(void)
{
	signal(SIGINT, ctrl_c_heredoc);
	signal(SIGQUIT, ctrl_slash_child);
}

void	unlink_file_err(void)
{
	unlink(".heredoc_tmp");
	ft_putendl_fd("Error: unable to open a file", 2);
}

void	start_heredoc(t_struct *p, char *stop)
{
	int			file;
	char		*buf;
	pid_t		pid;

	file = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_APPEND, 0000644);
	pid = fork();
	if (pid == 0)
	{
		act_signals();
		while (21)
		{
			write(1, "heredoc> ", 9);
			if (get_next_line(0, &buf) < 0)
				exit(1);
			if (!ft_strncmp(stop, buf, ft_strlen(stop) + 1))
				exit(1);
			write(file, buf, ft_strlen(buf));
			write(file, "\n", 1);
			free(buf);
		}
		free(buf);
	}
	else
		waitpid(pid, NULL, 0);
	close(file);
	p->in_file = open(".heredoc_tmp", O_RDONLY);
	if (p->in_file < 0)
		unlink_file_err();
}