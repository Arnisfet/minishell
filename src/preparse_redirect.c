/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparse_redirect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrudge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 01:50:12 by mrudge            #+#    #+#             */
/*   Updated: 2022/01/20 20:55:09 by mrudge           ###   ########.fr       */
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

static	int	check_redirect(t_struct *p)
{
	int		i;
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
	t_redirect	*tmp;

	tmp = p->redirect;
	while (tmp != NULL)
	{
		if (tmp->file == NULL)
		{
			ft_putstr_fd("\t\tsyntax error near unexpected token: ", 1);
			ft_putstr_fd("syntax error near unexpected token `newline'\n", 1);
			p->error = 2;
			return (2);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	check_digit(char const *start, char *end, t_struct *p)
{
	char	*point;
	int		flag;

	flag = 0;
	point = (char *) start;
	while ((point != end || flag != 1) && *point != ' ' && *point != '>'
		&& *point != '<' && *point != '\0')
	{
		if ((ft_isalpha(*point)))
			flag = 1;
		point++;
	}
	if (flag == 0)
	{
		point = ft_substr(start, 0, end - start);
		p->error = 2;
		ft_putstr_fd("\t\tsyntax error near unexpected token: ", 1);
		ft_putendl_fd(point, 1);
		free(point);
		return (0);
	}
	return (1);
}

int	correct_check(t_struct *p)
{
	if (check_redirect(p))
		return (2);
	if (check_filename(p))
		return (2);
	return (0);
}
