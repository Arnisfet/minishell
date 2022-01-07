/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrudge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 22:18:39 by mrudge            #+#    #+#             */
/*   Updated: 2021/12/18 19:29:25 by mrudge           ###   ########.fr       */
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
		if (s[i] == '\'' || s[i] == '"')
		{
			i = end_of_quote((char *) s, i);
			counter++;
		}
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
			counter++;
		if (s[i] == '\'' || s[i] == '"')
			i = end_of_quote((char *) s, i);
		while ((s[i] != '\0') && (s[i] != c || s[i] == '\'' || s[i] == '"'))
			i++;
	}
	return (counter);
}

static char	*ft_copy(const char *str, size_t n)
{
	char	*new;
	size_t	i;

	new = (char *)malloc(sizeof(char) * (n + 1));
	if (new == NULL)
		return (NULL);
	i = 0;
	while ((str[i] != '\0') && (i < n))
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	return (new);
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
		if (s[i] == '\'' || s[i] == '"')
			i = end_of_quote((char *) s, i);
		while ((s[i] != '\0') && (s[i] != c))
			i++;
		if (place < i)
			new[word++] = ft_copy(s + place, i - place);
	}
	new[word] = NULL;
	return (new);
}
