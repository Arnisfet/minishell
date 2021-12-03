/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrudge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 17:53:59 by mrudge            #+#    #+#             */
/*   Updated: 2021/12/03 17:54:20 by mrudge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	build_cd(const char *str)
{
	if (chdir(str) == 0)
	{
		return (0);
	}
	return (-1);
}

int main(int argc, char **argv, char **env)
{
	t_struct	*p;

	p = (t_struct *)malloc(sizeof(t_struct));
	init_env(env, p);
	while (1)
	{

	}
	return (0);
}