/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmacmill <jmacmill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 17:43:26 by jmacmill          #+#    #+#             */
/*   Updated: 2022/01/24 19:57:32 by jmacmill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	is_al_num(char *str)
{
	size_t	res;
	int		sign;

	res = 0;
	sign = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		res = (res * 10) + *str - '0';
		if (res > 2147483648 || (sign == 1 && res > 2147483647))
			return (0);
		str++;
	}
	return (1);
}

int	build_exit(char **cmd)
{
	if (!cmd[1])
	{
		printf("exit\n");
		unlink(".heredoc_tmp");
		exit(g_status);
	}
	if (is_al_num(cmd[1]))
	{
		printf("exit\n");
		if (cmd[2] == NULL)
		{
			unlink(".heredoc_tmp");
			exit(ft_atoi(cmd[1]) % 256);
		}
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	else
	{
		g_status = 2;
		printf("exit\n");
		ft_putstr_fd("minishell: exit: not numeric argument\n", 2);
		unlink(".heredoc_tmp");
		exit(g_status);
	}
	return (0);
}
