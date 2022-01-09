/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparse_redirect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrudge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 01:50:12 by mrudge            #+#    #+#             */
/*   Updated: 2022/01/09 18:12:58 by mrudge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	freed(t_struct *p)
{
	t_redirect	*tmp;
	t_redirect	*next_elem;

	tmp = p->redirect;
	if (tmp->next)
		next_elem = tmp->next;
	else
		next_elem = NULL;
	while (next_elem != NULL)
	{
		free(tmp->file);
		free(tmp->type);
		free(tmp);
		tmp = next_elem;
		next_elem = next_elem->next;
	}
	free(tmp->file);
	free(tmp->type);
	p->redirect = NULL;
	next_elem = NULL;
}

int		correct_check(char *array, t_struct *p)
{
	int	i;
	char	*checker;

	i = 0;
	while (i != 4 && array[i])
	{
		if (i >= 2 || array[0] != array[i])
		{
			checker = ft_strndup(&array[i], 2);
			ft_putstr_fd("\t\tsyntax error near unexpected token: ", 1);
			ft_putstr_fd(checker, 1);
			ft_putstr_fd("\n", 1);
			free(checker);
			p->error = 2;
			return (2);
		}
		i++;
	}
	return (0);
}