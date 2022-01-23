/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmacmill <jmacmill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 11:42:51 by jmacmill          #+#    #+#             */
/*   Updated: 2022/01/23 17:04:26 by jmacmill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ctrl_c_heredoc(int status)
{
	int		file;

	(void)status;
	g_status = 1;
	write(1, "\n", 1);
	exit(130);
}

// void	ctrl_c_pipe_heredoc(int status)
// {
// 	status++;
// 	write(1, "\n", 1);
// 	rl_on_new_line();
// 	exit(130);
// }
