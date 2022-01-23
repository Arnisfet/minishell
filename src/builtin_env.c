/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmacmill <jmacmill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 17:01:04 by mrudge            #+#    #+#             */
/*   Updated: 2022/01/23 11:37:09 by jmacmill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	export_errors(char **str)
{
	if (special_check(str[1]))
	{
		ft_putstr_fd("minishell: export: '", 1);
		ft_putstr_fd(str[1], 1);
		ft_putendl_fd("': not a valid identifier", 1);
		return (1);
	}
	return (0);
}

int	print_env(t_struct *p)
{
	t_env	*tmp;

	tmp = p->my_env;
	while (tmp != NULL)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(tmp->var, 1);
		if (!tmp->is_blank)
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(tmp->value, 1);
			ft_putstr_fd("\"", 1);
		}
		ft_putchar_fd('\n', 1);
		tmp = tmp->next;
	}
	return (1);
}

int	builtin_env(t_struct *p)
{
	t_env	*tmp;

	tmp = p->my_env;
	while (tmp != NULL)
	{
		if (!tmp->is_blank)
		{
			ft_putstr_fd(tmp->var, 1);
			ft_putchar_fd('=', 1);
			ft_putendl_fd(tmp->value, 1);
		}
		tmp = tmp->next;
	}
	return (1);
}
