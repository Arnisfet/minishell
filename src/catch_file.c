/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   catch_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmacmill <jmacmill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 17:22:12 by jmacmill          #+#    #+#             */
/*   Updated: 2022/01/24 17:41:07 by jmacmill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	catch_file(t_struct *p, char *filename, int state)
{
	if (p->flag)
	{
		close(p->out_file);
		p->flag = 0;
	}
	p->flag++;
	if (state == 1)
	{
		p->out_file = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (p->out_file == -1)
		{
			g_status = 1;
			perror("minishell");
		}
	}
	if (state == 2)
	{
		p->out_file = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (p->out_file == -1)
		{
			g_status = 1;
			perror("minishell");
		}
	}
}
