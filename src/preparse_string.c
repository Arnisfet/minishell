/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparse_string.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrudge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 20:52:06 by mrudge            #+#    #+#             */
/*   Updated: 2022/01/10 21:05:20 by mrudge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int check_the_pipe(char *array, t_struct *p)
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

