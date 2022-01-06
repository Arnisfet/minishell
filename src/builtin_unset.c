/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmacmill <jmacmill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 17:43:53 by jmacmill          #+#    #+#             */
/*   Updated: 2022/01/07 04:13:42 by mrudge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	delete_var(t_env *to_delete, t_struct *p)
{
	t_env	*tmp;

	tmp = p->my_env;
	if (tmp == to_delete)
	{
		p->my_env = to_delete->next;
		free(to_delete->var);
		free(to_delete->value);
		free(to_delete);
		return ;
	}
	while (tmp->next != to_delete)
		tmp = tmp->next;
	tmp->next = to_delete->next;
	free(to_delete->var);
	free(to_delete->value);
	free(to_delete);
}

int	special_check(char *str)
{
	// int	i;

	// i = 0;
	// while (str[i] != '\0')
	// {
		// if (!ft_isalpha((int)str[0]) && str[i] != '_')
		if (!ft_isalpha((int)str[0]))
			return (1);
	// 	i++;	
	// }
	return (0);
}

int	unset_errors(char **str)
{
	if (!str[1])
	{
		ft_putstr_fd("unset: not enough arguments\n", 2);
		return (1);
	}
	if (special_check(str[1]))
	{
		ft_putstr_fd("unset: ", 2);
		ft_putstr_fd(str[1], 2);
		ft_putstr_fd(": invalid parameter name\n", 2);
		return (1);
	}
	return (0);
}

void	to_delete(char *str, t_struct *p)
{
	t_env	*tmp;

	tmp = p->my_env;
	while (tmp != NULL)
	{
		if (find_str(str, tmp->var))
		{
			delete_var(tmp, p);
			return ;
		}
		tmp = tmp->next;
	}
}

int	build_unset(char **str, t_struct *p)
{
	int		i;

	i = 1;
	if (unset_errors(str))
		return (-1);
	while (str[i])
	{
		to_delete(str[i], p);
		i++;
	}
	return (1);
}