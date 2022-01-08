/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmacmill <jmacmill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 17:43:42 by jmacmill          #+#    #+#             */
/*   Updated: 2022/01/08 16:14:49 by mrudge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*build_pwd(char **str)
{
	char	*cwd;
	char	buf[4096 + 1];

	if (str[1])
	{
		ft_putstr_fd("pwd: too many arguments", 2);
		return (NULL);
	}
	else
	{
		cwd = getcwd(buf, 4096);
		printf("pwd: %s\n", cwd);
	}
	return (cwd);
}
