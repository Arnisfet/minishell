/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrudge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 17:49:43 by mrudge            #+#    #+#             */
/*   Updated: 2021/12/03 17:50:00 by mrudge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int  env_len(char **env)
{
	int  i;

	i = 0;
	while (**env++)
		i++;
	return (i);
}

void  init_env(char **env, t_struct *p)
{
	int i;

	i = 0;
	p->arr_env = (char **)malloc(sizeof (char *) * (env_len(env) + 1));
	while (env[i])
	{
		p->arr_env[i] = ft_strdup(env[i]);
		if (!p->arr_env[i])
			exit (0);
		i++;
	}
}