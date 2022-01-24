/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmacmill <jmacmill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 19:34:26 by jmacmill          #+#    #+#             */
/*   Updated: 2022/01/24 19:38:59 by jmacmill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*ft_chartrim(char *s1, char set)
{
	char	*str;
	int		start;
	int		end;
	int		i;

	end = ft_strlen(s1);
	start = 0;
	i = 0;
	while (s1[start] && s1[start] == set)
		start++;
	while (end > start && s1[end - 1] == set)
		end--;
	str = (char *)malloc(sizeof(char) * ((end - start) + 1));
	if (!str)
		return (NULL);
	while (start < end)
	{
		str[i] = s1[start];
		i++;
		start++;
	}
	str[i] = '\0';
	return (str);
}

void	remove_spaces_in_line(char **str)
{
	char	*save;

	save = *str;
	*str = ft_chartrim(save, ' ');
	free(save);
}
