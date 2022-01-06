/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrudge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 18:13:15 by mrudge            #+#    #+#             */
/*   Updated: 2022/01/06 20:35:12 by mrudge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	first_node(t_struct *p, char *type, char *file, int num)
{
	t_redirect 	*tmp;

	p->redirect = (t_redirect *)malloc(sizeof(t_struct));
	if (!p->redirect)
		return ((void )NULL);
	tmp = p->redirect;
	tmp->next = NULL;
	tmp->file = file;
	tmp->number_command = num;
	tmp->type = type;
}

void	add_to_list_redirect(t_struct *p, char *type, char *file, int num)
{
	t_redirect *tmp;

	if (p->redirect == NULL)
		first_node(p, type, file, num);
	else
	{
		tmp = p->redirect;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = (t_redirect *)malloc(sizeof(t_struct));
		if (!tmp->next)
			return((void) NULL);
		tmp = tmp->next;
		tmp->type = type;
		tmp->file = file;
		tmp->number_command = num;
		tmp->next = NULL;
	}
}

void	print_list(t_struct *p)
{
	t_redirect	*tmp;

	tmp = p->redirect;
	if (!tmp)
		return ;
	while (tmp->next != NULL)
	{
		printf ("type of redirect: %s, filename: %s, number of pipe: %d",
				tmp->type, tmp->file, tmp->number_command);
		tmp = tmp->next;
	}
	printf ("type of redirect: %s, filename: %s, number of pipe: %d",
			tmp->type, tmp->file, tmp->number_command);
}