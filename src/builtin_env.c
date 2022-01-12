/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrudge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 17:01:04 by mrudge            #+#    #+#             */
/*   Updated: 2022/01/12 20:32:00 by mrudge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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