/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_msg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrudge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 22:26:43 by mrudge            #+#    #+#             */
/*   Updated: 2022/01/12 19:50:19 by mrudge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	create_file(t_redirect *p)
{
	int	fd;

	fd = open(p->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		perror("minishell");
	return (1);
}

int	create_redir(t_struct *p)
{
	t_redirect *point;

	point = p->redirect;
	while (point != NULL)
	{
		if (point->type[0] == '>')
			create_file(point);
		point = point->next;
	}
	return (0);
}
