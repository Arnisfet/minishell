/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparse_redirect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrudge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 01:50:12 by mrudge            #+#    #+#             */
/*   Updated: 2022/01/11 21:21:44 by mrudge           ###   ########.fr       */
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

static	int check_redirect(t_struct *p)
{
	int	i;
	char	*checker;

	i = 0;
	while (i != 4 && p->redirect->type[i])
	{
		if (i >= 2 || p->redirect->type[0] != p->redirect->type[i])
		{
			checker = ft_strndup(&p->redirect->type[i], 2);
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

static	int	check_filename(t_struct *p)
{
	t_redirect *tmp;

	tmp = p->redirect;
	while (tmp->next != NULL)
	{
		if (tmp->file == NULL || strcmp(tmp->file, "") == 0)
		{
			ft_putstr_fd("\t\tsyntax error near unexpected token: ", 1);
			ft_putstr_fd("syntax error near unexpected token `newline'\n", 1);
			p->error = 2;
			return (2);
		}
		tmp = tmp->next;
	}
	if (tmp->file == NULL || strcmp(tmp->file, "") == 0)
	{
		ft_putstr_fd("\t\tsyntax error near unexpected token: ", 1);
		ft_putstr_fd("syntax error near unexpected token `newline'\n", 1);
		p->error = 2;
		return (2);
	}
	return (0);
}

int		check_digit_2(t_struct *p, t_redirect *tmp, int i, int flag)
{
	while (tmp->file[i])
	{
		if (ft_isalpha(tmp->file[i]) != 0)
			flag = 1;
		i++;
	}
	if (flag != 1)
	{
		ft_putstr_fd("\t\tsyntax error near unexpected token: ", 1);
		ft_putstr_fd(tmp->file, 1);
		ft_putstr_fd("\n", 1);
		p->error = 2;
		return (2);
	}
}

int		check_digit(t_struct *p)
{
	t_redirect	*tmp;
	t_redirect	*last_elem;
	int			i;

	i = 0;
	tmp = p->redirect;
	while (tmp->next != NULL)
		tmp = tmp->next;
	last_elem = tmp;
	tmp = p->redirect;
	while (tmp->next != NULL)
	{
		if (tmp != last_elem)
		{
			i = check_digit_2(p, tmp, i, 0);
			if (p->error != 0)
				return (2);
		}
		tmp = tmp->next;
	}
	return (0);
}

int		correct_check(t_struct *p)
{
	if (check_redirect(p))
		return (2);
	if (check_filename(p))
		return (2);
//	if (check_digit(p))
//		return (2);
	return (0);
}