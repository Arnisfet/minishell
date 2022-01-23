/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_strings.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmacmill <jmacmill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 17:53:59 by mrudge            #+#    #+#             */
/*   Updated: 2022/01/23 19:46:06 by jmacmill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	**parsing(char *line, t_struct *p, char **commands)
{
	if (check_string(line, p) != 0)
		return (NULL);
	commands = parse_pipe(line, p);
	if (p->error != 0)
	{
		if (commands)
			ft_free(commands);
		return (NULL);
	}
	commands = parse_redirect(commands, p);
	if (p->error != 0)
	{
		ft_free(commands);
		return (NULL);
	}
	return (commands);
}

char	**parse_strings(char **commands, t_struct *p)
{
	int		i;

	i = 0;
	while (commands[i])
	{
		commands[i] = parse_dollar_without_quote(commands[i], p);
		commands[i] = parse_revert(commands[i], 0, p);
		i++;
	}
	return (commands);
}
