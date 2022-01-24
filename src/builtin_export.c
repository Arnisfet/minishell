/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmacmill <jmacmill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 17:43:35 by jmacmill          #+#    #+#             */
/*   Updated: 2022/01/24 17:41:56 by jmacmill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	add_new(char *var, char *value, t_struct *p, int flag)
{
	t_env	*tmp;

	tmp = p->my_env;
	if (tmp == NULL)
	{
		tmp = (t_env *)malloc(sizeof(t_env));
		if (!(tmp))
			return ;
		tmp->var = ft_strdup(var);
		if (flag)
		{
			tmp->value = NULL;
			tmp->is_blank = 1;
		}
		else
		{
			tmp->value = ft_strdup(value);
			tmp->is_blank = 0;
		}
		tmp->next = NULL;
	}
	else
		addition_var(var, value, p, flag);
}

void	find_and_update(char *str, t_struct *p)
{
	char	*stop_position;

	stop_position = ft_strchr(str, '=');
	*stop_position = '\0';
	if (check_var(str, p))
	{
		stop_position++;
		if (*stop_position)
			exist_add(str, stop_position, p, 0);
		else
			exist_add(str, stop_position, p, 1);
	}
	else
	{
		stop_position++;
		if (*stop_position)
			add_new(str, stop_position, p, 0);
		else
			add_new(str, stop_position, p, 1);
	}
}

int	build_export(char **str, t_struct *p)
{
	int		i;
	char	*equal;
	t_env	*tmp;

	if (!str[1])
	{
		print_env(p);
		return (1);
	}
	if (export_errors(str))
		return (1);
	i = 1;
	tmp = p->my_env;
	while (str[i])
	{
		equal = ft_strchr(str[i], '=');
		if (equal)
			find_and_update(str[i], p);
		else
			blank_and_replace(str[i], p);
		i++;
	}
	return (1);
}
