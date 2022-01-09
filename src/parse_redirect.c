/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrudge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 18:13:15 by mrudge            #+#    #+#             */
/*   Updated: 2022/01/09 17:15:46 by mrudge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*ft_strtrim_quote(char *arr, char *start, char *end)
{
	int		num;
	char	*new_arr;
	int		i;
	char	*point;
	int		len;
	int		j;

	j = 0;
	num = end - start;
	point = arr;
	i = 0;
	if (!arr)
		return (NULL);
	len = ft_strlen(arr) - num;
	new_arr = (char *)malloc(sizeof (char) * len + 1);
	while (arr[j] != '\0')
	{
		if (point == start)
		{
			j += num;
			point++;
		}
		else
		{
			new_arr[i] = arr[j];
			i++;
			j++;
			point++;
		}
	}
	new_arr[i] = '\0';
	free(arr);
	return (new_arr);
}

int	substring(char *start, t_struct *p)
{
	char	*redirect;
	char	*file;
	char	*end;

	end = start;
	p->point_r = start;
	while (*end != '\0' && (*end != ' ' && (*end == '<' || *end == '>')))
		end++;
	redirect = ft_strndup(start, end - start);
	if (*end != '\0' && *(end + 1) == ' ')
		end++;
	start = end;
	while (*end != ' ' && *end != '>' && *end != '<' && *end != '\0')
		end++;
	p->point_f = end;
	file = ft_strndup(start, end - start);
	file = parse_dollar_without_quote(file, p);
	file = parse_revert(file, 0, p);
	if (correct_check(redirect, p))
	{
		free(redirect);
		free(file);
		return (2);
	}
	add_to_list_redirect(p, redirect, file, p->count);
	return (0);
}

char	*first_rparse(char *commands, t_struct *p)
{
	char	*start;
	int		i;

	i = 0;
	while (commands[i])
	{
		if (commands[i] == '>' || commands[i] == '<')
		{
			start = &commands[i];
			if (substring(start, p))
				return (NULL);
			commands = ft_strtrim_quote(commands, p->point_r, p->point_f);
			continue ;
		}
		i++;
	}
	return (commands);
}


char	**parse_redirect(char **commands, t_struct *p)
{
	int	i;

	p->count = 0;
	i = 0;
	while (commands[i])
	{
		commands[i] = first_rparse(commands[i], p);
		i++;
		p->count++;
	}
	return (commands);
}