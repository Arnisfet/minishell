/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmacmill <jmacmill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 18:13:15 by mrudge            #+#    #+#             */
/*   Updated: 2022/01/23 19:48:01 by jmacmill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_array(char **str)
{
	int	i;

	if (str)
	{
		i = 0;
		while (str[i])
		{
			free(str[i]);
			i++;
		}
		free(str);
	}
}

void	free2(char *array, char *trimmer)
{
	free (array);
	free(trimmer);
}

void	util(t_struct *p, char *file, char *redirect)
{
	p->tmp_red = ft_strdup(redirect);
	file = parse_revert(file, 0, p);
	add_to_list_redirect(p, redirect, file, p->count);
}

char	*first_rparse(char *commands, t_struct *p)
{
	char	*start;
	int		i;

	p->tmp_red = NULL;
	i = 0;
	while (commands[i])
	{
		if (commands[i] == '\'' || commands[i] == '"')
			i = end_of_quote(commands, i);
		if (commands[i] == '>' || commands[i] == '<')
		{
			start = &commands[i];
			if (substring(start, p))
			{
				free(p->tmp_red);
				return (NULL);
			}
			free(p->tmp_red);
			commands = ft_strtrim_quote(commands, p->point_r, p->point_f);
			continue ;
		}
		i++;
	}
	return (commands);
}

void	clean_split_tmp(char **clean)
{
	if (clean[0])
		free(clean[0]);
	if (clean[1])
		free(clean[1]);
	free(clean);
}
