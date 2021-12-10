/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrudge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 21:51:41 by mrudge            #+#    #+#             */
/*   Updated: 2021/12/10 19:12:54 by mrudge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_bultin(char **str, t_struct *p)
{


	if (find_str(str[0], "cd")) //segfault
		build_cd(str, p);
	if (find_str(str[0], "pwd"))
		build_pwd(str);
	if (find_str(str[0], "echo"))
		builtin_echo(str + 1, p);
}

int	parse_cmd(char **str, t_struct *p)
{
		if (check_bultin(str, p) == 0)
			return (0);
	return (1);
}
