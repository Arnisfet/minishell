/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_revert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrudge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 17:54:00 by mrudge            #+#    #+#             */
/*   Updated: 2022/01/04 23:42:50 by mrudge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
	first = ft_strjoin(first, middle);
	first = ft_strjoin(first, last);
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
	first = ft_strjoin(first, middle);
	first = ft_strjoin(first, last);
	return(first);
}

char	*rev_2(char *now, char *array, int start, t_struct *p)
{
	if (array[start] == '\'')
		now = parse_ones_revert(now, p);
	if (array[start] == '"')
		now = parse_d_revert(now, p);
	return (now);
}

char *parse_revert(char *array, int i, t_struct *p)
{
	int 	start;
	int 	end;
	char	*before;
	char	*now;
	char	*trimmer;
	char	*last;

	trimmer = NULL;
	while (array[i])
	{
		if (array[i] == '\'' || array[i] == '"')
		{
			start = i;
			end = last_revert(array + start + 1 , array[i]) - array;
			before = ft_substr(array, 0, start - 0);
			now = ft_substr(array, start, end - start + 1);
			now = rev_2(now, array, start, p);
			if (!trimmer)
				trimmer = ft_strdup(before);
			trimmer = ft_strjoin(trimmer, now);
			i = ft_strlen(trimmer);
			last = ft_substr(array, end + 1, ft_strlen(array));
			free (array);
			array = ft_strdup(trimmer);
			array = ft_strjoin(array, last);
			free(last);
			free(now);
			continue ;
		}
		i++;
	}
	free (trimmer);
	return (array);
}