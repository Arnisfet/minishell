/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrudge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 22:29:33 by mrudge            #+#    #+#             */
/*   Updated: 2021/12/10 20:12:24 by mrudge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"


int	check_echo_sym(char **str, t_struct *p)
{
	int i;
	int count;
	int j;

	j = 0;
	i = 0;
	count = 0;
	while (str[i])
	{
		j = 0;
		while(str[i][j])
		{
			if (str[i][j] == '"')
				count++;
			j++;
		}
		i++;
	}
	if ((count % 2) != 0)
		return (0);
	return (1);
}

void	print_echo(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"' && (str[i - 1] == '"' || str[i + 1] == '"'))
			i++;
		if(str[i] && str[i] != '"' )
			ft_putchar_fd(str[i], 1);
		i++;
	}
}

int	builtin_echo(char **str, t_struct *p)
{
	int	i;
	int	flag_n;

	flag_n = 0;
	i = 0;
	if (!str[0])
	{
		write(1, "\n", 1);
		return (1);
	}
	else if (str[0][0] == '-' && str[0][1] == 'n' && str[0][2] == '\0')
		flag_n = 1;
	if (flag_n)
		++i;
	if (check_echo_sym(str, p) == 0)
		return (0);
	while (str[i])
	{
		print_echo(str[i]);
		if (str[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (!flag_n)
		ft_putchar_fd('\n', 1);
	return (1);
}