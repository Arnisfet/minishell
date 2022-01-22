/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmacmill <jmacmill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 17:43:26 by jmacmill          #+#    #+#             */
/*   Updated: 2022/01/22 18:30:23 by jmacmill         ###   ########.fr       */
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

int	is_al_num(char *str)
{
	long long res;
	// int		sign;
	int i;

	i = 0;
	res = 0;
	// sign = 1;
	// if (*str == '-' || *str == '+')
	// {
	// 	if (*str == '-')
	// 		sign *= -1;
	// 	str++;
	// }
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
		res = (res * 10) + str[i] - '0';
		if (res > 2147483647 || res < -2147483648)
			return (-1);
		i++;
	}
	return (1);
}

void	build_exit(char **str, t_struct *p)
{
	int	i;
	int	counter;

	i = 1;
	counter = 0;
	if (!str[1])
	{
		unlink(".heredoc_tmp");
		free_list(p);
		ft_putendl_fd("exit", 1);
		exit(0);
	}
	while (str[i])
	{
		if (is_al_num(str[i]))
			counter++;
		i++;
	}
	//printf("%d\n", counter);
	if (counter > 1)
	{
		ft_putendl_fd("exit", 1);
		ft_putendl_fd("bash: exit: too many arguments", 2);
		return ;
	}
	// if (str[2])
	// {
		// ft_putendl_fd("exit", 1);
		// ft_putendl_fd("bash: exit: too many arguments", 2);
		// return ;
	// }
	if (str[1] && check_is_digit(str[1]))
	{
		ft_putendl_fd("exit", 1);
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(str[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		exit(1);
	}
	free_list(p);
	exit((int)ft_atoi(str[1]));
}