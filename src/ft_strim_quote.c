/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strim_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrudge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 20:06:04 by mrudge            #+#    #+#             */
/*   Updated: 2022/01/20 20:06:34 by mrudge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/minishell.h"

static void	*trim(char *new_arr, char *arr, char *start, char *end)
{
	int		i;
	int		j;
	char	*point;

	i = 0;
	j = 0;
	point = arr;
	while (arr[j] != '\0')
	{
		if (point == start)
		{
			j += (end - start);
			point++;
		}
		else
		{
			new_arr[i] = arr[j];
			i++;
			j++;
			point++;
		}
		new_arr[i] = '\0';
	}
}

char	*ft_strtrim_quote(char *arr, char *start, char *end)
{
	char	*new_arr;
	int		i;
	char	*point;
	int		j;

	j = 0;
	point = arr;
	i = 0;
	if (!arr)
		return (NULL);
	new_arr = (char *)malloc(sizeof (char) * (ft_strlen(arr) - (end - start))
			+ 1);
	trim(new_arr, arr, start, end);
	free(arr);
	return (new_arr);
}
