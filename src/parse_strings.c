/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrudge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 17:53:59 by mrudge            #+#    #+#             */
/*   Updated: 2022/01/08 16:14:49 by mrudge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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