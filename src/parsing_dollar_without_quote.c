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
	while ((*end && *end >= 65 && *end <= 90) || *end == '_')
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