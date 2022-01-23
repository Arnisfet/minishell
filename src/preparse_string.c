/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparse_string.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrudge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 20:52:06 by mrudge            #+#    #+#             */
/*   Updated: 2022/01/20 20:56:58 by mrudge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_the_pipe(char *array, t_struct *p)
{
	int	i;

	i = 0;
	if (array[0] == '|')
	{
		ft_putstr_fd("\t\tsyntax error near unexpected token '|'\n", 1);
		p->error = 2;
		return (2);
	}
	while (array[i])
		i++;
	if (array[i - 1] == '|')
	{
		ft_putstr_fd("\t\tsyntax error near unexpected token '|'\n", 1);
		p->error = 2;
		return (2);
	}
	return (0);
}

static int	error_code(char *array, int i, t_struct *p)
{
	if (array[i] == '|')
	{
		p->error_code = 2;
		ft_putstr_fd("\t\tsyntax error near unexpected token '|'\n", 1);
		return (2);
	}
	return (0);
}

int	check_double_pipe(char *array, t_struct *p)
{
	int	i;

	i = 0;
	while (array[i])
	{
		if (array[i] == '"' || array[i] == '\'')
		{
			i = end_of_quote(array, i);
			i++;
			continue ;
		}
		if (array[i] == '|')
		{
			while (array[i] == ' ' || array[i] == '|')
			{
				i++;
				if ((error_code(array, i, p)) == 2)
					return (2);
				i++;
			}
		}
		i++;
	}
	return (0);
}

int	check_string(char *array, t_struct *p)
{
	if (check_the_pipe(array, p) != 0)
		return (2);
	if (check_double_pipe(array, p) != 0)
		return (2);
	return (0);
}
