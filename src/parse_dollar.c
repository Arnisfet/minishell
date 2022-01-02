/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrudge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 18:17:26 by mrudge            #+#    #+#             */
/*   Updated: 2022/01/04 19:37:55 by mrudge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	trim_env(t_struct *p)
{
	int		i;
	char	*trimmer;
	char	*start;

	i = 0;
	p->trim_env = (char **)malloc(sizeof (char*) * env_len(p->arr_env) + 1);
	if (!p->trim_env)
		return ((void) NULL);
	while (p->arr_env[i])
	{
		start = ft_strchr(p->arr_env[i], '=');
		trimmer = ft_substr(p->arr_env[i], start - p->arr_env[i] + 1, ft_strlen
		(p->arr_env[i]));
		p->trim_env[i] = ft_strdup(trimmer);
		i++;
	}
}

char	*trim_and_find(char *array, int i, t_struct *p)
{
	int		j;
	char	*env;
	char	*trimmer;
	char	*end;

	if (!p->trim_env)
		trim_env(p);
	j = 0;
	if (i == 0)
	{
		while (p->trim_env[j])
		{
			end = ft_strchr(p->arr_env[j], '=');
			trimmer = ft_substr(p->arr_env[j], 0, end - p->arr_env[j]);
			if ((ft_strcmp(array, trimmer)) == 0)
				return (p->trim_env[j]);
			j++;
		}
	}
	return (ft_strdup(""));
}

char	*parse_dollar_without_quote(char *array, t_struct *p)
{
	char	*middle;
	char	*start;
	char	*end;
	char	*first;
	char	*last;

	start = ft_strchr_quote(array, '$');
	if (start == NULL)
		return (array);
	end = start + 1;
	while (*end && (*end >= 65 && *end <= 90) || *end == '_')
	{
		if (*end == '?')
			break ;
		end++;
	}
	first = ft_substr(array, 0, start - array);
	middle = ft_substr(array, start - array + 1, end - start - 1);
	if (*end == '?')
		middle = trim_and_find(middle, 1, p);
	middle = trim_and_find(middle, 0, p);
	last = ft_substr(array, end - array, ft_strlen(array));
	first = ft_strjoin(first, middle);
	first = ft_strjoin(first, last);
	return (first);
}

char	*parse_dollar_with_quote(char *array, t_struct *p)
{
	char	*middle;
	char	*start;
	char	*end;
	char	*first;
	char	*last;

	start = ft_strchr(array, '$');
	if (start == NULL)
		return (array);
	end = start + 1;
	while (*end && (*end >= 65 && *end <= 90) || *end == '_')
	{
		if (*end == '?')
			break ;
		end++;
	}
	first = ft_substr(array, 0, start - array);
	middle = ft_substr(array, start - array + 1, end - start - 1);
	if (*end == '?')
		middle = trim_and_find(middle, 1, p);
	middle = trim_and_find(middle, 0, p);
	last = ft_substr(array, end - array, ft_strlen(array));
	first = ft_strjoin(first, middle);
	first = ft_strjoin(first, last);
	return (first);
}