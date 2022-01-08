/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_revert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrudge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 17:54:00 by mrudge            #+#    #+#             */
/*   Updated: 2022/01/08 17:36:21 by mrudge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*concat_and_free(char *first, char *second)
{
	char *result;

	result = ft_strjoin(first, second);
	free(first);
	free(second);
	return (result);
}

char	*parse_d_revert(char *array, t_struct *p)
{
	char	*middle;
	char	*start;
	char	*end;
	char	*first;
	char	*last;

	start = ft_strchr(array, '"');
	end = ft_strchr(start + 1, '"');
	first = ft_substr(array, 0, start - array);
	middle = ft_substr(array, start - array + 1, end - start - 1);
	if (ft_strchr(middle, '$'))
		middle = parse_dollar_with_quote(middle, p);
	last = ft_substr(array, end - array + 1, ft_strlen(array));
	first = concat_and_free(first, middle);
	first = concat_and_free(first, last);
	return (first);
}

char	*parse_ones_revert(char *array, t_struct *p)
{
	char	*middle;
	char	*start;
	char	*end;
	char	*first;
	char	*last;

	start = ft_strchr(array, '\'');
	end = ft_strchr(start + 1, '\'');
	first = ft_substr(array, 0, start - array);
	middle = ft_substr(array, start - array + 1, end - start - 1);
	last = ft_substr(array, end - array + 1, ft_strlen(array));
	first = concat_and_free(first, middle);
	first = concat_and_free(first, last);
	return(first);
}

char	*rev_2(char *now, char *array, int start, t_struct *p)
{
	char	*new;

	if (array[start] == '\'')
		new = parse_ones_revert(now, p);
	if (array[start] == '"')
		new = parse_d_revert(now, p);
	free (now);
	return (new);
}

char *parse_revert(char *array, int i, t_struct *p)
{
	int 	start;
	int 	end;
	char	*before;
	char	*now;
	char	*trimmer;
	char	*last;

	while (array[i])
	{
		if (array[i] == '\'' || array[i] == '"')
		{
			trimmer = NULL;
			start = i;
			end = ft_strchr(array + start + 1 , array[i]) - array;
			before = ft_substr(array, 0, start - 0);
			now = ft_substr(array, start, end - start + 1);
			now = rev_2(now, array, start, p);
			if (!trimmer)
				trimmer = ft_strdup(before);
			trimmer = concat_and_free(trimmer, now);
			i = ft_strlen(trimmer);
			last = ft_substr(array, end + 1, ft_strlen(array));
			free (array);
			array = ft_strdup(trimmer);
			array = concat_and_free(array, last);
			free (trimmer);
			continue ;
		}
		i++;
	}
	return (array);
}