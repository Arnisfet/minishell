/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrudge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 17:01:04 by mrudge            #+#    #+#             */
/*   Updated: 2021/12/12 17:42:05 by mrudge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	builtin_env(t_struct *p)
{
	int	i;

	i = 0;
	while (p->arr_env[i])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putendl_fd(p->arr_env[i], 1);
		i++;
	}
	return (1);
}