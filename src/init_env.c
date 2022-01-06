/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmacmill <jmacmill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 17:49:43 by mrudge            #+#    #+#             */
/*   Updated: 2022/01/06 20:35:12 by mrudge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	clean_split_tmp(char **clean)
{
	if(clean[0])
		free(clean[0]);
	if(clean[1])
		free(clean[1]);
	free(clean);
}

void	init_env_list(t_struct *p, char *content)
{
	t_env	*tmp;
	char	**str;

	tmp = p->my_env;
	if (p->my_env == NULL)
	{
		p->my_env = (t_env *)malloc(sizeof(t_env));
		str = ft_split(content, '=');
		p->my_env->var = ft_strdup(str[0]);
		p->my_env->value = ft_strdup(str[1]);
		p->my_env->is_blank = 0;
		clean_split_tmp(str);
		p->my_env->next = NULL;
	}
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = (t_env *)malloc(sizeof(t_env));
		str = ft_split(content, '=');
		tmp->next->var = ft_strdup(str[0]);
		tmp->next->value = ft_strdup(str[1]);
		tmp->next->is_blank = 0;
		clean_split_tmp(str);
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
	p->arr_env[i] = NULL;
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
