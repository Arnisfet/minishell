/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmacmill <jmacmill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 17:43:26 by jmacmill          #+#    #+#             */
/*   Updated: 2022/01/23 11:15:03 by jmacmill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	is_al_num(char *str)
{
	size_t	res;
	int		sign;

	res = 0;
	sign = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		res = (res * 10) + *str - '0';
		if (res > 2147483648 || (sign == 1 && res > 2147483647))
			return (0);
		str++;
	}
	return (1);
}

int	build_exit(char **cmd, t_struct *p)
{
	if (!cmd[1])
	{
		printf("exit\n");
		unlink(".heredoc_tmp");
		exit(g_status);
	}
	if (is_al_num(cmd[1]))
	{
		printf("exit\n");
		if (cmd[2] == NULL)
		{
			unlink(".heredoc_tmp");
			exit(ft_atoi(cmd[1]) % 256);
		}
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	else
	{
		printf("exit\n");
		ft_putstr_fd("minishell: exit: not numeric argument\n", 2);
		unlink(".heredoc_tmp");
		exit(2);
	}
	return (0);
}


// void	free_list(t_struct *p)
// {
// 	t_env	*tmp;

// 	while (p->my_env != NULL)
// 	{
// 		tmp = p->my_env;
// 		p->my_env = p->my_env->next;
// 		free(tmp->var);
// 		if (tmp->value)
// 			free(tmp->value);
// 		free(tmp);
// 	}
// }

// int	check_is_digit(char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i] != '\0')
// 	{
// 		if (!ft_isdigit(str[i]))
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }

// int	is_al_num(char *str)
// {
// 	long long	res;
// 	int			i;

// 	i = 0;
// 	res = 0;
// 	while (str[i])
// 	{
// 		if (!(str[i] >= '0' && str[i] <= '9'))
// 			return (0);
// 		res = (res * 10) + str[i] - '0';
// 		if (res > 2147483647 || res < -2147483648)
// 			return (-1);
// 		i++;
// 	}
// 	return (1);
// }

// void	unlink_free(t_struct *p)
// {
// 	unlink(".heredoc_tmp");
// 	free_list(p);
// 	ft_putendl_fd("exit", 1);
// }

// void	special_exit(char **str)
// {
// 	write(2, "aaa\n", 4);
// 	ft_putendl_fd("exit\nminishell: exit: ", 2);
// 	ft_putstr_fd(str[1], 2);
// 	ft_putendl_fd(": numeric argument required", 2);
// 	exit((int)ft_atoi(str[1]));
// }

// void	build_exit(char **str, t_struct *p)
// {
// 	int	i;
// 	int	counter;

// 	i = 1;
// 	counter = 0;
// 	while (str[i])
// 	{
// 		if (is_al_num(str[i]))
// 			counter++;
// 		i++;
// 	}
// 	if (!str[1] || (!str[2] && is_al_num(str[1]) == -1))
// 	{
// 		unlink_free(p);
// 		exit(0);
// 	}
// 	if (counter > 1)
// 	{
// 		ft_putendl_fd("exit\nbash: exit: too many arguments", 2);
// 		return ;
// 	}
// 	if (str[1] && !check_is_digit(str[1]))
// 		special_exit(str);
// 	free_list(p);
// 	exit((int)ft_atoi(str[1]));
// }
