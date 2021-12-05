/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrudge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 17:49:43 by mrudge            #+#    #+#             */
/*   Updated: 2021/12/05 22:01:17 by mrudge           ###   ########.fr       */#.fr       */
=======
/*   Updated: 2021/12/05 20:44:18 by mrudge           ###   ########.fr       */
>>>>>>> 02437a4db877d98d289ad7eba4fed4b2b4a561a5
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int  env_len(char **env)
{
	int  i;

	i = 0;
	while (env[i])
	{
		//printf("%s\n", env[i]);
		i++;
	}
	return (i - 1);
}

void  init_env(char **env, t_struct *p)
{
	int i;

	i = 0;
	p->arr_env = (char **)malloc(sizeof (char *) * (env_len(env) + 1));
	if (!(p->arr_env))
		return ;
	while (env[i])
	{
		p->arr_env[i] = ft_strdup(env[i]);
		if (!p->arr_env[i])
			exit(0);
		i++;
	}
}

int	input_is_empty(char *check)
{
	int	i;

	i = 0;
	while (check[i] != '\0')
	{
		if (check[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}
