/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmacmill <jmacmill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 17:43:26 by jmacmill          #+#    #+#             */
/*   Updated: 2022/01/20 19:27:18 by mrudge           ###   ########.fr       */
/*   Updated: 2022/01/12 19:50:19 by mrudge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_list(t_struct *p)
{
	t_env	*tmp;

	while (p->my_env != NULL)
	{
		tmp = p->my_env;
		p->my_env = p->my_env->next;
		free(tmp->var);
		if (tmp->value)
			free(tmp->value);
		free(tmp);
	}
}

int	check_is_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

void	build_exit(char **str, t_struct *p)
{
	if (!str[1])
	{
		free_list(p);
		ft_putendl_fd("exit", 1);
		exit(1);
	}
	if (str[2])
	{
		ft_putendl_fd("exit", 1);
		ft_putendl_fd("bash: exit: too many arguments", 2);
		return ;
	}
	if (str[1] && check_is_digit(str[1]))
	{
		ft_putendl_fd("exit", 1);
		ft_putstr_fd("bash: exit: ", 2);
		ft_putstr_fd(str[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		return ;
	}
	free_list(p);
	exit((int)ft_atoi(str[1]));
}