/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_wo_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmacmill <jmacmill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 17:00:46 by jmacmill          #+#    #+#             */
/*   Updated: 2022/01/23 17:07:01 by jmacmill         ###   ########.fr       */
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
	t_redirect	*point;

	point = p->redirect;
	while (point != NULL)
	{
		if (point->type[0] == '>')
			create_file(point);
		point = point->next;
	}
	return (0);
}
