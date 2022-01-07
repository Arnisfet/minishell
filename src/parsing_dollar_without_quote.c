/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_dollar_without_quote.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrudge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 04:24:32 by mrudge            #+#    #+#             */
/*   Updated: 2022/01/07 04:24:32 by mrudge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int		end_of_quote(char *array, int i)
{
	char	quote;

	quote = array[i++];
	while (array[i] && array[i] != quote)
		i++;
	return (i++);
}

char	*trimming_dollar_without(char *array, int i, char *trimmer, t_struct *p)
{
	char	*start;
	char	*end;
	char	*before;
	char	*middle;
	char	*copy;

	start = &array[i];
	end = start + 1;
	end = find_end_dollar(end);
	before = ft_substr(array, 0, start - array);
	middle = ft_substr(array, start - array, end - start);
	middle = trim_and_find(middle, 0, p);
	copy = ft_strdup(before);
	copy = ft_strjoin(copy, middle);
	free(before);
	free(middle);
	return (copy);
}

char	*parse_dollar_without_quote(char *array, t_struct *p)
{
	int		i;
	char	*trimmer;
	char	*start;
	char	*end;
	char	*last;

	i = 0;
	trimmer = NULL;
	while (array[i])
	{
		if (array[i] == '\'' || array[i] == '"')
			i = end_of_quote(array, i);
		if (array[i] == '$')
		{
			start = &array[i];
			end = start + 1;
			end = find_end_dollar(end);
			trimmer = trimming_dollar_without(array, i, trimmer, p);
			i = ft_strlen(trimmer);
			last = ft_substr(array, end - array, ft_strlen(array));
			free(array);
			array = ft_strdup(trimmer);
			array = ft_strjoin(array, last);
			free(trimmer);
			free(last);
			continue ;
		}
		i++;
	}
	return (array);
}