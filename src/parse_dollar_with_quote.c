/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrudge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 18:17:26 by mrudge            #+#    #+#             */
/*   Updated: 2022/01/12 19:50:19 by mrudge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_ones(char *array, int flag)
{
	if (flag == 1 && array[1] == '\0')
		return (1);
	if (array[1] == '\'' || array[1] == '"' || array[1] == '\0'
		|| array[1] == ' ')
		return (1);
	return (0);
}

char	*find_end_dollar(char *end)
{
	if (*end == '?')
	{
		end++;
		return (end);
	}
	while (*end && (ft_isdigit(*end) || ft_isalpha(*end)))
		end++;
	return (end);
}

char	*trimming_dollar(char *array, int i, t_struct *p)
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
	copy = concat_and_free(copy, middle);
	free(before);
	return (copy);
}

static char	*trimming(char *array, t_struct *p, int i)
{
	char	*trimmer;
	char	*start;
	char	*end;

	trimmer = NULL;
	start = &array[i];
	end = start + 1;
	end = find_end_dollar(end);
	trimmer = trimming_dollar(array, i, p);
	return (trimmer);
}

char	*parse_dollar_with_quote(char *array, t_struct *p)
{
	int		i;
	char	*trimmer;
	char	*last;
	char	*end;

	i = 0;
	trimmer = NULL;
	while (array[i])
	{
		if (array[i] == '$')
		{
			end = &array[i] + 1;
			end = find_end_dollar(end);
			trimmer = trimming(array, p, i);
			i = ft_strlen(trimmer);
			last = ft_substr(array, end - array, ft_strlen(array));
			free(array);
			array = ft_strdup(trimmer);
			array = concat_and_free(array, last);
			free(trimmer);
			continue ;
		}
		i++;
	}
	return (array);
}
