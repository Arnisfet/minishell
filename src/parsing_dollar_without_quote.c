/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_dollar_without_quote.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrudge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 04:24:32 by mrudge            #+#    #+#             */
/*   Updated: 2022/01/20 20:10:13 by mrudge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	end_of_quote(const char *array, int i)
{
	char	quote;

	quote = array[i++];
	while (array[i] && array[i] != quote)
		i++;
	return (i);
}

char	*trimming_dollar_without(char *array, int i, t_struct *p)
{
	char	*start;
	char	*end;
	char	*before;
	char	*middle;
	char	*copy;

	start = &array[i];
	end = start + 1;
	end = find_end_dollar(end);
	if (array[i + 1] == '\'' || array[i + 1] == '"')
	{
		before = ft_substr(array, 0, start - array);
		copy = ft_strdup(before);
		free(before);
		return (copy);
	}
	before = ft_substr(array, 0, start - array);
	middle = ft_substr(array, start - array, end - start);
	middle = trim_and_find(middle, 1, p);
	copy = ft_strdup(before);
	copy = concat_and_free(copy, middle);
	free(before);
	return (copy);
}

static char	*trimmering(char *array, char *trimmer, char *end)
{
	char	*last;

	last = ft_substr(array, end - array, ft_strlen(array));
	free(array);
	array = ft_strdup(trimmer);
	array = concat_and_free(array, last);
	return (array);
}

char	*parse_dollar_without_quote(char *array, t_struct *p)
{
	int		i;
	char	*trimmer;
	char	*end;

	i = 0;
	trimmer = NULL;
	while (array[i])
	{
		if (array[i] == '\'' || array[i] == '"')
			i = end_of_quote(array, i);
		if (array[i] == '$')
		{
			end = &array[i] + 1;
			end = find_end_dollar(end);
			trimmer = trimming_dollar_without(array, i, p);
			i = ft_strlen(trimmer);
			array = trimmering(array, trimmer, end);
			free(trimmer);
			continue ;
		}
		i++;
	}
	return (array);
}
