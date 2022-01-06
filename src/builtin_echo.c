/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrudge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 22:29:33 by mrudge            #+#    #+#             */
/*   Updated: 2022/01/07 04:13:42 by mrudge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_n(char *str, t_struct *p)
{
	int	i;

	i = 0;
	if (str[0] == '-' && str[1] == 'n')
	{
		i++;
		while (str[i])
		{
			if (str[i] == 'n')
				i++;
			else
				return (0);
		}
		p->echo_flag = 1;
		return (1);
	}
	return (0);
}

int	print_echo(char *str, t_struct *p)
{
		if (check_n(str, p) == 1)
			return (1);
		ft_putstr_fd(str, 1);
	return (0);
}

int	builtin_echo(char **str, t_struct *p)
{
	int	i;

	p->echo_flag = 0;
	i = 0;
	if (!str[0])
	{
		write(1, "\n", 1);
		return (1);
	}
	while (str[i])
	{
		if (print_echo(str[i], p) == 1)
		{
			i++;
			continue;
		}
		if (str[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (!p->echo_flag)
		ft_putchar_fd('\n', 1);
	return (1);
}
