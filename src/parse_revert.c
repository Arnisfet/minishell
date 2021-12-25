/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_revert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrudge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 13:22:21 by mrudge            #+#    #+#             */
/*   Updated: 2021/12/25 13:22:21 by mrudge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*parse_ones_revert(char *command, char *line, int i, t_struct *p)
{
	while (line[i] != '\'' && line[i] != '\0')
	{
		command = ft_realloc_ch(command, line[i]);
		i++;
		p->count++;
	}
	if (line[i] != '\'')
		exit (0);
	p->count++;
	return (command);
}

char	*parse_double_revert(char *command, char *line, int i, t_struct *p)
{
	int j;

	while(line[i] != '"' && line[i] != '\0')
	{
		if (line[i] == '$')
		{
			j = p->count;
			dollar(command, line, ++i, p);
			p->count++;
			j = j - p->count;
			i += j;
		command = ft_realloc_ch(command, line[i]);
		i++;
		p->count++;
	}
	if (line[i] != '"')
		exit (0);
	p->count++;
	return (command);
}

char	*parse_revert(char *command, char *line, int i, t_struct *p)
{
	if (line[i] == '"')
		command = parse_double_revert(command, line, ++i, p);
	if (line[i] == '\'')
		command = parse_ones_revert(command, line, ++i, p);
	return (command);
}