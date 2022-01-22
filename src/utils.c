/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmacmill <jmacmill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 18:13:15 by mrudge            #+#    #+#             */
/*   Updated: 2022/01/22 18:29:40 by jmacmill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	first_node(t_struct *p, char *type, char *file, int num)
{
	t_redirect	*tmp;

	p->redirect = (t_redirect *)malloc(sizeof(t_struct));
	if (!p->redirect)
		return ((void ) NULL);
	tmp = p->redirect;
	tmp->next = NULL;
	tmp->file = file;
	tmp->number_command = num;
	tmp->type = type;
}

void	add_to_list_redirect(t_struct *p, char *type, char *file, int num)
{
	t_redirect	*tmp;

	if (p->redirect == NULL)
		first_node(p, type, file, num);
	else
	{
		tmp = p->redirect;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = (t_redirect *)malloc(sizeof(t_struct));
		if (!tmp->next)
			return ((void ) NULL);
		tmp = tmp->next;
		tmp->type = type;
		tmp->file = file;
		tmp->number_command = num;
		tmp->next = NULL;
	}
}

char	*trim_and_find(char *array, int i, t_struct *p)
{
	t_env *point;

	point = p->my_env;
	if (check_ones(array, i))
		return (ft_strdup(array));
	if (strcmp(array, "$?") == 0)
		return (ft_itoa(p->error_code));
	if (p->tmp_red != NULL && ft_strcmp("<<", p->tmp_red) == 0)
		return (array);
	while (point != NULL)
	{
		if (!ft_strcmp(array + 1, point->var))
			return (ft_strdup(point->value));
		point = point->next;
	}
	return (ft_strdup(""));
}
