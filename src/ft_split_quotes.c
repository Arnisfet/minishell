/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_revert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrudge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 17:54:00 by mrudge            #+#    #+#             */
/*   Updated: 2022/01/08 17:07:06 by mrudge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int    ft_count(const char *s, char c)
{
	size_t    i;
	int        counter;

	i = 0;
	counter = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
			counter++;
		while (s[i] != '\0' && s[i] != c)
		{
			if (s[i] == '"' || s[i] == '\'')
				i = end_of_quote(s, i);
			i++;
		}
	}
	return (counter);
}

static char    *ft_copy(const char *str, size_t n)
{
	char    *new;
	size_t    i;

	i = 0;
	new = (char *)malloc(sizeof(char) * (n + 1));
	if (new == NULL)
		return (NULL);
	while ((str[i] != '\0') && (i < n))
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

char    **ft_split_quotes(char const *s, char c)
{
	char    **new;
	size_t    i;
	size_t    place;
	int        word;

	if (s == NULL)
		return (NULL);
	new = (char **)malloc(sizeof(char *) * (ft_count(s, c) + 1));
	if (new == NULL)
		return (NULL);
	i = 0;
	word = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		place = i;
		while (s[i] != '\0' && s[i] != c)
		{
			if (s[i] == '\'' || s[i] == '"')
				i = end_of_quote(s, i);
			i++;
		}
		if (place < i)
			new[word++] = ft_copy(s + place, i - place);
	}
	new[word] = NULL;
	return (new);
}