/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrudge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 17:49:43 by mrudge            #+#    #+#             */
/*   Updated: 2021/12/23 22:45:03 by mrudge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	init_env_list(t_struct *p, char *content)
{
	t_env	*tmp;

	tmp = p->my_env;
	if (p->my_env == NULL)
	{
		p->my_env = (t_env *)malloc(sizeof(t_env));
		p->my_env->var = ft_strdup(content);
		p->my_env->next = NULL;
	}
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = (t_env *)malloc(sizeof(t_env));
		tmp->next->var = ft_strdup(content);
		tmp->next->next = NULL;
	}
}

int  env_len(char **env)
{
	int  i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

void  init_env(char **env, t_struct *p)
{
	int i;

	i = 0;
	p->arr_env = (char **)malloc(sizeof (char *) * (env_len(env) + 1));
	if (!(p->arr_env))
		return ;
	p->my_env = NULL;
	while (env[i])
	{
		p->arr_env[i] = ft_strdup(env[i]);
		init_env_list(p, env[i]);
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
