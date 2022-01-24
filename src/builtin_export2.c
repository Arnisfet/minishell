/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmacmill <jmacmill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 11:38:31 by jmacmill          #+#    #+#             */
/*   Updated: 2022/01/24 17:42:33 by jmacmill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	add_null_value(char *str, t_struct *p, int flag)
{
	t_env	*tmp;

	(void )flag;
	tmp = p->my_env;
	if (tmp == NULL)
	{
		tmp = (t_env *)malloc(sizeof(t_env));
		if (!tmp)
			return ;
		tmp->var = ft_strdup(str);
		tmp->value = NULL;
		tmp->is_blank = 1;
		tmp->next = NULL;
	}
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = (t_env *)malloc(sizeof(t_env));
		tmp->next->var = ft_strdup(str);
		tmp->next->value = NULL;
		tmp->next->is_blank = 1;
		tmp->next->next = NULL;
	}
}

void	blank_and_replace(char *str, t_struct *p)
{
	t_env	*tmp;

	tmp = p->my_env;
	while (tmp != NULL)
	{
		if (find_str(str, tmp->var))
			return ;
		tmp = tmp->next;
	}
	add_null_value(str, p, 1);
}

int	check_var(char *str, t_struct *p)
{
	t_env	*tmp;

	tmp = p->my_env;
	while (tmp != NULL)
	{
		if (find_str(str, tmp->var))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	exist_add(char *var, char *value, t_struct *p, int flag)
{
	t_env	*tmp;

	tmp = p->my_env;
	while (tmp != NULL)
	{
		if (find_str(var, tmp->var))
		{
			if (flag)
			{
				if (tmp->value)
					free(tmp->value);
				tmp->value = NULL;
				tmp->is_blank = 0;
			}
			else
			{
				if (tmp->value)
					free(tmp->value);
				tmp->value = ft_strdup(value);
				tmp->is_blank = 0;
			}
		}
		tmp = tmp->next;
	}
}

void	addition_var(char *var, char *value, t_struct *p, int flag)
{
	t_env	*tmp;

	tmp = p->my_env;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = (t_env *)malloc(sizeof(t_env));
	if (!tmp->next)
		return ;
	tmp->next->var = ft_strdup(var);
	if (flag)
	{
		tmp->next->value = NULL;
		tmp->next->is_blank = 0;
	}
	else
	{
		tmp->next->value = ft_strdup(value);
		tmp->next->is_blank = 0;
	}
}
