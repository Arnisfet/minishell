/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmacmill <jmacmill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 22:18:39 by mrudge            #+#    #+#             */
/*   Updated: 2022/01/23 19:43:02 by jmacmill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	ft_count(const char *s, char c)
{
	size_t	i;
	int		counter;

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

static char	*ft_copy(const char *str, size_t n)
{
	char	*new;
	size_t	i;

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

int	count_counter(char const *s, char c, int i)
{
	while (s[i] != '\0' && s[i] != c)
	{
		if (s[i] == '\'' || s[i] == '"')
			i = end_of_quote(s, i);
		i++;
	}
	return (i);
}

char	**ft_split_quotes(char const *s, char c)
{
	char	**new;
	size_t	i;
	size_t	place;
	int		word;

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
		i = count_counter(s, c, i);
		if (place < i)
			new[word++] = ft_copy(s + place, i - place);
	}
	new[word] = NULL;
	return (new);
}
