/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmacmill <jmacmill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 14:20:57 by jmacmill          #+#    #+#             */
/*   Updated: 2022/01/23 18:16:30 by jmacmill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	get_outfile(t_struct *p, int pos)
{
	t_redirect	*tmp;

	tmp = p->redirect;
	p->flag = 0;
	while (tmp != NULL)
	{
		if (!ft_strncmp(">", tmp->type, 2) && pos == tmp->number_command)
			catch_file(p, tmp->file, 1);
		if (!ft_strncmp(">>", tmp->type, 3) && pos == tmp->number_command)
			catch_file(p, tmp->file, 2);
		tmp = tmp->next;
	}
	return (p->out_file);
}

int	check_outfile(t_struct *p, int pos)
{
	t_redirect	*tmp;

	tmp = p->redirect;
	p->is_outfile = 0;
	while (tmp)
	{
		if (!ft_strncmp(">", tmp->type, 2) && pos == tmp->number_command)
			return (1);
		if (!ft_strncmp(">>", tmp->type, 3) && pos == tmp->number_command)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

static int	tup(char **filename, t_redirect *tmp)
{
	*filename = tmp->file;
	return (2);
}

char	*get_infile(t_struct *p, int pos)
{
	t_redirect	*tmp;
	char		*filename;
	int			flag;

	filename = NULL;
	tmp = p->redirect;
	flag = 0;
	while (tmp != NULL)
	{
		if (!ft_strncmp("<<", tmp->type, 3) && \
		tmp->number_command == pos && g_status != 130)
		{
			if (!access(".heredoc_tmp", F_OK))
				unlink(".heredoc_tmp");
			start_heredoc(p, tmp->file);
			flag = 1;
		}
		if (!ft_strncmp("<", tmp->type, 2) && tmp->number_command == pos)
			flag = tup(&filename, tmp);
		tmp = tmp->next;
	}
	if (flag == 1)
		filename = ".heredoc_tmp";
	return (filename);
}

int	check_infile(t_struct *p, int pos)
{
	t_redirect	*tmp;

	tmp = p->redirect;
	while (tmp)
	{
		if (!ft_strncmp("<", tmp->type, 2) && pos == tmp->number_command)
			return (1);
		if (!ft_strncmp("<<", tmp->type, 3) && pos == tmp->number_command)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
